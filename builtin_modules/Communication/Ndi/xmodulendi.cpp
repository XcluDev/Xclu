#include "xmodulendi.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xc_project.h"
 

REGISTER_XMODULE(Ndi)

//---------------------------------------------------------------------
XModuleNdi::XModuleNdi(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
void XModuleNdi::gui_clear() {

    set_connected(false);

}

//---------------------------------------------------------------------
void XModuleNdi::set_connected(bool connected) {
  connected_ = connected;
  //seti_connected(connected);
}

//---------------------------------------------------------------------
XModuleNdi::~XModuleNdi()
{

}

//---------------------------------------------------------------------
void XModuleNdi::on_loaded() {
    gui_clear();
}

//---------------------------------------------------------------------
//нажатие кнопки, даже когда модуль остановлен - модуль также должен переопределить эту функцию
//внимание, обычно вызывается из основного потока как callback
void XModuleNdi::on_button_pressed(QString button_id) {
    if (button_id == "print_devices") {
        print_devices();
    }

  //xc_console_warning("Serial: Port is not connected, may be you need to start the project.");
}

//---------------------------------------------------------------------
void XModuleNdi::print_devices() {
    //clear_string_device_list();
    //append_string_device_list(out, 1);
}



//---------------------------------------------------------------------
void XModuleNdi::start() {
    gui_clear();

}

//---------------------------------------------------------------------
void XModuleNdi::update() {

}


//---------------------------------------------------------------------
void XModuleNdi::stop() {
    if (connected_) {
        //...
        set_connected(false);
    }
}



//---------------------------------------------------------------------


