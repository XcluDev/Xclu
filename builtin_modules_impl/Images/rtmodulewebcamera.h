#ifndef RTMODULEWEBCAMERA_H
#define RTMODULEWEBCAMERA_H

//Реализация модуля Webcamera - получение кадров с вебкамеры
//Важно, что камера может давать кадры в собственном потоке
//но внутреннее состояние изображения в модуле меняется ТОЛЬКО при update

#include <QScopedPointer>
#include <QCamera>
#include <QAbstractVideoSurface>
#include <QMutex>
#include "incl_qt.h"
#include "rtmodule.h"
#include "xcluobjectimage.h"
#include "xcluprotecteddata.h"
class QCameraInfo;

class RtModuleWebcamera;

//класс для обработки полученных изображений с камеры
//https://doc.qt.io/archives/qt-5.8/videooverview.html
//https://www.qtcentre.org/threads/57090-How-could-I-get-the-image-buffer-of-QCamera
class RtModuleWebcameraSurface: public QAbstractVideoSurface
{
public:
    //в конструктор передается сам модуль, чтобы в него посылать сигналы
    RtModuleWebcameraSurface(RtModuleWebcamera *module);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
    bool present(const QVideoFrame &frame);

protected:
    RtModuleWebcamera *module_; //удалять не нужно
};

//Данные для обмена с surface, которые защищаются с помощью mutex
struct RtModuleWebcameraSurfaceData : public XcluProtectedData
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


//Сам модуль для работы с вебкамерой
class RtModuleWebcamera: public RtModule
{
public:
    RtModuleWebcamera();
    ~RtModuleWebcamera();

    static QString *static_class_name_ptr; //"Webcamera", эта переменная используется для создания новых объектов
    static RtModuleWebcamera *new_module();

    //обмен данными с surface_ - чтобы он мог установить обновленное изображение
    RtModuleWebcameraSurfaceData &surface_data();

protected:
    //Выполнение

    virtual void execute_start_internal();
    virtual void execute_update_internal();
    virtual void execute_stop_internal();

protected:
    //режим захвата картинок
    enum CaptureSource : int {
        CaptureSourceNone = 0,
        CaptureSourceCamera = 1,
        CaptureSourceLoad_Frames = 2,
        CaptureSourceN = 3
    };
    //режим выбора камеры
    enum SelectDevice: int {
        SelectDeviceDefault = 0,
        SelectDeviceByIndex = 1,
        SelectDeviceByName = 2,
        SelectDeviceByN = 3
    };

    //камера
    void update_camera();
    void stop_camera();

    QScopedPointer<QCamera> camera_;
    bool camera_tried_to_start_ = false;
    void start_camera();
    void start_camera(const QCameraInfo &cameraInfo);
    void get_gui_resolution(int &w, int &h);    //считать из GUI разрешение камеры, -1 - использовать по умолчанию
    int get_gui_frame_rate();          //считать из GUI частоту кадров, -1 - использовать по умолчанию
    void read_gui_output_data_format();       //получить из GUI описание данных. Предполагается что mutex включен

    bool camera_started_ = false;
    void set_started(bool started); //ставит camera_started_ и gui-элемент is_started

    //получение кадров с камеры
    RtModuleWebcameraSurface surface_;

    //Данные для обмена с surface, которые защищаются с помощью mutex
    RtModuleWebcameraSurfaceData data_;

    //количество обработанных кадров
    int processed_frames_ = 0;

    //печать в консоль доступных камер
    void print_devices();
    bool print_devices_worked_ = false;

    //печать в консоль разрешений запускаемой камеры
    //внимание, эта функция запускает camera_->load()
    void print_formats();
    bool print_formats_worked_ = false;

protected slots:
    void on_changed_camera_state(QCamera::State state);
    void on_camera_error();

protected:
    //загрузка кадров
    void update_load_frames();

    //запись кадров
    void update_save_frames();

};


#endif // RTMODULEWEBCAMERA_H
