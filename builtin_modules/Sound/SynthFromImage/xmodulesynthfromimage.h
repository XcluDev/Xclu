#ifndef RTMODULESYNTHFROMIMAGE_H
#define RTMODULESYNTHFROMIMAGE_H

//Реализация модуля SynthFromImage - сонификация картинки

#include <QObject>
#include <QScopedPointer>
#include <QMutex>

#include "incl_h.h"
#include "xmodule.h"
#include "xarray.h"
#include "xcluobjectsoundformat.h"
#include "xcluprotecteddata.h"

//Данные для генерации
struct XModuleSynthFromImageData: public XcluProtectedData
{
    int image_background = 0;   //0 - black, 1 - white
    float pcm_speed_hz = 10;
    float contrast=100;

    float phase_ = 0;

    //установить картинку - схлапывает в однопиксельную float
    //TODO сейчас только rbg
    void set_image(int w, int h, const quint8 *rgb);

    //получить значение звука
    float get_volume(float phase);  //x=0..1

    //параметры оцифровки
    float min_ = 0;
    float max_ = 1;
    float center_ = 0.5;
    float range_ = 1;


    void clear() {
        image_background = 0;
        pcm_speed_hz = 0;
        phase_ = 0;

        w_ = 0;
        image_.clear();

        min_ = 0;
        max_ = 1;
        center_ = 0.5;
        range_ = 1;

    }

    int w_= 0;
    QVector<float> image_;  //1-пиксельная картинка
};

//Модуль
class XModuleSynthFromImage: public XModule
{
    Q_OBJECT
public:
    XModuleSynthFromImage();
    ~XModuleSynthFromImage();

    static QString *static_class_name_ptr;
    static XModuleSynthFromImage *new_module();

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

    QString image_file_;    //файл с последней загруженной картинкой
    void load_image_file(QString image_file);
    //загрузка изображения из другого модуля
    void load_image_link(QString image_link);

    //данные - они обновляются из GUI в основном потоке
    //и используются при генерации звука
    XModuleSynthFromImageData data_;
    void update_data();

};

#endif // RTMODULESYNTHFROMIMAGE_H
