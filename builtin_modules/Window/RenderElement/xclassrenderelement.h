#pragma once

//RenderElement module - Buttons, sliders, circles, lines, etc. drawn on RenderArea.

#include <QObject>

#include "sdk_h.h"
#include "xclasswidget.h"

class XClassRenderElement: public XClass
{
    Q_OBJECT
public:
    XClassRenderElement(QString class_name);
    virtual ~XClassRenderElement();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    virtual void draw(QPainter &painter, int w, int h);

};

