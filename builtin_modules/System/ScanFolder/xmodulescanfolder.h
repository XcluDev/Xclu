#ifndef XMODULESCANFOLDER_H
#define XMODULESCANFOLDER_H

//ScanFolder implementation

#include "sdk_h.h"
#include "xmodule.h"

class XModuleScanFolder: public XModule
{
public:
    XModuleScanFolder(QString class_name);
    ~XModuleScanFolder();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

};



#endif // XMODULESCANFOLDER_H
