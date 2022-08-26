#ifndef XCLASSRANDOM_H
#define XCLASSRANDOM_H

//ValueMap implementation

#include "sdk_h.h"
#include "xclass.h"

class XClassValueMap: public XClass
{
public:
    XClassValueMap(QString class_name);
    virtual ~XClassValueMap();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();
    //virtual void on_button_pressed(QString button_id);

};



#endif // XCLASSRANDOM_H
