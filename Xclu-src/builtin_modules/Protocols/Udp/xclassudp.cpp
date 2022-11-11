#include "xclassudp.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include <QtNetwork>
#include <QProcess>
#include "project_props.h"


//registering module implementation
REGISTER_XCLASS(Udp)

//---------------------------------------------------------------------
XClassUdp::XClassUdp(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassUdp::~XClassUdp()
{

}

//---------------------------------------------------------------------
void XClassUdp::start() {
    if (gete_mode() == mode_Send) {
        send_start();
    }
    else {
        receive_start();
    }
}

//---------------------------------------------------------------------
void XClassUdp::send_start() {

}

//---------------------------------------------------------------------
void XClassUdp::receive_start() {
    seti_received_packets(0);
    seti_received_new_data(0);
    received_data_.write().data().clear();
    setf_receive_file_position(0);

    if (geti_receive_emulate()) {
        file_ = xc_read_text_file_relpath(gets_receive_emulate_file_name());
        xc_assert(!file_.isEmpty(), "File is empty: " + gets_receive_emulate_file_name());
        file_pos_ = 0;
        timer.reset(new QTimer(this));
        timer->setTimerType(Qt::PreciseTimer);
        connect(timer.data(), &QTimer::timeout, this, &XClassUdp::slot_timer_receive_emulate);
        timer->start(1000 / geti_receive_emulate_rate());
    }
    else {
        udpSocket.reset(new QUdpSocket(this));
        udpSocket->bind(geti_receive_port(), QUdpSocket::ShareAddress);
        //udpSocket.bind(QHostAddress::Any, geti_receive_port(), QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
        connect(udpSocket.data(), &QUdpSocket::readyRead, this, &XClassUdp::slot_readPendingDatagrams);
    }
}

//---------------------------------------------------------------------
void XClassUdp::update() {
    if (gete_mode() == mode_Send) {
        send_update();
    }
    else {
        receive_update();
    }

}

//---------------------------------------------------------------------
void XClassUdp::send_update() {

}

//---------------------------------------------------------------------
void XClassUdp::receive_update() {
    bool received;
    {
        auto write = received_data_.write();  // write должен существовать пока работаем с list
        auto& list = write.data();
        received = (!list.empty());
        if (received) {
            if (geti_receive_only_last_packet()) {
                sets_received_data(list.last());
            }
            else {
                clear_string_received_data();
                append_string_received_data(list);
            }
            list.clear();
        }
    }
    seti_received_new_data(received);
}

//---------------------------------------------------------------------
void XClassUdp::receive_data(QStringList data) {
    increase_int_received_packets();
    received_data_.write().data().append(data);
}

//---------------------------------------------------------------------
void XClassUdp::slot_timer_receive_emulate() {
    file_pos_++;
    int n = file_.size();
    if (file_pos_ >= n) file_pos_ = 0;
    float perc = (n>=2) ? float(file_pos_)/(n-1)*100.f : 0.f;
    setf_receive_file_position(perc);
    receive_data(QStringList() << file_[file_pos_]);
}

//---------------------------------------------------------------------
void XClassUdp::slot_readPendingDatagrams() {
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) {
        int size = int(udpSocket->pendingDatagramSize());

        datagram.resize(size);
        int read_size = udpSocket->readDatagram(datagram.data(), datagram.size());

        // Примечание: здесь исключение может возникнуть в параллельном потоке,
        // но я надеюсь, что оно вообще никогда не возникает, поэтому оставляю его так.
        xc_assert(read_size == size, "Error at XClassUdp::readPendingDatagrams, read_size != size");

        receive_data(QStringList() << datagram.constData());
    }

}

//---------------------------------------------------------------------
void XClassUdp::stop() {
    if (gete_mode() == mode_Send) {
        send_stop();
    }
    else {
        receive_stop();
    }
}

//---------------------------------------------------------------------
void XClassUdp::send_stop() {
    udpSocket.reset();
}

//---------------------------------------------------------------------
void XClassUdp::receive_stop() {
    if (geti_receive_emulate()) {
        timer.reset();
    }
    else {
        udpSocket.reset();
    }
}

//---------------------------------------------------------------------
