#include "xmodulesynthfromimage.h"
#include "incl_cpp.h"
#include <qmath.h>
#include <qendian.h>
#include "registrarxmodule.h"
#include "projectruntime.h"
#include "module.h"
#include "xcluobjectimage.h"

//registering module implementation
REGISTER_XMODULE(SynthFromImage)


//---------------------------------------------------------------------
//установить картинку - схлапывает в однопиксельную float
//TODO сейчас только rbg
void XModuleSynthFromImageData::set_image(int w, int h, const quint8 *rgb) {
    w_ = w;
    image_.resize(w_);
    for (int x=0; x<w; x++) {
        float sum = 0;
        for (int y=0; y<h; y++) {
            int i = 3*(x+w*y);
            sum += int(rgb[i]) + int(rgb[i+1]) + int(rgb[i+2]);
        }
        image_[x] = sum / (3*255*h);
    }
    //считываем диапазон
    min_ = 1;
    max_ = 0;
    double m = 0;
    double mm = 0;

    for (int x=0; x<w; x++) {
        float v = image_[x];
        min_ = qMin(min_, v);
        max_ = qMax(max_, v);
        m += v;
        mm += v*v;
    }
    m /= w;
    mm /= w;
    center_ = m;
    range_ = 2*sqrt(mm - m*m);

    //трансформируем image в значение, используя center_ и use_range_
    if (contrast > 0) {
        float use_range = 1.0 / contrast;
        for (int x=0; x<w; x++) {
            image_[x] = mapf_clamped(image_[x],center_ - use_range/2, center_ + use_range/2, -1, 1);
        }
    }
    else {
        for (int x=0; x<w; x++) {
            image_[x] = 0;
        }
    }
}

//---------------------------------------------------------------------
//получить значение звука
float XModuleSynthFromImageData::get_volume(float phase) {  //x=0..1
    if (w_ == 0) return 0;
    float x = phase * w_;
    int x0 = int(x);
    int x1 = (x0+1) % w_;
    x -= x0;
    return image_[x0]*(1-x) + image_[x1]*x;
}

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
    //Очистка переменных
    image_file_ = "";

    {
        DataAccess access(data_);
        data_.clear();
    }

    XStructWrite(getstruct_image()).clear();
    XStructWrite(getstruct_image_sound()).clear();

    update_data();
}

//---------------------------------------------------------------------
void XModuleSynthFromImage::impl_update() {
    //получение картинки - загрузка из файла или взятие из другого модуля
    auto image_source = gete_image_source();
    switch (image_source) {
    case image_source_Image_File: {
        QString image_file = gets_image_file();
        if (image_file != image_file_) {
            load_image_file(image_file);
        }
    }
        break;
    case image_source_Other_Module_Image: {
            QString image_link = gets_image_link();
            load_image_link(image_link);
    }
        break;
     default:
        xclu_exception("Unknown image_source " + gets_("image_source"));
    }

    //считываем данные из GUI и обновляем картинку
    update_data();
}

//---------------------------------------------------------------------
void XModuleSynthFromImage::load_image_file(QString image_file) {
    image_file_ = image_file;
}

//---------------------------------------------------------------------
//загрузка изображения из другого модуля
//webcam1->image
void XModuleSynthFromImage::load_image_link(QString image_link) {    
    XStruct *object = RUNTIME.get_struct_by_link(image_link);
    XStructRead obj(object);
    obj.copy_to(getstruct_image());
}

//---------------------------------------------------------------------
void XModuleSynthFromImage::impl_stop() {

}

//---------------------------------------------------------------------
void XModuleSynthFromImage::update_data() {
    DataAccess access(data_);
    //data_.image_background = geti_image_background");
    data_.pcm_speed_hz = getf_pcm_speed_hz();
    data_.contrast = getf_contrast();

    //установка картинки для генерации звука
    //TODO не только rgb
    XStructRead obj(getstruct_image());
    if (obj.has_int("w")) {
        int w = obj.geti("w");
        int h = obj.geti("h");

        //int channels = obj.geti_channels");
        //xclu_assert(channels == 1 || channels == 3 || channels == 4, "XStructImage::convert_to_QImage_fast_preview - only 1,3,4 channels are supported");

        auto *array = obj.get_array("data");
        //auto data_type = array->data_type();
        //xclu_assert(data_type == XTypeId_u8 || data_type == XTypeId_float,
        //            "XStructImage::convert_to_QImage_fast_preview - only u8 and float data types are supported");
        data_.set_image(w, h, array->data_u8());


        //устанавливаем диапазон
        setf_min_value(data_.min_);
        setf_max_value(data_.max_);
        setf_center_value(data_.center_);
        setf_range_value(data_.range_);

        //рисуем выходную картинку
        {
            int w = data_.w_;
            int h = 200;
            XStructWrite object(getstruct_image_sound());
            XStructImage::allocate(object, XTypeId_u8, 1, w, h);
            quint8 *data =  XStructImage::var_array(object)->data_u8();
            for (int x=0; x<w; x++) {
                int y0 = int(mapf_clamped(data_.image_[x],-1,1, h, 0));
                for (int y=0; y<y0; y++) {
                    data[x+w*y] = 255;
                }
            }

        }
    }
}

//---------------------------------------------------------------------
//sound generation
//"sound_buffer_add" call, fills `data` buffer
//there are required to fill channels * samples values at data
void XModuleSynthFromImage::impl_sound_buffer_add(int sample_rate, int channels, int samples, float *data) {
    DataAccess access(data_);
    float freq_Hz = data_.pcm_speed_hz;
    int k = 0;

    qreal phase_add = freq_Hz / sample_rate;
    for (int i=0; i<samples; i++) {
        //получить значение звука
        float v = data_.get_volume(data_.phase_); //qSin(data_.phase_);
        data_.phase_+=phase_add;
        data_.phase_ = fmod(data_.phase_, 1);
        for (int u=0; u<channels; u++) {
            data[k++] += v;
        }
    }
}

//---------------------------------------------------------------------
