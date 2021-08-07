#include "xmoduleserial.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xc_project.h"
#include <QtSerialPort/QSerialPortInfo>

REGISTER_XMODULE(Serial)

//---------------------------------------------------------------------
XModuleSerial::XModuleSerial(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
void XModuleSerial::gui_clear() {
    seti_total_sent(0);
    clear_string_device_list();
    clear_string_port_info();
    set_connected(false); //также ставит gui-элемент connected
    port_name_ = "";
    set_total_sent(0);

    clear_string_received_line();
    clear_string_received_text();
    clear_string_received_bytes();

    in_string_.clear();
}

//---------------------------------------------------------------------
void XModuleSerial::set_connected(bool connected) {
  connected_ = connected;
  seti_connected(connected);
}

//---------------------------------------------------------------------
void XModuleSerial::set_total_sent(int t) {
    total_sent_ = t;
    seti_total_sent(t);
}

//---------------------------------------------------------------------
XModuleSerial::~XModuleSerial()
{
    stop();
}

//---------------------------------------------------------------------
void XModuleSerial::on_loaded() {
    gui_clear();
}

//---------------------------------------------------------------------
//нажатие кнопки, даже когда модуль остановлен - модуль также должен переопределить эту функцию
//внимание, обычно вызывается из основного потока как callback
void XModuleSerial::on_button_pressed(QString button_id) {
    if (button_id == "print_devices") {
        print_devices();
    }

    if (general_is_enabled()) {
        bool connect_warning = false;
        //-----------------------
        //TODO duplication in code
        //send string
        if (button_id == button_send_string_btn()) {
            if (connected_) {
                send_string(gets_send_string());
            }
            else {
                connect_warning = true;
            }
        }
        if (button_id == button_send_string2_btn()) {
            if (connected_) {
                send_string(gets_send_string2());
            }
            else {
                connect_warning = true;
            }
        }
        if (button_id == button_send_string3_btn()) {
            if (connected_) {
                send_string(gets_send_string3());
            }
            else {
                connect_warning = true;
            }
        }
        if (button_id == button_send_string4_btn()) {
            if (connected_) {
                send_string(gets_send_string4());
            }
            else {
                connect_warning = true;
            }
        }
        if (button_id == button_send_string5_btn()) {
            if (connected_) {
                send_string(gets_send_string5());
            }
            else {
                connect_warning = true;
            }
        }
        if (button_id == button_send_string6_btn()) {
            if (connected_) {
                send_string(gets_send_string6());
            }
            else {
                connect_warning = true;
            }
        }
        if (button_id == button_send_string7_btn()) {
            if (connected_) {
                send_string(gets_send_string7());
            }
            else {
                connect_warning = true;
            }
        }
        if (button_id == button_send_string8_btn()) {
            if (connected_) {
                send_string(gets_send_string8());
            }
            else {
                connect_warning = true;
            }
        }
        //-----------------------
        if (button_id == button_send_string_link_btn()) {
            if (connected_) {
                QString str = xc_get_string_by_link(gets_string_link_send());
                send_string(str);
            }
            else {
                connect_warning = true;
            }
        }

        if (button_id == button_send_bytes_btn()) {
            if (connected_) {
                int byte = geti_send_byte();
                send_byte(byte);
            }
            else {
                connect_warning = true;
            }
        }

        if (connect_warning) {
            //xc_message_box("Serial: Port is not connected, may be you need to start the project.");
            xc_console_warning("Serial: Port is not connected, may be you need to start the project.");
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
    clear_string_device_list();
    append_string_device_list(out, 1);
}



//---------------------------------------------------------------------
void XModuleSerial::start() {
    //Очистка переменных
    gui_clear();

    //открытие порта
    open_port();

    //watchdog
    watchdog_sent_ = -100000;
}

//---------------------------------------------------------------------
void XModuleSerial::open_port() {
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    int n = serialPortInfos.count();

    if (n == 0) {
        //TODO сейчас просто игнорируем ошибку
        xc_console_append("Error: No Serial devices");
        return;
    }

    int index0 = -1;
    int index1 = -1;

    auto select_port = gete_select_port();
    switch (select_port) {
    case select_port_Default: {
        index0 = 0;
        index1 = 0;
    }
        break;
    case select_port_By_Index: {
        index0 = geti_port_index0();
        index1 = geti_port_index1();
        xc_assert(index0 >= 0 && index1 >= index0, QString("Bad port index range %1-%2").arg(index0).arg(index1));
        xc_assert(index1 < n, QString("Bad port 'to' index %1, because connected devices: ").arg(index1));
    }
        break;
    case select_port_By_Name: {
        QString port_name = gets_port_name();
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
        xc_assert(k >= 0, "No port containing '" + port_name+ "'");
        index0 = k;
        index1 = k;
    }
        break;
    default:
        xc_exception("Bad `select_port` value");
    }

    //Это не должно показываться пользователю, а проверка нашей логики
    xc_assert(index0 >= 0 && index1 >= 0, "Internal error: No port to connect");

    //Скорость подключения
    int baud_rate = getraw_baud_rate().toInt();
    xc_assert(baud_rate>0, QString("Bad baud rate %1").arg(baud_rate));

    //Поиск свободного порта
    int k = 0;
    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        if (k >= index0 && k <= index1) {
            if (!serialPortInfo.isBusy()) {
                //подключение
                serialPort_.setPort(serialPortInfo);
                serialPort_.setBaudRate(baud_rate);
                xc_assert(serialPort_.open(QIODevice::ReadWrite),
                    QString("Failed to open port %1, error: %2")
                            .arg(serialPortInfo.portName()).arg(serialPort_.errorString()));
                set_connected(true);

                port_name_ = serialPortInfo.portName();

                QString port_info = "port_info";
                clear_string_port_info();
                append_string_port_info(QString("Port: %1").arg(k));
                append_string_port_info(QString("Name: %1").arg(serialPortInfo.portName()));
                append_string_port_info(QString("Location: %1").arg(serialPortInfo.systemLocation()));
                append_string_port_info(QString("Description: %1").arg((!serialPortInfo.description().isEmpty() ? serialPortInfo.description() : "N/A")));
                break;
            }
        }
        k++;
    }

    xc_assert(connected_, "Can't connect, all selected ports are busy");
}

//---------------------------------------------------------------------
void XModuleSerial::update() {
    //sending data processes at on_button_pressed

    //receiving data
    receive();

    //watchdog
    double time = xc_elapsed_time_sec();
    if (geti_watchdog_send()) {
        if (time >= watchdog_sent_ + getf_watchdog_send_period()) {
            send_string(gets_watchdog_message());
            watchdog_sent_ = time;
        }

    }
}

//---------------------------------------------------------------------
void XModuleSerial::send_string(QString str) {
    //добавляем завершение строки
    auto ts = gete_line_term(); //None,\n,\r,\r\n
    if (ts == line_term__n) str += "\n";
    if (ts == line_term__r) str += "\r";
    if (ts == line_term__r_n) str += "\r\n";

    if (geti_debug()) {
        xc_console_append("Send string `" + str + "`");
    }

    if (connected_ && !str.isEmpty()) {
        QByteArray writeData;
        writeData.append(str.toLatin1());

        qint64 bytesWritten = serialPort_.write(writeData);
        if (bytesWritten == -1) {
            xc_console_append(QString("Failed to write the data to port %1, error: %2")
                                .arg(port_name_).arg(serialPort_.errorString()));
        }

        set_total_sent(total_sent_ + bytesWritten);
        if (bytesWritten != writeData.size()) {
            xc_console_append(QString("Failed to write all the data to port %1, error: %2")
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
    if (geti_debug()) {
        xc_console_append("Send byte `" + QString::number(byte) + "`");
    }
    xc_exception("Sending byte is not implented");

    //Пометить, что отправили
    //set_total_sent(total_sent_ + 1);

}

//---------------------------------------------------------------------
void XModuleSerial::stop() {
    if (connected_) {
        serialPort_.close();
        set_connected(false);
    }
}


//---------------------------------------------------------------------
void XModuleSerial::receive() {
    if (connected_ && geti_receive()) {
        const int N = 50;
        char buffer[N];
        int numReadTotal = 0;
        for (;;) {
            int n = serialPort_.read(buffer, N);
            numReadTotal += n;
            if (n == 0) {
                break;
            }

            //TODO here should be switch of mode

            //scan for "\n", ignore "\r"
            for (int i=0; i<n; i++) {
                if (buffer[i] == '\r') continue;
                if (buffer[i] == '\n') {
                    sets_received_line(in_string_);
                    in_string_.clear();
                    continue;
                }
                in_string_.append(buffer[i]);
            }
        }
    }

}


//---------------------------------------------------------------------


