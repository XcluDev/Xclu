#ifndef RTMODULESYNTHFROMIMAGE_H
#define RTMODULESYNTHFROMIMAGE_H

//Реализация модуля SynthFromImage - сонификация картинки

#include <QObject>

#include "sdk_h.h"
#include "xmodule.h"
#include "xarray.h"
#include "xcluobjectsoundformat.h"
#include "xcluprotecteddata.h"
#include "xraster.h"

//Данные для генерации
struct XModuleSynthFromImageData: public XcluProtectedData
{
    float sample_rate = 50; //pixels per second
    float volume=1;         //volume

    //playing line, with sample_rate speed
    QVector<float> line_;
};

//Модуль
class XModuleSynthFromImage: public XModule
{
    Q_OBJECT
public:
    XModuleSynthFromImage(QString class_name);
    ~XModuleSynthFromImage();
protected:
#include "auto.h"
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();

    //sound generation
    //"sound_buffer_add" call, fills `data` buffer
    //there are required to fill channels * samples values at data
    virtual void impl_sound_buffer_add(int sample_rate, int channels, int samples, float *data);

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

#endif // RTMODULESYNTHFROMIMAGE_H
