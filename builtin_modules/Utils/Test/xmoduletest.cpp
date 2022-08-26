#include "xmoduletest.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"

//registering module implementation
REGISTER_XMODULE(Test)

//---------------------------------------------------------------------
XModuleTest::XModuleTest(QString class_name)
    :XClass(class_name)
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
        //xc_execute_callbacks(gets_callback_modules"));
    }
}

//---------------------------------------------------------------------
void XModuleTest::stop() {
    xc_console_append(QString("%1 - stop").arg(name()));



}

//---------------------------------------------------------------------
