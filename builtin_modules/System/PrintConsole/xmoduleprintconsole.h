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
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

};



#endif // XMODULEPRINTCONSOLE_H
