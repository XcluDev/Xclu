#include "./../utility/xerrorhandling.h"
#include "xrasterutils.h"
#include "incl_cpp.h"
#include <QImage>
#include <QImageReader>
#include <QImageWriter>
#include <QPainter>

//---------------------------------------------------------------------
// TODO Implement converting all to all types by adding second version for code_for_all_XTypeId at types.h scanning T2
// and using this macroses nested
void XRasterUtils::convert(const XRaster& source, XRaster& destination, XTypeId destination_type) {
    destination.allocate(source.w, source.h, destination_type);
    if (source.type_id == XTypeId::rgb_u8 && destination_type == XTypeId::uint8) {
        const rgb_u8* data1 = (const rgb_u8*)source.data_pointer();
        uint8* data2 = (uint8*)destination.data_pointer();
        for (int i=0; i<source.n; i++) {
            data2[i] = data1[i].grayi();
        }
        return;
    }
    if (source.type_id == XTypeId::uint8 && destination_type == XTypeId::rgb_u8) {
        const uint8* data1 = (const uint8*)source.data_pointer();
        rgb_u8* data2 = (rgb_u8*)destination.data_pointer();
        for (int i=0; i<source.n; i++) {
            data2[i] = rgb_u8(data1[i]);
        }
        return;
    }
    xc_exception(QString("XRasterUtils::convert - unsupported conversion types %1 -> %2")
                 .arg(XTypeId_to_string(source.type_id))
                 .arg(XTypeId_to_string(destination_type)));
}

//---------------------------------------------------------------------
void XRasterUtils::convert(QImage qimage, XRaster &raster,
                           XTypeId type,    // if type not specified - set from qimage
                           RGBA_Bytes_Order order) {
    int w = qimage.size().width();
    int h = qimage.size().height();

    auto format = qimage.format();
    xc_assert(format == QImage::Format_RGB32,
                "XRasterUtils::convert - QImage format is unsupported, only Format_RGB32 is supported");

    if (type == XTypeId::none) {
        if (format == QImage::Format_RGB32) {
            type = XTypeId::rgba_u8;
        }
    }
    xc_assert(type != XTypeId::none, "XRasterUtils::convert - internal error, invalid type");

    raster.allocate(w, h, type);

    void *data = raster.data_pointer();

    for (int y=0; y<h; y++) {
        const uchar *line = qimage.scanLine(y);
        int k = 0;
        for (int x=0; x<w; x++) {
            uchar b = line[k++];
            uchar g = line[k++];
            uchar r = line[k++];
            uchar a = line[k++];
            // TODO need to implement separately to optimize (unroll etc)
            switch (type) {
            case XTypeId::uint8:
                ((uint*)data)[x+w*y] = rgb_u8::grayi(r,g,b);
                break;
            case XTypeId::rgb_u8:
                ((rgb_u8*)data)[x+w*y] = rgb_u8(r,g,b);
                break;
            case XTypeId::rgba_u8:
                switch (order) {
                case RGBA_Bytes_Order::RGBA:
                    ((rgba_u8*)data)[x+w*y] = rgba_u8(r,g,b,a);
                    break;
                case RGBA_Bytes_Order::BGRA:
                    ((rgba_u8*)data)[x+w*y] = rgba_u8(b,g,r,a);
                    // TODO can use memcpy(&(raster_data[w*y]), line, w*4) to copy whole line
                    break;
                default:
                    xc_exception("XRasterUtils::convert - bad RGBA_Bytes_Order value");
                }
                break;
            default:
                xc_exception(QString("XRasterUtils::convert - unsupported type %1")
                             .arg(XTypeId_to_string(type)));
            }
        }
    }
}


//---------------------------------------------------------------------
void XRasterUtils::convert(const XRaster& raster, QImage &qimage) {
    xc_assert(!raster.is_empty(), "XRasterUtils::convert - empty raster");
    int w = raster.w;
    int h = raster.h;
    switch (raster.type_id)
    {
    case XTypeId::uint8:
    {
        qimage = QImage(w, h, QImage::Format_RGB32);
        auto *raster_data = (const uint8*)raster.data_pointer();
        for (int y=0; y<h; y++) {
            uchar *line = qimage.scanLine(y);
            int k = 0;
            for (int x=0; x<w; x++) {
                auto &v = raster_data[x+w*y];
                line[k+2] = v;
                line[k+1] = v;
                line[k] = v;
                line[k+3] = 255;
                k+=4;
            }
        }
        break;
    }
    case XTypeId::rgb_u8:
    {
        qimage = QImage(w, h, QImage::Format_RGB32);
        auto *raster_data = (rgb_u8*)raster.data_pointer();
        for (int y=0; y<h; y++) {
            uchar *line = qimage.scanLine(y);
            int k = 0;
            for (int x=0; x<w; x++) {
                auto &v = raster_data[x+w*y];
                line[k+2] = v.v[0];
                line[k+1] = v.v[1];
                line[k] = v.v[2];
                line[k+3] = 255;
                k+=4;
            }
        }
        break;
    }
    default:
        xc_exception(QString("XRasterUtils::convert - raster type %1 not supported")
                     .arg(XTypeId_to_string(raster.type_id)));
    }
}

//---------------------------------------------------------------------
QImage XRasterUtils::link_qimage(const XRaster& raster) {
    QImage::Format format = QImage::Format_Invalid;
    switch (raster.type_id)
    {
    case XTypeId::uint8: format = QImage::Format_Grayscale8;
        break;
    case XTypeId::rgb_u8: format = QImage::Format_RGB888;
        break;
    default:
        xc_exception("XRasterUtils::link_qimage - unsupported format");
    }

    return QImage((const unsigned char*)raster.data_pointer(),
                  raster.w, raster.h, raster.bytes_per_line(), format);
}

//---------------------------------------------------------------------
void XRasterUtils::load(QString file_name, XRaster& raster) {
    QImage qimage;
    xc_assert(qimage.load(file_name), "XRasterUtils::load: Can't load image '" + file_name + "'");
    convert(qimage, raster);
}

//-----------------------------------------------------------------------------------
void XRasterUtils::save(XRaster& raster, QString file_name, QString file_format, int quality) {
    xc_assert(!raster.is_empty(), "Error saving image, because raster is empty: '" + file_name + "' ");
    QImage qimage = link_qimage(raster);
    xc_assert(qimage.save(file_name, file_format.toStdString().c_str(), quality),
                "save: Can't save image '" + file_name + "'");
}

//-----------------------------------------------------------------------------------
void XRasterUtils::draw(QPainter& painter, const XRaster& raster, int x, int y, int w, int h) {
    draw(painter, raster, QRect(x, y, w, h));
}
void XRasterUtils::draw(QPainter& painter, const XRaster& raster, int x, int y) {
    draw(painter, raster, QPoint(x, y));
}
void XRasterUtils::draw(QPainter& painter, const XRaster& raster, int x, int y, int sx, int sy, int sw, int sh) {
    painter.drawImage(x, y, link_qimage(raster), sx, sy, sw, sh);
}
void XRasterUtils::draw(QPainter& painter, const XRaster& raster, const QRectF &r) {
    painter.drawImage(r, link_qimage(raster));
}
void XRasterUtils::draw(QPainter& painter, const XRaster& raster, const QRectF &targetRect, const QRectF &sourceRect) {
    painter.drawImage(targetRect, link_qimage(raster), sourceRect);
}
void XRasterUtils::draw(QPainter& painter, const XRaster& raster, const QRect &targetRect, const QRect &sourceRect) {
    painter.drawImage(targetRect, link_qimage(raster), sourceRect);
}
void XRasterUtils::draw(QPainter& painter, const XRaster& raster, const QPointF &p, const QRectF &sr) {
    painter.drawImage(p, link_qimage(raster), sr);
}
void XRasterUtils::draw(QPainter& painter, const XRaster& raster, const QPoint &p, const QRect &sr) {
    painter.drawImage(p, link_qimage(raster), sr);
}
void XRasterUtils::draw(QPainter& painter, const XRaster& raster, const QRect &r) {
    painter.drawImage(r, link_qimage(raster));
}
void XRasterUtils::draw(QPainter& painter, const XRaster& raster, const QPointF &p) {
    painter.drawImage(p, link_qimage(raster));
}
void XRasterUtils::draw(QPainter& painter, const XRaster& raster, const QPoint &p) {
    painter.drawImage(p, link_qimage(raster));
}

//-----------------------------------------------------------------------------------
//Resize
void XRasterUtils::resize_nearest(const XRaster& input, XRaster& output, int new_w, int new_h) {
    int w = input.w;
    int h = input.h;
    xc_assert(input.data_pointer() != output.data_pointer(), "resize_nearest, input and output must be different images");
    xc_assert(w > 0 && h > 0, "resize_nearest error, input image must have positive size");
    xc_assert(new_w > 0 && new_h > 0, "resize_nearest error, resized image must have positive size");
    output.allocate(new_w, new_h, input.type_id);
    for (int y=0; y<new_h; y++) {
        for (int x=0; x<new_w; x++) {
            output.set_pixel_unsafe<void*>(x, y, input.pixel_unsafe<void*>(x * w / new_w, y * h / new_h));
        }
    }
}

//-----------------------------------------------------------------------------------
void XRasterUtils::resize_nearest(XRaster& input, XRaster& output, float scale) {
    int new_w = int(input.w * scale);
    int new_h = int(input.h * scale);
    resize_nearest(input, output, new_w, new_h);
}

//-----------------------------------------------------------------------------------
// Blur
// Works in-place too.
// Note: not very optimal implementation, but made on pure Qt. For better performance, use OpenCV.
void XRasterUtils::blur(XRaster& raster, XRaster& result, float blur_radius) {
    xc_assert(!raster.is_empty(), "XRaster::blur - input raster is empty");
    xc_assert(blur_radius>=0, "XRaster::blur - blur radius must be non-negative");
    QImage img;
    convert(raster, img);
    img = XImageEffect::blur(img, blur_radius);
    convert(img, result);
}

//-----------------------------------------------------------------------------------
