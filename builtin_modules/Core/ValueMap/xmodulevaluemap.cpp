#include "xmodulevaluemap.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xcore.h"


//registering module implementation
REGISTER_XMODULE(ValueMap)

//---------------------------------------------------------------------
XModuleValueMap::XModuleValueMap(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleValueMap::~XModuleValueMap()
{

}

//---------------------------------------------------------------------
void XModuleValueMap::impl_start() {

}

//---------------------------------------------------------------------
void XModuleValueMap::impl_update() {
    if (geti_use_var1()) {
        int clamp = geti_clamp1();
        int map = geti_map1();
        if (gete_type1() == type1_int) {
            int v = geti_value_in1_int();
            int dest0 = geti_dest0_int();
            int dest1 = geti_dest1_int();
            if (map) {
                v = mapi(v, geti_src0_int(), geti_src1_int(), dest0, dest1);
            }
            if (clamp) {
                v = clampi(v, dest0, dest1);
            }
            seti_value_out1_int(v);
        }
        if (gete_type1() == type1_float) {
            float v = geti_value_in1_int();
            float dest0 = geti_dest0_int();
            float dest1 = geti_dest1_int();
            if (map) {
                v = mapf(v, getf_src0_float(), getf_src1_float(), dest0, dest1);
            }
            if (clamp) {
                v = clampf(v, dest0, dest1);
            }
            setf_value_out1_float(v);
        }
    }
}

//---------------------------------------------------------------------
void XModuleValueMap::impl_stop() {

}

//---------------------------------------------------------------------
//void XModuleTimerm::impl_button_pressed(QString button_id) {
//}

//---------------------------------------------------------------------
