#include "xmoduleserial.h"
#include "incl_cpp.h"
#include "xmoduleregistrar.h"
#include "projectruntime.h"
#include <QtSerialPort/QSerialPortInfo>

REGISTRAR(Serial)

//---------------------------------------------------------------------
/*static*/ XModuleSerial *XModuleSerial::new_module() {
    return new XModuleSerial();
}

//---------------------------------------------------------------------
XModuleSerial::XModuleSerial()
    :XModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
void XModuleSerial::gui_clear() {
    seti("total_sent",0);
    clear_string("device_list");
    clear_string("port_info");
    set_connected(false); //также ставит gui-элемент connected
    port_name_ = "";
    set_total_sent(0);
}

//---------------------------------------------------------------------
void XModuleSerial::set_connected(bool connected) {
  connected_ = connected;
  seti("connected", connected);
}

//---------------------------------------------------------------------
void XModuleSerial::set_total_sent(int t) {
    total_sent_ = t;
    seti("total_sent", t);
}

//---------------------------------------------------------------------
XModuleSerial::~XModuleSerial()
{
    impl_stop();
}

//---------------------------------------------------------------------
void XModuleSerial::impl_loaded() {
    gui_clear();
}

//---------------------------------------------------------------------
//нажатие кнопки, даже когда модуль остановлен - модуль также должен переопределить эту функцию
//внимание, обычно вызывается из основного потока как callback
void XModuleSerial::impl_button_pressed(QString button_id) {
    if (button_id == "print_devices") {
        print_devices();
    }

    if (is_enabled()) {
        bool connect_warning = false;
        if (button_id == "send_string_btn") {
            if (connected_) {
                QString str = gets("send_string");
                send_string(str);
            }
            else {
                connect_warning = true;
            }

        }
        if (button_id == "send_string_link_btn") {
            if (connected_) {
                QString str = RUNTIME.get_string_by_link(gets("string_link_send"));
                send_string(str);
            }
            else {
                connect_warning = true;
            }
        }

        if (button_id == "send_bytes_btn") {
            if (connected_) {
                int byte = geti("send_byte");
                send_byte(byte);
            }
            else {
                connect_warning = true;
            }
        }

        if (connect_warning) {
            //xclu_message_box("Serial: Port is not connected, may be you need to start the project.");
            xclu_console_warning("Serial: Port is not connected, may be you need to start the project.");
        }
    }
}

//---------------------------------------------------------------------
void XModuleSerial::print_devices() {
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
void XModuleSerial::impl_start() {
    //Очистка переменных
    gui_clear();

    //открытие порта
    open_port();
}

//---------------------------------------------------------------------
void XModuleSerial::open_port() {
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    int n = serialPortInfos.count();

    if (n == 0) {
        //TODO сейчас просто игнорируем ошибку
        xclu_console_append("Error: No Serial devices");
        return;
    }

    int index0 = -1;
    int index1 = -1;

    int select_port = geti("select_port");
    switch (select_port) {
    case SelectDeviceDefault: {
        index0 = 0;
        index1 = 0;
    }
        break;
    case SelectDeviceByIndex: {
        index0 = geti("port_index0");
        index1 = geti("port_index1");
        xclu_assert(index0 >= 0 && index1 >= index0, QString("Bad port index range %1-%2").arg(index0).arg(index1));
        xclu_assert(index1 < n, QString("Bad port 'to' index %1, because connected devices: ").arg(index1));
    }
        break;
    case SelectDeviceByName: {
        QString port_name = gets("port_name");
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
    int baud_rate = gets("baud_rate").toInt();
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

                port_name_ = serialPortInfo.portName();

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
void XModuleSerial::impl_update() {
   //отработка отправки данных путем нажатия кнопок идет в impl_button_pressed

}

//---------------------------------------------------------------------
void XModuleSerial::send_string(QString str) {
    //добавляем завершение строки
    int ts = geti("line_term"); //None,\n,\r,\r\n
    if (ts == 1) str += "\n";
    if (ts == 2) str += "\r";
    if (ts == 3) str += "\r\n";

    if (geti("debug")) {
        xclu_console_append("Send string `" + str + "`");
    }

    if (connected_ && !str.isEmpty()) {
        QByteArray writeData;
        writeData.append(str);

        qint64 bytesWritten = serialPort_.write(writeData);
        if (bytesWritten == -1) {
            xclu_console_append(QString("Failed to write the data to port %1, error: %2")
                                .arg(port_name_).arg(serialPort_.errorString()));
        }

        set_total_sent(total_sent_ + bytesWritten);
        if (bytesWritten != writeData.size()) {
            xclu_console_append(QString("Failed to write all the data to port %1, error: %2")
                                .arg(port_name_).arg(serialPort_.errorString()));
        }
        //else if (!serialPort.waitForBytesWritten(5000)) {
        //    standardOutput << QObject::tr("Operation timed out or an error occurred for port %1, error: %2").arg(serialPortName).arg(serialPort.errorString()) << endl;
        //    return 1;
        //}
    }
}

//---------------------------------------------------------------------
void XModuleSerial::send_byte(int byte) {
    if (geti("debug")) {
        xclu_console_append("Send byte `" + QString::number(byte) + "`");
    }
    xclu_exception("Sending byte is not implented");

    //Пометить, что отправили
    //set_total_sent(total_sent_ + 1);

}

//---------------------------------------------------------------------
void XModuleSerial::impl_stop() {
    if (connected_) {
        serialPort_.close();
        set_connected(false);
    }
}




//---------------------------------------------------------------------


