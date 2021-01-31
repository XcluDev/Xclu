#ifndef XIMAGEEFFECT_H
#define XIMAGEEFFECT_H

//Implementing applying QGraphicsEffect  to image, for example,
//image blur using QGraphicsBlurEffect
//Code adapted from Петър Петров, https://stackoverflow.com/questions/14915129/qimage-transform-using-qgraphicsblureffect
//
//Note: this effects for processing CPU rasters QImage, XRaster are not so optimal,
//I use it just for fast implementationin pure Qt.
//For better performance consider using OpenCV.

#include "incl_h.h"

#include <QGraphicsEffect>

class XImageEffect
{
public:
    XImageEffect();

    static QImage blur(QImage src, float blur_radius);

    static QImage drop_shadow(QImage src, QColor color, float blur_radius, float offset_x, float offset_y);

protected:
    //Note: effect_will_destroyed will be destroyed because binding to image in implementation
    static QImage apply_effect(QImage src, QGraphicsEffect *effect_will_destroyed, int extent=0);



};

#endif // XIMAGEEFFECT_H
