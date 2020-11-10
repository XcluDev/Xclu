#ifndef XMODULERANDOM_H
#define XMODULERANDOM_H

//Random implementation

#include "sdk_h.h"
#include "xmodule.h"

class XModuleRandom: public XModule
{
public:
    XModuleRandom(QString class_name);
    ~XModuleRandom();
#include "auto.h"

protected:
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();
    //virtual void impl_button_pressed(QString button_id);


    QString get_random_string();

    float time_ = -1;

    void make_new_value();
};



#endif // XMODULERANDOM_H
