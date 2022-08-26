#ifndef XCLASSRANDOM_H
#define XCLASSRANDOM_H

//Random implementation

#include "sdk_h.h"
#include "xclass.h"

class XModuleRandom: public XClass
{
public:
    XModuleRandom(QString class_name);
    virtual ~XModuleRandom();
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



#endif // XCLASSRANDOM_H
