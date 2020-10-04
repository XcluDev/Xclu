#ifndef RTMODULEPROJECT_H
#define RTMODULEPROJECT_H

//Control project:
//FPS
//Autostart

#include <QObject>
#include <QLabel>

#include "sdk_h.h"
#include "xmodule.h"


class XModuleProject: public XModule
{
    Q_OBJECT
public:
    XModuleProject(QString class_name);
    ~XModuleProject();
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
