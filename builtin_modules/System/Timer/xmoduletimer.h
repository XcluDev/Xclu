#ifndef XMODULESLEEP_H
#define XMODULESLEEP_H

//Timer implementation

#include "sdk_h.h"
#include "xclass.h"

class XModuleTimer: public XClass
{
public:
    XModuleTimer(QString class_name);
    virtual ~XModuleTimer();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();
    //virtual void on_button_pressed(QString button_id);

    void register_bang_time();
    void update_bang(float delay_sec);

    bool working_ = false;

    double time_ = 0;    //last bang time
    void one_shot();

    void bang();

    void set_working(bool v);

};



#endif // XMODULESLEEP_H
