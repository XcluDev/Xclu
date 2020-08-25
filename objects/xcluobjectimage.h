#ifndef XCLUIMAGE_H
#define XCLUIMAGE_H

#include "xcluobject.h"
#include <QImage>
#include "xcluobjectwrapper.h"
class QLabel;
class XcluArray;
class InterfaceGuiObject;

//Здесь описан класс XcluObjectImage,
//который позволяет конвертировать QImage в XcluObject и обратно

//Функция для тестирования работы с изображениями
void XcluImage_test();

//Поддерживаемые каналы: Grayscale,RGB,BGR,RGBA,ABGR,R,G,B  [не поддерживается HSL,H,S,L]
//Подерживаемые типы данных: u8bit,float
/*Поля изображения:
int "w"
int "h"
int "channels"
string "channels_description"
string "data_type"
array "data"
*/


//поля класса, которые полностью характеризует изображение
class XcluObjectImageData {
public:
    int w = 0;
    int h = 0;
    int channels = 0;
    QString channels_description;
    QString data_type;
};


//класс для работы с объектами-изображениями
class XcluObjectImage: public XcluObjectWrapper {
public:
    XcluObjectImage(XcluObject *object);

    //показать объект в GUI
    virtual void show_object(InterfaceGuiObject *item);

    //показать объект в QLabel
    virtual void show_object(QLabel *label, const XcluObjectShowSettings &settings);

    //Извлечение всех полей из изображения
    static XcluObjectImageData get_data(ObjectRead &object);


    //создание изображения - выделение памяти и заполнение из массива
    static void allocate(ObjectReadWrite &object, XcluArrayDataType data_type, int channels, int w, int h);
    static void create_from_array(ObjectReadWrite &object, quint8 *data, int channels, int w, int h);

    static XcluArray const *get_array(ObjectRead &object) {return object.get_array("data");}
    static XcluArray *var_array(ObjectReadWrite &object) {return object.var_array("data");}



    //число каналов по строковому описанию
    //Grayscale,RGB,BGR,RGBA,BGRA,R,G,B
    static int get_channels_count(QString channels_str);


    //Создание из Raster_...
    static void create_from_raster(ObjectReadWrite &object, Raster_u8c3 &raster);


    //Создание из QImage
    //TODO mirrorx не реализована
    static void create_from_QImage(ObjectReadWrite &object, const QImage &qimage,
                                   QString channels_str, QString data_type_str,
                                   bool mirrorx=false, bool mirrory=false);
    static void create_from_QImage(ObjectReadWrite &object, const QImage &qimage,
                                   QString channels_str, XcluArrayDataType data_type,
                                   bool mirrorx=false, bool mirrory=false);

    //Конвертировать изображение в QImage - например, для записи на диск
    //Внимание - не учитывается значение каналов, а только их количество
    //то есть "R" будет выглядет как Grayscale
    static void convert_to_QImage(ObjectRead &object, QImage &qimage,
                                  bool mirrorx=false, bool mirrory=false);

    //Конвертировать изображение в QImage с уменьшением размера, быстро
    //используется для создания быстрых Preview
    //Внимание - не учитывается значение каналов, а только их количество
    //то есть "R" будет выглядет как Grayscale
    static void convert_to_QImage_fast_preview(ObjectRead &object, QImage &qimage, int out_w, int out_h,
                                               bool mirrorx=false, bool mirrory=false);



};

#endif // XCLUIMAGE_H
