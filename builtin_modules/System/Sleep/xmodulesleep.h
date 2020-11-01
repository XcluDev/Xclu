#ifndef XMODULESLEEP_H
#define XMODULESLEEP_H

//Delay implementation

#include "sdk_h.h"
#include "xmodule.h"

class XModuleSleep: public XModule
{
public:
    XModuleSleep(QString class_name);
    ~XModuleSleep();
#include "auto.h"

protected:
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();
    //virtual void impl_button_pressed(QString button_id);

    void register_bang_time();
    void update_bang(float delay_sec);

    double time_ = 0;    //last bang time
    void bang();

};



#endif // XMODULESLEEP_H
