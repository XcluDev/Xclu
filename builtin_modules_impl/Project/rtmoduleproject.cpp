#include "qt_widgets.h"
#include "rtmoduleproject.h"
#include "incl_cpp.h"
#include "rtmoduleregistrar.h"
#include "projectruntime.h"


//Register implementation class
REGISTRAR(Project)

//---------------------------------------------------------------------
/*static*/ XModuleProject *XModuleProject::new_module() {
    return new XModuleProject();
}

//---------------------------------------------------------------------
XModuleProject::XModuleProject()
    :XModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
XModuleProject::~XModuleProject()
{

}

//---------------------------------------------------------------------
void XModuleProject::loaded_impl() {
    if (is_enabled()) {
        apply_control_values();
    }
}

//---------------------------------------------------------------------
void XModuleProject::apply_control_values() {
    RUNTIME.set_frame_rate(geti("frame_rate"));
    RUNTIME.set_autostart(geti("autostart"));
}

//---------------------------------------------------------------------
void XModuleProject::start_impl() {
    apply_control_values();
}

//---------------------------------------------------------------------
void XModuleProject::update_impl() {
    setf("elapsed_time_sec", RUNTIME.elapsed_time_sec());

    float dt = RUNTIME.dt();
    setf("dt", dt);

    float fps = 10000;
    if (dt > 0) fps = 1.0 / dt;
    setf("measured_frame_rate", fps);

}

//---------------------------------------------------------------------
void XModuleProject::stop_impl() {

}

//---------------------------------------------------------------------
