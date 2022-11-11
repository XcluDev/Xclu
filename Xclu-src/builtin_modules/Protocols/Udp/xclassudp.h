#pragma once

//UDP sender/receiver implementation

#include "sdk_h.h"
#include <QTimer>
#include "xclass.h"

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

    void send_start();
    void send_update();
    void send_stop();

    void receive_start();
    void receive_update();
    void receive_stop();

    void receive_data(QStringList data);

    QScopedPointer<QTimer> timer;
private slots:
    void slot_readPendingDatagrams();
    void slot_timer_receive_emulate();

};

