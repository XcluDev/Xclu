//----------------------------------------------------
//Interface for XClassTest
//Created automatically at 2020.09.14 11:01:46
//----------------------------------------------------
//Page Main
//

//Button Test
//Test button.
bool was_changed_button1() { return was_changed("button1"); }
int geti_button1() { return geti("button1"); }


//Const Checkbox Const Checkbox
//Constant value.
bool was_changed_const_check() { return was_changed("const_check"); }
int geti_const_check() { return geti("const_check"); }

//Checkbox In Checkbox
//Input value.
bool was_changed_in_check() { return was_changed("in_check"); }
int geti_in_check() { return geti("in_check"); }

//Out Checkbox Out Checkbox
//Output value.
bool was_changed_out_check() { return was_changed("out_check"); }
int geti_out_check() { return geti("out_check"); }
void seti_out_check(int value) { seti("out_check", value); }


//Const Float Const Float
//Constant value.
bool was_changed_float1() { return was_changed("float1"); }
float getf_float1() { return getf("float1"); }

//Float In Float
//Input value.
bool was_changed_float2() { return was_changed("float2"); }
float getf_float2() { return getf("float2"); }

//Out Float Out Float
//Output value.
bool was_changed_float3() { return was_changed("float3"); }
float getf_float3() { return getf("float3"); }
void setf_float3(float value) { setf("float3", value); }


//Const Int Const Int
//Constant value.
bool was_changed_int1() { return was_changed("int1"); }
int geti_int1() { return geti("int1"); }

//Int In Int
//Input value.
bool was_changed_int2() { return was_changed("int2"); }
int geti_int2() { return geti("int2"); }

//Out Int Out Int
//Output value.
bool was_changed_int3() { return was_changed("int3"); }
int geti_int3() { return geti("int3"); }
void seti_int3(int value) { seti("int3", value); }
void increase_int_int3(int increase = 1) { increase_int("int3", increase); }


//Const String Const String
//Constant value.
bool was_changed_string1() { return was_changed("string1"); }
QString gets_string1() { return gets("string1"); }
QStringList get_strings_string1() { return get_strings("string1"); }

//String In String
//Input value.
bool was_changed_string2() { return was_changed("string2"); }
QString gets_string2() { return gets("string2"); }
QStringList get_strings_string2() { return get_strings("string2"); }

//Out String Out String
//Output value.
bool was_changed_string3() { return was_changed("string3"); }
QString gets_string3() { return gets("string3"); }
QStringList get_strings_string3() { return get_strings("string3"); }
void sets_string3(QString value) { sets("string3", value); }
void clear_string_string3() { clear_string("string3"); }
void append_string_string3(QString v, int extra_new_lines_count = 0) { append_string("string3", v, extra_new_lines_count); }
void append_string_string3(QStringList v, int extra_new_lines_count = 0) { append_string("string3", v, extra_new_lines_count); }


//Const Enum Const List
//Constant value.
enum enum_list1 {
    list1_By_Name = 0,
    list1_By_Id = 1,
    list1_N__ = 2
};
bool was_changed_list1() { return was_changed("list1"); }
enum_list1 gete_list1() { return enum_list1(geti("list1")); }

//Enum In List
//Input value.
enum enum_list2 {
    list2_By_Name = 0,
    list2_By_Id = 1,
    list2_N__ = 2
};
bool was_changed_list2() { return was_changed("list2"); }
enum_list2 gete_list2() { return enum_list2(geti("list2")); }

//Out Enum Out List
//Output value.
enum enum_list3 {
    list3_By_Name = 0,
    list3_By_Id = 1,
    list3_N__ = 2
};
bool was_changed_list3() { return was_changed("list3"); }
enum_list3 gete_list3() { return enum_list3(geti("list3")); }
void sete_list3(enum_list3 value) { seti("list3", value); }


//Const Text Const Text
//Constant value.
bool was_changed_text1() { return was_changed("text1"); }
QString gets_text1() { return gets("text1"); }
QStringList get_strings_text1() { return get_strings("text1"); }

//Text In Text
//Input value.
bool was_changed_text2() { return was_changed("text2"); }
QString gets_text2() { return gets("text2"); }
QStringList get_strings_text2() { return get_strings("text2"); }

//Out Text Out Text
//Output value.
bool was_changed_text3() { return was_changed("text3"); }
QString gets_text3() { return gets("text3"); }
QStringList get_strings_text3() { return get_strings("text3"); }
void sets_text3(QString value) { sets("text3", value); }
void clear_string_text3() { clear_string("text3"); }
void append_string_text3(QString v, int extra_new_lines_count = 0) { append_string("text3", v, extra_new_lines_count); }
void append_string_text3(QStringList v, int extra_new_lines_count = 0) { append_string("text3", v, extra_new_lines_count); }


//Object Object
//
bool was_changed_object() { return was_changed("object"); }
XDict *getobj_object() { return get_object("object"); }

//----------------------------------------------------
//Page Choose Files
//

//String Choose File
//Description
bool was_changed_choose:file() { return was_changed("choose:file"); }
QString gets_choose:file() { return gets("choose:file"); }
QStringList get_strings_choose:file() { return get_strings("choose:file"); }

//String Choose Folder
//Description.
bool was_changed_choose_Folder() { return was_changed("choose_Folder"); }
QString gets_choose_Folder() { return gets("choose_Folder"); }
QStringList get_strings_choose_Folder() { return get_strings("choose_Folder"); }

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
bool was_changed_type() { return was_changed("type"); }
enum_type gete_type() { return enum_type(geti("type")); }


//String Numbered
//
bool was_changed_numbered() { return was_changed("numbered"); }
QString gets_numbered() { return gets("numbered"); }
QStringList get_strings_numbered() { return get_strings("numbered"); }


//Text Number Text
//
bool was_changed_number_text() { return was_changed("number_text"); }
QString gets_number_text() { return gets("number_text"); }
QStringList get_strings_number_text() { return get_strings("number_text"); }

//String Stringed
//
bool was_changed_stringed() { return was_changed("stringed"); }
QString gets_stringed() { return gets("stringed"); }
QStringList get_strings_stringed() { return get_strings("stringed"); }


//Text String Text
//
bool was_changed_string_text() { return was_changed("string_text"); }
QString gets_string_text() { return gets("string_text"); }
QStringList get_strings_string_text() { return get_strings("string_text"); }

//----------------------------------------------------
//Page Callback
//Testing Callback mechanism. Create other instance of Test, set it Run mode Callback and put its id here and press button.

//Button Callback
//Press button to start callback of selected modules.
bool was_changed_callback() { return was_changed("callback"); }
int geti_callback() { return geti("callback"); }

//Text Callback Modules
//List of modules which will be called by callback.
bool was_changed_callback_modules() { return was_changed("callback_modules"); }
QString gets_callback_modules() { return gets("callback_modules"); }
QStringList get_strings_callback_modules() { return get_strings("callback_modules"); }

//----------------------------------------------------
