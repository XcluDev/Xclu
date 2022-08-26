#ifndef XMODULETEST_H
#define XMODULETEST_H

//Реализация модуля Test - для проверки элементов GUI и исполнения - печатает в консоль, что делает

#include "sdk_h.h"
#include "xclass.h"

class XModuleTest: public XModule
{
public:
    XModuleTest(QString class_name);
    virtual ~XModuleTest();
protected:
    //Выполнение
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();


};

#endif // XMODULETEST_H
