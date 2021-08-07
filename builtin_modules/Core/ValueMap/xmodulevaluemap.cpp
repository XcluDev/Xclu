#include "xmodulevaluemap.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xc_project.h"


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
void XModuleValueMap::start() {

}

//---------------------------------------------------------------------
void XModuleValueMap::update() {
    if (geti_use_var1()) {
        int clamp = geti_clamp1();
        int map = geti_map1();
        if (gete_type1() == type1_int) {
            int v = geti_value_in1_int();
            int dest0 = geti_dest0_int();
            int dest1 = geti_dest1_int();
            if (map) {
                v = xmapi(v, geti_src0_int(), geti_src1_int(), dest0, dest1);
            }
            if (clamp) {
                v = xclampi(v, dest0, dest1);
            }
            seti_value_out1_int(v);
        }
        if (gete_type1() == type1_float) {
            float v = getf_value_in1_float();
            float dest0 = getf_dest0_float();
            float dest1 = getf_dest1_float();
            if (map) {
                v = xmapf(v, getf_src0_float(), getf_src1_float(), dest0, dest1);
            }
            if (clamp) {
                v = xclampf(v, dest0, dest1);
            }
            setf_value_out1_float(v);
        }
    }
}

//---------------------------------------------------------------------
void XModuleValueMap::stop() {

}

//---------------------------------------------------------------------
//void XModuleTimerm::on_button_pressed(QString button_id) {
//}

//---------------------------------------------------------------------
