#pragma once
//--------------------------------------------------
// XRasterUtils
// Operations on XRaster inclusing save, load, convert
//--------------------------------------------------

#include "incl_h.h"

#include "xraster.h"
#include <QImage>
#include <QPainter>
#include "ximageeffect.h"


class XRasterUtils {
public:
    enum class RGBA_Bytes_Order: int
    {
        RGBA = 0,
        BGRA = 1
    };

    // Convert - copies data
    static void convert(XRaster_u8c3 &raster_rgb, XRaster_u8 &raster);
    static void convert(XRaster_u8 &raster, XRaster_u8c3 &raster_rgb);

    static void convert(QImage qimage, XRaster_u8 &raster);
    static void convert(QImage qimage, XRaster_u8c3 &raster);
    static void convert(QImage qimage, XRaster_u8c4 &raster, RGBA_Bytes_Order order);

    static void convert(XRaster *raster, QImage &qimage);

    // Link - create image without copying pixels raster
    // Much faster than `convert`, but requires care
    static QImage link_qimage(const XRaster* raster);

    //Save and load
    static void load(QString file_name, XRaster_u8 &raster);
    static void load(QString file_name, XRaster_u8c3 &raster);
    static void save(XRaster* raster, QString file_name, QString file_format, int quality = 90);

    // Draw raster on painter
    static void draw(QPainter *painter, XRaster *raster, int x, int y, int w, int h);
    static void draw(QPainter *painter, XRaster *raster, int x, int y);
    static void draw(QPainter *painter, XRaster *raster, int x, int y, int sx, int sy, int sw, int sh);
    static void draw(QPainter *painter, XRaster *raster, const QRectF &r);
    static void draw(QPainter *painter, XRaster *raster, const QRectF &targetRect, const QRectF &sourceRect);
    static void draw(QPainter *painter, XRaster *raster, const QRect &targetRect, const QRect &sourceRect);
    static void draw(QPainter *painter, XRaster *raster, const QPointF &p, const QRectF &sr);
    static void draw(QPainter *painter, XRaster *raster, const QPoint &p, const QRect &sr);
    static void draw(QPainter *painter, XRaster *raster, const QRect &r);
    static void draw(QPainter *painter, XRaster *raster, const QPointF &p);
    static void draw(QPainter *painter, XRaster *raster, const QPoint &p);

    //Resize
    static void resize_nearest(XRaster &input, XRaster &output, int new_w, int new_h) {
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

    static void resize_nearest(XRaster &input, XRaster &output, float scale) {
        int new_w = int(input.w * scale);
        int new_h = int(input.h * scale);
        resize_nearest(input, output, new_w, new_h);
    }

    // Blur
    // Works in-place!
    // Note: not very optimal implementation, but made on pure Qt. For better performance, use OpenCV.
    static void blur(XRaster &raster, XRaster &result, float blur_radius) {
        xc_assert(!raster.is_empty(), "XRaster::blur - input raster is empty");
        xc_assert(blur_radius>=0, "XRaster::blur - blur radius must be non-negative");
        QImage img;
        convert(raster, img);
        img = XImageEffect::blur(img, blur_radius);
        convert(img, result);
    }


};
