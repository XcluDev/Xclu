#include "xdrawhelper.h"

#include "incl_cpp.h"
#include <QImage>
#include <QPainter>
#include <xobjectimage.h>


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
void XDrawHelper::draw_QImage_fit(QImage &qimage, float posx_u, float posy_u, float size_u, QPainter &painter, int w, int h) {
    if (qimage.isNull()) {
        return;
    }
    painter.drawImage(fit_rect(qimage.width(), qimage.height(), posx_u, posy_u, size_u, w, h),
                      qimage);

}

//---------------------------------------------------------------------
void XDrawHelper::draw_XObject_fit(const XObject* object, float posx_u, float posy_u, float size_u, QPainter &painter, int w, int h) {
    xc_assert(object, "XDrawHelper::draw_XObject_fit - null object");
    QImage qimage;
    XObjectImage::link_to_QImage(*object,qimage);
    draw_QImage_fit(qimage, posx_u, posy_u, size_u, painter, w, h);
}

//---------------------------------------------------------------------
