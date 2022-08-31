#pragma once

//Renderer area module. It renders itself to Window, and controls RenderElements - buttons, faders, etc.

#include <QObject>
#include <QWindow>

#include "sdk_h.h"
#include "xclasswidget.h"


class XClassRenderArea: public XClassWidget
{
    Q_OBJECT
public:
    XClassRenderArea(QString class_name);
    virtual ~XClassRenderArea();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    virtual void draw(QPainter &painter, int w, int h);

protected:
    //Collect modules to render from
    void collect_modules();
    QVector<XClass *> modules_;

};


