#ifndef RTMODULESERIAL_H
#define RTMODULESERIAL_H

//Serial interface with Arduino and other devices

#include <QScopedPointer>
#include <QImage>
#include <QMutex>
#include <QtSerialPort/QSerialPort>
#include "incl_h.h"
#include "rtmodule.h"
#include "xcluobjectimage.h"
#include "xcluprotecteddata.h"
#include "incl_h.h"

class RtModuleSerial: public RtModule
{
public:
    RtModuleSerial();
    ~RtModuleSerial();

    static QString *static_class_name_ptr;
    static RtModuleSerial *new_module();

protected:
    //Выполнение
    virtual void execute_loaded_internal();
    virtual void execute_start_internal();
    virtual void execute_update_internal();
    virtual void execute_stop_internal();
    virtual void button_pressed_internal(QString button_id);

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

};



#endif // RTMODULESERIAL_H
