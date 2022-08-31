#pragma once

//Sending and receiving OSC messages.

#include "sdk_h.h"
#include "xnetworkaddr.h"
#include "qosc.h"

class XOsc
{
public:
    //example of net_addr_port: 127.0.0.1:12345
    static void send(QString net_addr_port, QString osc_address, const QOscValue &value);
    static void send(QString net_addr, int net_port, QString osc_address, const QOscValue &value);
    static void send(XNetworkAddr net_address, QString osc_address, const QOscValue &value);
//public slots:
    //void onOscMessage(const QOscMessage& msg);  // Can't use "on_osc_message" - because Qt treats two "_" specially

};

