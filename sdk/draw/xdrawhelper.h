#ifndef XDRAWHELPER_H
#define XDRAWHELPER_H

// Drawing helper functions for ourout to RenderArea
#include "sdk_h.h"
#include "xobject.h"

class QImage;
class QPainter;

class XDrawHelper {
public:
    // Put given, say, image with size areaw x areah to a screen w x h, at relative position posx_u, posy_u and scale size_u,
    // size_u = 1 means fit image by size.
    // Used for draw images and other rectangular areas to RenderArea.
    static QRectF fit_rect(float areaw, float areah, float posx_u, float posy_u, float size_u, float w, float h);

    static QRectF draw_QImage_fit(QImage &qimage, float posx_u, float posy_u, float size_u, QPainter &painter, int w, int h);

    // draw_XObject_fit() draws object, it it's image
    // Usage:
    // auto image_read = getobject_image()->read();
    // const XObject *object = image_read.pointer();
    // XDrawHelper::draw_XObject_fit(...);

    static QRectF draw_XObject_fit(const XObject* object, float posx_u, float posy_u, float size_u, QPainter &painter, int w, int h);

};


#endif // XDRAWHELPER_H
