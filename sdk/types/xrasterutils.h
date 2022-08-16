#pragma once
//--------------------------------------------------
// XRasterUtils
// Operations on XRaster inclusing save, load, convert
//--------------------------------------------------

#include "incl_h.h"

#include <QImage>
//class QPainter;
#include <QPainter>

#include "xraster.h"


class XRasterUtils {
public:
    //Convert - copies data
    static void convert(XRaster_u8c3 &raster_rgb, XRaster_u8 &raster);
    static void convert(XRaster_u8 &raster, XRaster_u8c3 &raster_rgb);

    static void convert(QImage qimage, XRaster_u8 &raster);
    static void convert(QImage qimage, XRaster_u8c3 &raster);
    static void convert_rgba(QImage qimage, XRaster_u8c4 &raster);
    static void convert_bgra(QImage qimage, XRaster_u8c4 &raster);  //Fast, expected QImage img(w,h,QImage::Format_ARGB32);
    static void convert(XRaster_u8 &raster, QImage &qimage);
    static void convert(XRaster_u8c3 &raster, QImage &qimage);

    //Link - create image without copying pixels raster
    //Much faster than `convert`, but requires care
    static QImage link(const XRaster* raster);

    //save and load
    //TODO currently for disk operations QImage is used - but faster to use OpenCV, FreeImage or TurboJpeg
    static void load(QString file_name, XRaster_u8 &raster);
    static void load(QString file_name, XRaster_u8c3 &raster);
    static void save(XRaster_u8 &raster, QString file_name, QString format, int quality = 90);
    static void save(XRaster_u8c3 &raster, QString file_name, QString format, int quality = 90);

    //Draw raster on painter
    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, int x, int y, int sx = 0, int sy = 0, int sw = -1, int sh = -1) {
        painter->drawImage(x, y, link(raster), sx, sy, sw, sh);
    }

    //draw to a given rectangle
    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QRectF &r) {
        painter->drawImage(r, link(raster));
    }

    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QRectF &targetRect, const QRectF &sourceRect) {
        painter->drawImage(targetRect, link(raster), sourceRect);
    }

    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QRect &targetRect, const QRect &sourceRect) {
        painter->drawImage(targetRect, link(raster), sourceRect);
    }

    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QPointF &p, const QRectF &sr) {
        painter->drawImage(p, link(raster), sr);
    }

    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QPoint &p, const QRect &sr) {
        painter->drawImage(p, link(raster), sr);
    }

    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QRect &r) {
        painter->drawImage(r, link(raster));
    }

    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QPointF &p) {
        painter->drawImage(p, link(raster));
    }

    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QPoint &p) {
        painter->drawImage(p, link(raster));
    }

    //Resize
    template<typename T>
    static void resize_nearest(XRaster_<T> &input, XRaster_<T> &output, int new_w, int new_h) {
        int w = input.w;
        int h = input.h;
        xc_assert(input.data_pointer() != output.data_pointer(), "resize_nearest, input and output must be different images");
        xc_assert(w > 0 && h > 0, "resize_nearest error, input image must have positive size");
        xc_assert(new_w > 0 && new_h > 0, "resize_nearest error, resized image must have positive size");
        output.allocate(new_w, new_h);
        for (int y=0; y<new_h; y++) {
            for (int x=0; x<new_w; x++) {
                output.pixel_unsafe(x, y) = input.pixel_unsafe(x * w / new_w, y * h / new_h);
            }
        }
    }

    template<typename T>
    static void resize_nearest(XRaster_<T> &input, XRaster_<T> &output, float scale) {
        int new_w = int(input.w * scale);
        int new_h = int(input.h * scale);
        resize_nearest(input, output, new_w, new_h);
    }

    //blur
    //Works in-place!
    //Note: not very optimal implementation, but made on pure Qt. For better performance, use OpenCV.
    template<typename T>
    static void blur(XRaster_<T> &raster, XRaster_<T> &result, float blur_radius) {
        xc_assert(!raster.is_empty(), "XRaster::blur - input raster is empty");
        xc_assert(blur_radius>=0, "XRaster::blur - blur radius must be non-negative");
        QImage img;
        convert(raster, img);
        img = XImageEffect::blur(img, blur_radius);
        convert(img, result);
    }


};
