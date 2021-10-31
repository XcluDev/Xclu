#include "./../utility/console.h"
#include "xraster.h"
#include "incl_cpp.h"
#include <QImage>
#include <QImageReader>
#include <QImageWriter>
#include <QPainter>

//---------------------------------------------------------------------
/*XRaster_u8;
 XRaster_u8c3;
XRaster_s8;
XRaster_int16;
 XRaster_u16;
 XRaster_u32;
XRaster_int32;
XRaster_float;
 XRaster_double;
XRaster_vec2;
XRaster_vec3;
XRaster_int2;
*/

//---------------------------------------------------------------------
#define XTypeId_XRaster_type_id(TYPE_RASTER, TYPE_ID) \
template<> XTypeId TYPE_RASTER::type_id() { \
    return TYPE_ID; \
}

//template<> XTypeId XRaster_u8::type_id() {
//    return XTypeId_u8;
//}

XTypeId_XRaster_type_id(XRaster_u8, XTypeId_u8)
XTypeId_XRaster_type_id(XRaster_u8c3, XTypeId_u8c3)
XTypeId_XRaster_type_id(XRaster_s8, XTypeId_s8)
XTypeId_XRaster_type_id(XRaster_int16, XTypeId_int16)
XTypeId_XRaster_type_id(XRaster_u16, XTypeId_uint16)
XTypeId_XRaster_type_id(XRaster_int32, XTypeId_int32)
XTypeId_XRaster_type_id(XRaster_u32, XTypeId_uint32)
XTypeId_XRaster_type_id(XRaster_float, XTypeId_float)
XTypeId_XRaster_type_id(XRaster_double, XTypeId_double)
XTypeId_XRaster_type_id(XRaster_vec2, XTypeId_vec2)
XTypeId_XRaster_type_id(XRaster_vec3, XTypeId_vec3)
XTypeId_XRaster_type_id(XRaster_vec4, XTypeId_vec4)
XTypeId_XRaster_type_id(XRaster_int2, XTypeId_int2)



//---------------------------------------------------------------------
//maximal difference between two rasters at some point - used for checking if they are equal or different
template<>
float XRaster_<glm::vec2>::distance_C(XRaster_<glm::vec2> &compare_with) {
    float maxx = 0;
    for (int i=0; i<w*h; i++) {
        maxx = qMax(glm::distance2(pixel_unsafe(i), compare_with.pixel_unsafe(i)), maxx);
    }
    return qSqrt(maxx);
}

template<>
float XRaster_<glm::vec3>::distance_C(XRaster_<glm::vec3> &compare_with) {
    float maxx = 0;
    for (int i=0; i<w*h; i++) {
        maxx = qMax(glm::distance2(pixel_unsafe(i), compare_with.pixel_unsafe(i)), maxx);
    }
    return qSqrt(maxx);
}

template<>
float XRaster_<glm::vec4>::distance_C(XRaster_<glm::vec4> &compare_with) {
    float maxx = 0;
    for (int i=0; i<w*h; i++) {
        maxx = qMax(glm::distance2(pixel_unsafe(i), compare_with.pixel_unsafe(i)), maxx);
    }
    return qSqrt(maxx);
}

//---------------------------------------------------------------------
void XRaster::convert(XRaster_u8c3 &raster_rgb, XRaster_u8 &raster) {
    raster.allocate(raster_rgb.w, raster_rgb.h);
    for (int i=0; i<raster.w*raster.h; i++) {
        raster.data[i] = raster_rgb.data[i].grayi();
    }
}

//---------------------------------------------------------------------
void XRaster::convert(XRaster_u8 &raster, XRaster_u8c3 &raster_rgb) {
    raster_rgb.allocate(raster.w, raster.h);
    for (int i=0; i<raster.w*raster.h; i++) {
        raster_rgb.data[i] = rgb_u8(raster.data[i]);
    }
}

//---------------------------------------------------------------------
void XRaster::convert(QImage qimage, XRaster_u8 &raster) {
    int w = qimage.size().width();
    int h = qimage.size().height();

    auto format = qimage.format();
    xc_assert(format == QImage::Format_RGB32,
                "XObjectImage::create_from_QImage - QImage format is unsupported, only Format_RGB32 is supported");

    raster.allocate(w, h);

    int mirrory = 0;
    for (int y=0; y<h; y++) {
        const uchar *line = qimage.scanLine(mirrory?(h-1-y):y);
        int k = 0;
        for (int x=0; x<w; x++) {
            uchar b = line[k++];
            uchar g = line[k++];
            uchar r = line[k++];
            k++;
            raster.data[x+w*y] = rgb_u8::grayi(r,g,b);
        }
    }
}


//---------------------------------------------------------------------
void XRaster::convert(QImage qimage, XRaster_u8c3 &raster) {
    int w = qimage.size().width();
    int h = qimage.size().height();

    auto format = qimage.format();
    xc_assert(format == QImage::Format_RGB32,
                "XObjectImage::create_from_QImage - QImage format is unsupported, only Format_RGB32 is supported");

    raster.allocate(w, h);

    int mirrory = 0;
    for (int y=0; y<h; y++) {
        const uchar *line = qimage.scanLine(mirrory?(h-1-y):y);
        int k = 0;
        for (int x=0; x<w; x++) {
            uchar b = line[k++];
            uchar g = line[k++];
            uchar r = line[k++];
            k++;
            raster.data[x+w*y] = rgb_u8(r,g,b);
        }
    }

}

//---------------------------------------------------------------------
//TODO duplication of previous function except withing with alpha
void XRaster::convert_rgba(QImage qimage, XRaster_u8c4 &raster) {
    int w = qimage.size().width();
    int h = qimage.size().height();

    auto format = qimage.format();
    xc_assert(format == QImage::Format_RGB32,
                "XObjectImage::create_from_QImage - QImage format is unsupported, only Format_RGB32 is supported");

    raster.allocate(w, h);

    int mirrory = 0;
    for (int y=0; y<h; y++) {
        const uchar *line = qimage.scanLine(mirrory?(h-1-y):y);
        int k = 0;
        for (int x=0; x<w; x++) {
            uchar b = line[k++];
            uchar g = line[k++];
            uchar r = line[k++];
            uchar a = line[k++];
            raster.data[x+w*y] = rgba_u8(r,g,b,a);
        }
    }
}

//---------------------------------------------------------------------
//Fast, expected QImage img(w,h,QImage::Format_ARGB32);
void XRaster::convert_bgra(QImage qimage, XRaster_u8c4 &raster) {
    int w = qimage.size().width();
    int h = qimage.size().height();

    auto format = qimage.format();
    xc_assert(format == QImage::Format_RGB32,
                "XObjectImage::create_from_QImage - QImage format is unsupported, only Format_RGB32 is supported");

    raster.allocate(w, h);

    for (int y=0; y<h; y++) {
        const uchar *line = qimage.scanLine(y);
        memcpy(&(raster.data[w*y]), line, w*4);
    }
}

//---------------------------------------------------------------------
void XRaster::convert(XRaster_u8 &raster, QImage &qimage) {
    int w = raster.w;
    int h = raster.h;
    qimage = QImage(w, h, QImage::Format_RGB32);

    int mirrory = 0;
    for (int y=0; y<h; y++) {
        uchar *line = qimage.scanLine(mirrory?(h-1-y):y);
        int k = 0;
        for (int x=0; x<w; x++) {
            auto &v = raster.data[x+w*y];
            line[k+2] = v;
            line[k+1] = v;
            line[k] = v;
            line[k+3] = 255;
            k+=4;
        }
    }
}

//---------------------------------------------------------------------
void XRaster::convert(XRaster_u8c3 &raster, QImage &qimage) {
    int w = raster.w;
    int h = raster.h;
    qimage = QImage(w, h, QImage::Format_RGB32);

    int mirrory = 0;
    for (int y=0; y<h; y++) {
        uchar *line = qimage.scanLine(mirrory?(h-1-y):y);
        int k = 0;
        for (int x=0; x<w; x++) {
            auto &v = raster.data[x+w*y];
            line[k+2] = v.v[0];
            line[k+1] = v.v[1];
            line[k] = v.v[2];
            line[k+3] = 255;
            k+=4;
        }
    }
}

//---------------------------------------------------------------------
QImage XRaster::link(XRaster_u8 &raster) {
    int w = raster.w;
    int h = raster.h;
    return QImage(raster.data_pointer_u8(), w, h, raster.bytesPerLine(), QImage::Format_Grayscale8);

}

//---------------------------------------------------------------------
QImage XRaster::link(XRaster_u8c3 &raster) {
    int w = raster.w;
    int h = raster.h;
    return QImage(raster.data_pointer_u8(), w, h, raster.bytesPerLine(), QImage::Format_RGB888);
}

//---------------------------------------------------------------------
void XRaster::load(QString file_name, XRaster_u8 &raster) {
    QImage qimage;
    xc_assert(qimage.load(file_name), "load: Can't load image '" + file_name + "'");
    convert(qimage, raster);
}

//---------------------------------------------------------------------
void XRaster::load(QString file_name, XRaster_u8c3 &raster) {
    QImage qimage;
    xc_assert(qimage.load(file_name), "load: Can't load image '" + file_name + "'");
    convert(qimage, raster);
}

//-----------------------------------------------------------------------------------
void XRaster::save(XRaster_u8 &raster, QString file_name, QString format, int quality) {
    xc_assert(!raster.is_empty(), "Error saving image, because raster is empty: '" + file_name + "' ");
    QImage qimage;
    convert(raster, qimage);
    xc_assert(qimage.save(file_name, format.toStdString().c_str(), quality),
                "save: Can't save image '" + file_name + "'");
}

//-----------------------------------------------------------------------------------
void XRaster::save(XRaster_u8c3 &raster, QString file_name, QString format, int quality) {
    xc_assert(!raster.is_empty(), "Error saving image, because raster is empty: '" + file_name + "' ");
    QImage qimage;
    convert(raster, qimage);
    xc_assert(qimage.save(file_name, format.toStdString().c_str(), quality),
                "save: Can't save image '" + file_name + "'");
}

//-----------------------------------------------------------------------------------
