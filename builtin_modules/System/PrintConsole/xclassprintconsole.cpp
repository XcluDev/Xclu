#include "xclassprintconsole.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"


//registering module implementation
REGISTER_XCLASS(PrintConsole)

//---------------------------------------------------------------------
XClassPrintConsole::XClassPrintConsole(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassPrintConsole::~XClassPrintConsole()
{

}

//---------------------------------------------------------------------
void XClassPrintConsole::start() {

}

//---------------------------------------------------------------------
void XClassPrintConsole::update() {
    QString s;
    if (geti_add_title()) {
        s.append(gets_title());
    }
    if (geti_add_time_stamp()) {
        if (!s.isEmpty()) s.append(" ");
        s.append(QString("(%1 sec)").arg(xc_elapsed_time_sec()));
    }
    QString val = gets_str();
    if (!val.isEmpty()) {
        if (!s.isEmpty()) s.append(": ");
        s.append(val);
    }
    xc_console_append(s);
}

//---------------------------------------------------------------------
void XClassPrintConsole::stop() {

}

//---------------------------------------------------------------------
