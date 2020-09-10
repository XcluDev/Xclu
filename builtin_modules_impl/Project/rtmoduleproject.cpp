#include "qt_widgets.h"
#include "rtmoduleproject.h"
#include "incl_cpp.h"
#include "rtmoduleregistrar.h"
#include "projectruntime.h"


//Register implementation class
REGISTRAR(Project)

//---------------------------------------------------------------------
/*static*/ RtModuleProject *RtModuleProject::new_module() {
    return new RtModuleProject();
}

//---------------------------------------------------------------------
RtModuleProject::RtModuleProject()
    :RtModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
RtModuleProject::~RtModuleProject()
{

}

//---------------------------------------------------------------------
void RtModuleProject::loaded_impl() {
    if (is_enabled()) {
        apply_control_values();
    }
}

//---------------------------------------------------------------------
void RtModuleProject::apply_control_values() {
    RUNTIME.set_frame_rate(geti("frame_rate"));
    RUNTIME.set_autostart(geti("autostart"));
}

//---------------------------------------------------------------------
void RtModuleProject::start_impl() {
    apply_control_values();
}

//---------------------------------------------------------------------
void RtModuleProject::update_impl() {
    setf("elapsed_time_sec", RUNTIME.elapsed_time_sec());

    float dt = RUNTIME.dt();
    setf("dt", dt);

    float fps = 10000;
    if (dt > 0) fps = 1.0 / dt;
    setf("measured_frame_rate", fps);

}

//---------------------------------------------------------------------
void RtModuleProject::stop_impl() {

}

//---------------------------------------------------------------------
