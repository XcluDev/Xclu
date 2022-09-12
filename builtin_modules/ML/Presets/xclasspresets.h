#pragma once


#include "sdk_h.h"
#include "xclasswidget.h"


class XClassPresets: public XClassWidget {
    Q_OBJECT
public:
    XClassPresets(QString class_name);
    ~XClassPresets();

protected:
#include "auto.h"
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    virtual void draw(QPainter &painter, int w, int h);


};

