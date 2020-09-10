#ifndef RTMODULEFBO_H
#define RTMODULEFBO_H

//FBO для рисования

#include <QObject>
#include <QScopedPointer>
#include <QMutex>
#include <QWindow>

#include "incl_h.h"
#include "rtmodule.h"
#include "xcluprotecteddata.h"


//Модуль
class RtModuleFbo: public RtModule
{
    Q_OBJECT
public:
    RtModuleFbo();
    ~RtModuleFbo();

    static QString *static_class_name_ptr;
    static RtModuleFbo *new_module();

protected:
    //Выполнение
    virtual void start_impl();
    virtual void update_impl();
    virtual void stop_impl();

    //Вызовы
    virtual void call_impl(QString function, XDict *input, XDict * /*output*/);
protected:
    //QScopedPointer<QWindow> window_;
};


//RtModuleFbo

#endif // RTMODULEFBO_H
