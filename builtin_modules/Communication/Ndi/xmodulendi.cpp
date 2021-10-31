#include "xmodulendi.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xc_project.h"
#include <Processing.NDI.Lib.h>
 

REGISTER_XMODULE(Ndi)

//---------------------------------------------------------------------
XModuleNdi::XModuleNdi(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleNdi::~XModuleNdi()
{

}

//---------------------------------------------------------------------
void XModuleNdi::on_loaded() {
    sets_send_status("Not started");
}

//---------------------------------------------------------------------
//нажатие кнопки, даже когда модуль остановлен - модуль также должен переопределить эту функцию
//внимание, обычно вызывается из основного потока как callback
void XModuleNdi::on_button_pressed(QString button_id) {
    if (button_id == "print_devices") {

    }

  //xc_console_warning("Serial: Port is not connected, may be you need to start the project.");
}


//---------------------------------------------------------------------
void XModuleNdi::start() {
    sets_send_status("Not started");
    ndi_inited_ = false;

    sent_frames_  = 0;

    auto mode = gete_send_mode();
    if (mode != send_mode_Off) {
        ndi_init();
    }

}

//---------------------------------------------------------------------
void XModuleNdi::update() {
    auto mode = gete_send_mode();
    if (mode == send_mode_Each_Frame
            || (mode == send_mode_On_Checkbox && geti_send_new_frame())) {
        //Send frame
        send_frame();
    }
}


//---------------------------------------------------------------------
void XModuleNdi::stop() {
    ndi_stop();


}

//---------------------------------------------------------------------
void XModuleNdi::send_frame() {
    if (!ndi_inited_) {
        return;
    }

    sent_frames_++;
    sets_send_status(QString("Sending frame: %1").arg(sent_frames_));

}

//---------------------------------------------------------------------
void XModuleNdi::ndi_init() {
    if (!ndi_inited_) {
        auto result = NDIlib_initialize();
        xc_assert(result, "Can't initialize NDI: Library error");
        if (!result) return;

        // We create the NDI sender
        pNDI_send_ = NDIlib_send_create();
        xc_assert(pNDI_send_, "Can't initialize NDI: error creating sender");
        if (!pNDI_send_) return;

        sets_send_status("NDI started");
        ndi_inited_ = true;
    }
}

//---------------------------------------------------------------------
void XModuleNdi::ndi_stop() {
    if (ndi_inited_) {
        // Destroy the NDI sender
        NDIlib_send_destroy(pNDI_send_);
        pNDI_send_ = nullptr;

        // Not required, but nice
        NDIlib_destroy();

        ndi_inited_ = false;
        sets_send_status("NDI stopped");
    }
}

//---------------------------------------------------------------------


