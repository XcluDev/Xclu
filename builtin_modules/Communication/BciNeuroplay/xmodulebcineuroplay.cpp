#include "xmodulebcineuroplay.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "project_props.h"
#include "xosc.h"

REGISTER_XMODULE(BciNeuroplay)

//---------------------------------------------------------------------
XModuleBciNeuroplay::XModuleBciNeuroplay(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleBciNeuroplay::~XModuleBciNeuroplay()
{
    rec_stop();
    disconnect_();
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::on_loaded() {
    //sets_send_status("Not started");
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::on_button_pressed(QString button_id) {
    //if (button_id == "print_devices") {

    //}

}


//---------------------------------------------------------------------
void XModuleBciNeuroplay::start() {
    exception_.clear();
    if (geti_autoconnect()) {
        connect_();
    }

    rec_clear();

    seti_values_osc_sent(0);

    graphs_.clear();
    graphs_lines_.clear();

    rhythms_buffer_.clear();

    info_.clear();

    // If Blink detection is enabled, it's required to have graphs enabled too.
    xc_assert(!(!geti_graphs_enabled() && geti_blink_detection()), "Please enable Connect > Graphs to detect blinks.");
    blink_channels_.clear();
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::connect_() {
    neuroplay_.reset(new NeuroplayPro());

    connect(neuroplay_.data(), &NeuroplayPro::deviceConnected, [=](NeuroplayDevice *device)
    {
        on_deviceConnected(device);
    });

    num_requests_ = 0;
    num_received_ = 0;

    neuroplay_->open();

}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::disconnect_() {
    if (device_) {
        device_->disableGrabMode();
    }
    device_ = 0;    // device_ will be deleted by neuroplay_

    if (neuroplay_.data()) {
        neuroplay_->close();
        neuroplay_.reset();
    }

    seti_connected(0);
    append_string_device_info("Disconnected");

    num_requests_ = 0;
    num_received_ = 0;
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::on_deviceConnected(NeuroplayDevice *device) {

    //TODO note, this call can be from another signal

    info_ = device->info();

    clear_string_device_info();

    append_string_device_info("Connected: " + info_.name);
//    item->setData(1, 42, QVariant::fromValue<NeuroplayDevice*>(device));
    append_string_device_info("id: " + QString::number(info_.id));
    append_string_device_info("model: " + info_.model);
    append_string_device_info("serialNumber: " + info_.serial_number);
    append_string_device_info("channels " + QString::number(info_.channels_count) + ": " + info_.channels_names.join(" "));
    append_string_device_info("frequency: " + QString::number(info_.frequency));

    device_ = device;
    /*
   //TODO Channel Modes
    QTreeWidgetItem *modesItem = new QTreeWidgetItem(item, {"channelModes"});
    QStringList modes = device->channelModes();
    for (int i=0; i<modes.size(); i++)
    {
        QString mode = modes[i];
        QTreeWidgetItem *modeItem = new QTreeWidgetItem(modesItem, {mode, "<click here to start>"});
        modeItem->setData(1, 42, QVariant::fromValue<NeuroplayDevice*>(device));
        modeItem->setData(1, 43, device->channelModesValues()[i].first);
    }*/

    connect(device, &NeuroplayDevice::ready, [=]()
    {
        seti_connected(1);

        // Responses to signals from BCI device
        connect(device, &NeuroplayDevice::error, [=](QString message)
        {
            // We can't throw exception right here, because this halts whole app,
            // so we store it and show in main thread.
            //xc_exception(name() + " " + message);
            if (exception_.isEmpty()) {
                exception_ = message;
            }
        });

        connect(device_, &NeuroplayDevice::bciReady, [=]()
        {
            float meditation = device_->meditation() / 100.0f;
            float concentration = device_->concentration() / 100.0f;

            setf_value_meditation(meditation);
            setf_value_concentration(concentration);
            inc_received();
        });

        connect(device_, &NeuroplayDevice::rhythmsReady, [=]()
        {
            set_rhythms(device_->rhythms());
            //setf_rhythm_alpha( / 100.0f);
            inc_received();
        });

        connect(device, &NeuroplayDevice::filteredDataReceived, [=](NeuroplayDevice::ChannelsData data)
        {
            //qDebug() << "Filtered data:" << data.size() << "x" << (data.size()? data[0].size(): 0);
            //chart->setData(data, 200);
            set_graphs(data);
        });

        /*

        //---------------------
        connect(device, &NeuroplayDevice::spectrumReady, [=]()
        {
            //Spectrum is updated each 0.1 seconds
            NeuroplayDevice::ChannelsData spectrum = device->spectrum();
            chart->setData(spectrum, -20);
            qDebug() << "Spectrum: " << spectrum.size() << "x" << (spectrum.size()? spectrum[0].size(): 0);
            //qDebug() << spectrum;
        });



        connect(device, &NeuroplayDevice::rawDataReceived, [=](NeuroplayDevice::ChannelsData data)
        {
            qDebug() << "Raw data:" << data.size() << "x" << (data.size()? data[0].size(): 0);
            chart->setData(data, 100000);
        });

        */
    });

}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::set_graphs(const NeuroplayDevice::ChannelsData &data)
{
    graphs_.clear();
    graphs_lines_.clear();
    if (data.empty()) {
        return;
    }
    for (QVector<double> chdata: data)
    {
        int n = chdata.size();
        QVector<float> graph(n);
        QVector<QPointF> line(n);
        for (int i=0; i<chdata.size(); i++) {
            float v = chdata[i] * 0.01f;
            graph[i] = v;
            line[i] = QPointF(i, v*100.0f);
        }
        graphs_ << graph;
        graphs_lines_ << line;
    }
    update_blink();
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::update_blink() {
    bool detected = false;
    if (!graphs_.empty()) {
        setup_blink_channels();
        int frames = getf_blink_time_measure() * device_->info().frequency;
        int n = graphs_[0].size();
        frames = qMin(frames, n);

        float threshold = getf_blink_thresh();

        float value = 0;
        for (auto ch: blink_channels_) {
            auto &graph = graphs_[ch];
            for (int i=0; i<frames; i++) {
                value = qMax(fabs(graph[n-1-i]), value);
            }
        }
        detected = (value >= threshold);
        setf_blink_value(value);
    }
    seti_blink_detected(detected);
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::setup_blink_channels() {
    if (!blink_channels_.empty())
        return;
    auto list = gets_blink_channels().split(" ");
    xc_assert(!list.empty(), "List of Channels for detecting blinks must be not empty.");
    for (auto name: list) {
        int i = device_->info().find_channel_by_name(name);
        xc_assert(i != -1, "Can't found channel '" + name +"', Neuroplay has channels '" + device_->info().channels_names.join(" ") + "'");
        blink_channels_.append(i);
    }
}

//---------------------------------------------------------------------
// Buffering rhythms values for blink detection
void XModuleBciNeuroplay::set_rhythms(const NeuroplayDevice::ChannelsRhythms &rhythms)
{
    // Buffering for remove eyes blinking
    float time = xc_elapsed_time_sec();
    if (!geti_blink_detection()) {
        process_rhythms(rhythms);
    }
    else {
        // Store this values
        rhythms_buffer_.push(rhythms, time);
        // Clear blink
        float time_from = time - getf_blink_time_before();
        if (geti_blink_detected()) {
            float time_to = time + getf_blink_time_after();
            rhythms_buffer_.clear_range(time_from, time_to);
        }
        // Process values before not inside blink
        while (rhythms_buffer_.has_earlier(time_from)) {
            auto data = rhythms_buffer_.pop();
            process_rhythms(data);
        }
    }
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::process_rhythms(const NeuroplayDevice::ChannelsRhythms &rhythms) {
    // Read buffer
    int channels = rhythms.size();
    int N = NeuroplayDevice::RhythmN;

    // Fill lines
    QVector<QString> Lines(N);
    for (int c=0; c<channels; c++) {
        for (int i=0; i<N; i++) {
            if (c > 0) {
                Lines[i].append(" ");
            }
            Lines[i].append(QString::number(rhythms[c].data[i] * 0.01));
        }
    }
    sets_rhythms_delta(Lines[NeuroplayDevice::RhythmDelta]);
    sets_rhythms_theta(Lines[NeuroplayDevice::RhythmTheta]);
    sets_rhythms_alpha(Lines[NeuroplayDevice::RhythmAlpha]);
    sets_rhythms_beta(Lines[NeuroplayDevice::RhythmBeta]);
    sets_rhythms_gamma(Lines[NeuroplayDevice::RhythmGamma]);

    // Average
    auto indices = gets_rhythms_avg_channels().split(" ");
    NeuroplayDevice::Rhythms R;
    R.data.resize(N);
    int count = 0;
    for (auto &s: indices) {
        int c = s.toInt();
        if (c >= 0 && c < N) {
            for (int i=0; i<N; i++) {
                R.data[i] += rhythms[c].data[i] * 0.01;
            }
            count++;
        }
    }
    if (count > 0) {
        for (int i=0; i<N; i++) {
            R.data[i] /= count;
        }
    }
    setf_rhythm_avg_delta(R.data[NeuroplayDevice::RhythmDelta]);
    setf_rhythm_avg_theta(R.data[NeuroplayDevice::RhythmTheta]);
    setf_rhythm_avg_alpha(R.data[NeuroplayDevice::RhythmAlpha]);
    setf_rhythm_avg_beta(R.data[NeuroplayDevice::RhythmBeta]);
    setf_rhythm_avg_gamma(R.data[NeuroplayDevice::RhythmGamma]);
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::update() {
    // Buttons
    if (geti_btn_connect()) {
        connect_();
    }
    if (geti_btn_disconnect()) {
        disconnect_();
    }
    if (geti_btn_recording_start()) {
        rec_start();
    }
    if (geti_btn_recording_stop()) {
        rec_stop();
    }

    // Data requests
    if (geti_connected()) {
        if (geti_graphs_enabled()) {
            inc_requests();
            device_->requestFilteredData();
        }

        if (geti_values_enabled()) {
            inc_requests();
            device_->requestBCI();

            // OSC
            if (geti_values_osc_enabled()) {
                auto net_address = XNetworkAddr(gets_values_osc_address());
                XOsc::send(net_address, gets_values_osc_meditation(), getf_value_meditation());
                XOsc::send(net_address, gets_values_osc_concentration(), getf_value_concentration());

                increase_int_values_osc_sent();
            }

        }
        if (geti_rhythms_enabled()) {
            inc_requests();
            device_->requestRhythms();
        }
        if (geti_spectrum_enabled()) {
            inc_requests();
            device_->requestSpectrum();
        }

        if (geti_graphs_enabled()) {
            inc_requests();
            device_->requestFilteredData();
            //device->requestRawData();
        }
    }

    // Connection status
    update_stat();

    // Record
    rec_update();

    if (!exception_.isEmpty()) {    // Process exception from BCI device
        xc_exception(name() + " " + exception_);
        exception_.clear();
    }
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::inc_requests() {
    num_requests_++;
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::inc_received() {
    num_received_++;
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::reset_stat() {
    num_requests_ = 0;
    num_received_ = 0;
    update_stat();
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::update_stat() {
    QString s = QString("req.: %1, received: %2, lost: %3").arg(num_requests_).arg(num_received_).arg(num_requests_-num_received_);
    sets_stat(s);
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::stop() {
    rec_stop();
    disconnect_();
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::rec_clear() {
    recording_ = false;
    rec_update_status("");
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::rec_start() {
    if (!recording_) {
        xc_assert(geti_connected(), "Not connected, please check Neuroplay app is running");
        recording_ = true;
        rec_time_start_ = xc_elapsed_time_sec();

        rec_data_.clear();

        QString folder = xc_absolute_path_from_project(gets_recording_folder());
        xc_assert(!gets_recording_folder().isEmpty() && xc_folder_exists(folder),
                  "Bad folder for records: `" + folder + "`");

        QString time_format = "yyMMdd_hhmmsszzz";
        auto time = QDateTime::currentDateTime();
        rec_file_ = folder + "/" + time.toString(time_format) + ".txt";

        rec_update_status("Started");
    }
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::rec_stop() {
    if (recording_) {
        recording_ = false;
        if (rec_data_.size() > 0) {
            xc_write_text_file(rec_data_, rec_file_);
        }

        rec_update_status(QString("Saved %1 sec").
                          arg(int(xc_elapsed_time_sec() - rec_time_start_)));
    }
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::rec_update() {
    if (recording_) {
        auto source = gete_recording_source();
        if (source == recording_source_Rhythms_Avg) {
            if (was_changed_rhythm_avg_beta()) {
                rec_data({getf_rhythm_avg_delta(),
                          getf_rhythm_avg_theta(),
                          getf_rhythm_avg_alpha(),
                          getf_rhythm_avg_beta(),
                          getf_rhythm_avg_gamma()});
            }
        }
        if (source == recording_source_Rhytms_All_Channels) {
            if (was_changed_rhythms_alpha()) {
                QVector<float> V;
                for (int i=0; i<5; i++) {
                    QString s;
                    if (i == 0) s = gets_rhythms_delta();
                    if (i == 1) s = gets_rhythms_theta();
                    if (i == 2) s = gets_rhythms_alpha();
                    if (i == 3) s = gets_rhythms_beta();
                    if (i == 4) s = gets_rhythms_gamma();
                    auto list = s.split(" ");
                    for (auto v: list) {
                        V.append(v.toFloat());
                    }
                }
                rec_data(V);
            }
        }

    }
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::rec_update_status(QString status) {
    clear_string_recording_status();
    append_string_recording_status(status);
    append_string_recording_status(QString("Frames: %1").arg(rec_data_.size()));
    append_string_recording_status(QString("File: %1").arg(rec_file_));
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::rec_data(QVector<float> values) {
    rec_update_status(QString("Recording %1 sec").
                      arg(int(xc_elapsed_time_sec() - rec_time_start_)));
    QString s;
    for (int i=0; i<values.size(); i++) {
        if (i > 0) s.append("\t");
        s.append(QString::number(values[i]));
    }
    rec_data_.append(s);
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::draw(QPainter &painter, int outw, int outh) {

    //Antialiasing
    painter.setRenderHint(QPainter::Antialiasing);

    //Draw background
    //painter.setBrush(QColor(0, 0, 0));
    //painter.setPen(Qt::PenStyle::NoPen);
    //painter.drawRect(0, 0, outw, outh);

    // Blue background on eye blink, else white
    QColor back_color = (geti_blink_detected()) ? QColor(200,200,255) : Qt::white;
    painter.fillRect(0, 0, outw, outh, back_color);

    if (!graphs_lines_.isEmpty())
        {
            painter.setPen(Qt::black);
            int channels = graphs_lines_.size();
            int h1 = outh / channels;
            for (int i=0; i<channels; i++)
            {
                int count = graphs_lines_[i].size();
                float y0 = (i + 0.5f) * h1;

                const float scale_y = 200;

                painter.save();
                painter.translate(0, y0);
                painter.scale(float(outw) / count, h1 / scale_y);
                painter.drawPolyline(graphs_lines_[i]);
                painter.restore();
            }
        }

  /*
    //YOLO
    for (int i=0; i<pnt_.size(); i++) {
        QPen pen(QColor(255,255,0));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.setBrush(Qt::BrushStyle::NoBrush);
        painter.drawRect((pnt_[i].x-size_[i].x/2)*outw, (pnt_[i].y-size_[i].y/2)*outh,
                         size_[i].x*outw, size_[i].y*outh);
    }

    //Cross
    bool pickup  = !queue_.isEmpty();

    QPen pen(QColor(0,255,255));
    if (pickup) pen.setColor(QColor(255,0,0));
    if (walking_) pen.setColor(QColor(0,0,255));

    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::BrushStyle::NoBrush);
    glm::vec2 cross = glm::vec2(getf_cross_x(),getf_cross_y());
    glm::vec2 size = glm::vec2(getf_cross_w(),getf_cross_h());
    painter.drawRect((cross.x-size.x/2)*outw, (cross.y-size.y/2)*outh,
                     size.x*outw, size.y*outh);
    painter.drawLine((cross.x-size.x/4)*outw, (cross.y)*outh,
                     (cross.x+size.x/4)*outw, (cross.y)*outh);
    painter.drawLine((cross.x)*outw, (cross.y-size.y/4)*outh,
                     (cross.x)*outw, (cross.y+size.y/4)*outh);

    //Target
    if (!pickup) {
        QPen pen(QColor(0,0,255));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawLine((cross.x)*outw, (cross.y)*outh,
                         (cross.x+target_.x)*outw, (cross.y+target_.y)*outh);
    }
    //Compute translate and scale
    //Note: we use scaling to have independence of lines width from screen resolution
    int spacing = geti_spacing();

    float w = 300;  //base size
    float h = 300;
    float wsp = w + spacing;

    float scrw = 3*w + 2*spacing;
    float scrh = h;

    float scl = qMin(outw/scrw, outh/scrh);
    float outw1 = scrw*scl;
    float outh1 = scrh*scl;

    int x0 = (outw-outw1)/2;
    int y0 = (outh-outh1)/2;

    painter.save();
    painter.translate(x0, y0);
    painter.scale(scl, scl);

    //------------------------
    //Actual drawing

    //Face
    face_draw(painter, w, h);

    //Vector field - attractors
    painter.save();
    painter.translate(wsp, 0);
    //painter.setPen(QColor(255,255,255));
    //painter.setBrush(Qt::BrushStyle::NoBrush);
    //painter.drawRect(0,0,w,h);
    attr_draw(painter, w, h);

    painter.restore();

    //Morph
    painter.save();
    painter.translate(2*wsp, 0);
    morph_draw(painter, w, h);
    painter.restore();

    //border
    painter.setPen(get_col(getf_border_color()));
    painter.setBrush(Qt::BrushStyle::NoBrush);
    painter.drawRect(0,0,scrw,scrh);
    painter.drawLine(w,0,w,h);
    painter.drawLine(scrw-w,0,scrw-w,h);


    //------------------------
    painter.restore();
    */
}

//---------------------------------------------------------------------


