#pragma once

//UDP sender/receiver implementation

#include "sdk_h.h"
#include "xclass.h"

class XClassUdp: public XClass
{
public:
    XClassUdp(QString class_name);
    virtual ~XClassUdp();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

};

