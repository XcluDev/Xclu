#ifndef XOBJECTIMAGE_H
#define XOBJECTIMAGE_H

#include "xobject.h"
#include <QImage>
#include "xobjectwrapper.h"
#include "xraster.h"
class QLabel;
class XArray;
class XGuiObject;

//Здесь описан класс XObjectImage,
//который позволяет конвертировать QImage в XObject и обратно

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
class XObjectImageData {
public:
    int w = 0;
    int h = 0;
    int channels = 0;
    QString channels_description;
    QString data_type;

    bool is_empty() { return w <= 0 || h <= 0 || channels <= 0;}
    //int bytes_per_line() { return w * channels; } - for proper implementation need to store data_type not as string, but as id, and comput lenght.
};


// Helper class for working with XObject-images.
// See also XCvHelper class for working with OpenCV images.
class XObjectImage: public XObjectWrapper {
public:
    XObjectImage(const XObject *object);

    //показать объект в GUI
    virtual void show_object(XGuiObject *item);

    //показать объект в QLabel
    virtual void show_object(QLabel *label, const XObjectShowSettings &settings);

    // Check that object is already image
    static bool is_image(const XObject &object);

    //Извлечение всех полей из изображения
    static XObjectImageData get_data(const XObject &object);



    //создание изображения - выделение памяти и заполнение из массива
    static void allocate(XObject &object, XTypeId data_type, int channels, int w, int h);
    static void create_from_array(XObject &object, quint8 *data, int channels, int w, int h);

    static XArray const *get_array(const XObject &object) {return object.get_array("data");}
    static XArray *var_array(XObject &object) {return object.var_array("data");}



    //число каналов по строковому описанию
    //Grayscale,RGB,BGR,RGBA,BGRA,R,G,B
    static int get_channels_count(QString channels_str);


    //Creating object from XRaster
    //Simple function which directly creates image at GUI object
    //Usage: XObjectImage::create_from_raster(getobject_color_image(), raster);
    template<typename color_type>
    static void create_from_raster(XProtectedObject *object, XRaster_<color_type> &raster) {
        xc_assert(object, "NULL object at calling XObjectImage::create_from_raster");
        create_from_raster(object->write().data(), raster);
    }
    template<typename color_type>
    static void create_from_raster(XProtectedObject &object, XRaster_<color_type> &raster) {
        create_from_raster(object.write().data(), raster);
    }

    //Advanced function which works with internal object
    //Usage: XObjectImage::create_from_raster(getobject_color_image()->write().data(), raster);
    static void create_from_raster(XObject &object, XRaster_u8 &raster);
    static void create_from_raster(XObject &object, XRaster_u8c3 &raster);

    //Copy object to raster
    //Usage:
    //  XRaster_u8c3 raster;
    //  to_raster(getobject_image(), raster);

    // Simple function, works with protected object;
    // not generates error if object is NULL or not image
    template<typename color_type>
    static void to_raster(XProtectedObject *image_object, XRaster_<color_type> &raster, rect_int rect = rect_int(-1,-1,-1,-1)) {
        if (!image_object) {
            raster.clear();
            return;
        }
        auto &data = image_object->read().data();

        //no image
        if (data.type() != XObjectType::Image) {
            raster.clear();
            return;
        }

        //read image
        //TODO optimize, may receive and grayscale!
        //but now converts to u8 rgb.
        to_raster(data, raster, rect);
    }

    //Function used with non-protected object, obtained for example as guiobject->read().data()
    static void to_raster(const XObject &object, XRaster_u8 &raster, rect_int rect = rect_int(-1,-1,-1,-1));
    static void to_raster(const XObject &object, XRaster_u8c3 &raster, rect_int rect = rect_int(-1,-1,-1,-1));

    //Создание из QImage
    //TODO mirrorx не реализована
    static void create_from_QImage(XObject &object, const QImage &qimage,
                                   QString channels_str, QString data_type_str,
                                   bool mirrorx=false, bool mirrory=false);
    static void create_from_QImage(XObject &object, const QImage &qimage,
                                   QString channels_str, XTypeId data_type,
                                   bool mirrorx=false, bool mirrory=false);

    //Конвертировать изображение в QImage - например, для записи на диск
    //Внимание - не учитывается значение каналов, а только их количество
    //то есть "R" будет выглядет как Grayscale
    static void convert_to_QImage(const XObject &object, QImage &qimage,
                                  bool mirrorx=false, bool mirrory=false);

    //Конвертировать изображение в QImage с уменьшением размера, быстро
    //используется для создания быстрых Preview
    //Внимание - не учитывается значение каналов, а только их количество
    //то есть "R" будет выглядет как Grayscale
    static void convert_to_QImage_fast_preview(const XObject &object, QImage &qimage, int out_w, int out_h,
                                               bool mirrorx=false, bool mirrory=false);

    // Linking dosn't copies raster, so resulted QImage must be used only for short action,
    // such as draw or save to screen
    static bool link_to_QImage(const XObject &object, QImage &qimage);

    //Загрузка изображения с диска
    //TODO выполняется через QImage, поэтому не очень быстрая
    //быстрее через OpenCV или FreeImage или TurboJpeg
    static void load(XObject &object, QString file_name);

    //Запись изображения на диск
    //TODO выполняется через QImage, поэтому не очень быстрая
    //быстрее через OpenCV или FreeImage или TurboJpeg
    static void save(const XObject &object, QString file_name, QString format = "JPG", int quality = 90);


};

#endif // XOBJECTIMAGE_H
