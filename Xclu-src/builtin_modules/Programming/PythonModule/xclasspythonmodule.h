#pragma once

//Python module with UI and possibility to draw

#include <QImage>
#include "sdk_h.h"
#include "xclasswidget.h"
#include "xobjectvis.h"
#include "xprotecteddata.h"
#include "sdk_h.h"

class XClassPythonModule: public XClass
{
public:
    XClassPythonModule(QString class_name);
    ~XClassPythonModule();
protected:
#include "auto.h"
    virtual void on_loaded();
    virtual void start();
    virtual void update();
    virtual void stop();
    virtual void on_button_pressed(QString button_id);

    virtual void draw(QPainter &painter, int w, int h);

protected:
    //QScopedPointer<NeuroplayPro> neuroplay_;

};

