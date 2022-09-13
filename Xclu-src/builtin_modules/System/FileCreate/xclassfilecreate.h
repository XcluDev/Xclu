#pragma once

//Реализация модуля Execute - запуск программы с диска

#include "sdk_h.h"
#include "xclass.h"

class XClassFileCreate: public XClass
{
public:
    XClassFileCreate(QString class_name);
    virtual ~XClassFileCreate();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();
    virtual void on_button_pressed(QString button_id);

};

