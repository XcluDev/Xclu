#include "xnetworkaddr.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
XNetworkAddr::XNetworkAddr(QString addr_port) {    //127.0.0.1:12345
    setup(addr_port);
}

//---------------------------------------------------------------------
XNetworkAddr::XNetworkAddr(QString address0, int port0) {
    setup(address0, port0);
}

//---------------------------------------------------------------------
void XNetworkAddr::setup(QString addr_port) {   //127.0.0.1:12345
    auto list = addr_port.split(":");
    xc_assert(list.size() == 2, "Bad address format, got `" + addr_port + "`, but expected kind of 127.0.0.1:12345");

    QString addr = list.at(0);
    int port = list.at(1).toInt();
    setup(addr, port);
}

//---------------------------------------------------------------------
void XNetworkAddr::setup(QString addr0, int port0) {
    xc_assert(!addr0.isEmpty(), "Empty address `" + addr0 + "`");
    xc_assert(port0 > 0 && port0 < 65536, QString("Bad networking port at '%1:%2'").arg(addr0).arg(port0));
    address = addr0;
    port = port0;
}

//---------------------------------------------------------------------
QString XNetworkAddr::to_str() {
    return QString("%1:%2").arg(address).arg(port);
}

//---------------------------------------------------------------------


