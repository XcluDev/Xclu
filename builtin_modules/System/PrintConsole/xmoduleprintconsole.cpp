#include "xmoduleprintconsole.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xcore.h"


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
void XModulePrintConsole::impl_start() {

}

//---------------------------------------------------------------------
void XModulePrintConsole::impl_update() {
    QString s = gets_str();
    if (geti_time_stamp()) {
        s = QString("%1 sec: %2").arg(xcore_elapsed_time_sec()).arg(s);
    }
    xclu_console_append(s);
}

//---------------------------------------------------------------------
void XModulePrintConsole::impl_stop() {

}

//---------------------------------------------------------------------
