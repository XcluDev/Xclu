#ifndef RTMODULEEXECUTE_H
#define RTMODULEEXECUTE_H

//Реализация модуля Execute - запуск программы с диска

#include "incl_h.h"
#include "xmodule.h"

class XModuleExecute: public XModule
{
public:
    XModuleExecute();
    ~XModuleExecute();

    static QString *static_class_name_ptr;
    static XModuleExecute *new_module();

protected:
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();

    enum WorkMode : int {
        WorkModeEach_Frame = 0,
        WorkModeOn_Bang = 1
    };


};



#endif // RTMODULEEXECUTE_H
