#include "rtmodulerealsensecamera.h"
#include "incl_cpp.h"
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
    execute_stop_internal();
}

//---------------------------------------------------------------------
void RtModuleRealsenseCamera::execute_loaded_internal() {
    clear_string("device_list");
    clear_string("connected_device_info");
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
    clear_string("device_list");
    append_string("device_list", out, 1);

}


//---------------------------------------------------------------------
void RtModuleRealsenseCamera::execute_start_internal() {
    //здесь мы не стартуем камеру, так как делаем это в update
    //в зависимости от capture_source

    //Очистка переменных
    set_started(false); //также ставит gui-элемент is_started


    ObjectReadWrite(get_object("rgb_image")).clear();
    ObjectReadWrite(get_object("depth_image")).clear();
    ObjectReadWrite(get_object("ir_image")).clear();

    is_new_frame = 0;
    processed_frames_ = 0;

    clear_string("connected_device_info");
    set_int("is_new_frame", 0);
    clear_string("frames_captured");

    //очищаем список устройств
    clear_string("device_list");

    //запуск камеры или воспроизведения файла
    start_camera();
}

//---------------------------------------------------------------------
void RtModuleRealsenseCamera::execute_update_internal() {
    //TODO сделать возможность обработки кадров по callback
    //- а сейчас реализовано из основного потока

    //если камера не стартовала - то делать нечего
    //TODO возможно стоит попробовать запустить камеру снова через некоторое время
    if (!camera_started_) return;

    //на всякий случай ставим, что нет новых кадров
    //чтобы в случае ошибки не осталось "1"
    set_int("is_new_frame", 0);

    camera_.update();
    bool is_new_frame = camera_.isFrameNew();
    //обрабатываем только новые кадры
    if (is_new_frame) {
        set_int("is_new_frame", 1);
        processed_frames_++;

        //метка числа обработанных кадров
        QString processed = QString("Processed %1 frame(s)").arg(processed_frames_);
        set_string("frames_captured", processed);

        //установка изображений
        if (get_int("show_rgb") && camera_.settings().use_rgb) {
            Raster_u8c3 raster;
            xclu_assert(camera_.get_color_pixels_rgb(raster), "get_color_pixels_rgb() returned false");

            //TODO оптимизация: устранить создание промежуточного растра raster !
            ObjectReadWrite image(get_object("rgb_image"));
            XcluObjectImage::create_from_raster(image, raster);
        }
        if (get_int("show_depth") && camera_.settings().use_depth) {
            Raster_u8c3 raster;
            xclu_assert(camera_.get_depth_pixels_rgb(raster), "get_depth_pixels_rgb() returned false");

            //TODO оптимизация: устранить создание промежуточного растра raster !
            ObjectReadWrite image(get_object("depth_image"));
            XcluObjectImage::create_from_raster(image, raster);
        }
        if (get_int("show_ir") && camera_.settings().use_ir) {
            Raster_u8 raster;
            xclu_assert(camera_.get_ir_pixels8(raster), "get_ir_pixels8() returned false");

            //TODO оптимизация: устранить создание промежуточного растра raster !
            ObjectReadWrite image(get_object("ir_image"));
            XcluObjectImage::create_from_raster(image, raster);
        }
    }



}

//---------------------------------------------------------------------
void RtModuleRealsenseCamera::execute_stop_internal() {
    if (camera_started_) {
        camera_.close();
        set_started(false);
    }

}

//---------------------------------------------------------------------
void RtModuleRealsenseCamera::start_camera() {
    //запуск камеры

    int capture_source = get_int("capture_source");
    if (capture_source == CaptureSourceNone) return;
    if (capture_source == CaptureSourceBagFile) {
        //TODO реализовать считывание bag-файла
        xclu_exception("RealsenseCamera: loading bag files are not implemented");
    }
    if (capture_source == CaptureSourceCamera) {
        //выбор устройства
        QVector<RealsenseCameraInfo> cameras = RealsenseCamera::get_connected_devices_info();
        xclu_assert(!cameras.empty(), "No connected devices");

        int device_index = -1;
        SelectDevice method = SelectDevice(get_int("select_device"));
        switch (method) {
        case SelectDeviceDefault:
            device_index = 0;
            break;
        case SelectDeviceByIndex:
            device_index = get_int("device_index");
            xclu_assert(device_index >= 0 && device_index < cameras.size(), "Bad device index " + QString::number(device_index));
            break;
        case SelectDeviceBySerial: {
            QString serial = get_string("device_serial");
            for (int i=0; i<cameras.size(); i++) {
                if (cameras[i].serial == serial) {
                    device_index = i;
                    break;
                }
                xclu_exception("No device with serial '" + serial + "'");
            }
            break;
        }
        default:
            //мы здесь не должны быть, так как все методы запуска рассмотренли,
            //поэтому выдаем ошибку
            xclu_exception(QString("Internal error, bad select_device value '%1'").arg(method));
        }
        //TODO может быть нюанс, что список камер изменится пока мы ищем индекс.

        //TODO прикрутить реакцию на отключение камеры
        //connect(camera_.data(), &QCamera::stateChanged, this, &RtModuleRealsenseCamera::on_changed_camera_state);
        //connect(camera_.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &RtModuleRealsenseCamera::on_camera_error);
        //TODO также, стоит запускать watchdog, чтобы он проверял, что камера не зависла

        //Заполнение настроек
        RealsenseSettings sett = get_settings();

        //Запуск камеры
        bool started = camera_.start_camera(device_index, sett);
        set_started(started);
        if (started) {
            set_string("connected_device_info", cameras[device_index].descr_short);
            //append_string("device_list", "Starting: " + device_name, 1);
        }

    }
}

//---------------------------------------------------------------------
//заполнение настроек камеры из интерфейса
RealsenseSettings RtModuleRealsenseCamera::get_settings() {
    RealsenseSettings s;

    //RGB
    s.use_rgb = get_int("rgb_stream_enabled");
    if (s.use_rgb) {
        int2 res = get_res(get_string("rgb_resolution"));
        s.rgb_w = res.x;
        s.rgb_h = res.y;
        s.rgb_fps = get_frame_rate(get_string("rgb_frame_rate"));
    }

    //Depth & IR
    s.use_depth = get_int("depth_stream_enabled");
    s.use_ir = get_int("ir_stream_enabled");
    s.visual_preset = get_int("depth_preset");  //TODO convert string->RealsenseSDK enum values
    s.use_emitter = get_int("emitter");
    if (s.use_depth || s.use_ir) {
        int2 res = get_res(get_string("depth_resolution"));
        s.depth_w = res.x;
        s.depth_h = res.y;
    }

    s.align_to_depth = get_int("align_to_depth");

    return s;
}

//---------------------------------------------------------------------
int2 RtModuleRealsenseCamera::get_res(QString res_string) {    //320_x_240-> 320,240 {
    auto list = res_string.split("_x_");
    xclu_assert(list.size() == 2, "Can't start camera, bad resolution string " + res_string);
    int2 res(list.at(0).toInt(), list.at(1).toInt());
    xclu_assert(res.x > 0 && res.y > 0, QString("Can't start camera, bad resolution %1x%2").arg(res.x).arg(res.y));
    return res;
}

//---------------------------------------------------------------------
int RtModuleRealsenseCamera::get_frame_rate(QString rate_string) {
    int fps = rate_string.toInt();
    xclu_assert(fps > 0, QString("Can't start camera, bad frame rate %1").arg(fps));
    return fps;
}

//---------------------------------------------------------------------
void RtModuleRealsenseCamera::set_started(bool started) { //ставит camera_started_ и gui-элемент is_started
    camera_started_ = started;
    set_int("is_started", started);
}


//---------------------------------------------------------------------


