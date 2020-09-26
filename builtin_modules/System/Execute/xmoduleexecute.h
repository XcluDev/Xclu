#ifndef RTMODULEEXECUTE_H
#define RTMODULEEXECUTE_H

//Реализация модуля Execute - запуск программы с диска

#include "incl_h.h"
#include "xmodule.h"

class XModuleExecute: public XModule
{
public:
    XModuleExecute(QString class_name);
    ~XModuleExecute();
protected:
#include "auto.h"

    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();

};



#endif // RTMODULEEXECUTE_H
