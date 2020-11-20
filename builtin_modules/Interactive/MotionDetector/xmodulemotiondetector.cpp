#include "xmodulemotiondetector.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xcore.h"

//registering module implementation
REGISTER_XMODULE(MotionDetector)

//---------------------------------------------------------------------
XModuleMotionDetector::XModuleMotionDetector(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleMotionDetector::~XModuleMotionDetector()
{

}

//---------------------------------------------------------------------
void XModuleMotionDetector::impl_start() {
    //link images with internal objects
    setobject_output_image(&out_image_);
    setobject_background_image(&out_background_);

    //Human presence detection
    //Algorithm works using correlation inside smaller pixel blocks of fixed size.
    //If correlation in some block exceeds threshold, the object is detected.
    //If no changes of "block image" for a minute - then update background.

}

//---------------------------------------------------------------------
void XModuleMotionDetector::impl_update() {

}

//---------------------------------------------------------------------
void XModuleMotionDetector::impl_stop() {


}

//---------------------------------------------------------------------
//void XModuleTimerm::impl_button_pressed(QString button_id) {
//}

//---------------------------------------------------------------------
