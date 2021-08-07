#include "xmoduleprintconsole.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xc_project.h"


//registering module implementation
REGISTER_XMODULE(PrintConsole)

//---------------------------------------------------------------------
XModulePrintConsole::XModulePrintConsole(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModulePrintConsole::~XModulePrintConsole()
{

}

//---------------------------------------------------------------------
void XModulePrintConsole::start() {

}

//---------------------------------------------------------------------
void XModulePrintConsole::update() {
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
void XModulePrintConsole::stop() {

}

//---------------------------------------------------------------------
