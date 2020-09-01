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
    clear_string("port_info");
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
    //Очистка переменных
    gui_clear();

    //открытие порта
    open_port();
}

//---------------------------------------------------------------------
void RtModuleSerial::open_port() {
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    int n = serialPortInfos.count();

    if (n == 0) {
        //TODO сейчас просто игнорируем ошибку
        xclu_console_append("Error: No Serial devices");
        return;
    }

    int index0 = -1;
    int index1 = -1;

    int select_port = get_int("select_port");
    switch (select_port) {
    case SelectDeviceDefault: {
        index0 = 0;
        index1 = 0;
    }
        break;
    case SelectDeviceByIndex: {
        index0 = get_int("port_index0");
        index1 = get_int("port_index1");
        xclu_assert(index0 >= 0 && index1 >= index0, QString("Bad port index range %1-%2").arg(index0).arg(index1));
        xclu_assert(index1 < n, QString("Bad port 'to' index %1, because connected devices: ").arg(index1));
    }
        break;
    case SelectDeviceByName: {
        QString port_name = get_string("port_name");
        int k = 0;
        for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
            QString name = serialPortInfo.portName();
            if (name.contains(port_name)) {
               index0 = k;
               index1 = k;
               break;
            }
            k++;
        }
        xclu_assert(k >= 0, "No port containing '" + port_name+ "'");
        index0 = k;
        index1 = k;
    }
        break;
    default:
        xclu_exception("Bad `select_port` value");
    }

    //Это не должно показываться пользователю, а проверка нашей логики
    xclu_assert(index0 >= 0 && index1 >= 0, "Internal error: No port to connect");

    //Скорость подключения
    int baud_rate = get_string("baud_rate").toInt();
    xclu_assert(baud_rate>0, QString("Bad baud rate %1").arg(baud_rate));

    //Поиск свободного порта
    int k = 0;
    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        if (k >= index0 && k <= index1) {
            if (!serialPortInfo.isBusy()) {
                //подключение
                serialPort_.setPort(serialPortInfo);
                serialPort_.setBaudRate(baud_rate);
                xclu_assert(serialPort_.open(QIODevice::ReadWrite),
                    QString("Failed to open port %1, error: %2")
                            .arg(serialPortInfo.portName()).arg(serialPort_.errorString()));
                set_connected(true);

                QString port_info = "port_info";
                clear_string(port_info);
                append_string(port_info, QString("Port: %1").arg(k));
                append_string(port_info, QString("Name: %1").arg(serialPortInfo.portName()));
                append_string(port_info, QString("Location: %1").arg(serialPortInfo.systemLocation()));
                append_string(port_info, QString("Description: %1").arg((!serialPortInfo.description().isEmpty() ? serialPortInfo.description() : "N/A")));
                break;
            }
        }
        k++;
    }

    xclu_assert(connected_, "Can't connect, all selected ports are busy");
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
    if (connected_) {
        serialPort_.close();
        set_connected(false);
    }
}




//---------------------------------------------------------------------


