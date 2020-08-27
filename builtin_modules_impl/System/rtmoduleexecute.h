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

    virtual void execute_start_internal();
    virtual void execute_update_internal();
    virtual void execute_stop_internal();

    enum WorkMode : int {
        WorkModeEach_Frame = 0,
        WorkModeOn_Bang = 1
    };


};



#endif // RTMODULEEXECUTE_H
