#ifndef XCLASSTEST_H
#define XCLASSTEST_H

//Реализация модуля Test - для проверки элементов GUI и исполнения - печатает в консоль, что делает

#include "sdk_h.h"
#include "xclass.h"

class XClassTest: public XClass
{
public:
    XClassTest(QString class_name);
    virtual ~XClassTest();
protected:
    //Выполнение
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();


};

#endif // XCLASSTEST_H
