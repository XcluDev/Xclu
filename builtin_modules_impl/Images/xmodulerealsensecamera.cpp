#include "xmodulerealsensecamera.h"
#include "incl_cpp.h"
#include "rtmoduleregistrar.h"
#include <QProcess>
#include "projectruntime.h"
#include <QDateTime>
//#include <QImageWriter>
//#include <QImageReader>

#include "xcluobjectimage.h"

//заполнение имени класса и регистрация класса
REGISTRAR(RealsenseCamera)


//---------------------------------------------------------------------
/*static*/ XModuleRealsenseCamera *XModuleRealsenseCamera::new_module() {
    return new XModuleRealsenseCamera();
}

//---------------------------------------------------------------------
XModuleRealsenseCamera::XModuleRealsenseCamera()
    :XModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
XModuleRealsenseCamera::~XModuleRealsenseCamera()
{
    impl_stop();
}

//---------------------------------------------------------------------
void XModuleRealsenseCamera::impl_loaded() {
    gui_clear();
}

//---------------------------------------------------------------------
//нажатие кнопки, даже когда модуль остановлен - модуль также должен переопределить эту функцию
//внимание, обычно вызывается из основного потока как callback
void XModuleRealsenseCamera::impl_button_pressed(QString button_id) {
    if (button_id == "print_devices") {
        print_devices();
    }
}

//---------------------------------------------------------------------
void XModuleRealsenseCamera::print_devices() {
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
void XModuleRealsenseCamera::gui_clear() {
    clear_string("device_list");
    clear_string("connected_device_info");
    clear_string("saved_to");
    seti("is_new_frame", 0);
    clear_string("frames_captured");

    set_started(false); //также ставит gui-элемент is_started
}

//---------------------------------------------------------------------
void XModuleRealsenseCamera::impl_start() {
    //здесь мы не стартуем камеру, так как делаем это в update
    //в зависимости от capture_source

    //Очистка переменных
    gui_clear();

    XDictWrite(get_object("color_image")).clear();
    XDictWrite(get_object("depth_image")).clear();
    XDictWrite(get_object("ir_image")).clear();

    is_new_frame = 0;
    processed_frames_ = 0;
    wait_save_frames_ = 0;

    //запуск камеры или воспроизведения файла
    start_camera();
}

//---------------------------------------------------------------------
void XModuleRealsenseCamera::impl_update() {
    //если нажата кнопка - поставить флажок ожидания записи кадров на диск
    if (geti("save_frames_button")) {
        wait_save_frames_ = 1;
    }

    //TODO сделать возможность обработки кадров по callback
    //- а сейчас реализовано из основного потока

    //если камера не стартовала - то делать нечего
    //TODO возможно стоит попробовать запустить камеру снова через некоторое время
    if (!camera_started_) return;

    //на всякий случай ставим, что нет новых кадров
    //чтобы в случае ошибки не осталось "1"
    seti("is_new_frame", 0);

    camera_.update();
    bool is_new_frame = camera_.isFrameNew();
    //обрабатываем только новые кадры
    if (is_new_frame) {
        seti("is_new_frame", 1);
        processed_frames_++;

        //метка числа обработанных кадров
        QString processed = QString("Processed %1 frame(s)").arg(processed_frames_);
        sets("frames_captured", processed);

        //установка изображений и запись их на диск, если нужно
        //TODO оптимизация: устранить создание промежуточного растра raster !

        bool make_color = false;
        bool make_depth = false;
        bool make_ir = false;
        if ((geti("show_color") || wait_save_frames_) && camera_.settings().use_rgb) {
            Raster_u8c3 raster_color;
            xclu_assert(camera_.get_color_pixels_rgb(raster_color), "get_color_pixels_rgb() returned false");
            XDictWrite image(get_object("color_image"));
            XDictImage::create_from_raster(image, raster_color);
            make_color = true;
        }
        if ((geti("show_depth") || wait_save_frames_) && camera_.settings().use_depth) {
            Raster_u8c3 raster_depth;
            xclu_assert(camera_.get_depth_pixels_rgb(raster_depth), "get_depth_pixels_rgb() returned false");
            XDictWrite image(get_object("depth_image"));
            XDictImage::create_from_raster(image, raster_depth);
            make_depth = true;
        }
        if ((geti("show_ir") || wait_save_frames_) && camera_.settings().use_ir) {
            Raster_u8 raster_ir;
            xclu_assert(camera_.get_ir_pixels8(raster_ir), "get_ir_pixels8() returned false");
            XDictWrite image(get_object("ir_image"));
            XDictImage::create_from_raster(image, raster_ir);
            make_ir = true;
        }
        //если требуется - записать на диск
        if (wait_save_frames_) {
            save_frames(make_color, make_depth, make_ir);
        }

        wait_save_frames_ = 0;
    }



}

//---------------------------------------------------------------------
//запись кадра на диск
void XModuleRealsenseCamera::save_frames(bool color, bool depth, bool ir) {
    //Создаем папку для записи
    QString folder = rt_path(gets("save_folder"), true /*create_folder*/);

    //время
    /*dd.MM.yyyy    21.05.2001
    ddd MMMM d yy     Tue May 21 01
    hh:mm:ss.zzz    14:13:09.120
    hh:mm:ss.z     14:13:09.12
    h:m:s ap    2:13:9 pm*/

    QString time_format = "yy_MM_dd_hh_mm_ss_zzz";
    auto time = QDateTime::currentDateTime();

    //запись
    QString path = folder + "/" + time.toString(time_format);
    if (color) {
        XDictRead image(get_object("color_image"));
        XDictImage::save(image, path + "_color.png", "PNG", 100);
    }
    if (depth) {
        XDictRead image(get_object("depth_image"));
        XDictImage::save(image, path + "_depth.png", "PNG", 100);
    }
    if (ir) {
        XDictRead image(get_object("ir_image"));
        XDictImage::save(image, path + "_ir.png", "PNG", 100);
    }
    sets("saved_to", path);

}

//---------------------------------------------------------------------
void XModuleRealsenseCamera::impl_stop() {
    if (camera_started_) {
        camera_.close();
        set_started(false);
    }

}

//---------------------------------------------------------------------
void XModuleRealsenseCamera::start_camera() {
    //запуск камеры

    int capture_source = geti("capture_source");
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
        SelectDevice method = SelectDevice(geti("select_device"));
        switch (method) {
        case SelectDeviceDefault:
            device_index = 0;
            break;
        case SelectDeviceByIndex:
            device_index = geti("device_index");
            xclu_assert(device_index >= 0 && device_index < cameras.size(), "Bad device index " + QString::number(device_index));
            break;
        case SelectDeviceBySerial: {
            QString serial = gets("device_serial");
            for (int i=0; i<cameras.size(); i++) {
                if (cameras[i].serial == serial) {
                    device_index = i;
                    break;
                }
            }
            xclu_assert(device_index >= 0, "No device with serial '" + serial + "'");
            break;
        }
        default:
            //мы здесь не должны быть, так как все методы запуска рассмотренли,
            //поэтому выдаем ошибку
            xclu_exception(QString("Internal error, bad select_device value '%1'").arg(method));
        }
        //TODO может быть нюанс, что список камер изменится пока мы ищем индекс.

        //TODO прикрутить реакцию на отключение камеры
        //connect(camera_.data(), &QCamera::stateChanged, this, &XModuleRealsenseCamera::on_changed_camera_state);
        //connect(camera_.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &XModuleRealsenseCamera::on_camera_error);
        //TODO также, стоит запускать watchdog, чтобы он проверял, что камера не зависла

        //Заполнение настроек
        RealsenseSettings sett = get_settings();

        //Запуск камеры
        bool started = camera_.start_camera(device_index, sett);
        set_started(started);
        if (started) {
            sets("connected_device_info", cameras[device_index].descr_short);
            //append_string("device_list", "Starting: " + device_name, 1);
        }

    }
}

//---------------------------------------------------------------------
//заполнение настроек камеры из интерфейса
RealsenseSettings XModuleRealsenseCamera::get_settings() {
    RealsenseSettings s;

    //RGB
    s.use_rgb = geti("color_stream_enabled");
    if (s.use_rgb) {
        int2 res = get_res(gets("color_resolution"));
        s.rgb_w = res.x;
        s.rgb_h = res.y;
        s.rgb_fps = get_frame_rate(gets("color_frame_rate"));
    }

    //Depth & IR
    s.use_depth = geti("depth_stream_enabled");
    s.use_ir = geti("ir_stream_enabled");
    s.visual_preset = geti("depth_preset");  //TODO convert string->RealsenseSDK enum values
    s.use_emitter = geti("emitter");
    if (s.use_depth || s.use_ir) {
        int2 res = get_res(gets("depth_resolution"));
        s.depth_w = res.x;
        s.depth_h = res.y;
        s.depth_fps = get_frame_rate(gets("depth_frame_rate"));
    }

    s.align_to_depth = geti("align_to_depth");

    return s;
}

//---------------------------------------------------------------------
int2 XModuleRealsenseCamera::get_res(QString res_string) {    //320_x_240-> 320,240 {
    auto list = res_string.split("_x_");
    xclu_assert(list.size() == 2, "Can't start camera, bad resolution string " + res_string);
    int2 res(list.at(0).toInt(), list.at(1).toInt());
    xclu_assert(res.x > 0 && res.y > 0, QString("Can't start camera, bad resolution %1x%2").arg(res.x).arg(res.y));
    return res;
}

//---------------------------------------------------------------------
int XModuleRealsenseCamera::get_frame_rate(QString rate_string) {
    int fps = rate_string.toInt();
    xclu_assert(fps > 0, QString("Can't start camera, bad frame rate %1").arg(fps));
    return fps;
}

//---------------------------------------------------------------------
void XModuleRealsenseCamera::set_started(bool started) { //ставит camera_started_ и gui-элемент is_started
    camera_started_ = started;
    seti("is_started", started);
}


//---------------------------------------------------------------------


