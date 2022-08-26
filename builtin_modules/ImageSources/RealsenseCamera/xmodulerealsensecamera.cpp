#include "xmodulerealsensecamera.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QProcess>
#include "project_props.h"
#include <QDateTime>
//#include <QImageWriter>
//#include <QImageReader>

#include "xobjectimage.h"

//registering module implementation
REGISTER_XMODULE(RealsenseCamera)


//---------------------------------------------------------------------
XModuleRealsenseCamera::XModuleRealsenseCamera(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XModuleRealsenseCamera::~XModuleRealsenseCamera()
{
    stop();
}

//---------------------------------------------------------------------
void XModuleRealsenseCamera::on_loaded() {
    gui_clear();
}

//---------------------------------------------------------------------
//нажатие кнопки, даже когда модуль остановлен - модуль также должен переопределить эту функцию
//внимание, обычно вызывается из основного потока как callback
void XModuleRealsenseCamera::on_button_pressed(QString button_id) {
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
    clear_string_device_list();
    append_string_device_list(out, 1);

}

//---------------------------------------------------------------------
void XModuleRealsenseCamera::gui_clear() {
    clear_string_device_list();
    clear_string_connected_device_info();
    clear_string_saved_to();
    seti_is_new_frame(0);
    seti_frame(0);

    set_started(false); //также ставит gui-элемент is_started
}

//---------------------------------------------------------------------
void XModuleRealsenseCamera::start() {
    //здесь мы не стартуем камеру, так как делаем это в update
    //в зависимости от capture_source

    //Очистка переменных
    gui_clear();

    getobject_color_image()->clear();
    getobject_depth_image()->clear();
    getobject_ir_image()->clear();

    raster_color_.clear();
    raster_depth_.clear();
    raster_ir_.clear();

    is_new_frame = 0;
    processed_frames_ = 0;
    wait_save_frames_ = 0;

    //transform
    //link images with internal objects
    setobject_depth_grayscale_image(&depth8_gui_);
    //setobject_depth_grayscale_image(&out_binary_gui_);

    depth8_gui_.clear();
    //out_binary_gui_.clear();

    raster_depth16_.clear();
    depth8_.clear();
    //out_binary_.clear();

    //start camera or BAG file
    start_camera();

}

//---------------------------------------------------------------------
void XModuleRealsenseCamera::update() {
    //если нажата кнопка - поставить флажок ожидания записи кадров на диск
    if (geti_save_frames_button()) {
        wait_save_frames_ = 1;
    }
    bool save_each_frame = geti_save_each_frame();

    bool need_save = wait_save_frames_ || save_each_frame;

    //TODO сделать возможность обработки кадров по callback
    //- а сейчас реализовано из основного потока

    //если камера не стартовала - то делать нечего
    //TODO возможно стоит попробовать запустить камеру снова через некоторое время
    if (!camera_started_) return;

    //на всякий случай ставим, что нет новых кадров
    //чтобы в случае ошибки не осталось "1"
    seti_is_new_frame(0);

    camera_.update();
    bool is_new_frame = camera_.isFrameNew();
    //обрабатываем только новые кадры
    if (is_new_frame) {
        seti_is_new_frame(1);
        processed_frames_++;

        //метка числа обработанных кадров
        seti_frame(processed_frames_);

        //установка изображений и запись их на диск, если нужно
        //TODO оптимизация: устранить создание промежуточного растра raster !

        bool make_color = false;
        bool make_depth = false;
        bool make_ir = false;
        if ((geti_show_color() || need_save) && camera_.settings().use_rgb) {
            xc_assert(camera_.get_color_pixels_rgb(raster_color_), "get_color_pixels_rgb() returned false");
            XObjectImage::create_from_raster(getobject_color_image(), raster_color_);
            make_color = true;
        }
        if ((geti_show_depth() || need_save) && camera_.settings().use_depth) {
            xc_assert(camera_.get_depth_pixels_rgb(raster_depth_), "get_depth_pixels_rgb() returned false");
            XObjectImage::create_from_raster(getobject_depth_image(), raster_depth_);
            make_depth = true;
        }
        if ((geti_show_ir() || need_save) && camera_.settings().use_ir) {
            xc_assert(camera_.get_ir_pixels8(raster_ir_), "get_ir_pixels8() returned false");
            XObjectImage::create_from_raster(getobject_ir_image(), raster_ir_);
            make_ir = true;
        }

        //generate transformed images
        transform();


        //если требуется - записать на диск
        if (wait_save_frames_) {
            bool timestamp = true;
            save_frames(make_color, make_depth, make_ir, timestamp);
            wait_save_frames_ = 0;
        }
        if (save_each_frame) {
            bool timestamp = false;
            save_frames(make_color, make_depth, make_ir, timestamp);
        }

    }

}

//---------------------------------------------------------------------
//запись кадра на диск
void XModuleRealsenseCamera::save_frames(bool color, bool depth, bool ir, bool use_timestamp) {
    xc_assert(!depth, "XModuleRealsenseCamera::save_frames - saving depth is not implemented");

    //Создаем папку для записи
    QString folder = xc_absolute_path_from_project(gets_save_folder(), true /*create_folder*/);

    //Create file names
    QString file_color, file_ir, file_depth;
    QString saved_to;

    if (use_timestamp) {
        //[timestamp]_color.png

        //время
        /*dd.MM.yyyy    21.05.2001
        ddd MMMM d yy     Tue May 21 01
        hh:mm:ss.zzz    14:13:09.120
        hh:mm:ss.z     14:13:09.12
        h:m:s ap    2:13:9 pm*/

        QString time_format = "yy_MM_dd_hh_mm_ss_zzz";
        auto time = QDateTime::currentDateTime();

        QString path = folder + "/" + time.toString(time_format);

        file_color = path + "_color.png";
        file_ir = path + "_ir.png";
        file_depth = path + "_depth8.png";

        saved_to = path;
    }
    else {
        //color_00001.png and so on.
        QString frame = QString::number(processed_frames_).rightJustified(5, '0');
        file_color = QString("%1/color_%2.png").arg(folder).arg(frame);
        file_ir = QString("%1/ir_%2.png").arg(folder).arg(frame);
        file_depth = QString("%1/depth_%2.png").arg(folder).arg(frame);

        saved_to = folder + " " + frame;
    }

    //запись
    if (color && geti_save_color()) {
        XRaster::save(raster_color_, file_color, "PNG", 100);
    }
    //TODO save 16 bit
    //if (depth) {
    //   XRaster::save(depth_, path + "_depth16.png", "PNG", 100);
    //}
    if (ir && geti_save_ir()) {
        XRaster::save(raster_ir_, file_ir, "PNG", 100);
    }
    if (!depth8_.is_empty() && geti_save_depth8()) {
        XRaster::save(depth8_, file_depth, "PNG", 100);
    }
    sets_saved_to(saved_to);

}

//---------------------------------------------------------------------
void XModuleRealsenseCamera::stop() {
    if (camera_started_) {
        camera_.close();
        set_started(false);
    }

}

//---------------------------------------------------------------------
void XModuleRealsenseCamera::start_camera() {
    //запуск камеры

    auto capture_source = gete_capture_source();
    if (capture_source == capture_source_Disable) return;
    if (capture_source == capture_source_Bag_File) {
        //Load BAG file
        QString file_name = xc_absolute_path_from_project(gets_bag_file());
        xc_assert(xc_file_exists(file_name), "File '" + file_name + "' doesn't exists");
        camera_.start_bag(file_name);
        sets_connected_device_info("Playing BAG file '" + file_name + "'");
    }
    if (capture_source == capture_source_Camera) {
        //Start Realsense Camera
        QVector<RealsenseCameraInfo> cameras = RealsenseCamera::get_connected_devices_info();
        xc_assert(!cameras.empty(), "No connected devices");

        int device_index = -1;
        auto method = gete_select_device();
        switch (method) {
        case select_device_Default:
            device_index = 0;
            break;
        case select_device_By_Index:
            device_index = geti_device_index();
            xc_assert(device_index >= 0 && device_index < cameras.size(), "Bad device index " + QString::number(device_index));
            break;
        case select_device_By_Serial: {
            QString serial = gets_device_serial();
            for (int i=0; i<cameras.size(); i++) {
                if (cameras[i].serial == serial) {
                    device_index = i;
                    break;
                }
            }
            xc_assert(device_index >= 0, "No device with serial '" + serial + "'");
            break;
        }
        default:
            //мы здесь не должны быть, так как все методы запуска рассмотренли,
            //поэтому выдаем ошибку
            xc_exception(QString("Internal error, bad select_device value '%1'").arg(method));
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
            sets_connected_device_info(cameras[device_index].descr_short);
            //append_string_device_list", "Starting: " + device_name, 1);
        }

    }
}

//---------------------------------------------------------------------
//заполнение настроек камеры из интерфейса
RealsenseSettings XModuleRealsenseCamera::get_settings() {
    RealsenseSettings s;

    //RGB
    s.use_rgb = geti_color_stream_enabled();
    if (s.use_rgb) {
        int2 res = get_res(getraw_color_resolution());
        s.rgb_w = res.x;
        s.rgb_h = res.y;
        s.rgb_fps = get_frame_rate(getraw_color_frame_rate());
    }

    //Depth & IR
    s.use_depth = geti_depth_stream_enabled();
    s.use_ir = geti_ir_stream_enabled();
    s.visual_preset = gete_depth_preset();  //TODO convert string->RealsenseSDK enum values
    s.use_emitter = geti_emitter();
    if (s.use_depth || s.use_ir) {
        int2 res = get_res(getraw_depth_resolution());
        s.depth_w = res.x;
        s.depth_h = res.y;
        s.depth_fps = get_frame_rate(getraw_depth_frame_rate());
    }

    s.align_to_depth = geti_align_to_depth();

    return s;
}

//---------------------------------------------------------------------
int2 XModuleRealsenseCamera::get_res(QString res_string) {    //320_x_240-> 320,240 {
    auto list = res_string.split("_x_");
    xc_assert(list.size() == 2, "Can't start camera, bad resolution string " + res_string);
    int2 res(list.at(0).toInt(), list.at(1).toInt());
    xc_assert(res.x > 0 && res.y > 0, QString("Can't start camera, bad resolution %1x%2").arg(res.x).arg(res.y));
    return res;
}

//---------------------------------------------------------------------
int XModuleRealsenseCamera::get_frame_rate(QString rate_string) {
    int fps = rate_string.toInt();
    xc_assert(fps > 0, QString("Can't start camera, bad frame rate %1").arg(fps));
    return fps;
}

//---------------------------------------------------------------------
void XModuleRealsenseCamera::set_started(bool started) { //ставит camera_started_ и gui-элемент is_started
    camera_started_ = started;
    seti_is_started(started);
}

//---------------------------------------------------------------------
//compute transformed depth to grayscale 8 bit and binary image
void XModuleRealsenseCamera::transform() {
    if (geti_make_depth_grayscale()) {
        xc_assert(camera_.get_depth_pixels_mm(raster_depth16_), "get_depth_pixels_mm() returned false");
        //XObjectImage::create_from_raster(getobject_color_image(), raster_color_);

        //crop
        auto &input = raster_depth16_;
        auto &output = depth8_;
        int w = input.w;
        int h = input.h;
        int x0 = int(w * getf_depth_grayscale_x0());
        int x1 = int(w * getf_depth_grayscale_x1());
        int y0 = int(h * getf_depth_grayscale_y0());
        int y1 = int(h * getf_depth_grayscale_y1());
        if (x0 > x1) qSwap(x0, x1);
        if (y0 > y1) qSwap(y0, y1);
        int w1 = x1 - x0;
        int h1 = y1 - y0;

        int in0 = geti_depth_grayscale_thresh_near_mm();
        int in1 = geti_depth_grayscale_thresh_far_mm();
        int out0 = geti_depth_grayscale_output0();
        int out1 = geti_depth_grayscale_output1();

        output.allocate(w1, h1);
        if (in1 == in0) {
            for (int y=0; y<h1; y++) {
                for (int x=0; x<w1; x++) {
                    output.pixel_unsafe(x, y) = (out0+out1)/2;
                }
            }
        }
        else {
            for (int y=0; y<h1; y++) {
                for (int x=0; x<w1; x++) {
                    int v = input.pixel_unsafe(x+x0, y+y0);
                    //zero depth value means junk pixel
                    if (v > 0) v = xmapi_clamped(v, in0, in1, out0, out1);
                    else v = out1;
                    output.pixel_unsafe(x, y) = v;
                }
            }
        }

        //set output
        XObjectImage::create_from_raster(depth8_gui_, output);

    }

}

//---------------------------------------------------------------------


