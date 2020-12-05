#ifndef XMODULEFILECREATE_H
#define XMODULEFILECREATE_H

//Реализация модуля Execute - запуск программы с диска

#include "sdk_h.h"
#include "xmodule.h"

class XModuleFileCreate: public XModule
{
public:
    XModuleFileCreate(QString class_name);
    ~XModuleFileCreate();
protected:
#include "auto.h"

    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();
    virtual void impl_button_pressed(QString button_id);

};

#endif // XMODULEFILECREATE_H
