#ifndef XCLASSFBO_H
#define XCLASSFBO_H

//FBO для рисования

#include <QObject>
#include <QWindow>

#include "sdk_h.h"
#include "xclass.h"
#include "xprotecteddata.h"


//Модуль
class XClassFbo: public XClass
{
    Q_OBJECT
public:
    XClassFbo(QString class_name);
    virtual ~XClassFbo();
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


//XClassFbo

#endif // XCLASSFBO_H
