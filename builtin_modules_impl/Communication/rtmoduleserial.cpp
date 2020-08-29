#include "rtmoduleserial.h"
#include "incl_cpp.h"
#include "rtmoduleregistrar.h"
#include "projectruntime.h"

REGISTRAR(Serial)

//---------------------------------------------------------------------
/*static*/ RtModuleSerial *RtModuleSerial::new_module() {
    return new RtModuleSerial();
}

//---------------------------------------------------------------------
RtModuleSerial::RtModuleSerial()
    :RtModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
void RtModuleSerial::gui_clear() {
    /*clear_string("device_list");
    clear_string("connected_device_info");
    set_started(false); //также ставит gui-элемент is_started
    */
}
//---------------------------------------------------------------------
RtModuleSerial::~RtModuleSerial()
{
    execute_stop_internal();
}

//---------------------------------------------------------------------
void RtModuleSerial::execute_loaded_internal() {
    gui_clear();
}

//---------------------------------------------------------------------
//нажатие кнопки, даже когда модуль остановлен - модуль также должен переопределить эту функцию
//внимание, обычно вызывается из основного потока как callback
void RtModuleSerial::button_pressed_internal(QString button_id) {
    if (button_id == "print_devices") {
        print_devices();
    }
}

//---------------------------------------------------------------------
void RtModuleSerial::print_devices() {
  /*  QStringList out;
    out.append(QString("Realsense SDK: %1").arg(RealsenseCamera::get_sdk_version()));
    int n = RealsenseCamera::get_number_of_connected_devices();
    out.append(QString("Number of Realsense devices: %1").arg(n));
    if (n > 0) {
        out.append(RealsenseCamera::get_connected_devices_list());
    }
    clear_string("device_list");
    append_string("device_list", out, 1);
*/
}



//---------------------------------------------------------------------
void RtModuleSerial::execute_start_internal() {
  /*  //здесь мы не стартуем камеру, так как делаем это в update
    //в зависимости от capture_source

    //Очистка переменных
    gui_clear();

    ObjectReadWrite(get_object("color_image")).clear();
    ObjectReadWrite(get_object("depth_image")).clear();
    ObjectReadWrite(get_object("ir_image")).clear();

    is_new_frame = 0;
    processed_frames_ = 0;
    wait_save_frames_ = 0;

    //запуск камеры или воспроизведения файла
    start_camera();
    */
}

//---------------------------------------------------------------------
void RtModuleSerial::execute_update_internal() {
    /*
    //если нажата кнопка - поставить флажок ожидания записи кадров на диск
    if (get_int("save_frames_button")) {
        wait_save_frames_ = 1;
    }

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

        //установка изображений и запись их на диск, если нужно
        //TODO оптимизация: устранить создание промежуточного растра raster !

        bool make_color = false;
        bool make_depth = false;
        bool make_ir = false;
        if ((get_int("show_color") || wait_save_frames_) && camera_.settings().use_rgb) {
            Raster_u8c3 raster_color;
            xclu_assert(camera_.get_color_pixels_rgb(raster_color), "get_color_pixels_rgb() returned false");
            ObjectReadWrite image(get_object("color_image"));
            XcluObjectImage::create_from_raster(image, raster_color);
            make_color = true;
        }
        if ((get_int("show_depth") || wait_save_frames_) && camera_.settings().use_depth) {
            Raster_u8c3 raster_depth;
            xclu_assert(camera_.get_depth_pixels_rgb(raster_depth), "get_depth_pixels_rgb() returned false");
            ObjectReadWrite image(get_object("depth_image"));
            XcluObjectImage::create_from_raster(image, raster_depth);
            make_depth = true;
        }
        if ((get_int("show_ir") || wait_save_frames_) && camera_.settings().use_ir) {
            Raster_u8 raster_ir;
            xclu_assert(camera_.get_ir_pixels8(raster_ir), "get_ir_pixels8() returned false");
            ObjectReadWrite image(get_object("ir_image"));
            XcluObjectImage::create_from_raster(image, raster_ir);
            make_ir = true;
        }
        //если требуется - записать на диск
        if (wait_save_frames_) {
            save_frames(make_color, make_depth, make_ir);
        }

        wait_save_frames_ = 0;
    }

*/

}

//---------------------------------------------------------------------
void RtModuleSerial::execute_stop_internal() {
    /*if (camera_started_) {
        camera_.close();
        set_started(false);
    }
*/
}

//---------------------------------------------------------------------
void RtModuleSerial::set_started(bool started) { //ставит camera_started_ и gui-элемент is_started
  /*  camera_started_ = started;
    set_int("is_started", started);
    */
}


//---------------------------------------------------------------------


