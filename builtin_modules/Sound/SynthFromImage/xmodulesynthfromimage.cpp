#include "xmodulesynthfromimage.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xcore.h"
#include "module.h"
#include "xcluobjectimage.h"

//registering module implementation
REGISTER_XMODULE(SynthFromImage)




//---------------------------------------------------------------------
//interpolation
/*float XModuleSynthFromImageData::get_volume(float phase) {  //x=0..1
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
XModuleSynthFromImage::XModuleSynthFromImage(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleSynthFromImage::~XModuleSynthFromImage()
{

}

//---------------------------------------------------------------------
void XModuleSynthFromImage::impl_start() {
    {
        DataAccess access(data_);
        data_.line_.clear();
    }

    //link images with internal objects
    setobject_output_image(&out_image_);

    out_image_.write().data().clear();
    input_.clear();
    output_.clear();

    input_frozen_ = false;

}

//---------------------------------------------------------------------
void XModuleSynthFromImage::impl_update() {
    //Freeze/unfreeze buttons
    if (geti_freeze_btn()) {
        input_frozen_ = true;
    }
    if (geti_unfreeze_btn()) {
        input_frozen_ =false;
    }


    //Read image
    auto reader = getobject_input_image()->read();

    //no image yet
    if (reader.data().type() != XObjectTypeImage) return;

    //read image if not frozen
    if (!input_frozen_ || input_.is_empty()) {
        XObjectImage::to_raster(reader.data(), input_);
    }

    int w = input_.w;
    int h = input_.h;

    float ScanY = xclampf(getf_scan_y(), 0, 1);
    int scany = (h-1) * ScanY;
    int scanw = w * getf_scan_w();
    int x0 = w/2 - scanw/2;
    int x1 = x0 + scanw;    //excluded
    x0 = clampi(x0, 0, w-1);
    x1 = clampi(x1, x0+1, w);

    //Ignore black borders - useful for Realsense depth sonification
    if (geti_tone_black()) {
        while (input_.pixel_unsafe(x0,scany) == 0 && x0<w/2) {
            x0++;
        }
        while (input_.pixel_unsafe(x1,scany) == 0 && x1>w/2+1) {
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
        //xclu_console_append(QString::number(t0) + " " + QString::number(t));
        line_speed = t;
    }

    //read line
    QVector<float> line(scanw);
    for (int i=0; i<scanw; i++) {
        line[i] = xmapf(input_.pixel_unsafe(i+x0, scany), 0, 255, -1, 1);
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
        DataAccess access(data_);
        data_.sample_rate = geti_sample_rate();
        data_.volume = getf_volume();
        data_.line_ = line;
        data_.line_speed_ = line_speed;
    }

    //generate output
    XRaster::convert(input_, output_);

    //draw scan line and sound graph
    float deltay = h*0.2;
    for (int x=x0; x<x1; x++) {
        //output_.pixel_unsafe(x, scany) = rgb_u8(255,0,0);
        int y0 = scany;
        int y1 = y0 - deltay*line[x-x0];
        if (y0 > y1) qSwap(y0, y1);
        y0 = clampi(y0, 0, h-1);
        y1 = clampi(y1, 0, h-1);
        for (int y=y0; y<=y1; y++) {
            output_.pixel_unsafe(x, y) = rgb_u8(255,0,0);
        }
        output_.pixel_unsafe(x, scany) = rgb_u8(255,0,0);
    }


    //set to GUI
    XObjectImage::create_from_raster(out_image_.write().data(), output_);


}

//---------------------------------------------------------------------
void XModuleSynthFromImage::impl_stop() {

}


//---------------------------------------------------------------------
//sound generation
//"sound_buffer_add" call, fills `data` buffer
//there are required to fill channels * samples values at data
void XModuleSynthFromImage::impl_sound_buffer_add(int sample_rate, int channels, int samples, float *data) {
    DataAccess access(data_);

    float phase_add = float(data_.sample_rate) / float(sample_rate) / data_.line_speed_;
    //double phase_ = 0;
    //QVector<float> line_;


    //finish current line and then start a new line
    bool switched = false;
    int n = line_.size();

    //if empty - then copy immediately
    if (n == 0) {
        line_ = data_.line_;
        n = line_.size();
        switched = true;
    }

    int sample_index = 0;
    for (int k=0; k<samples; k++) {
        if (phase_ >= n) {
            phase_ = fmodf(phase_, n);
            if (!switched) {    //switch to a new line
                switched = true;
                line_ = data_.line_;
                n = line_.size();
            }
        }

        //read value
        int i = clampi(int(phase_), 0, n-1);
        float v = line_[i] * data_.volume; //qSin(data_.phase_);

        phase_ += phase_add;

        for (int u=0; u<channels; u++) {
            data[sample_index++] += v;
        }
    }

}

//---------------------------------------------------------------------
