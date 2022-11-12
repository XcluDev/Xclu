#pragma once

//Class for manipulations with network address

#include "sdk_h.h"

class XNetworkAddr
{
public:
    QString address;
    int port = 0;
    XNetworkAddr() {}
    XNetworkAddr(QString addr_port);    //127.0.0.1:12345   Note: don't use 'localhost'
    XNetworkAddr(QString address0, int port0);

    void setup(QString addr_port);      //127.0.0.1:12345    Note: don't use 'localhost'
    void setup(QString address0, int port0);
    QString to_str();
};

