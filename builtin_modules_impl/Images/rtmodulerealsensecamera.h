#ifndef RTMODULEREALSENSECAMERA1_H
#define RTMODULEREALSENSECAMERA1_H

//Working with Realsense camera

#include <QScopedPointer>
#include <QImage>
#include <QMutex>
#include "incl_h.h"
#include "rtmodule.h"
#include "xcluobjectimage.h"
#include "xcluprotecteddata.h"
#include "incl_h.h"
#include "rtmodulerealsensecamera_impl.h"
//class RealsenseCamera;

//The module for working with Realsense
class RtModuleRealsenseCamera: public RtModule
{
public:
    RtModuleRealsenseCamera();
    ~RtModuleRealsenseCamera();

    static QString *static_class_name_ptr;
    static RtModuleRealsenseCamera *new_module();

protected:
    //Выполнение
    virtual void execute_loaded_internal();
    virtual void execute_start_internal();
    virtual void execute_update_internal();
    virtual void execute_stop_internal();

    //нажатие кнопки, даже когда модуль остановлен - модуль также должен переопределить эту функцию
    //внимание, обычно вызывается из основного потока как callback
    virtual void button_pressed_internal(QString button_id);

protected:
    void gui_clear();

    //вывод устройств
    void print_devices();

    //камера
    RealsenseCamera camera_;
    void start_camera();
    bool camera_started_ = false;
    void set_started(bool started); //ставит camera_started_ и gui-элемент is_started


    int is_new_frame = 0;
    //количество обработанных кадров
    int processed_frames_ = 0;

    //ожидание записи кадров на диск
    int wait_save_frames_ = 0;

    //запись кадра на диск
    void save_frames(bool color, bool depth, bool ir);


protected slots:
    //void on_changed_camera_state(QCamera::State state);
    //void on_camera_error();

protected:
    int2 get_res(QString res_string);    //320_x_240-> 320,240
    int get_frame_rate(QString rate_string);
    RealsenseSettings get_settings();

    //режим захвата картинок
    enum CaptureSource : int {
        CaptureSourceNone = 0,
        CaptureSourceCamera = 1,
        CaptureSourceBagFile = 2,
        CaptureSourceN = 3
    };
    //режим выбора камеры
    enum SelectDevice: int {
        SelectDeviceDefault = 0,
        SelectDeviceByIndex = 1,
        SelectDeviceBySerial = 2,
        SelectDeviceByN = 3
    };

};



#endif // RTMODULEREALSENSECAMERA_H
