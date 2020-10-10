#include "xraster.h"
#include "incl_cpp.h"
#include <QImage>
#include <QImageReader>
#include <QImageWriter>

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
XTypeId_XRaster_type_id(XRaster_u16, XTypeId_u16)
XTypeId_XRaster_type_id(XRaster_int32, XTypeId_int32)
XTypeId_XRaster_type_id(XRaster_u32, XTypeId_u32)
XTypeId_XRaster_type_id(XRaster_float, XTypeId_float)
XTypeId_XRaster_type_id(XRaster_double, XTypeId_double)
XTypeId_XRaster_type_id(XRaster_vec2, XTypeId_vec2)
XTypeId_XRaster_type_id(XRaster_vec3, XTypeId_vec3)
XTypeId_XRaster_type_id(XRaster_int2, XTypeId_int2)


//---------------------------------------------------------------------
void raster_to_raster(XRaster_u8c3 &raster_rgb, XRaster_u8 &raster) {
    raster.allocate(raster_rgb.w, raster_rgb.h);
    for (int i=0; i<raster.w*raster.h; i++) {
        raster.data[i] = raster_rgb.data[i].gray();
    }
}

//---------------------------------------------------------------------
void raster_to_raster(XRaster_u8 &raster, XRaster_u8c3 &raster_rgb) {
    raster_rgb.allocate(raster.w, raster.h);
    for (int i=0; i<raster.w*raster.h; i++) {
        raster_rgb.data[i] = u8_rgb(raster.data[i]);
    }
}

//---------------------------------------------------------------------
void XRaster::convert(QImage qimage, XRaster_u8 &raster) {
    int w = qimage.size().width();
    int h = qimage.size().height();

    auto format = qimage.format();
    xclu_assert(format == QImage::Format_RGB32,
                "XStructImage::create_from_QImage - QImage format is unsupported, only Format_RGB32 is supported");

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
            raster.data[x+w*y] = u8_rgb::gray(r,g,b);
        }
    }
}


//---------------------------------------------------------------------
void XRaster::convert(QImage qimage, XRaster_u8c3 &raster) {
    int w = qimage.size().width();
    int h = qimage.size().height();

    auto format = qimage.format();
    xclu_assert(format == QImage::Format_RGB32,
                "XStructImage::create_from_QImage - QImage format is unsupported, only Format_RGB32 is supported");

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
            raster.data[x+w*y] = u8_rgb(r,g,b);
        }
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
void XRaster::load(QString file_name, XRaster_u8 &raster) {
    QImage qimage;
    xclu_assert(qimage.load(file_name), "load: Can't load image '" + file_name + "'");
    convert(qimage, raster);
}

//---------------------------------------------------------------------
void XRaster::load(QString file_name, XRaster_u8c3 &raster) {
    QImage qimage;
    xclu_assert(qimage.load(file_name), "load: Can't load image '" + file_name + "'");
    convert(qimage, raster);
}

//-----------------------------------------------------------------------------------
void XRaster::save(XRaster_u8 &raster, QString file_name, QString format, int quality) {
    QImage qimage;
    convert(raster, qimage);
    xclu_assert(qimage.save(file_name, format.toStdString().c_str(), quality),
                "save: Can't save image '" + file_name + "'");
}

//-----------------------------------------------------------------------------------
void XRaster::save(XRaster_u8c3 &raster, QString file_name, QString format, int quality) {
    QImage qimage;
    convert(raster, qimage);
    xclu_assert(qimage.save(file_name, format.toStdString().c_str(), quality),
                "save: Can't save image '" + file_name + "'");
}

//-----------------------------------------------------------------------------------
