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
    virtual void execute_start_internal();
    virtual void execute_update_internal();
    virtual void execute_stop_internal();

    //Вызовы
    virtual void call_internal(QString function, XcluObject *input, XcluObject * /*output*/);
protected:
    //QScopedPointer<QWindow> window_;
};


//RtModuleFbo

#endif // RTMODULEFBO_H
