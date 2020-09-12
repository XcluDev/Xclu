#include "xmoduletest.h"
#include "incl_cpp.h"
#include "moduleregistrar.h"
#include "projectruntime.h"

//registering module implementation
REGISTRAR(Test)

//---------------------------------------------------------------------
/*static*/ XModuleTest *XModuleTest::new_module() {
    return new XModuleTest();
}

//---------------------------------------------------------------------
XModuleTest::XModuleTest()
    :XModule(*static_class_name_ptr)
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
    if (geti("callback")) {
        xclu_console_append(QString("%1 - pressed Callback").arg(name()));
        xclu_message_box("Callbacks are not implemented here");
        //RUNTIME.execute_callbacks(gets("callback_modules"));
    }
}

//---------------------------------------------------------------------
void XModuleTest::impl_stop() {
    xclu_console_append(QString("%1 - stop").arg(name()));



}

//---------------------------------------------------------------------
