#include "rtmoduleserial.h"
#include "incl_cpp.h"
#include "rtmoduleregistrar.h"
#include "projectruntime.h"
#include <QtSerialPort/QSerialPortInfo>

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
    set_int("total_sent",0);
    clear_string("device_list");
    clear_string("connected_device_info");
    set_connected(false); //также ставит gui-элемент connected

}

//---------------------------------------------------------------------
void RtModuleSerial::set_connected(bool connected) {
  connected_ = connected;
  set_int("connected", connected);
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
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    QStringList out;
    out.append(QString("Serial ports available: %1").arg(serialPortInfos.count()));

    const QString blankString = QObject::tr("N/A");
    QString description;
    QString manufacturer;
    QString serialNumber;

    int k = 0;
    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        description = serialPortInfo.description();
        manufacturer = serialPortInfo.manufacturer();
        serialNumber = serialPortInfo.serialNumber();

        out.append(QString("  Port: %1").arg(k++));
        out.append(QString("  Name: %1").arg(serialPortInfo.portName()));
        out.append(QString("  Location: %1").arg(serialPortInfo.systemLocation()));
        out.append(QString("  Description: %1").arg((!description.isEmpty() ? description : blankString)));
        out.append(QString("  Manufacturer: %1").arg((!manufacturer.isEmpty() ? manufacturer : blankString)));
        out.append(QString("  Serial number: %1").arg((!serialNumber.isEmpty() ? serialNumber : blankString)));
        out.append(QString("  Vendor Identifier: %1").arg((serialPortInfo.hasVendorIdentifier() ? QByteArray::number(serialPortInfo.vendorIdentifier(), 16) : blankString)));
        out.append(QString("  Product Identifier: %1").arg((serialPortInfo.hasProductIdentifier() ? QByteArray::number(serialPortInfo.productIdentifier(), 16) : blankString)));
        out.append(QString("  Busy: %1").arg((serialPortInfo.isBusy() ? "Yes" : "No")));
    }
    clear_string("device_list");
    append_string("device_list", out, 1);
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


