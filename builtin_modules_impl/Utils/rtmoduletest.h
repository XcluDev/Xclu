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

    static QString *static_class_name_ptr;
    static RtModuleTest *new_module();

protected:
    //Выполнение
    virtual void loaded_impl() {}
    virtual void start_impl();
    virtual void update_impl();
    virtual void stop_impl();


};

#endif // RTMODULETEST_H
