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
    static void convert(const XRaster& source, XRaster& destination, XTypeId destination_type);

    static void convert(QImage qimage, XRaster &raster,
                        XTypeId force_type = XTypeId::none, // if type not specified - set from qimage
                        RGBA_Bytes_Order order = RGBA_Bytes_Order::RGBA);
    static void convert(const XRaster& raster, QImage &qimage);

    // Link - create image without copying pixels raster
    // Much faster than `convert`, but requires care
    static QImage link_qimage(const XRaster& raster);

    //Save and load
    static void load(XRaster& raster, QString file_name);
    static void save(const XRaster& raster, QString file_name, int quality = 90);
    static void save(const XRaster* raster, QString file_name, int quality = 90);

    // Draw raster on painter
    static void draw(QPainter& painter, const XRaster& raster, int x, int y, int w, int h);
    static void draw(QPainter& painter, const XRaster& raster, int x, int y);
    static void draw(QPainter& painter, const XRaster& raster, int x, int y, int sx, int sy, int sw, int sh);
    static void draw(QPainter& painter, const XRaster& raster, const QRectF &r);
    static void draw(QPainter& painter, const XRaster& raster, const QRectF &targetRect, const QRectF &sourceRect);
    static void draw(QPainter& painter, const XRaster& raster, const QRect &targetRect, const QRect &sourceRect);
    static void draw(QPainter& painter, const XRaster& raster, const QPointF &p, const QRectF &sr);
    static void draw(QPainter& painter, const XRaster& raster, const QPoint &p, const QRect &sr);
    static void draw(QPainter& painter, const XRaster& raster, const QRect &r);
    static void draw(QPainter& painter, const XRaster& raster, const QPointF &p);
    static void draw(QPainter& painter, const XRaster& raster, const QPoint &p);

    //Resize
    static void resize_nearest(const XRaster& input, XRaster& output, int new_w, int new_h);
    static void resize_nearest(XRaster& input, XRaster& output, float scale);

    // Blur
    // Works in-place too.
    // Note: not very optimal implementation, but made on pure Qt. For better performance, use OpenCV.
    static void blur(XRaster& raster, XRaster& result, float blur_radius);
};
