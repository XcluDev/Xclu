//----------------------------------------------------
//Interface for XClassTest
//Created automatically.
//----------------------------------------------------
//Page Gui Controls
//

//Button Test
//Test button.
bool was_changed_button1() { return was_changed_("button1"); }
int geti_button1() { return geti_("button1"); }
QString button_button1() { return "button1"; }


//Const Checkbox Const Checkbox
//Constant value.
bool was_changed_const_check() { return was_changed_("const_check"); }
int geti_const_check() { return geti_("const_check"); }

//Checkbox In Checkbox
//Input value.
bool was_changed_in_check() { return was_changed_("in_check"); }
int geti_in_check() { return geti_("in_check"); }

//Out Checkbox Out Checkbox
//Output value.
bool was_changed_out_check() { return was_changed_("out_check"); }
int geti_out_check() { return geti_("out_check"); }
void seti_out_check(int value) { seti_("out_check", value); }


//Const Float Const Float1
//Constant value.
bool was_changed_float1() { return was_changed_("float1"); }
float getf_float1() { return getf_("float1"); }

//Float In Float2
//Input value.
bool was_changed_float2() { return was_changed_("float2"); }
float getf_float2() { return getf_("float2"); }

//Float In Float3
//Input value.
bool was_changed_float3() { return was_changed_("float3"); }
float getf_float3() { return getf_("float3"); }

//Out Float Out Float4
//Output value.
bool was_changed_float4() { return was_changed_("float4"); }
float getf_float4() { return getf_("float4"); }
void setf_float4(float value) { setf_("float4", value); }


//Const Int Const Int1
//Constant value.
bool was_changed_int1() { return was_changed_("int1"); }
int geti_int1() { return geti_("int1"); }

//Int In Int2
//Input value.
bool was_changed_int2() { return was_changed_("int2"); }
int geti_int2() { return geti_("int2"); }

//Int In Int3
//Input value.
bool was_changed_int3() { return was_changed_("int3"); }
int geti_int3() { return geti_("int3"); }

//Out Int Out Int4
//Output value.
bool was_changed_int4() { return was_changed_("int4"); }
int geti_int4() { return geti_("int4"); }
void seti_int4(int value) { seti_("int4", value); }
void increase_int_int4(int increase = 1) { increase_int_("int4", increase); }


//Const String Const String
//Constant value.
bool was_changed_string1() { return was_changed_("string1"); }
QString gets_string1() { return gets_("string1"); }
QStringList get_strings_string1() { return get_strings_("string1"); }

//String In String
//Input value.
bool was_changed_string2() { return was_changed_("string2"); }
QString gets_string2() { return gets_("string2"); }
QStringList get_strings_string2() { return get_strings_("string2"); }

//Out String Out String
//Output value.
bool was_changed_string3() { return was_changed_("string3"); }
QString gets_string3() { return gets_("string3"); }
QStringList get_strings_string3() { return get_strings_("string3"); }
void sets_string3(QString value) { sets_("string3", value); }
void clear_string_string3() { clear_string_("string3"); }
void append_string_string3(QString v, int extra_new_lines_count = 0) { append_string_("string3", v, extra_new_lines_count); }
void append_string_string3(QStringList v, int extra_new_lines_count = 0) { append_string_("string3", v, extra_new_lines_count); }


//Const Enum Const List
//Constant value.
enum enum_list1 {
    list1_By_Name = 0,
    list1_By_Id = 1,
    list1_N__ = 2
};
bool was_changed_list1() { return was_changed_("list1"); }
enum_list1 gete_list1() { return enum_list1(geti_("list1")); }
QString getraw_list1() { return getraw_("list1");}

//Enum In List
//Input value.
enum enum_list2 {
    list2_By_Name = 0,
    list2_By_Id = 1,
    list2_N__ = 2
};
bool was_changed_list2() { return was_changed_("list2"); }
enum_list2 gete_list2() { return enum_list2(geti_("list2")); }
QString getraw_list2() { return getraw_("list2");}

//Out Enum Out List
//Output value.
enum enum_list3 {
    list3_By_Name = 0,
    list3_By_Id = 1,
    list3_N__ = 2
};
bool was_changed_list3() { return was_changed_("list3"); }
enum_list3 gete_list3() { return enum_list3(geti_("list3")); }
void sete_list3(enum_list3 value) { seti_("list3", value); }
QString getraw_list3() { return getraw_("list3");}


//Const Text Const Text
//Constant value.
bool was_changed_text1() { return was_changed_("text1"); }
QString gets_text1() { return gets_("text1"); }
QStringList get_strings_text1() { return get_strings_("text1"); }

//Text In Text
//Input value.
bool was_changed_text2() { return was_changed_("text2"); }
QString gets_text2() { return gets_("text2"); }
QStringList get_strings_text2() { return get_strings_("text2"); }

//Out Text Out Text
//Output value.
bool was_changed_text3() { return was_changed_("text3"); }
QString gets_text3() { return gets_("text3"); }
QStringList get_strings_text3() { return get_strings_("text3"); }
void sets_text3(QString value) { sets_("text3", value); }
void clear_string_text3() { clear_string_("text3"); }
void append_string_text3(QString v, int extra_new_lines_count = 0) { append_string_("text3", v, extra_new_lines_count); }
void append_string_text3(QStringList v, int extra_new_lines_count = 0) { append_string_("text3", v, extra_new_lines_count); }

//----------------------------------------------------
//Page Objects
//

//Int Width
//Generated image width.
bool was_changed_w() { return was_changed_("w"); }
int geti_w() { return geti_("w"); }

//Int Height
//Generated image height.
bool was_changed_h() { return was_changed_("h"); }
int geti_h() { return geti_("h"); }

//Int Wave
//Some parameter for contents.
bool was_changed_wave() { return was_changed_("wave"); }
int geti_wave() { return geti_("wave"); }

//Out Object Generated Image
//"out" object is a provider for "in" objects.
bool was_changed_object1() { return was_changed_("object1"); }
XProtectedObject *getobject_object1() { return get_object_("object1"); }
void setobject_object1(XProtectedObject *value) { set_object_("object1", value); }


//Object Input Image
//"in" object can only receive external object via link.
bool was_changed_object2() { return was_changed_("object2"); }
XProtectedObject *getobject_object2() { return get_object_("object2"); }

//----------------------------------------------------
//Page Choose Files
//

//String Choose File
//Description
bool was_changed_choose:file() { return was_changed_("choose:file"); }
QString gets_choose:file() { return gets_("choose:file"); }
QStringList get_strings_choose:file() { return get_strings_("choose:file"); }

//String Choose Folder
//Description.
bool was_changed_choose_Folder() { return was_changed_("choose_Folder"); }
QString gets_choose_Folder() { return gets_("choose_Folder"); }
QStringList get_strings_choose_Folder() { return get_strings_("choose_Folder"); }

//----------------------------------------------------
//Page Conditional GUI
//

//Enum Type
//Choose different types to see changed interface.
enum enum_type {
    type_Int = 0,
    type_Float = 1,
    type_String = 2,
    type_N__ = 3
};
bool was_changed_type() { return was_changed_("type"); }
enum_type gete_type() { return enum_type(geti_("type")); }
QString getraw_type() { return getraw_("type");}


//String Numbered
//
bool was_changed_numbered() { return was_changed_("numbered"); }
QString gets_numbered() { return gets_("numbered"); }
QStringList get_strings_numbered() { return get_strings_("numbered"); }


//Text Number Text
//
bool was_changed_number_text() { return was_changed_("number_text"); }
QString gets_number_text() { return gets_("number_text"); }
QStringList get_strings_number_text() { return get_strings_("number_text"); }

//String Stringed
//
bool was_changed_stringed() { return was_changed_("stringed"); }
QString gets_stringed() { return gets_("stringed"); }
QStringList get_strings_stringed() { return get_strings_("stringed"); }


//Text String Text
//
bool was_changed_string_text() { return was_changed_("string_text"); }
QString gets_string_text() { return gets_("string_text"); }
QStringList get_strings_string_text() { return get_strings_("string_text"); }

//----------------------------------------------------
//Page Callback
//Testing Callback mechanism. Create other instance of Test, set it Run mode Callback and put its id here and press button.

//Button Callback
//Press button to start callback of selected modules.
bool was_changed_callback() { return was_changed_("callback"); }
int geti_callback() { return geti_("callback"); }
QString button_callback() { return "callback"; }

//Text Callback Modules
//List of modules which will be called by callback.
bool was_changed_callback_modules() { return was_changed_("callback_modules"); }
QString gets_callback_modules() { return gets_("callback_modules"); }
QStringList get_strings_callback_modules() { return get_strings_("callback_modules"); }

//----------------------------------------------------
