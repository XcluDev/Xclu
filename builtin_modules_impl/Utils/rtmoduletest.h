#ifndef RTMODULETEST_H
#define RTMODULETEST_H

//Реализация модуля Test - для проверки элементов GUI и исполнения - печатает в консоль, что делает

#include "incl_h.h"
#include "rtmodule.h"

class RtModuleTest: public RtModule
{
public:
    RtModuleTest();
    ~RtModuleTest();

    static QString *static_class_name_ptr; //"Test", эта переменная используется для создания новых объектов
    static RtModuleTest *new_module();

protected:
    //Выполнение
    virtual void execute_start_internal();
    virtual void execute_update_internal();
    virtual void execute_stop_internal();


};

#endif // RTMODULETEST_H
