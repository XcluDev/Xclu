#pragma once

//UDP sender/receiver implementation

#include "sdk_h.h"
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

    QScopedPointer<QUdpSocket> udpSocket;

private slots:
    void readPendingDatagrams();

    void send_start();
    void send_update();
    void receive_start();
    void receive_update();

    void read_file(QString file_name);
    QStringList file_;  // text file used for reading or emulation
};

