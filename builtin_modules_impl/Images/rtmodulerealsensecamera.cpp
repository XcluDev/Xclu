#include "rtmodulerealsensecamera.h"
#include "incl_qtcpp.h"
#include "rtmoduleregistrar.h"
#include <QProcess>
#include "projectruntime.h"
//#include <QImageWriter>
//#include <QImageReader>

#include "xcluobjectimage.h"

//заполнение имени класса и регистрация класса
REGISTRAR(RealsenseCamera)


//---------------------------------------------------------------------
/*static*/ RtModuleRealsenseCamera *RtModuleRealsenseCamera::new_module() {
    return new RtModuleRealsenseCamera();
}

//---------------------------------------------------------------------
RtModuleRealsenseCamera::RtModuleRealsenseCamera()
    :RtModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
RtModuleRealsenseCamera::~RtModuleRealsenseCamera()
{
    stop_camera();
}

//---------------------------------------------------------------------
//нажатие кнопки, даже когда модуль остановлен - модуль также должен переопределить эту функцию
//внимание, обычно вызывается из основного потока как callback
void RtModuleRealsenseCamera::button_pressed_internal(QString button_id) {
    if (button_id == "print_devices") {
        print_devices();
    }
}

//---------------------------------------------------------------------
void RtModuleRealsenseCamera::print_devices() {
    QStringList out;
    out.append(QString("Realsense SDK: %1").arg(RealsenseCamera::get_sdk_version()));
    int n = RealsenseCamera::get_number_of_connected_devices();
    out.append(QString("Number of Realsense devices: %1").arg(n));
    if (n > 0) {
        out.append(RealsenseCamera::get_connected_devices_list());
    }
    clear_string("local_console");
    append_string("local_console", out, 1);

}

//---------------------------------------------------------------------
void RtModuleRealsenseCamera::execute_loaded_internal() {
    clear_string("local_console");
}

//---------------------------------------------------------------------
void RtModuleRealsenseCamera::execute_start_internal() {
    //здесь мы не стартуем камеру, так как делаем это в update
    //в зависимости от capture_source

    //Очистка переменных
    camera_tried_to_start_ = false;

    //данные surface
    {
        DataAccess access(data_);
        data_.clear();
    }

    processed_frames_ = 0;

    set_started(false); //также ставит gui-элемент is_started

    clear_string("connected_device_name");
    set_int("is_new_frame", 0);
    clear_string("frames_captured");

    //очищаем список устройств
    clear_string("local_console");

    //запуск камеры или воспроизведения файла
    start_camera();
    //------------------------------------

}

//---------------------------------------------------------------------
void RtModuleRealsenseCamera::execute_update_internal() {
    update_camera();

    //обработка ошибки
    {
        DataAccess access(data_);
        data_.err.throw_error();
    }
}

//---------------------------------------------------------------------
void RtModuleRealsenseCamera::execute_stop_internal() {
    //qDebug() << "stop";
    stop_camera();

}

//---------------------------------------------------------------------
void RtModuleRealsenseCamera::update_camera() {
    //захват с камеры или считывание изображений
    int source = get_int("capture_source");
    if (source == CaptureSourceNone) return;

    //если камера не стартовала - то делать нечего
    //TODO возможно стоит попробовать запустить камеру снова через некоторое время
    if (!camera_started_) return;

    //на всякий случай ставим, что нет новых кадров
    //чтобы в случае ошибки не осталось "1"
    set_int("is_new_frame", 0);

    //начинаем менять данные для surface - обновлять и считывать
    bool is_new_frame;
    {
        DataAccess access(data_);
        is_new_frame = data_.is_new_frame;
        data_.is_new_frame = 0;
    }

    //обрабатываем только новые кадры
    if (is_new_frame) {
        set_int("is_new_frame", is_new_frame);
        processed_frames_++;

        //копируем изображение для использования вовне и показа в GUI
        XcluObject *object = get_object("image");

        DataAccess access(data_);
        ObjectRead(&data_.image).copy_to(object);
    }

    //метка числа обработанных кадров
    QString processed = QString("Captured %1, Processed %2, Dropped %3 frame(s)")
            .arg(data_.captured_frames).arg(processed_frames_).arg(data_.captured_frames-processed_frames_);
    set_string("frames_captured", processed);


}

//---------------------------------------------------------------------
void RtModuleRealsenseCamera::start_camera() {
    //запуск камеры
    if (!camera_tried_to_start_) {
        //пытаемся стартовать камеру
        camera_tried_to_start_ = true;

        /*      //выбор устройства
        const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
        xclu_assert(!cameras.empty(), "No connected devices");

        SelectDevice method = SelectDevice(get_int("select_device"));
        switch (method) {
        case SelectDeviceDefault: {
            start_camera(QCameraInfo::defaultCamera());
            break;
        }
        case SelectDeviceByIndex: {
                int name = get_int("device_index");
                xclu_assert(name >= 0 && name < cameras.size(), "Bad device index " + QString::number(name));
                start_camera(cameras[name]);
                break;
        }
        case SelectDeviceByName: {
            QString name = get_string("device_name");
            for (int i=0; i<cameras.size(); i++) {
                auto &info = cameras.at(i);
                if (info.description().contains(name)) {
                    start_camera(info);
                    break;
                }
            }
            break;
        }
        default:
            //мы здесь не должны быть, так как все методы запуска рассмотренли,
            //поэтому выдаем ошибку
            xclu_exception(QString("Bad select_device value '%1'").arg(method));
        }


    read_gui_output_data_format();

    camera_.reset(new QCamera(cameraInfo));
    camera_->load();    //вообще это не требуется, но пробуем устранить ошибку с зависанием при старте.

    connect(camera_.data(), &QCamera::stateChanged, this, &RtModuleRealsenseCamera::on_changed_camera_state);
    connect(camera_.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &RtModuleRealsenseCamera::on_camera_error);

    //считывание разрешения
    int w, h;
    get_gui_resolution(w, h);

    //считывание FPS
    int fps = get_gui_frame_rate();

    if (w > 0 && h > 0 && fps > 0) {
        //установка разрешения и FPS в камеру
        QCameraViewfinderSettings settings;
        if (w > 0 && h > 0) {
            settings.setResolution(w, h);
        }
        if (fps > 0) {
            settings.setMinimumFrameRate(fps);
            settings.setMaximumFrameRate(fps);
        }
        //TODO проверить, что камера такое поддерживает
        camera_->setViewfinderSettings(settings);
    }

    //ставим захват изображений в нашу surface_
    camera_->setViewfinder(&surface_);

    on_changed_camera_state(camera_->state());

    QString device_name = cameraInfo.description();
    set_string("connected_device_name", device_name);
    append_string("local_console", "Starting: " + device_name, 1);

    //если требуется, вывести в консоль поддерживаемые разрешения и частоты кадров
    //делаем тут это до старта камеры, и в функции делаем "camera_->load()",
    //чтобы в случае ее падения увидеть поддерживаемые разрешения
    print_formats();

    camera_->start();
        */
    }

}



//---------------------------------------------------------------------
//считать из GUI разрешение камеры, -1 - использовать по умолчанию
void RtModuleRealsenseCamera::get_gui_resolution(int &w, int &h) {
    /*QString res_string = get_string("resolution");
    if (res_string == "Camera_Default") {
        w = -1;
        h = -1;
        return;
    }
    if (res_string == "Custom") {
        w = get_int("res_x");
        h = get_int("res_y");
    }
    else {
        //требуется распарсить "1280_x_720"
        auto list = res_string.split("_x_");
        xclu_assert(list.size() == 2, "Can't start camera, bad resolution string " + res_string);
        w = list.at(0).toInt();
        h = list.at(1).toInt();
    }
    xclu_assert(w > 0 && h > 0, QString("Can't start camera, bad resolution %1x%2").arg(w).arg(h));
    */
}

//---------------------------------------------------------------------
//считать из GUI частоту кадров, -1 - использовать по умолчанию
int RtModuleRealsenseCamera::get_gui_frame_rate() {
    QString fps_string = get_string("frame_rate");
    if (fps_string == "Camera_Default") {
        return -1;
    }
    int fps = 30;
    if (fps_string == "Custom") {
        fps = get_int("custom_frame_rate");
    }
    else {
        //FPS записано числом в строке
        fps = fps_string.toUInt();
    }
    xclu_assert(fps > 0, QString("Can't start camera, bad frame rate %1").arg(fps));
    return fps;
}

//---------------------------------------------------------------------
void RtModuleRealsenseCamera::set_started(bool started) { //ставит camera_started_ и gui-элемент is_started
    camera_started_ = started;
    set_int("is_started", started);
}

//---------------------------------------------------------------------
/*void RtModuleRealsenseCamera::on_changed_camera_state(QCamera::State state) {
    switch (state) {
    case QCamera::ActiveState:
        set_started(true);
        break;
    case QCamera::UnloadedState:
    case QCamera::LoadedState:
        set_started(false);
        break;
    }
}*/

//---------------------------------------------------------------------
/*void RtModuleRealsenseCamera::on_camera_error() {
    DataAccess access(data_);
    data_.err.setup(tr("Camera Error: ..."));// + camera_->errorString());
}
*/

//---------------------------------------------------------------------
void RtModuleRealsenseCamera::stop_camera() {
    /*if (camera_.data()) {
        //camera_->stop();  //Это не полная остановка, камера продолжает потреблять энергию
        camera_->unload();    //Остановка камеры
        camera_.reset();
    }*/
}

//---------------------------------------------------------------------


