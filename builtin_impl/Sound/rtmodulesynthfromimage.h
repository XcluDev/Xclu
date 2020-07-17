#ifndef RTMODULESYNTHFROMIMAGE_H
#define RTMODULESYNTHFROMIMAGE_H

//Реализация модуля SynthFromImage - сонификация картинки

#include <QObject>
#include <QScopedPointer>
#include <QMutex>

#include "incl_qt.h"
#include "rtmodule.h"
#include "xcluarray.h"
#include "xcluobjectsoundformat.h"
#include "xcluprotecteddata.h"

//Данные для генерации
struct RtModuleSynthFromImageData: public XcluProtectedData
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
class RtModuleSynthFromImage: public RtModule
{
    Q_OBJECT
public:
    RtModuleSynthFromImage();
    ~RtModuleSynthFromImage();

    static QString *static_class_name_ptr; //"Test", эта переменная используется для создания новых объектов
    static RtModuleSynthFromImage *new_module();

protected:
    //Выполнение
    virtual void execute_start_internal();
    virtual void execute_update_internal();
    virtual void execute_stop_internal();

    //генерация звука
    virtual void call_internal(QString function, XcluObject *input, XcluObject * /*output*/);


    //режим выбора источника изображения
    enum ImageSource: int {
        ImageSource_ImageFile = 0,
        ImageSource_Other_Module_Image = 1,
        ImageSource_N = 2
    };

    QString image_file_;    //файл с последней загруженной картинкой
    void load_image_file(QString image_file);
    //загрузка изображения из другого модуля
    void load_image_link(QString image_link);

    //данные - они обновляются из GUI в основном потоке
    //и используются при генерации звука
    RtModuleSynthFromImageData data_;
    void update_data();

};

#endif // RTMODULESYNTHFROMIMAGE_H
