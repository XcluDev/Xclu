#include "xmodulebcineuroplay.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "project_props.h"
#include <Processing.NDI.Lib.h>

REGISTER_XMODULE(BciNeuroplay)

//---------------------------------------------------------------------
XModuleBciNeuroplay::XModuleBciNeuroplay(QString class_name)
    :XModuleWidget(class_name)
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
    sets_device_info("Disconnected");

    num_requests_ = 0;
    num_received_ = 0;

}



//---------------------------------------------------------------------
void XModuleBciNeuroplay::on_deviceConnected(NeuroplayDevice *device) {

    //TODO note, this call can be from another signal

    clear_string_device_info();
    append_string_device_info("Connected: " + device->name());
//    item->setData(1, 42, QVariant::fromValue<NeuroplayDevice*>(device));
    append_string_device_info("id: " + QString::number(device->id()));
    append_string_device_info("model: " + device->model());
    append_string_device_info("serialNumber: " + device->serialNumber());
    append_string_device_info("maxChannels: " + QString::number(device->maxChannels()));
    append_string_device_info("preferredChannelCount: " + QString::number(device->preferredChannelCount()));

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

        connect(device, &NeuroplayDevice::filteredDataReceived, [=](NeuroplayDevice::ChannelsData data)
        {
            qDebug() << "Filtered data:" << data.size() << "x" << (data.size()? data[0].size(): 0);
            chart->setData(data, 200);
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
void XModuleBciNeuroplay::set_rhythms(const NeuroplayDevice::ChannelsRhythms &rhythms)
{
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
        if (geti_values_enabled()) {
            inc_requests();
            device_->requestBCI();

            // OSC
            if (geti_values_osc_enabled()) {
                QString net_address = gets_values_osc_address();
                osc_send(net_address, gets_values_osc_meditation(), getf_value_meditation());
                osc_send(net_address, gets_values_osc_concentration(), getf_value_concentration());

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

    redraw();   //Call to update screen
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
//example of net_address: 127.0.0.1:12345
void XModuleBciNeuroplay::osc_send(QString net_address, QString osc_address, const QOscValue &value) {
    auto list = net_address.split(":");
    xc_assert(list.size() == 2, "Bad OSC address format, got `" + net_address + "`, but expected kind of 127.0.0.1:12345");

    QString addr = list.at(0);
    int port = list.at(1).toInt();
    xc_assert(!addr.isEmpty(), "Empty OSC address `" + net_address + "`");
    xc_assert(port > 0 && port < 65536, "Bad port at OSC address `" + net_address + "`");

    QOscInterface iface;
    iface.setRemoteAddr(addr); // For some reason we can't use "localhost" - TODO need name resolving?
    iface.setRemotePort(port);
    iface.send(osc_address, value);
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::draw(QPainter &painter, int outw, int outh) {

    //Antialiasing
    painter.setRenderHint(QPainter::Antialiasing);

    //Draw background
    painter.setBrush(QColor(0, 0, 0));
    painter.setPen(Qt::PenStyle::NoPen);
    painter.drawRect(0, 0, outw, outh);

  /*  //Image
    XRaster::draw(&painter, image_, QRectF(0,0,outw,outh));

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
/*    //Compute translate and scale
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
/*void XModuleBciNeuroplay::send_frame() {
    if (!ndi_inited_) {
        return;
    }

    auto source = gete_send_image_source();
    if (source == send_image_source_Image) {
        XProtectedObject *image = getobject_send_image();
        auto read = image->read();
        if (read.data().type() == XObjectTypeImage) {
            auto info = XObjectImage::get_data(read.data());
            xc_assert(info.data_type == "u8" || info.channels == 4,
                     "XModuleBciNeuroplay::send_frame - only u8, 4 channels are supported");
            auto *array = XObjectImage::get_array(read.data());
            const unsigned char *u8 = array->data_u8();
            xc_assert(u8, "XModuleBciNeuroplay::send_frame - Empty image array 'u8'");

            ndi_send_image(u8, info.w, info.h);
        }
    }
    if (source == send_image_source_Test_Image) {
        send_test_frame(sent_frames_);
    }
}
*/
//---------------------------------------------------------------------
/*void XModuleBciNeuroplay::send_test_frame(int frame) {
    if (!ndi_inited_) {
        return;
    }
    int w = 512;
    int h = 256;

    // allocate
    if (test_raster_.is_empty()) {
        test_raster_.allocate(w, h);
    }

    // fill
    auto test_raster_data = test_raster_.data_pointer();
    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            test_raster_data[x + w*y] = rgba_u8(
                        ((x + frame) * 256 / w) % 256,
                        x * 256 / w,
                        y * 256 / h,
                        255);
        }
    }

    // send
    ndi_send_image(test_raster_.data_pointer_u8(), w, h);

}


//---------------------------------------------------------------------
void XModuleBciNeuroplay::ndi_init() {
    if (!ndi_inited_) {
        auto result = NDIlib_initialize();
        xc_assert(result, "Can't initialize NDI: Library error");
        if (!result) return;

        // We create the NDI sender
        NDIlib_send_create_t params;
        params.clock_audio = false;
        params.clock_video = false;
        params.p_groups = nullptr;
        params.p_ndi_name = gets_sender_name().toStdString().c_str();

        //TODO for unknown reason setting "p_ndi_name" not have effect when running "VB NDI Receive Example.exe"
        pNDI_send_ = NDIlib_send_create(&params);

        xc_assert(pNDI_send_, "Can't initialize NDI: error creating sender");
        if (!pNDI_send_) return;

        sets_send_status("NDI started");
        ndi_inited_ = true;
    }
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::ndi_send_image(const unsigned char *data_rgba, int w, int h) {
    if (!ndi_inited_) {
        return;
    }
    xc_assert(data_rgba && w > 0 && h > 0, "XModuleBciNeuroplay::ndi_send_image - bad input raster");

    NDIlib_video_frame_v2_t NDI_video_frame;
    NDI_video_frame.xres = w;
    NDI_video_frame.yres = h;
    NDI_video_frame.FourCC = NDIlib_FourCC_type_RGBA;
    NDI_video_frame.p_data = (unsigned char *)data_rgba;

    //-----------------------
    //We disabled clocking "params.clock_video = false", so may be this not occur:
    //??? "Note that this call will be clocked so that we end up submitting at exactly 29.97fps."
    //-----------------------
    //Sending the frame.
    NDIlib_send_send_video_v2(pNDI_send_, &NDI_video_frame);

    // updating status
    sent_frames_++;
    sets_send_status(QString("Sending frame: %1").arg(sent_frames_));

}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::ndi_stop() {
    if (ndi_inited_) {
        // Destroy the NDI sender
        NDIlib_send_destroy(pNDI_send_);
        pNDI_send_ = nullptr;

        // Not required, but nice
        NDIlib_destroy();

        ndi_inited_ = false;
        sets_send_status("NDI stopped");
    }
}
*/
//---------------------------------------------------------------------


