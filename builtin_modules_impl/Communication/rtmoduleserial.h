#ifndef RTMODULESERIAL_H
#define RTMODULESERIAL_H

//Serial interface with Arduino and other devices

#include <QScopedPointer>
#include <QImage>
#include <QMutex>
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
    static RtModuleRealsenseCamera *new_module();

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

    bool started_ = false;
    void set_started(bool started);

protected:

    //режим выбора камеры
    enum SelectDevice: int {
        SelectDeviceDefault = 0,
        SelectDeviceByIndex = 1,
        SelectDeviceByName = 2,
        SelectDeviceByN = 3
    };

};



#endif // RTMODULESERIAL_H
