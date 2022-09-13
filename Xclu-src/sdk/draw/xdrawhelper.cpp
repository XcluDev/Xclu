#include "xdrawhelper.h"

#include "incl_cpp.h"
#include <QImage>
#include <QPainter>
#include "xobjectvis.h"
#include "xrasterutils.h"


//---------------------------------------------------------------------
// Put given, say, image with size areaw x areah to a screen w x h, at relative position posx_u, posy_u and scale size_u,
// size_u = 1 means fit image by size.
// Used for draw images and other rectangular areas to RenderArea.
QRectF XDrawHelper::fit_rect(float areaw, float areah, float posx_u, float posy_u, float size_u, float w, float h) {
    if (areaw <= 0 || areah <= 0) {
        return QRectF(0,0,0,0);
    }

    float scl = qMin(w / areaw, h / areah) * size_u;
    return QRectF(posx_u * w, posy_u * h, areaw * scl, areah * scl);
}

//---------------------------------------------------------------------
QRectF XDrawHelper::draw_QImage_fit(QImage &qimage, float posx_u, float posy_u, float size_u, QPainter &painter, int w, int h) {
    if (qimage.isNull()) {
        return QRectF();
    }
    QRectF rect = fit_rect(qimage.width(), qimage.height(), posx_u, posy_u, size_u, w, h);
    painter.drawImage(rect, qimage);
    return rect;

}

//---------------------------------------------------------------------
QRectF XDrawHelper::draw_XObject_fit(const XObject* object, float posx_u, float posy_u, float size_u, QPainter &painter, int w, int h) {
    xc_assert(object, "XDrawHelper::draw_XObject_fit - null object");
    object->assert_type(XType::XRaster);
    const XRaster* raster = object->data<XRaster>();
    if (!raster) {
        return QRectF(0,0,0,0);
    }
    QRectF rect = fit_rect(raster->w, raster->h, posx_u, posy_u, size_u, w, h);
    XRasterUtils::draw(painter, *raster, rect);
    return rect;
}

//---------------------------------------------------------------------
