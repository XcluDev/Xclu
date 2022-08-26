#ifndef XCLASSSCANFOLDER_H
#define XCLASSSCANFOLDER_H

//ScanFolder implementation

#include "sdk_h.h"
#include "xclass.h"

class XModuleScanFolder: public XClass
{
public:
    XModuleScanFolder(QString class_name);
    virtual ~XModuleScanFolder();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

};



#endif // XCLASSSCANFOLDER_H
