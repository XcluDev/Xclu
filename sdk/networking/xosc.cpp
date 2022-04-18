#include "xosc.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
//example of net_addr_port: 127.0.0.1:12345
void XOsc::send(QString net_addr_port, QString osc_address, const QOscValue &value) {
    send(XNetworkAddr(net_addr_port), osc_address, value);
}

//---------------------------------------------------------------------
void XOsc::send(QString net_addr, int net_port, QString osc_address, const QOscValue &value) {
    send(XNetworkAddr(net_addr, net_port), osc_address, value);
}

//---------------------------------------------------------------------
void XOsc::send(XNetworkAddr net_address, QString osc_address, const QOscValue &value) {

    QOscInterface iface;
    iface.setRemoteAddr(net_address.address); // For some reason we can't use "localhost" - TODO need name resolving?
    iface.setRemotePort(net_address.port);
    iface.send(osc_address, value);
}

//---------------------------------------------------------------------


