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
        set_values();
    }
}

//---------------------------------------------------------------------
void RtModuleProject::set_values() {
    RUNTIME.set_frame_rate(get_int("frame_rate"));
    RUNTIME.set_autostart(get_int("autostart"));

}

//---------------------------------------------------------------------
void RtModuleProject::execute_start_internal() {
    set_values();
}

//---------------------------------------------------------------------
void RtModuleProject::execute_update_internal() {

}

//---------------------------------------------------------------------
void RtModuleProject::execute_stop_internal() {

}

//---------------------------------------------------------------------
