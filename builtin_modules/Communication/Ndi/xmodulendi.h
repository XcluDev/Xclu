#ifndef XMODULENDI_H
#define XMODULENDI_H

//NDI interface

#include <QImage>
#include <QtSerialPort/QSerialPort>
#include "sdk_h.h"
#include "xmodule.h"
#include "xobjectimage.h"
#include "xprotecteddata.h"
#include "sdk_h.h"

//Note: now this module writes warnings and errors to console, without interrupting the project.
//TODO: make possibility to interrupt. (Already it's set in Control module).
//It's great to do in wizard at adding the module.

class XModuleNdi: public XModule
{
public:
    XModuleNdi(QString class_name);
    ~XModuleNdi();
protected:
#include "auto.h"
    //Выполнение
    virtual void on_loaded();
    virtual void start();
    virtual void update();
    virtual void stop();
    virtual void on_button_pressed(QString button_id);

protected:
    void gui_clear();

    void print_devices();

    bool connected_ = false;
    void set_connected(bool connected);

protected:




};



#endif // XMODULESERIAL_H
