#ifndef XCLASSRENDERELEMENT_H
#define XCLASSRENDERELEMENT_H

//RenderElement module - Buttons, sliders, circles, lines, etc. drawn on RenderArea.

#include <QObject>

#include "sdk_h.h"
#include "xclasswidget.h"

class XModuleRenderElement: public XClass
{
    Q_OBJECT
public:
    XModuleRenderElement(QString class_name);
    virtual ~XModuleRenderElement();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    virtual void draw(QPainter &painter, int w, int h);

};

#endif // XCLASSRENDERELEMENT_H
