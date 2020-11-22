//----------------------------------------------------
//Interface for XClassValueMap
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Int Count
//Number of variables to show.
bool was_changed_count() { return was_changed_("count"); }
int geti_count() { return geti_("count"); }

//Checkbox Var 1
//Variable 1.
bool was_changed_use_var1() { return was_changed_("use_var1"); }
int geti_use_var1() { return geti_("use_var1"); }

//Enum Type
//Type of variable.
enum enum_type1 {
    type1_int = 0,
    type1_float = 1,
    type1_N__ = 2
};
bool was_changed_type1() { return was_changed_("type1"); }
enum_type1 gete_type1() { return enum_type1(geti_("type1")); }
QString getraw_type1() { return getraw_("type1");}

//Int Value In
//Input value.
bool was_changed_value_in1_int() { return was_changed_("value_in1_int"); }
int geti_value_in1_int() { return geti_("value_in1_int"); }

//Out Int Value Out
//Output value.
bool was_changed_value_out1_int() { return was_changed_("value_out1_int"); }
int geti_value_out1_int() { return geti_("value_out1_int"); }
void seti_value_out1_int(int value) { seti_("value_out1_int", value); }
void increase_int_value_out1_int(int increase = 1) { increase_int_("value_out1_int", increase); }

//Float Value In
//Input value.
bool was_changed_value_in1_float() { return was_changed_("value_in1_float"); }
float getf_value_in1_float() { return getf_("value_in1_float"); }

//Out Float Value Out
//Output value.
bool was_changed_value_out1_float() { return was_changed_("value_out1_float"); }
float getf_value_out1_float() { return getf_("value_out1_float"); }
void setf_value_out1_float(float value) { setf_("value_out1_float", value); }

//Checkbox Map
//Remap value from a given to an output range.
bool was_changed_map1() { return was_changed_("map1"); }
int geti_map1() { return geti_("map1"); }

//Checkbox Clamp
//Clamp value to an output range.
bool was_changed_clamp1() { return was_changed_("clamp1"); }
int geti_clamp1() { return geti_("clamp1"); }

//Int Source0
//Source range - is used for Map.
bool was_changed_src0_int() { return was_changed_("src0_int"); }
int geti_src0_int() { return geti_("src0_int"); }

//Int Source1
//Source range - is used for Map.
bool was_changed_src1_int() { return was_changed_("src1_int"); }
int geti_src1_int() { return geti_("src1_int"); }

//Int Dest0
//Destination range - is used for Map and Clamp.
bool was_changed_dest0_int() { return was_changed_("dest0_int"); }
int geti_dest0_int() { return geti_("dest0_int"); }

//Int Dest1
//Destination range - is used for Map and Clamp.
bool was_changed_dest1_int() { return was_changed_("dest1_int"); }
int geti_dest1_int() { return geti_("dest1_int"); }

//Float Source0
//Source range - is used for Map.
bool was_changed_src0_float() { return was_changed_("src0_float"); }
float getf_src0_float() { return getf_("src0_float"); }

//Float Source1
//Source range - is used for Map.
bool was_changed_src1_float() { return was_changed_("src1_float"); }
float getf_src1_float() { return getf_("src1_float"); }

//Float Dest0
//Destination range - is used for Map and Clamp.
bool was_changed_dest0_float() { return was_changed_("dest0_float"); }
float getf_dest0_float() { return getf_("dest0_float"); }

//Float Dest1
//Destination range - is used for Map and Clamp.
bool was_changed_dest1_float() { return was_changed_("dest1_float"); }
float getf_dest1_float() { return getf_("dest1_float"); }

//----------------------------------------------------
