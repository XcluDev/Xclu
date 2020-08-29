#ifndef RTMODULEPROJECT_H
#define RTMODULEPROJECT_H

//Control project:
//FPS
//Autostart

#include <QObject>
#include <QScopedPointer>
#include <QMutex>
#include <QLabel>

#include "incl_h.h"
#include "rtmodule.h"


class RtModuleProject: public RtModule
{
    Q_OBJECT
public:
    RtModuleProject();
    ~RtModuleProject();

    static QString *static_class_name_ptr;
    static RtModuleProject *new_module();

protected:
    //Выполнение
    virtual void execute_loaded_internal();
    virtual void execute_start_internal();
    virtual void execute_update_internal();
    virtual void execute_stop_internal();

    void set_values();

};

#endif // RTMODULEPROJECT_H
