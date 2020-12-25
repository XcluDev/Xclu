#include "xmoduletest.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xcore.h"

//registering module implementation
REGISTER_XMODULE(Test)

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
void XModuleTest::start() {
    xc_console_append(QString("%1 - start").arg(name()));

}

//---------------------------------------------------------------------
void XModuleTest::update() {
    //xc_console_append(QString("%1 - update").arg(name()));
    if (geti_("callback")) {
        xc_console_append(QString("%1 - pressed Callback").arg(name()));
        xc_message_box("Callbacks are not implemented here");
        //XCORE.execute_callbacks(gets_callback_modules"));
    }
}

//---------------------------------------------------------------------
void XModuleTest::stop() {
    xc_console_append(QString("%1 - stop").arg(name()));



}

//---------------------------------------------------------------------
