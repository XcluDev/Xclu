#ifndef XCLASSFBO_H
#define XCLASSFBO_H

//FBO для рисования

#include <QObject>
#include <QWindow>

#include "sdk_h.h"
#include "xclass.h"
#include "xprotecteddata.h"


//Модуль
class XModuleFbo: public XClass
{
    Q_OBJECT
public:
    XModuleFbo(QString class_name);
    virtual ~XModuleFbo();
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

#endif // XCLASSFBO_H
