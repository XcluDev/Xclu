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
#include "xmodule.h"


class XModuleProject: public XModule
{
    Q_OBJECT
public:
    XModuleProject();
    ~XModuleProject();

    static QString *static_class_name_ptr;
    static XModuleProject *new_module();

protected:
#include "auto.h"

    //Выполнение
    virtual void impl_loaded();
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();

    void apply_control_values();

};

#endif // RTMODULEPROJECT_H
