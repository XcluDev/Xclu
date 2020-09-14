#ifndef RTMODULESERIAL_H
#define RTMODULESERIAL_H

//Serial interface with Arduino and other devices

#include <QScopedPointer>
#include <QImage>
#include <QMutex>
#include <QtSerialPort/QSerialPort>
#include "incl_h.h"
#include "xmodule.h"
#include "xcluobjectimage.h"
#include "xcluprotecteddata.h"
#include "incl_h.h"

//Note: now this module writes warnings and errors to console, without interrupting the project.
//TODO: make possibility to interrupt. (Already it's set in Control module).
//It's great to do in wizard at adding the module.

class XModuleSerial: public XModule
{
public:
    XModuleSerial();
    ~XModuleSerial();

    static QString *static_class_name_ptr;
    static XModuleSerial *new_module();

protected:
#include "auto.h"
    //Выполнение
    virtual void impl_loaded();
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();
    virtual void impl_button_pressed(QString button_id);

protected:
    void gui_clear();

    //вывод устройств
    void print_devices();

    bool connected_ = false;
    void set_connected(bool connected); //также ставит gui-элемент connected

protected:

    void open_port();

    QSerialPort serialPort_;
    QString port_name_;

    void send_string(QString str);
    void send_byte(int byte);

    int total_sent_ = 0;
    void set_total_sent(int t);

};



#endif // RTMODULESERIAL_H