#ifndef RTMODULESERIAL_H
#define RTMODULESERIAL_H

//Serial interface with Arduino and other devices

#include <QImage>
#include <QtSerialPort/QSerialPort>
#include "sdk_h.h"
#include "xmodule.h"
#include "xcluobjectimage.h"
#include "xcluprotecteddata.h"
#include "sdk_h.h"

//Note: now this module writes warnings and errors to console, without interrupting the project.
//TODO: make possibility to interrupt. (Already it's set in Control module).
//It's great to do in wizard at adding the module.

class XModuleSerial: public XModule
{
public:
    XModuleSerial(QString class_name);
    ~XModuleSerial();
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

    void receive();

    QString in_string_;


    double watchdog_sent_ = 0;  //last time we sent watchdog event

};



#endif // RTMODULESERIAL_H
