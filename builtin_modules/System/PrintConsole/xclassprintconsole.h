#ifndef XCLASSPRINTCONSOLE_H
#define XCLASSPRINTCONSOLE_H

//PrintConsole implementation

#include "sdk_h.h"
#include "xclass.h"

class XClassPrintConsole: public XClass
{
public:
    XClassPrintConsole(QString class_name);
    virtual ~XClassPrintConsole();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

};



#endif // XCLASSPRINTCONSOLE_H
