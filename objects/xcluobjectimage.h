#ifndef XCLUIMAGE_H
#define XCLUIMAGE_H

#include "xdict.h"
#include <QImage>
#include "xcluobjectwrapper.h"
class QLabel;
class XcluArray;
class InterfaceGuiObject;

//Здесь описан класс XDictImage,
//который позволяет конвертировать QImage в XDict и обратно

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
class XDictImageData {
public:
    int w = 0;
    int h = 0;
    int channels = 0;
    QString channels_description;
    QString data_type;
};


//класс для работы с объектами-изображениями
class XDictImage: public XDictWrapper {
public:
    XDictImage(XDict *object);

    //показать объект в GUI
    virtual void show_object(InterfaceGuiObject *item);

    //показать объект в QLabel
    virtual void show_object(QLabel *label, const XDictShowSettings &settings);

    //Извлечение всех полей из изображения
    static XDictImageData get_data(XDictRead &object);


    //создание изображения - выделение памяти и заполнение из массива
    static void allocate(XDictWrite &object, XcluArrayDataType data_type, int channels, int w, int h);
    static void create_from_array(XDictWrite &object, quint8 *data, int channels, int w, int h);

    static XcluArray const *get_array(XDictRead &object) {return object.get_array("data");}
    static XcluArray *var_array(XDictWrite &object) {return object.var_array("data");}



    //число каналов по строковому описанию
    //Grayscale,RGB,BGR,RGBA,BGRA,R,G,B
    static int get_channels_count(QString channels_str);


    //Создание из Raster_... и обратно
    static void create_from_raster(XDictWrite &object, Raster_u8 &raster);
    static void create_from_raster(XDictWrite &object, Raster_u8c3 &raster);

    static void to_raster(XDictRead &object, Raster_u8 &raster, rect_int rect = rect_int(-1,-1,-1,-1));
    static void to_raster(XDictRead &object, Raster_u8c3 &raster, rect_int rect = rect_int(-1,-1,-1,-1));


    //Создание из QImage
    //TODO mirrorx не реализована
    static void create_from_QImage(XDictWrite &object, const QImage &qimage,
                                   QString channels_str, QString data_type_str,
                                   bool mirrorx=false, bool mirrory=false);
    static void create_from_QImage(XDictWrite &object, const QImage &qimage,
                                   QString channels_str, XcluArrayDataType data_type,
                                   bool mirrorx=false, bool mirrory=false);

    //Конвертировать изображение в QImage - например, для записи на диск
    //Внимание - не учитывается значение каналов, а только их количество
    //то есть "R" будет выглядет как Grayscale
    static void convert_to_QImage(XDictRead &object, QImage &qimage,
                                  bool mirrorx=false, bool mirrory=false);

    //Конвертировать изображение в QImage с уменьшением размера, быстро
    //используется для создания быстрых Preview
    //Внимание - не учитывается значение каналов, а только их количество
    //то есть "R" будет выглядет как Grayscale
    static void convert_to_QImage_fast_preview(XDictRead &object, QImage &qimage, int out_w, int out_h,
                                               bool mirrorx=false, bool mirrory=false);

    //Загрузка изображения с диска
    //TODO выполняется через QImage, поэтому не очень быстрая
    //быстрее через OpenCV или FreeImage или TurboJpeg
    static void load(XDictWrite &object, QString file_name);

    //Запись изображения на диск
    //TODO выполняется через QImage, поэтому не очень быстрая
    //быстрее через OpenCV или FreeImage или TurboJpeg
    static void save(XDictRead &object, QString file_name, QString format = "JPG", int quality = 90);


};

#endif // XCLUIMAGE_H
