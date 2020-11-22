#ifndef XMODULERANDOM_H
#define XMODULERANDOM_H

//ValueMap implementation

#include "sdk_h.h"
#include "xmodule.h"

class XModuleValueMap: public XModule
{
public:
    XModuleValueMap(QString class_name);
    ~XModuleValueMap();
#include "auto.h"

protected:
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();
    //virtual void impl_button_pressed(QString button_id);

};



#endif // XMODULERANDOM_H
