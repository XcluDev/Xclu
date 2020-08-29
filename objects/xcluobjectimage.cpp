#include "qt_widgets.h"

#include "xcluobjectimage.h"
#include "incl_cpp.h"
#include "interfaceguiobject.h"

#include <QImageReader>
#include <QImageWriter>

//---------------------------------------------------------------------
XcluObjectImage::XcluObjectImage(XcluObject *object)
: XcluObjectWrapper(object)
{

}


//---------------------------------------------------------------------
//показ в GUI
void XcluObjectImage::show_object(InterfaceGuiObject *item) {
    auto &visual = item->visual();

    //описание изображения
    ObjectRead obj_1(object());
    auto d = XcluObjectImage::get_data(obj_1);
    QString info_text = QString("%1\n%2 byte(s)").arg(object_type_to_string(obj_1.type())).arg(obj_1.size_bytes());
    obj_1.release();    //освобождаем объект


    info_text += QString("\n%1x%2, %3, %4").arg(d.w).arg(d.h).arg(d.channels_description).arg(d.data_type);
    visual.set_text(info_text);

    //TODO получение параметров просмотра из item
    XcluObjectShowSettings settings;
    settings.w = xclu::image_preview_small_w;
    settings.h = xclu::image_preview_small_h;

    //создаем preview для изображения
    int w = d.w;
    int h = d.h;
    if (w > 0 && h > 0) {
        float scl = qMin(float(settings.w) / w, float(settings.h) / h);
        w = w * scl;
        h = h * scl;

        QImage img;
        {
            ObjectRead obj(object());
            XcluObjectImage::convert_to_QImage_fast_preview(obj, img, w, h);
        }

        visual.set_image(img);
    }
    else {
        //если нет картинки, то очищаем
        visual.clear_image();
    }

}

//---------------------------------------------------------------------
//показать объект в QLabel
void XcluObjectImage::show_object(QLabel *label, const XcluObjectShowSettings &settings) {
    ObjectRead obj_1(object());
    auto d = XcluObjectImage::get_data(obj_1);
    obj_1.release();    //освобождаем объект

    //описание изображения
    //QString info_text = QString("%1\n%2 byte(s)").arg(object_type_to_string(obj.type())).arg(obj.size_bytes());
    //info_text += QString("\n%1x%2, %3, %4").arg(d.w).arg(d.h).arg(d.channels_description).arg(d.data_type);
    //visual.set_text(info_text);

    //создаем preview для изображения
    int w = d.w;
    int h = d.h;
    if (w > 0 && h > 0) {
        float scl = qMin(float(settings.w) / w, float(settings.h) / h);

        w = w * scl;
        h = h * scl;

        QImage img;
        {
            ObjectRead obj(object());
            XcluObjectImage::convert_to_QImage_fast_preview(obj, img, w, h);
        }

        QPixmap pix = QPixmap::fromImage(img);
        label->setPixmap(pix);
    }
    else {
        //если нет картинки, то очищаем
        label->setText("");
    }
}

//---------------------------------------------------------------------
//Извлечение всех полей из изображения
/*static*/ XcluObjectImageData XcluObjectImage::get_data(ObjectRead &object) {
    object.assert_type(XcluObjectTypeImage);

    XcluObjectImageData d;

    d.w = object.get_int("w");
    d.h = object.get_int("h");
    d.channels = object.get_int("channels");
    d.channels_description = object.get_string("channels_description");
    d.data_type = object.get_string("data_type");
    //d.data = &object.get_array("data");
    return d;
}

//---------------------------------------------------------------------
//Функция для тестирования работы с изображениями
void XcluImage_test() {
    qDebug()<< "TEST: XcluImage_test ------------";
    QImageReader reader("D:\\temp\\img.jpg");
    QImage img = reader.read();
    XcluObject obj;
    ObjectReadWrite object(obj);

    QString channels = "RGB";
    //"Grayscale";
    //"R";
    //"B";
    //"BGR";

    QString data_type = //"u8bit";
                "float";
    XcluObjectImage::create_from_QImage(object, img, channels, data_type);
    QImage img2;

    //XcluObjectImage::convert_to_QImage(object, img2);
    XcluObjectImage::convert_to_QImage_fast_preview(object, img2, 100, 100);

    QImageWriter writer("D:\\temp\\img2.jpg");
    writer.write(img2);
}

//---------------------------------------------------------------------
//функция для взятия каналов
//записывает прямо в массивы pixel - а потом сдвигаем это писель за пикселем
typedef std::function<void (uchar r, uchar g, uchar b, uchar *&pixel)> XcluImageGetChannelsFunction_u8bit;
typedef std::function<void (uchar r, uchar g, uchar b, float *&pixel)> XcluImageGetChannelsFunction_float;

//Grayscale,RGB,BGR,RGBA,ABGR,R,G,B
void XcluImageGetChannels_u8bit_Grayscale(uchar r, uchar g, uchar b, uchar *&pixel) {
    *(pixel++) = (int(r)+int(g)+int(b))/3;
}
void XcluImageGetChannels_u8bit_RGB(uchar r, uchar g, uchar b, uchar *&pixel) {
    *(pixel++) = r;
    *(pixel++) = g;
    *(pixel++) = b;
}
void XcluImageGetChannels_u8bit_BGR(uchar r, uchar g, uchar b, uchar *&pixel) {
    *(pixel++) = b;
    *(pixel++) = g;
    *(pixel++) = r;
}
void XcluImageGetChannels_u8bit_RGBA(uchar r, uchar g, uchar b, uchar *&pixel) {
    *(pixel++) = r;
    *(pixel++) = g;
    *(pixel++) = b;
    *(pixel++) = 255;
}
void XcluImageGetChannels_u8bit_ABGR(uchar r, uchar g, uchar b, uchar *&pixel) {
    *(pixel++) = 255;
    *(pixel++) = b;
    *(pixel++) = g;
    *(pixel++) = r;
}
void XcluImageGetChannels_u8bit_R(uchar r, uchar /*g*/, uchar /*b*/, uchar *&pixel) {
    *(pixel++) = r;
}
void XcluImageGetChannels_u8bit_G(uchar /*r*/, uchar g, uchar /*b*/, uchar *&pixel) {
    *(pixel++) = g;
}
void XcluImageGetChannels_u8bit_B(uchar /*r*/, uchar /*g*/, uchar b, uchar *&pixel) {
    *(pixel++) = b;
}

//---------------------------------------------------------------------

void XcluImageGetChannels_float_Grayscale(uchar r, uchar g, uchar b, float *&pixel) {
    *(pixel++) = (int(r)+int(g)+int(b))/(3*255.0f);
}
void XcluImageGetChannels_float_RGB(uchar r, uchar g, uchar b, float *&pixel) {
    *(pixel++) = r/255.0f;
    *(pixel++) = g/255.0f;
    *(pixel++) = b/255.0f;
}
void XcluImageGetChannels_float_BGR(uchar r, uchar g, uchar b, float *&pixel) {
    *(pixel++) = b/255.0f;
    *(pixel++) = g/255.0f;
    *(pixel++) = r/255.0f;
}
void XcluImageGetChannels_float_RGBA(uchar r, uchar g, uchar b, float *&pixel) {
    *(pixel++) = r/255.0f;
    *(pixel++) = g/255.0f;
    *(pixel++) = b/255.0f;
    *(pixel++) = 1;
}
void XcluImageGetChannels_float_ABGR(uchar r, uchar g, uchar b, float *&pixel) {
    *(pixel++) = 1;
    *(pixel++) = b/255.0f;
    *(pixel++) = g/255.0f;
    *(pixel++) = r/255.0f;
}
void XcluImageGetChannels_float_R(uchar r, uchar /*g*/, uchar /*b*/, float *&pixel) {
    *(pixel++) = r/255.0f;
}
void XcluImageGetChannels_float_G(uchar /*r*/, uchar g, uchar /*b*/, float *&pixel) {
    *(pixel++) = g/255.0f;
}
void XcluImageGetChannels_float_B(uchar /*r*/, uchar /*g*/, uchar b, float *&pixel) {
    *(pixel++) = b/255.0f;
}

//---------------------------------------------------------------------
//получение нужной функции в зависимости от имени канала
//Grayscale,RGB,BGR,RGBA,ABGR,R,G,B
#define GET_XcluImageGetChannelsFunction(CHANNELS, TYPE) \
{ if (channels_string == #CHANNELS) return XcluImageGetChannels_##TYPE##_##CHANNELS; }

XcluImageGetChannelsFunction_u8bit Get_XcluImageGetChannelsFunction_u8bit(QString channels_string) {
    GET_XcluImageGetChannelsFunction(Grayscale, u8bit);
    GET_XcluImageGetChannelsFunction(RGB, u8bit);
    GET_XcluImageGetChannelsFunction(BGR, u8bit);
    GET_XcluImageGetChannelsFunction(RGBA, u8bit);
    GET_XcluImageGetChannelsFunction(ABGR, u8bit);
    GET_XcluImageGetChannelsFunction(R, u8bit);
    GET_XcluImageGetChannelsFunction(G, u8bit);
    GET_XcluImageGetChannelsFunction(B, u8bit);
    xclu_exception("Unknown channels description " + channels_string);
    return nullptr;
}

XcluImageGetChannelsFunction_float Get_XcluImageGetChannelsFunction_float(QString channels_string) {
    GET_XcluImageGetChannelsFunction(Grayscale, float);
    GET_XcluImageGetChannelsFunction(RGB, float);
    GET_XcluImageGetChannelsFunction(BGR, float);
    GET_XcluImageGetChannelsFunction(RGBA, float);
    GET_XcluImageGetChannelsFunction(ABGR, float);
    GET_XcluImageGetChannelsFunction(R, float);
    GET_XcluImageGetChannelsFunction(G, float);
    GET_XcluImageGetChannelsFunction(B, float);
    xclu_exception("Unknown channels description " + channels_string);
    return nullptr;
}

//---------------------------------------------------------------------
/*static*/ void XcluObjectImage::allocate(ObjectReadWrite &object, XcluArrayDataType data_type, int channels, int w, int h) {
    object.clear();
    object.set_type(XcluObjectTypeImage);
    object.set_int("w", w);
    object.set_int("h", h);
    object.set_int("channels", channels);
    QString channels_str = (channels==1) ? "Grayscale" : "RGB"; //TODO если каналов не 1 или 3, то будет пустое описание
    object.set_string("channels_description", channels_str);

    object.set_string("data_type", XcluArrayDataType_to_string(data_type));

    //создание массива
    XcluArray *array = object.var_array("data", true);
    array->allocate_image(channels, w, h, data_type);
}

//---------------------------------------------------------------------
/*static*/ void XcluObjectImage::create_from_array(ObjectReadWrite &object, quint8 *data, int channels, int w, int h) {
    //заполнение полей описания изображения
    allocate(object, XcluArrayDataType_u8bit, channels, w, h);
    //заполнение массива
    XcluArray *array = object.var_array("data");
    quint8 *output_pixels = array->data_u8bit();
    for (int i = 0; i<channels*w*h; i++) {
        output_pixels[i] = data[i];
    }
}

//---------------------------------------------------------------------
/*static*/ void XcluObjectImage::create_from_raster(ObjectReadWrite &object, Raster_u8 &raster) {
    create_from_array(object, &raster.data[0], 1, raster.w, raster.h);
}

//---------------------------------------------------------------------
/*static*/ void XcluObjectImage::create_from_raster(ObjectReadWrite &object, Raster_u8c3 &raster) {
    create_from_array(object, (quint8 *)(&raster.data[0]), 3, raster.w, raster.h);
}

//---------------------------------------------------------------------
/*static*/ void XcluObjectImage::to_raster(ObjectRead &object, Raster_u8 &raster, rect_int rect) {

    int w = object.get_int("w");
    int h = object.get_int("h");
    int channels = object.get_int("channels");
    xclu_assert(channels == 1 || channels == 3 || channels == 4, "XcluObjectImage::to_raster - only 1,3 channels are supported");

    //прямоугольник
    if (rect.x == -1) {
        rect = rect_int(0,0,w,h);
    }
    xclu_assert(rect.is_inside(w, h), "Bad rectange in XcluObjectImage::to_raster");

    //доступ к пикселям
    XcluArray const *array = get_array(object);

    auto data_type = array->data_type();
    xclu_assert(data_type == XcluArrayDataType_u8bit,
                "XcluObjectImage::to_raster - only u8bit data type is supported");

    raster.allocate(rect.w, rect.h);

    quint8 const *pixels = array->data_u8bit();
    if (channels == 1) {
        for (int y=0; y<rect.h; y++) {
            int k = 0;
            for (int x=0; x<rect.w; x++) {
                k = (rect.x+x+w*(rect.y+y));
                raster.data[x+rect.w*y] = pixels[k];
            }
        }
    }
    if (channels == 3 || channels == 4) {
        int k = 0;
        for (int y=0; y<rect.h; y++) {
            for (int x=0; x<rect.w; x++) {
                k = channels * (rect.x+x+w*(rect.y+y));
                raster.data[x+rect.w*y] = (int(pixels[k]) + int(pixels[k+1]) + int(pixels[k+2]))/3;
            }
        }
    }
}

//---------------------------------------------------------------------
/*static*/ void XcluObjectImage::to_raster(ObjectRead &object, Raster_u8c3 &raster, rect_int rect) {
    int w = object.get_int("w");
    int h = object.get_int("h");
    int channels = object.get_int("channels");
    xclu_assert(channels == 1 || channels == 3 || channels == 4, "XcluObjectImage::to_raster - only 1,3 channels are supported");

    //прямоугольник
    if (rect.x == -1) {
        rect = rect_int(0,0,w,h);
    }
    xclu_assert(rect.is_inside(w, h), "Bad rectange in XcluObjectImage::to_raster");

    //доступ к пикселям
    XcluArray const *array = get_array(object);

    auto data_type = array->data_type();
    xclu_assert(data_type == XcluArrayDataType_u8bit,
                "XcluObjectImage::to_raster - only u8bit data type is supported");

    raster.allocate(w, h);

    quint8 const *pixels = array->data_u8bit();
    if (channels == 1) {
        for (int y=0; y<rect.h; y++) {
            int k = 0;
            for (int x=0; x<rect.w; x++) {
                k = (rect.x+x+w*(rect.y+y));
                raster.data[x+rect.w*y] = u8_rgb(pixels[k]);
            }
        }
    }
    if (channels == 3 || channels == 4) {
        int k = 0;
        for (int y=0; y<rect.h; y++) {
            for (int x=0; x<rect.w; x++) {
                k = channels * (rect.x+x+w*(rect.y+y));
                raster.data[x+rect.w*y] = u8_rgb(pixels[k], pixels[k+1], pixels[k+2]);
            }
        }
    }

}

//---------------------------------------------------------------------
/*static*/ void XcluObjectImage::create_from_QImage(ObjectReadWrite &object, const QImage &qimage,
                                              QString channels_str, QString data_type_str,
                                              bool mirrorx, bool mirrory) {
    XcluArrayDataType data_type = string_to_XcluArrayDataType(data_type_str);
    create_from_QImage(object, qimage, channels_str, data_type, mirrorx, mirrory);
}

//---------------------------------------------------------------------
//макрос для scanline с поддержкой mirrory
#define XcluImage_SCANLINE(H) (qimage.scanLine(mirrory?(H-1-y):y))

//---------------------------------------------------------------------
/*static*/ void XcluObjectImage::create_from_QImage(ObjectReadWrite &object, const QImage &qimage,
                                              QString channels_str, XcluArrayDataType data_type,
                                              bool mirrorx, bool mirrory) {
    xclu_assert(!mirrorx, "XcluObjectImage::create_from_QImage doesn't supports mirrorx");

    //TODO сейчас поддерживаем на вход только тип RGB32
    xclu_assert(qimage.format() == QImage::Format_RGB32, "XcluObjectImage::create_from_QImage - QImage format is unsupported, only Format_RGB32 is supported");

    //TODO сейчас поддерживаем на вход только типы u8bit и float
    xclu_assert(data_type == XcluArrayDataType_u8bit || data_type == XcluArrayDataType_float,
                "Only u8bit and float types for images are supported");

    int w = qimage.size().width();
    int h = qimage.size().height();
    int channels = get_channels_count(channels_str);

    //заполнение полей описания изображения
    object.clear();
    object.set_type(XcluObjectTypeImage);
    object.set_int("w", w);
    object.set_int("h", h);
    object.set_int("channels", channels);
    object.set_string("channels_description", channels_str);
    QString data_type_str = XcluArrayDataType_to_string(data_type);
    object.set_string("data_type", data_type_str);

    //заполнение массива
    XcluArray *array = object.var_array("data", true);
    array->allocate_image(channels, w, h, data_type);

#define XcluImage_IMPLEMENT(TYPE, CPP_TYPE) \
    if (data_type == XcluArrayDataType_##TYPE) { \
        auto pixel_fun = Get_XcluImageGetChannelsFunction_##TYPE(channels_str); \
        CPP_TYPE *output_pixels = array->data_##TYPE(); \
        for (int y=0; y<h; y++) { \
            const uchar *line = XcluImage_SCANLINE(h); \
            int k = 0; \
            for (int x=0; x<w; x++) { \
                uchar b = line[k++]; \
                uchar g = line[k++]; \
                uchar r = line[k++]; \
                k++;  \
                pixel_fun(r,g,b,output_pixels); \
            } \
        } \
    }

    XcluImage_IMPLEMENT(u8bit, quint8);
    XcluImage_IMPLEMENT(float, float);


}

//---------------------------------------------------------------------
//число каналов по строковому описанию
//Grayscale,RGB,BGR,RGBA,BGRA,R,G,B
/*static*/ int XcluObjectImage::get_channels_count(QString channels_str) {
    if (channels_str == "Grayscale") return 1;
    int count = channels_str.length();
    xclu_assert(count>0, "Empty channels string in image creating");
    return count;
}

//---------------------------------------------------------------------
//вставка в QImage пикселей, для float: PRE = "int", AFTER = *255.0f
#define XcluImage_Qimage_CH1(PRE,AFTER) { \
    line[k] = line[k+1] = line[k+2] = PRE (*(input_pixels++) AFTER); \
    line[k+3] = 255; \
    k+=4; \
}
#define XcluImage_Qimage_CH3(PRE,AFTER) { \
    line[k+2] = PRE(*(input_pixels++) AFTER); \
    line[k+1] = PRE(*(input_pixels++) AFTER); \
    line[k] = PRE(*(input_pixels++) AFTER); \
    line[k+3] = 255; \
    k+=4; \
}
#define XcluImage_Qimage_CH4(PRE,AFTER) { \
    line[k+2] = PRE(*(input_pixels++) AFTER); \
    line[k+1] = PRE(*(input_pixels++) AFTER); \
    line[k] = PRE(*(input_pixels++) AFTER); \
    line[k+3] = PRE(*(input_pixels++) AFTER); \
    k+=4; \
}

//---------------------------------------------------------------------
//Конвертировать изображение в QImage - например, для записи на диск
//Внимание - не учитывается значение каналов, а только их количество
//то есть "R" будет выглядет как Grayscale
/*static*/ void XcluObjectImage::convert_to_QImage(ObjectRead &object, QImage &qimage,
                                             bool mirrorx, bool mirrory) {

    object.assert_type(XcluObjectTypeImage);

    xclu_assert(!mirrorx, "XcluObjectImage::convert_to_QImage doesn't supports mirrorx");

    int w = object.get_int("w");
    int h = object.get_int("h");

    int channels = object.get_int("channels");
    xclu_assert(channels == 1 || channels == 3 || channels == 4, "XcluObjectImage::convert_to_QImage - only 1,3,4 channels are supported");

    auto *array = object.get_array("data");
    auto data_type = array->data_type();
    xclu_assert(data_type == XcluArrayDataType_u8bit || data_type == XcluArrayDataType_float,
                "XcluObjectImage::convert_to_QImage - only u8bit and float data types are supported");

    qimage = QImage(w, h, QImage::Format_RGB32);


    //u8bit
    if (data_type == XcluArrayDataType_u8bit) {
        quint8 const *input_pixels = array->data_u8bit();
        for (int y=0; y<h; y++) {
            uchar *line = XcluImage_SCANLINE(h);
            int k = 0;
            if (channels == 1) for (int x=0; x<w; x++) XcluImage_Qimage_CH1(,);
            if (channels == 3) for (int x=0; x<w; x++) XcluImage_Qimage_CH3(,);
            if (channels == 4) for (int x=0; x<w; x++) XcluImage_Qimage_CH4(,);
        }
    }
    //float
    if (data_type == XcluArrayDataType_float) {
        float const *input_pixels = array->data_float();
        for (int y=0; y<h; y++) {
            uchar *line = XcluImage_SCANLINE(h);
            int k = 0;
            if (channels == 1) for (int x=0; x<w; x++) XcluImage_Qimage_CH1(int, *255.0f);
            if (channels == 3) for (int x=0; x<w; x++) XcluImage_Qimage_CH3(int, *255.0f);
            if (channels == 4) for (int x=0; x<w; x++) XcluImage_Qimage_CH4(int, *255.0f);
        }
    }

}


//---------------------------------------------------------------------
/*static*/ void XcluObjectImage::convert_to_QImage_fast_preview(ObjectRead &object, QImage &qimage,
                                                          int out_w, int out_h,
                                                          bool mirrorx, bool mirrory) {
    xclu_assert(!mirrorx, "XcluObjectImage::convert_to_QImage_fast_preview doesn't supports mirrorx");

    //если входные размеры заданы неверно - выдаем пустое изображение
    if (out_w <= 0 || out_h <= 0) {
        qimage = QImage();
        return;
    }

    object.assert_type(XcluObjectTypeImage);

    int w = object.get_int("w");
    int h = object.get_int("h");

    int channels = object.get_int("channels");
    xclu_assert(channels == 1 || channels == 3 || channels == 4, "XcluObjectImage::convert_to_QImage_fast_preview - only 1,3,4 channels are supported");

    auto *array = object.get_array("data");
    auto data_type = array->data_type();
    xclu_assert(data_type == XcluArrayDataType_u8bit || data_type == XcluArrayDataType_float,
                "XcluObjectImage::convert_to_QImage_fast_preview - only u8bit and float data types are supported");

    qimage = QImage(out_w, out_h, QImage::Format_RGB32);

    //макрос для взятие координат пикселей
#define XcluImage_GET_PIX(CPP_TYPE) { input_pixels = (CPP_TYPE const*) array->pixel_pointer(x*w/out_w,y1); }

    //u8bit
    if (data_type == XcluArrayDataType_u8bit) {
        quint8 const*input_pixels;
        for (int y=0; y<out_h; y++) {
            uchar *line = XcluImage_SCANLINE(out_h);
            int k = 0;
            int y1 = y * h / out_h;
            if (channels == 1) for (int x=0; x<out_w; x++) { XcluImage_GET_PIX(quint8); XcluImage_Qimage_CH1(,); }
            if (channels == 3) for (int x=0; x<out_w; x++) { XcluImage_GET_PIX(quint8); XcluImage_Qimage_CH3(,); }
            if (channels == 4) for (int x=0; x<out_w; x++) { XcluImage_GET_PIX(quint8); XcluImage_Qimage_CH4(,); }
        }
    }
    //float
    if (data_type == XcluArrayDataType_float) {
        float const *input_pixels;
        for (int y=0; y<out_h; y++) {
            uchar *line = XcluImage_SCANLINE(out_h);
            int k = 0;
            int y1 = y * h / out_h;
            if (channels == 1) for (int x=0; x<out_w; x++) { XcluImage_GET_PIX(float); XcluImage_Qimage_CH1(int, *255.0f); }
            if (channels == 3) for (int x=0; x<out_w; x++) { XcluImage_GET_PIX(float); XcluImage_Qimage_CH3(int, *255.0f); }
            if (channels == 4) for (int x=0; x<out_w; x++) { XcluImage_GET_PIX(float); XcluImage_Qimage_CH4(int, *255.0f); }
        }
    }

}


//---------------------------------------------------------------------
//Загрузка изображения с диска
//TODO выполняется через QImage, поэтому не очень быстрая
//быстрее через OpenCV или FreeImage или TurboJpeg
/*static*/ void XcluObjectImage::load(ObjectReadWrite &object, QString file_name) {
    QImage qimage;
    xclu_assert(qimage.load(file_name), "Can't load image " + file_name);
    create_from_QImage(object, qimage, "RGB", XcluArrayDataType_u8bit);
}

//---------------------------------------------------------------------
//Запись на диск
//TODO выполняется через QImage, поэтому не очень быстрая
//быстрее через OpenCV или FreeImage или TurboJpeg
/*static*/ void XcluObjectImage::save(ObjectRead &object, QString file_name, QString format, int quality) {
    QImage qimage;
    convert_to_QImage(object, qimage);
    xclu_assert(qimage.save(file_name, format.toStdString().c_str(), quality),
                "Can't save image " + file_name);
}

//---------------------------------------------------------------------
