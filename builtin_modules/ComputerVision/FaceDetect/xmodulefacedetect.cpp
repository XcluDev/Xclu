#include "xmodulefacedetect.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "project_props.h"
 

REGISTER_XMODULE(FaceDetect)

//---------------------------------------------------------------------
XModuleFaceDetect::XModuleFaceDetect(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleFaceDetect::~XModuleFaceDetect()
{

}

//---------------------------------------------------------------------
void XModuleFaceDetect::on_loaded() {

}

//---------------------------------------------------------------------
//нажатие кнопки, даже когда модуль остановлен - модуль также должен переопределить эту функцию
//внимание, обычно вызывается из основного потока как callback
void XModuleFaceDetect::on_button_pressed(QString button_id) {
    if (button_id == "print_devices") {

    }

}


//---------------------------------------------------------------------
void XModuleFaceDetect::start() {


}

//---------------------------------------------------------------------
void XModuleFaceDetect::update() {
    //auto mode = gete_send_mode();
    //if (mode == send_mode_Each_Frame
    //        || (mode == send_mode_On_Checkbox && geti_send_new_frame())) {
    //    process();
    //}
}


//---------------------------------------------------------------------
void XModuleFaceDetect::stop() {


}

//---------------------------------------------------------------------


