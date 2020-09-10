#ifndef RTMODULEEXECUTE_H
#define RTMODULEEXECUTE_H

//Реализация модуля Execute - запуск программы с диска

#include "incl_h.h"
#include "rtmodule.h"

class RtModuleExecute: public RtModule
{
public:
    RtModuleExecute();
    ~RtModuleExecute();

    static QString *static_class_name_ptr;
    static RtModuleExecute *new_module();

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
