#include "ximageeffect.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QScopedPointer>

//---------------------------------------------------------------------
XImageEffect::XImageEffect()
{

}

//---------------------------------------------------------------------
//Note: effect_will_destroyed will be destroyed because binding to image in implementation

QImage XImageEffect::apply_effect(QImage src, QGraphicsEffect *effect_will_destroyed, int extent)
{
    QGraphicsEffect *effect = effect_will_destroyed;

    if (src.isNull()) {
        delete effect_will_destroyed;
        return QImage();   //No need to do anything else!
    }
    if (!effect) {
        delete effect_will_destroyed;
        return src;             //No need to do anything else!
    }
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(src));
    item.setGraphicsEffect(effect);     //this cause destroying effect after item releasing in the function end
    scene.addItem(&item);
    QImage res(src.size()+QSize(extent*2, extent*2), src.format()); //QImage::Format_ARGB32);
    res.fill(Qt::transparent);
    QPainter ptr(&res);
    scene.render(&ptr, QRectF(), QRectF( -extent, -extent, src.width()+extent*2, src.height()+extent*2 ) );
    return res;
}

//---------------------------------------------------------------------
QImage XImageEffect::blur(QImage src, float blur_radius) {
    QGraphicsBlurEffect *eff = new QGraphicsBlurEffect;
    //eff will be deleted at apply_effect

    eff->setBlurRadius(blur_radius);
    QImage result = apply_effect(src, eff);
    return result;
}

//---------------------------------------------------------------------
QImage XImageEffect::drop_shadow(QImage src, QColor color, float blur_radius, float offset_x, float offset_y) {
    QGraphicsDropShadowEffect *eff = new QGraphicsDropShadowEffect;
    //eff will be deleted at apply_effect

    eff->setColor(color);
    eff->setBlurRadius(blur_radius);
    eff->setOffset(offset_x,offset_y);
    QImage result = apply_effect(src, eff);
    return result;
}

//---------------------------------------------------------------------
