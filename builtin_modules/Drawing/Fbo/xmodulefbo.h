#ifndef RTMODULEFBO_H
#define RTMODULEFBO_H

//FBO для рисования

#include <QObject>
#include <QWindow>

#include "sdk_h.h"
#include "xmodule.h"
#include "xcluprotecteddata.h"


//Модуль
class XModuleFbo: public XModule
{
    Q_OBJECT
public:
    XModuleFbo(QString class_name);
    ~XModuleFbo();
protected:
#include "auto.h"

    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();

    //Вызовы
    virtual void impl_call(QString function, XObject *input, XObject * /*output*/);
protected:
    //QScopedPointer<QWindow> window_;
};


//XModuleFbo

#endif // RTMODULEFBO_H
