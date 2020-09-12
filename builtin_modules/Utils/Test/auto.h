//----------------------------------------------------
//Interface for XClassTest
//Created automatically at 2020.09.12 21:37:02
//----------------------------------------------------
//Page Main
//

//Button Test
//Test button.
int i_button1() { return geti("button1"); }


//Const Checkbox Const Checkbox
//Constant value.
int i_const_check() { return geti("const_check"); }

//Checkbox In Checkbox
//Input value.
int i_in_check() { return geti("in_check"); }

//Out Checkbox Out Checkbox
//Output value.
int i_out_check() { return geti("out_check"); }
void i_out_check(int value) { seti("out_check", value); }


//Const Float Const Float
//Constant value.
float f_float1() { return getf("float1"); }

//Float In Float
//Input value.
float f_float2() { return getf("float2"); }

//Out Float Out Float
//Output value.
float f_float3() { return getf("float3"); }
void f_float3(float value) { setf("float3", value); }


//Const Int Const Int
//Constant value.
int i_int1() { return geti("int1"); }

//Int In Int
//Input value.
int i_int2() { return geti("int2"); }

//Out Int Out Int
//Output value.
int i_int3() { return geti("int3"); }
void i_int3(int value) { seti("int3", value); }


//Const String Const String
//Constant value.
QString s_string1() { return gets("string1"); }

//String In String
//Input value.
QString s_string2() { return gets("string2"); }

//Out String Out String
//Output value.
QString s_string3() { return gets("string3"); }
void s_string3(QString value) { sets("string3", value); }


//Const Enum Const List
//Constant value.

enum enum_list1 {
    list1_By_Name = 0,
    list1_By_Id = 1,
    list1_N__ = 2
};
enum_list1 en_list1() { return enum_list1(geti("list1")); }

//Enum In List
//Input value.

enum enum_list2 {
    list2_By_Name = 0,
    list2_By_Id = 1,
    list2_N__ = 2
};
enum_list2 en_list2() { return enum_list2(geti("list2")); }

//Out Enum Out List
//Output value.

enum enum_list3 {
    list3_By_Name = 0,
    list3_By_Id = 1,
    list3_N__ = 2
};
enum_list3 en_list3() { return enum_list3(geti("list3")); }
void en_list3(enum_list3 value) { seti("list3", value); }


//Const Text Const Text
//Constant value.
QString s_text1() { return gets("text1"); }

//Text In Text
//Input value.
QString s_text2() { return gets("text2"); }

//Out Text Out Text
//Output value.
QString s_text3() { return gets("text3"); }
void s_text3(QString value) { sets("text3", value); }


//Object Object
//
XDict *obj_object() { return get_object("object"); }

//----------------------------------------------------
//Page Choose Files
//

//String Choose File
//Description
QString s_choose:file() { return gets("choose:file"); }

//String Choose Folder
//Description.
QString s_choose_Folder() { return gets("choose_Folder"); }

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
enum_type en_type() { return enum_type(geti("type")); }


//String Numbered
//
QString s_numbered() { return gets("numbered"); }


//Text Number Text
//
QString s_number_text() { return gets("number_text"); }

//String Stringed
//
QString s_stringed() { return gets("stringed"); }


//Text String Text
//
QString s_string_text() { return gets("string_text"); }

//----------------------------------------------------
//Page Callback
//Testing Callback mechanism. Create other instance of Test, set it Run mode Callback and put its id here and press button.

//Button Callback
//Press button to start callback of selected modules.
int i_callback() { return geti("callback"); }

//Text Callback Modules
//List of modules which will be called by callback.
QString s_callback_modules() { return gets("callback_modules"); }

//----------------------------------------------------
