#include "xmodulefacedetect.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "project_props.h"
#include "xobjectimage.h"
#include "xdrawhelper.h"

#include <cv.h>
#include <opencv2/imgcodecs.hpp>

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
    //haar_load(...);

    //cv::Mat mat(100,100,CV_8UC3);
    //cv::imwrite("d:\\Image.jpg", mat);
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
    haar_unload();

}


//---------------------------------------------------------------------
void XModuleFaceDetect::draw(QPainter &painter, int w, int h) {
    /*if (geti_transform()) {
        auto image_read = getobject_image_transformed()->read();
        const XObject *object = image_read.pointer();
        XDrawHelper::draw_XObject_fit(object, getf_draw_x(), getf_draw_y(), getf_draw_size(), painter, w, h);
    }
    else {
        auto image_read = getobject_image()->read();
        const XObject *object = image_read.pointer();
        XDrawHelper::draw_XObject_fit(object, getf_draw_x(), getf_draw_y(), getf_draw_size(), painter, w, h);
    }*/

}

//---------------------------------------------------------------------
void XModuleFaceDetect::haar_load(QString file_name) {

}

//---------------------------------------------------------------------
void XModuleFaceDetect::haar_unload() {

}

//---------------------------------------------------------------------
void XModuleFaceDetect::haar_search() {

}

//---------------------------------------------------------------------
// The default value is 1.2. For accuracy, bring it closer but not equal to 1.0. To make it faster, use a larger value.
void XModuleFaceDetect::haar_set_scale(float scaleHaar) {

}

//---------------------------------------------------------------------
// How many neighbors can be grouped into a face? Default value is 2. If set to 0, no grouping will be done.
void XModuleFaceDetect::haar_set_neighbors(int neighbors) {

}

//---------------------------------------------------------------------


