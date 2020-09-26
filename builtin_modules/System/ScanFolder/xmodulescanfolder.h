#ifndef RTMODULESCANFOLDER_H
#define RTMODULESCANFOLDER_H

//ScanFolder implementation

#include "incl_h.h"
#include "xmodule.h"

class XModuleScanFolder: public XModule
{
public:
    XModuleScanFolder(QString class_name);
    ~XModuleScanFolder();
#include "auto.h"

protected:
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();

};



#endif // RTMODULESCANFOLDER_H
