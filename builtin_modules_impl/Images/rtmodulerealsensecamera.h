#ifndef RTMODULEREALSENSECAMERA1_H
#define RTMODULEREALSENSECAMERA1_H

//Working with Realsense camera

#include <QScopedPointer>
#include <QImage>
#include <QMutex>
#include "incl_qt.h"
#include "rtmodule.h"
#include "xcluobjectimage.h"
#include "xcluprotecteddata.h"
#include "incl_qt.h"
#include "rtmodulerealsensecamera_impl.h"
//class RealsenseCamera;

//Данные, которые защищаются с помощью mutex
struct RtModuleRealsenseData : public XcluProtectedData
{
    XcluObject image;           //Изображение с камеры - заполняется surface_, для доступа использовать mutex
    int captured_frames = 0;   //Количество полученных кадров - заполняется surface_, для доступа использовать mutex
    int is_new_frame = 0;

    QString channels;   //Grayscale,RGB,BGR,RGBA,BGRA,R,G,B
    QString data_type;  //u8bit,float

    //данные об ошибке
    ErrorInfo err;

    void clear() {
        ObjectReadWrite(image).clear();
        captured_frames = 0;
        is_new_frame = 0;
        channels = "";
        data_type = "";
        err.clear();
    }

};

//The module for working with Realsense
class RtModuleRealsenseCamera: public RtModule
{
public:
    RtModuleRealsenseCamera();
    ~RtModuleRealsenseCamera();

    static QString *static_class_name_ptr; //"RealsenseCamera", эта переменная используется для создания новых объектов
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
        SelectDeviceByName = 2,
        SelectDeviceByN = 3
    };

    //вывод устройств
    void print_devices();

    //камера
    void update_camera();
    void stop_camera();

    QScopedPointer<RealsenseCamera> camera_;
    bool camera_tried_to_start_ = false;
    void start_camera();

    RtModuleRealsenseData data_;

    bool camera_started_ = false;
    void set_started(bool started); //ставит camera_started_ и gui-элемент is_started

    //количество обработанных кадров
    int processed_frames_ = 0;

protected slots:
    //void on_changed_camera_state(QCamera::State state);
    //void on_camera_error();

protected:
    void get_gui_resolution(int &w, int &h);
    int get_gui_frame_rate();


};



#endif // RTMODULEREALSENSECAMERA_H
