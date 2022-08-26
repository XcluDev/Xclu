#ifndef XMODULEPRINTCONSOLE_H
#define XMODULEPRINTCONSOLE_H

//PrintConsole implementation

#include "sdk_h.h"
#include "xclass.h"

class XModulePrintConsole: public XClass
{
public:
    XModulePrintConsole(QString class_name);
    virtual ~XModulePrintConsole();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

};



#endif // XMODULEPRINTCONSOLE_H
