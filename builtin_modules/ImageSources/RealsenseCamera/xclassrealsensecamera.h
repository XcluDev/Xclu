#ifndef XCLASSREALSENSECAMERA1_H
#define XCLASSREALSENSECAMERA1_H

//Working with Realsense camera

#include <QImage>
#include "sdk_h.h"
#include "xclass.h"
#include "xobjectimage.h"
#include "xprotecteddata.h"
#include "sdk_h.h"
#include "xclassrealsensecamera_impl.h"
//class RealsenseCamera;

//The module for working with Realsense
class XClassRealsenseCamera: public XClass
{
public:
    XClassRealsenseCamera(QString class_name);
    virtual ~XClassRealsenseCamera();
protected:
#include "auto.h"

    //Выполнение
    virtual void on_loaded();
    virtual void start();
    virtual void update();
    virtual void stop();

    //нажатие кнопки, даже когда модуль остановлен - модуль также должен переопределить эту функцию
    //внимание, обычно вызывается из основного потока как callback
    virtual void on_button_pressed(QString button_id);

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
    void save_frames(bool color, bool depth, bool ir, bool use_timestamp);


protected slots:
    //void on_changed_camera_state(QCamera::State state);
    //void on_camera_error();

protected:
    int2 get_res(QString res_string);    //320_x_240-> 320,240
    int get_frame_rate(QString rate_string);
    RealsenseSettings get_settings();

    XRaster_u8c3 raster_color_;
    XRaster_u8c3 raster_depth_;
    XRaster_u8 raster_ir_;

    //compute transformed depth to grayscale 8 bit and binary image
    void transform();

    //TODO if will be required in other place - do reading carefully, to prevent duplication
    XRaster_u16 raster_depth16_;

    XProtectedObject depth8_gui_;
    XRaster_u8 depth8_;
};



#endif // XCLASSREALSENSECAMERA_H
