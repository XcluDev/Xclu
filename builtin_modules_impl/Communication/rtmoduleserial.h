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
    //Выполнение
    virtual void loaded_impl();
    virtual void start_impl();
    virtual void update_impl();
    virtual void stop_impl();
    virtual void button_pressed_impl(QString button_id);

protected:
    void gui_clear();

    //вывод устройств
    void print_devices();

    bool connected_ = false;
    void set_connected(bool connected); //также ставит gui-элемент connected

protected:

    void open_port();

    //режим выбора камеры
    enum SelectDevice: int {
        SelectDeviceDefault = 0,
        SelectDeviceByIndex = 1,
        SelectDeviceByName = 2,
        SelectDeviceByN = 3
    };

    QSerialPort serialPort_;
    QString port_name_;

    void send_string(QString str);
    void send_byte(int byte);

    int total_sent_ = 0;
    void set_total_sent(int t);

};



#endif // RTMODULESERIAL_H
