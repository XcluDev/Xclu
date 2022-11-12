#pragma once

//UDP sender/receiver implementation

#include "sdk_h.h"
#include <QTimer>
#include "xclass.h"
#include "xnetworkaddr.h"

QT_BEGIN_NAMESPACE
class QUdpSocket;
QT_END_NAMESPACE

class XClassUdp: public XClass
{
public:
    XClassUdp(QString class_name);
    virtual ~XClassUdp();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

protected:
    QScopedPointer<QUdpSocket> udpSocket;

    QStringList file_;  // text file used for reading or emulation
    int file_pos_ = 0;  // line for reading

    // Send
    void send_start();
    void send_update();
    void send_stop();

    XNetworkAddr send_addr_;
    float lines_to_send_ = 0;

    void send_data(QStringList data);

    // Receive
    void receive_start();
    void receive_update();
    void receive_stop();

    void receive_data(QStringList data);

    QScopedPointer<QTimer> timer;
private slots:
    void slot_readPendingDatagrams();
    void slot_timer_receive_emulate();

    // async received data
    XProtectedData_<QStringList> received_data_;

};

