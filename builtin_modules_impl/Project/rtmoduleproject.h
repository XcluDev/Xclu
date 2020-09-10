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
    //Выполнение
    virtual void loaded_impl();
    virtual void start_impl();
    virtual void update_impl();
    virtual void stop_impl();

    void apply_control_values();

};

#endif // RTMODULEPROJECT_H
