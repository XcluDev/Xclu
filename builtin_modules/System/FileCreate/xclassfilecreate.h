#ifndef XCLASSFILECREATE_H
#define XCLASSFILECREATE_H

//Реализация модуля Execute - запуск программы с диска

#include "sdk_h.h"
#include "xclass.h"

class XModuleFileCreate: public XClass
{
public:
    XModuleFileCreate(QString class_name);
    virtual ~XModuleFileCreate();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();
    virtual void on_button_pressed(QString button_id);

};

#endif // XCLASSFILECREATE_H
