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

        seti_received_total_bytes(0);
        seti_received_new_data(0);
    }
    if (gete_mode() == mode_Receive) {
        seti_received_total_bytes(0);
        seti_received_new_data(0);

        udpSocket.reset(new QUdpSocket(this));
        udpSocket->bind(geti_receive_port(), QUdpSocket::ShareAddress);
        //udpSocket.bind(QHostAddress::Any, geti_receive_port(), QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
        connect(udpSocket.data(), &QUdpSocket::readyRead, this, &XClassUdp::readPendingDatagrams);
    }
}

//---------------------------------------------------------------------
void send_start() {

}

//---------------------------------------------------------------------
void send_update() {

}

//---------------------------------------------------------------------
void receive_start() {

}

//---------------------------------------------------------------------
void receive_update() {

}


//---------------------------------------------------------------------
void XClassUdp::read_file(QString file_name)
{

}

//---------------------------------------------------------------------
void XClassUdp::readPendingDatagrams()
{
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) {
        int size = int(udpSocket->pendingDatagramSize());
        seti_received_total_bytes(geti_received_total_bytes() + size);

        datagram.resize(size);
        int read_size = udpSocket->readDatagram(datagram.data(), datagram.size());

        // Примечание: здесь исключение может возникнуть в параллельном потоке,
        // но я надеюсь, что оно вообще никогда не возникает, поэтому оставляю его так.
        xc_assert(read_size == size, "Error at XClassUdp::readPendingDatagrams, read_size != size");

        //statusLabel->setText(tr("Received datagram: \"%1\"")
        //                     .arg(datagram.constData()));
    }

}

//---------------------------------------------------------------------
void XClassUdp::update() {


}

//---------------------------------------------------------------------
void XClassUdp::stop() {
    if (gete_mode() == mode_Receive) {
        udpSocket.reset();
    }
}

//---------------------------------------------------------------------
