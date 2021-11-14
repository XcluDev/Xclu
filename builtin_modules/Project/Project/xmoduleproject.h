#ifndef XMODULEPROJECT_H
#define XMODULEPROJECT_H

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
    virtual ~XModuleProject();
protected:
#include "auto.h"

    //Выполнение
    virtual void on_loaded();
    virtual void start();
    virtual void update();
    virtual void stop();

    void apply_control_values();

};

#endif // XMODULEPROJECT_H
