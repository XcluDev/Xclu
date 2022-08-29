#include "xclasssynthfromimage.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"
#include "xclass.h"
#include "xobjectvis.h"

//registering module implementation
REGISTER_XCLASS(SynthFromImage)




//---------------------------------------------------------------------
//interpolation
/*float XClassSynthFromImageData::get_volume(float phase) {  //x=0..1
    if (w_ == 0) return 0;
    float x = phase * w_;
    int x0 = int(x);
    int x1 = (x0+1) % w_;
    x -= x0;
    return image_[x0]*(1-x) + image_[x1]*x;
}*/

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
XClassSynthFromImage::XClassSynthFromImage(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassSynthFromImage::~XClassSynthFromImage()
{

}

//---------------------------------------------------------------------
void XClassSynthFromImage::start() {
    data_.clear();

    //link images with internal objects
    setobject_output_image(&out_image_);
    out_image_.write().data().link<XRaster>(output_u8c3_);

    input_u8_.clear();
    output_u8c3_.clear();

    input_frozen_ = false;

}

//---------------------------------------------------------------------
void XClassSynthFromImage::update() {
    //Freeze/unfreeze buttons
    if (geti_freeze_btn()) {
        input_frozen_ = true;
    }
    if (geti_unfreeze_btn()) {
        input_frozen_ =false;
    }


    //Read image
    {
        auto read = getobject_input_image()->read();
        auto *raster = read.data().data<XRaster>();
        if (!raster || raster->is_empty()) return;
        // Read image if not frozen
        if (!input_frozen_ || input_u8_.is_empty()) {
            XRasterUtils::convert(*raster, input_u8_, XTypeId::u8);
        }
    }

    int w = input_u8_.w;
    int h = input_u8_.h;

    float ScanY = xclampf(getf_scan_y(), 0, 1);
    int scany = (h-1) * ScanY;
    int scanw = w * getf_scan_w();
    int x0 = w/2 - scanw/2;
    int x1 = x0 + scanw;    //excluded
    x0 = xclampi(x0, 0, w-1);
    x1 = xclampi(x1, x0+1, w);

    //Ignore black borders - useful for Realsense depth sonification
    if (geti_tone_black()) {
        while (input_u8_.pixel_unsafe<u8>(x0,scany) == 0 && x0<w/2) {
            x0++;
        }
        while (input_u8_.pixel_unsafe<u8>(x1,scany) == 0 && x1>w/2+1) {
            x1--;
        }
        scanw = x1 - x0;
    }

    //line speed - for tone change
    float line_speed = 1;
    float nonlinear_tone = getf_nonlinear_tone();
    if (nonlinear_tone > 0) {
        float t0 = float(scanw) / w;
        float t = t0;
        if (t>0) {
            t = pow(t, nonlinear_tone);
        }
        //xc_console_append(QString::number(t0) + " " + QString::number(t));
        line_speed = t;
    }

    //read line
    QVector<float> line(scanw);
    for (int i=0; i<scanw; i++) {
        line[i] = xmapf(input_u8_.pixel_unsafe<u8>(i+x0, scany), 0, 255, -1, 1);
    }

    //Normalize
    if (geti_normalize()) {
        float minv = line[0];
        float maxv = minv;
        for (int i=0; i<scanw; i++) {
            minv = qMin(line[i], minv);
            maxv = qMax(line[i], maxv);
        }
        if (minv != maxv) {
            for (int i=0; i<scanw; i++) {
                line[i] = xmapf(line[i],minv,maxv,-1,1);
            }
        }
    }

    //distort
    float distort = getf_distort();
    for (int i=0; i<line.size(); i++) {
        line[i] = xclampf(line[i]*distort, -1, 1);
    }

    //duplicate line if loop ping-pong; exclude the beginning and final pixel
    //Note: line will be longer than we draw it
    if (gete_loop_mode() == loop_mode_Ping_Pong && scanw >= 3) {
        int n = scanw*2-2;
        line.resize(n);
        for (int i=1; i<n-1; i++) {
            line[n-i] = line[i];
        }
    }


    //set values to data_ for sound generation
    //we do it by locking access, and trying to minimize lock,
    //that's why we prepare all and set it here at a once.
    {
        auto write = data_.write();
        auto &data = write.data();
        data.sample_rate = geti_sample_rate();
        data.volume = getf_volume();
        data.line_ = line;
        data.line_speed_ = line_speed;
    }

    //generate output
    XRasterUtils::convert(input_u8_, output_u8c3_, XTypeId::rgb_u8);

    //draw scan line and sound graph
    float deltay = h*0.2;
    for (int x=x0; x<x1; x++) {
        //output_u8c3_.pixel_unsafe(x, scany) = rgb_u8(255,0,0);
        int y0 = scany;
        int y1 = y0 - deltay*line[x-x0];
        if (y0 > y1) qSwap(y0, y1);
        y0 = xclampi(y0, 0, h-1);
        y1 = xclampi(y1, 0, h-1);
        for (int y=y0; y<=y1; y++) {
            output_u8c3_.pixel_unsafe<rgb_u8>(x, y) = rgb_u8(255,0,0);
        }
        output_u8c3_.pixel_unsafe<rgb_u8>(x, scany) = rgb_u8(255,0,0);
    }


    // Дать сигнал в GUI что было изменение объекта
    out_image_.was_updated();
}

//---------------------------------------------------------------------
void XClassSynthFromImage::stop() {

}

//---------------------------------------------------------------------
//sound generation
//"sound_buffer_add" call, fills `data` buffer
//there are required to fill channels * samples values at data
void XClassSynthFromImage::on_sound_buffer_add(int sample_rate, int channels, int samples, float *data) {
    auto read = data_.read();
    auto &dat = read.data();

    float phase_add = float(dat.sample_rate) / float(sample_rate) / dat.line_speed_;
    //double phase_ = 0;
    //QVector<float> line_;


    //finish current line and then start a new line
    bool switched = false;
    int n = line_.size();

    //if empty - then copy immediately
    if (n == 0) {
        line_ = dat.line_;
        n = line_.size();
        switched = true;
    }

    int sample_index = 0;
    for (int k=0; k<samples; k++) {
        if (phase_ >= n) {
            phase_ = fmodf(phase_, n);
            if (!switched) {    //switch to a new line
                switched = true;
                line_ = dat.line_;
                n = line_.size();
            }
        }

        //read value
        int i = xclampi(int(phase_), 0, n-1);
        float v = line_[i] * dat.volume; //qSin(data_.phase_);

        phase_ += phase_add;

        for (int u=0; u<channels; u++) {
            data[sample_index++] += v;
        }
    }

}

//---------------------------------------------------------------------
