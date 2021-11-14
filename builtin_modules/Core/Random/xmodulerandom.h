#ifndef XMODULERANDOM_H
#define XMODULERANDOM_H

//Random implementation

#include "sdk_h.h"
#include "xmodule.h"

class XModuleRandom: public XModule
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



#endif // XMODULERANDOM_H
