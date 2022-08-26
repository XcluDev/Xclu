#ifndef XMODULERENDERAREA_H
#define XMODULERENDERAREA_H

//Renderer area module. It renders itself to Window, and controls RenderElements - buttons, faders, etc.

#include <QObject>
#include <QWindow>

#include "sdk_h.h"
#include "xclasswidget.h"


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
    //Collect modules to render from
    void collect_modules();
    QVector<Module *> modules_;


};



#endif // XMODULERENDERAREA_H
