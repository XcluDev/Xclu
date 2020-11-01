#ifndef XMODULEPRINTCONSOLE_H
#define XMODULEPRINTCONSOLE_H

//PrintConsole implementation

#include "sdk_h.h"
#include "xmodule.h"

class XModulePrintConsole: public XModule
{
public:
    XModulePrintConsole(QString class_name);
    ~XModulePrintConsole();
#include "auto.h"

protected:
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();

};



#endif // XMODULEPRINTCONSOLE_H
