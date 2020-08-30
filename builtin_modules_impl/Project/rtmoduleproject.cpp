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
void RtModuleProject::execute_loaded_internal() {
    if (is_enabled()) {
        apply_control_values();
    }
}

//---------------------------------------------------------------------
void RtModuleProject::apply_control_values() {
    RUNTIME.set_frame_rate(get_int("frame_rate"));
    RUNTIME.set_autostart(get_int("autostart"));
}

//---------------------------------------------------------------------
void RtModuleProject::execute_start_internal() {
    apply_control_values();
}

//---------------------------------------------------------------------
void RtModuleProject::execute_update_internal() {
    set_float("elapsed_time_sec", RUNTIME.elapsed_time_sec());

    float dt = RUNTIME.dt();
    set_float("dt", dt);

    float fps = 10000;
    if (dt > 0) fps = 1.0 / dt;
    set_float("measured_frame_rate", fps);

}

//---------------------------------------------------------------------
void RtModuleProject::execute_stop_internal() {

}

//---------------------------------------------------------------------
