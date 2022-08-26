#ifndef XCLASSSYNTHFROMIMAGE_H
#define XCLASSSYNTHFROMIMAGE_H

//Реализация модуля SynthFromImage - сонификация картинки

#include <QObject>

#include "sdk_h.h"
#include "xclass.h"
#include "xarray.h"
#include "xobjectsoundformat.h"
#include "xprotecteddata.h"
#include "xraster.h"

//Данные для генерации
struct XModuleSynthFromImageData: public XcluProtectedData
{
    float sample_rate = 50; //pixels per second
    float volume=1;         //volume

    //playing line, with sample_rate speed
    QVector<float> line_;
    float line_speed_ = 1;  //speed regulation - matter for non-linearity
};

//Модуль
class XModuleSynthFromImage: public XClass
{
    Q_OBJECT
public:
    XModuleSynthFromImage(QString class_name);
    virtual ~XModuleSynthFromImage();
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

    XProtectedObject out_image_;

    XRaster_u8 input_;
    XRaster_u8c3 output_;

    bool input_frozen_ = false;

    //данные - они обновляются из GUI в основном потоке
    //и используются при генерации звука
    XModuleSynthFromImageData data_;

    //internal values used for sound generation -----------------------
    double phase_ = 0;
    QVector<float> line_;

};

#endif // XCLASSSYNTHFROMIMAGE_H
