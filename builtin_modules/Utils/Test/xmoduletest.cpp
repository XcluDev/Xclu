#include "xmoduletest.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "projectruntime.h"

//registering module implementation
REGISTRAR(Test)

//---------------------------------------------------------------------
XModuleTest::XModuleTest(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleTest::~XModuleTest()
{

}

//---------------------------------------------------------------------
void XModuleTest::impl_start() {
    xclu_console_append(QString("%1 - start").arg(name()));

}

//---------------------------------------------------------------------
void XModuleTest::impl_update() {
    xclu_console_append(QString("%1 - update").arg(name()));
    if (geti_("callback")) {
        xclu_console_append(QString("%1 - pressed Callback").arg(name()));
        xclu_message_box("Callbacks are not implemented here");
        //RUNTIME.execute_callbacks(gets_callback_modules"));
    }
}

//---------------------------------------------------------------------
void XModuleTest::impl_stop() {
    xclu_console_append(QString("%1 - stop").arg(name()));



}

//---------------------------------------------------------------------
