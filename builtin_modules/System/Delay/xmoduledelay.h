#ifndef XMODULEDELAY_H
#define XMODULEDELAY_H

//Delay implementation

#include "sdk_h.h"
#include "xmodule.h"

class XModuleDelay: public XModule
{
public:
    XModuleDelay(QString class_name);
    ~XModuleDelay();
#include "auto.h"

protected:
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();

    void register_bang_time();
    void update_bang(float delay_sec);

    double time_ = 0;    //last bang time
    void bang();

};



#endif // XMODULEDELAY_H
