#include "qt_widgets.h"
#include "xmoduleproject.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "project_props.h"


//Register implementation class
REGISTER_XMODULE(Project)

//---------------------------------------------------------------------
XModuleProject::XModuleProject(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleProject::~XModuleProject()
{

}

//---------------------------------------------------------------------
void XModuleProject::on_loaded() {
    if (is_enabled()) {
        apply_control_values();
    }
}

//---------------------------------------------------------------------
void XModuleProject::apply_control_values() {
    xc_working_properties().set_frame_rate(geti_frame_rate());
    xc_working_properties().set_autostart(geti_autostart());
    xc_working_properties().set_dont_save_at_exit(geti_dont_save_at_exit());
}

//---------------------------------------------------------------------
void XModuleProject::start() {

    apply_control_values();

    //frame number
    seti_frame(xc_frame());
}

//---------------------------------------------------------------------
void XModuleProject::update() {
    setf_elapsed_time_sec(xc_elapsed_time_sec());

    float dt = xc_dt();
    setf_dt(dt);

    float fps = 10000;
    if (dt > 0) fps = 1.0 / dt;
    setf_measured_frame_rate(fps);

    //frame number
    //increase_int_frame();
    seti_frame(xc_frame());

}

//---------------------------------------------------------------------
void XModuleProject::stop() {

}

//---------------------------------------------------------------------
