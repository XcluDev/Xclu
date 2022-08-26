#ifndef XCLASSRANDOM_H
#define XCLASSRANDOM_H

//ValueMap implementation

#include "sdk_h.h"
#include "xclass.h"

class XModuleValueMap: public XClass
{
public:
    XModuleValueMap(QString class_name);
    virtual ~XModuleValueMap();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();
    //virtual void on_button_pressed(QString button_id);

};



#endif // XCLASSRANDOM_H
