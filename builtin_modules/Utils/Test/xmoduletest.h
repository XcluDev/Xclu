#ifndef XMODULETEST_H
#define XMODULETEST_H

//Реализация модуля Test - для проверки элементов GUI и исполнения - печатает в консоль, что делает

#include "sdk_h.h"
#include "xmodule.h"

class XModuleTest: public XModule
{
public:
    XModuleTest(QString class_name);
    ~XModuleTest();
protected:
    //Выполнение
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();


};

#endif // XMODULETEST_H
