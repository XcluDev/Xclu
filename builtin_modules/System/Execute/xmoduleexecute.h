#ifndef XMODULEEXECUTE_H
#define XMODULEEXECUTE_H

//Реализация модуля Execute - запуск программы с диска

#include "sdk_h.h"
#include "xmodule.h"

class XModuleExecute: public XModule
{
public:
    XModuleExecute(QString class_name);
    ~XModuleExecute();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

};



#endif // XMODULEEXECUTE_H
