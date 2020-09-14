#include "qt_widgets.h"
#include "xmoduleproject.h"
#include "incl_cpp.h"
#include "moduleregistrar.h"
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
void XModuleProject::impl_loaded() {
    if (is_enabled()) {
        apply_control_values();
    }
}

//---------------------------------------------------------------------
void XModuleProject::apply_control_values() {
    RUNTIME.set_frame_rate(geti_frame_rate());
    RUNTIME.set_autostart(geti_autostart());
}

//---------------------------------------------------------------------
void XModuleProject::impl_start() {
    apply_control_values();
}

//---------------------------------------------------------------------
void XModuleProject::impl_update() {
    setf_elapsed_time_sec(rt_elapsed_time_sec());

    float dt = rt_dt();
    setf_dt(dt);

    float fps = 10000;
    if (dt > 0) fps = 1.0 / dt;
    setf_measured_frame_rate(fps);

}

//---------------------------------------------------------------------
void XModuleProject::impl_stop() {

}

//---------------------------------------------------------------------