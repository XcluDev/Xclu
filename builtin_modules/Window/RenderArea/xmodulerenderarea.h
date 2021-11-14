#ifndef XMODULERENDERAREA_H
#define XMODULERENDERAREA_H

//XUI image

#include <QObject>
#include <QWindow>

#include "sdk_h.h"
#include "xmodulewidget.h"


class XModuleRenderArea: public XModuleWidget
{
    Q_OBJECT
public:
    XModuleRenderArea(QString class_name);
    virtual ~XModuleRenderArea();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    virtual void draw(QPainter &painter, int w, int h);

protected:


};



#endif // XMODULERENDERAREA_H
