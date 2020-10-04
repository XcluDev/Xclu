#ifndef XCLUIMAGE_H
#define XCLUIMAGE_H

#include "xstruct.h"
#include <QImage>
#include "xcluobjectwrapper.h"
#include "xraster.h"
class QLabel;
class XArray;
class XGuiObject;

//Здесь описан класс XStructImage,
//который позволяет конвертировать QImage в XStruct и обратно

//Функция для тестирования работы с изображениями
void XcluImage_test();

//Поддерживаемые каналы: Grayscale,RGB,BGR,RGBA,ABGR,R,G,B  [не поддерживается HSL,H,S,L]
//Подерживаемые типы данных: u8,float
/*Поля изображения:
int "w"
int "h"
int "channels"
string "channels_description"
string "data_type"
array "data"
*/


//поля класса, которые полностью характеризует изображение
class XStructImageData {
public:
    int w = 0;
    int h = 0;
    int channels = 0;
    QString channels_description;
    QString data_type;
};


//класс для работы с объектами-изображениями
class XStructImage: public XStructWrapper {
public:
    XStructImage(const XStruct *object);

    //показать объект в GUI
    virtual void show_object(XGuiObject *item);

    //показать объект в QLabel
    virtual void show_object(QLabel *label, const XStructShowSettings &settings);

    //Извлечение всех полей из изображения
    static XStructImageData get_data(const XStruct &object);


    //создание изображения - выделение памяти и заполнение из массива
    static void allocate(XStruct &object, XTypeId data_type, int channels, int w, int h);
    static void create_from_array(XStruct &object, quint8 *data, int channels, int w, int h);

    static XArray const *get_array(const XStruct &object) {return object.get_array("data");}
    static XArray *var_array(XStruct &object) {return object.var_array("data");}



    //число каналов по строковому описанию
    //Grayscale,RGB,BGR,RGBA,BGRA,R,G,B
    static int get_channels_count(QString channels_str);


    //Создание из XRaster_... и обратно
    static void create_from_raster(XStruct &object, XRaster_u8 &raster);
    static void create_from_raster(XStruct &object, XRaster_u8c3 &raster);

    static void to_raster(const XStruct &object, XRaster_u8 &raster, rect_int rect = rect_int(-1,-1,-1,-1));
    static void to_raster(const XStruct &object, XRaster_u8c3 &raster, rect_int rect = rect_int(-1,-1,-1,-1));


    //Создание из QImage
    //TODO mirrorx не реализована
    static void create_from_QImage(XStruct &object, const QImage &qimage,
                                   QString channels_str, QString data_type_str,
                                   bool mirrorx=false, bool mirrory=false);
    static void create_from_QImage(XStruct &object, const QImage &qimage,
                                   QString channels_str, XTypeId data_type,
                                   bool mirrorx=false, bool mirrory=false);

    //Конвертировать изображение в QImage - например, для записи на диск
    //Внимание - не учитывается значение каналов, а только их количество
    //то есть "R" будет выглядет как Grayscale
    static void convert_to_QImage(const XStruct &object, QImage &qimage,
                                  bool mirrorx=false, bool mirrory=false);

    //Конвертировать изображение в QImage с уменьшением размера, быстро
    //используется для создания быстрых Preview
    //Внимание - не учитывается значение каналов, а только их количество
    //то есть "R" будет выглядет как Grayscale
    static void convert_to_QImage_fast_preview(const XStruct &object, QImage &qimage, int out_w, int out_h,
                                               bool mirrorx=false, bool mirrory=false);

    //Загрузка изображения с диска
    //TODO выполняется через QImage, поэтому не очень быстрая
    //быстрее через OpenCV или FreeImage или TurboJpeg
    static void load(XStruct &object, QString file_name);

    //Запись изображения на диск
    //TODO выполняется через QImage, поэтому не очень быстрая
    //быстрее через OpenCV или FreeImage или TurboJpeg
    static void save(const XStruct &object, QString file_name, QString format = "JPG", int quality = 90);


};

#endif // XCLUIMAGE_H
