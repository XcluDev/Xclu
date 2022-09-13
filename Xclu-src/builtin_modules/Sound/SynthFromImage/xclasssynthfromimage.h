#pragma once

//Реализация модуля SynthFromImage - сонификация картинки

#include <QObject>

#include "sdk_h.h"
#include "xclass.h"
#include "xarray.h"
#include "xsoundtypes.h"
#include "xprotecteddata.h"
#include "xraster.h"

//Данные для генерации
struct XClassSynthFromImageData {
    float sample_rate = 50; //pixels per second
    float volume=1;         //volume

    //playing line, with sample_rate speed
    QVector<float> line_;
    float line_speed_ = 1;  //speed regulation - matter for non-linearity

    void clear() {
        *this = XClassSynthFromImageData();
    }
};

//Модуль
class XClassSynthFromImage: public XClass
{
    Q_OBJECT
public:
    XClassSynthFromImage(QString class_name);
    virtual ~XClassSynthFromImage();
protected:
#include "auto.h"
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    //sound generation
    //"sound_buffer_add" call, fills `data` buffer
    //there are required to fill channels * samples values at data
    virtual void on_sound_buffer_add(int sample_rate, int channels, int samples, float *data);

    XRaster out_image_holder_;

    XRaster input_u8_;
    XRaster output_u8c3_;

    bool input_frozen_ = false;

    //данные - они обновляются из GUI в основном потоке
    //и используются при генерации звука
    XProtectedData_<XClassSynthFromImageData> data_;

    //internal values used for sound generation -----------------------
    double phase_ = 0;
    QVector<float> line_;

};

