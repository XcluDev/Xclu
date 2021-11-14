#ifndef XMODULEFBO_H
#define XMODULEFBO_H

//FBO для рисования

#include <QObject>
#include <QWindow>

#include "sdk_h.h"
#include "xmodule.h"
#include "xprotecteddata.h"


//Модуль
class XModuleFbo: public XModule
{
    Q_OBJECT
public:
    XModuleFbo(QString class_name);
    ~XModuleFbo();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    //Вызовы
    //virtual void on_custom_call(QString function, XObject *input, XObject * /*output*/);
protected:
    //QScopedPointer<QWindow> window_;
};


//XModuleFbo

#endif // XMODULEFBO_H
