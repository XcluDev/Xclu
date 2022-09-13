#pragma once

//Random implementation

#include "sdk_h.h"
#include "xclass.h"

class XClassRandom: public XClass
{
public:
    XClassRandom(QString class_name);
    virtual ~XClassRandom();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();
    //virtual void on_button_pressed(QString button_id);


    QString get_random_string();

    float time_ = -1;

    void make_new_value();
};


