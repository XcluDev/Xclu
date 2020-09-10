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
    //Выполнение

    virtual void start_impl();
    virtual void update_impl();
    virtual void stop_impl();

    enum WorkMode : int {
        WorkModeEach_Frame = 0,
        WorkModeOn_Bang = 1
    };


};



#endif // RTMODULEEXECUTE_H
