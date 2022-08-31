#pragma once

//ScanFolder implementation

#include "sdk_h.h"
#include "xclass.h"

class XClassScanFolder: public XClass
{
public:
    XClassScanFolder(QString class_name);
    virtual ~XClassScanFolder();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

};

