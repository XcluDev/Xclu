#include "./../utility/console.h"
#include "xrasterutils.h"
#include "incl_cpp.h"
#include <QImage>
#include <QImageReader>
#include <QImageWriter>
#include <QPainter>

//---------------------------------------------------------------------
void XRasterUtils::convert(XRaster_u8c3 &raster_rgb, XRaster_u8 &raster) {
    raster.allocate(raster_rgb.w, raster_rgb.h);
    auto *raster_data = raster.typed_data_pointer();
    auto *raster_rgb_data = raster_rgb.typed_data_pointer();
    for (int i=0; i<raster.w*raster.h; i++) {
        raster_data[i] = raster_rgb_data[i].grayi();
    }
}

//---------------------------------------------------------------------
void XRasterUtils::convert(XRaster_u8 &raster, XRaster_u8c3 &raster_rgb) {
    raster_rgb.allocate(raster.w, raster.h);
    auto *raster_data = raster.typed_data_pointer();
    auto *raster_rgb_data = raster_rgb.typed_data_pointer();
    for (int i=0; i<raster.w*raster.h; i++) {
        raster_rgb_data[i] = rgb_u8(raster_data[i]);
    }
}

//---------------------------------------------------------------------
void XRasterUtils::convert(QImage qimage, XRaster_u8 &raster) {
    int w = qimage.size().width();
    int h = qimage.size().height();

    auto format = qimage.format();
    xc_assert(format == QImage::Format_RGB32,
                "XObjectImage::create_from_QImage - QImage format is unsupported, only Format_RGB32 is supported");

    raster.allocate(w, h);

    auto *raster_data = raster.typed_data_pointer();

    int mirrory = 0;
    for (int y=0; y<h; y++) {
        const uchar *line = qimage.scanLine(mirrory?(h-1-y):y);
        int k = 0;
        for (int x=0; x<w; x++) {
            uchar b = line[k++];
            uchar g = line[k++];
            uchar r = line[k++];
            k++;
            raster_data[x+w*y] = rgb_u8::grayi(r,g,b);
        }
    }
}


//---------------------------------------------------------------------
void XRasterUtils::convert(QImage qimage, XRaster_u8c3 &raster) {
    int w = qimage.size().width();
    int h = qimage.size().height();

    auto format = qimage.format();
    xc_assert(format == QImage::Format_RGB32,
                "XObjectImage::create_from_QImage - QImage format is unsupported, only Format_RGB32 is supported");

    raster.allocate(w, h);
    auto *raster_data = raster.typed_data_pointer();

    int mirrory = 0;
    for (int y=0; y<h; y++) {
        const uchar *line = qimage.scanLine(mirrory?(h-1-y):y);
        int k = 0;
        for (int x=0; x<w; x++) {
            uchar b = line[k++];
            uchar g = line[k++];
            uchar r = line[k++];
            k++;
            raster_data[x+w*y] = rgb_u8(r,g,b);
        }
    }

}

//---------------------------------------------------------------------
void XRasterUtils::convert(QImage qimage, XRaster_u8c4 &raster, RGBA_Bytes_Order order) {
    int w = qimage.size().width();
    int h = qimage.size().height();

    auto format = qimage.format();
    xc_assert(format == QImage::Format_RGB32,
                "XRasterUtils::convert - QImage format is unsupported, only Format_RGB32 is supported");

    raster.allocate(w, h);
    auto *raster_data = raster.typed_data_pointer();

    switch (order)
    {
    case RGBA_Bytes_Order::RGBA:
    {
        int mirrory = 0;
        for (int y=0; y<h; y++) {
            const uchar *line = qimage.scanLine(mirrory?(h-1-y):y);
            int k = 0;
            for (int x=0; x<w; x++) {
                uchar b = line[k++];
                uchar g = line[k++];
                uchar r = line[k++];
                uchar a = line[k++];
                raster_data[x+w*y] = rgba_u8(r,g,b,a);
            }
        }
        break;
    }
    case RGBA_Bytes_Order::BGRA:
    {
        for (int y=0; y<h; y++) {
            const uchar *line = qimage.scanLine(y);
            memcpy(&(raster_data[w*y]), line, w*4);
        }
        break;
    }
    default:
        xc_exception("XRasterUtils::convert - bad bytes order specified");
    }
}


//---------------------------------------------------------------------
void XRasterUtils::convert(XRaster* raster, QImage &qimage) {
    xc_assert(raster, "XRasterUtils::convert - empty raster");
    int w = raster->w;
    int h = raster->h;
    switch (raster->type_id)
    {
    case XTypeId::u8:
    {
        qimage = QImage(w, h, QImage::Format_RGB32);
        auto *raster_data = (uint8*)raster->data_pointer();
        int mirrory = 0;
        for (int y=0; y<h; y++) {
            uchar *line = qimage.scanLine(mirrory?(h-1-y):y);
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
    case XTypeId::u8c3:
    {
        qimage = QImage(w, h, QImage::Format_RGB32);
        auto *raster_data = (rgb_u8*)raster->data_pointer();
        int mirrory = 0;
        for (int y=0; y<h; y++) {
            uchar *line = qimage.scanLine(mirrory?(h-1-y):y);
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
        xc_exception("XRasterUtils::convert - raster type not supported");
    }
}

//---------------------------------------------------------------------
QImage XRasterUtils::link(const XRaster* raster) {
    xc_assert(raster, "XRasterUtils::link - null raster");
    QImage::Format format = QImage::Format_Invalid;
    switch (raster->type_id)
    {
    case XTypeId::u8: format = QImage::Format_Grayscale8;
        break;
    case XTypeId::u8c3: format = QImage::Format_RGB888;
        break;
    default:
        xc_exception("XRasterUtils::link - unsupported format");
    }

    return QImage((const unsigned char*)raster->data_pointer(),
                  raster->w, raster->h, raster->bytes_per_line(), format);
}

//---------------------------------------------------------------------
void XRasterUtils::load(QString file_name, XRaster_u8 &raster) {
    QImage qimage;
    xc_assert(qimage.load(file_name), "load: Can't load image '" + file_name + "'");
    convert(qimage, raster);
}

//---------------------------------------------------------------------
void XRasterUtils::load(QString file_name, XRaster_u8c3 &raster) {
    QImage qimage;
    xc_assert(qimage.load(file_name), "load: Can't load image '" + file_name + "'");
    convert(qimage, raster);
}

//-----------------------------------------------------------------------------------
void XRasterUtils::save(XRaster* raster, QString file_name, QString file_format, int quality) {
    xc_assert(raster, "XRasterUtils::save - empty raster");
    xc_assert(!raster->is_empty(), "Error saving image, because raster is empty: '" + file_name + "' ");
    QImage qimage = link(raster);
    xc_assert(qimage.save(file_name, file_format.toStdString().c_str(), quality),
                "save: Can't save image '" + file_name + "'");
}

//-----------------------------------------------------------------------------------
void XRasterUtils::draw(QPainter *painter, XRaster *raster, int x, int y, int w, int h) {
    draw(painter, raster, QRect(x, y, w, h));
}
void XRasterUtils::draw(QPainter *painter, XRaster *raster, int x, int y) {
    draw(painter, raster, QPoint(x, y));
}
void XRasterUtils::draw(QPainter *painter, XRaster *raster, int x, int y, int sx, int sy, int sw, int sh) {
    painter->drawImage(x, y, link(raster), sx, sy, sw, sh);
}
void XRasterUtils::draw(QPainter *painter, XRaster *raster, const QRectF &r) {
    painter->drawImage(r, link(raster));
}
void XRasterUtils::draw(QPainter *painter, XRaster *raster, const QRectF &targetRect, const QRectF &sourceRect) {
    painter->drawImage(targetRect, link(raster), sourceRect);
}
void XRasterUtils::draw(QPainter *painter, XRaster *raster, const QRect &targetRect, const QRect &sourceRect) {
    painter->drawImage(targetRect, link(raster), sourceRect);
}
void XRasterUtils::draw(QPainter *painter, XRaster *raster, const QPointF &p, const QRectF &sr) {
    painter->drawImage(p, link(raster), sr);
}
void XRasterUtils::draw(QPainter *painter, XRaster *raster, const QPoint &p, const QRect &sr) {
    painter->drawImage(p, link(raster), sr);
}
void XRasterUtils::draw(QPainter *painter, XRaster *raster, const QRect &r) {
    painter->drawImage(r, link(raster));
}
void XRasterUtils::draw(QPainter *painter, XRaster *raster, const QPointF &p) {
    painter->drawImage(p, link(raster));
}
void XRasterUtils::draw(QPainter *painter, XRaster *raster, const QPoint &p) {
    painter->drawImage(p, link(raster));
}

//-----------------------------------------------------------------------------------
