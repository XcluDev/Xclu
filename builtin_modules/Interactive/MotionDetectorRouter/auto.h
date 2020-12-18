//----------------------------------------------------
//Interface for XClassMotionDetectorRouter
//Created automatically.
//----------------------------------------------------
//Page Main
//General settings

//Const Int Inputs
//How many images use.
bool was_changed_inputs() { return was_changed_("inputs"); }
int geti_inputs() { return geti_("inputs"); }


//Object Input1
//Input image.
bool was_changed_input1() { return was_changed_("input1"); }
XProtectedObject *getobject_input1() { return get_object_("input1"); }
//Object Input2
//Input image.
bool was_changed_input2() { return was_changed_("input2"); }
XProtectedObject *getobject_input2() { return get_object_("input2"); }
//Object Input3
//Input image.
bool was_changed_input3() { return was_changed_("input3"); }
XProtectedObject *getobject_input3() { return get_object_("input3"); }
//Object Input4
//Input image.
bool was_changed_input4() { return was_changed_("input4"); }
XProtectedObject *getobject_input4() { return get_object_("input4"); }

//----------------------------------------------------
//Page Output
//


//Out Object Output1
//Output image.
bool was_changed_output1() { return was_changed_("output1"); }
XProtectedObject *getobject_output1() { return get_object_("output1"); }
void setobject_output1(XProtectedObject *value) { set_object_("output1", value); }
void setobject_output1(XProtectedObject &value) { set_object_("output1", value); }
//Out Object Output2
//Output image.
bool was_changed_output2() { return was_changed_("output2"); }
XProtectedObject *getobject_output2() { return get_object_("output2"); }
void setobject_output2(XProtectedObject *value) { set_object_("output2", value); }
void setobject_output2(XProtectedObject &value) { set_object_("output2", value); }
//Out Object Output3
//Output image.
bool was_changed_output3() { return was_changed_("output3"); }
XProtectedObject *getobject_output3() { return get_object_("output3"); }
void setobject_output3(XProtectedObject *value) { set_object_("output3", value); }
void setobject_output3(XProtectedObject &value) { set_object_("output3", value); }
//Out Object Output4
//Output image.
bool was_changed_output4() { return was_changed_("output4"); }
XProtectedObject *getobject_output4() { return get_object_("output4"); }
void setobject_output4(XProtectedObject *value) { set_object_("output4", value); }
void setobject_output4(XProtectedObject &value) { set_object_("output4", value); }

//----------------------------------------------------
//Page Routing
//

//Const Enum Route Method
//Use manual routing or automatic based on saved tamplate
enum enum_route_method {
    route_method_Manual = 0,
    route_method_Using_Templates = 1,
    route_method_N__ = 2
};
bool was_changed_route_method() { return was_changed_("route_method"); }
enum_route_method gete_route_method() { return enum_route_method(geti_("route_method")); }
QString getraw_route_method() { return getraw_("route_method");}


//Const String Route
//Destination of routing for first, second, third and fourth cameras, such as "1 2 3 4" or "1 3 2 4", and so on.
bool was_changed_route_manual() { return was_changed_("route_manual"); }
QString gets_route_manual() { return gets_("route_manual"); }
QStringList get_strings_route_manual() { return get_strings_("route_manual"); }

//Out String Route
//Automatically made destination of routing for first, second, third and fourth cameras, such as "1 2 3 4" or "1 3 2 4", and so on.
bool was_changed_route_template() { return was_changed_("route_template"); }
QString gets_route_template() { return gets_("route_template"); }
QStringList get_strings_route_template() { return get_strings_("route_template"); }
void sets_route_template(QString value) { sets_("route_template", value); }
void clear_string_route_template() { clear_string_("route_template"); }
void append_string_route_template(QString v, int extra_new_lines_count = 0) { append_string_("route_template", v, extra_new_lines_count); }
void append_string_route_template(QStringList v, int extra_new_lines_count = 0) { append_string_("route_template", v, extra_new_lines_count); }


//Out Object Template1
//Output image.
bool was_changed_template1() { return was_changed_("template1"); }
XProtectedObject *getobject_template1() { return get_object_("template1"); }
void setobject_template1(XProtectedObject *value) { set_object_("template1", value); }
void setobject_template1(XProtectedObject &value) { set_object_("template1", value); }
//Out Object Template2
//Output image.
bool was_changed_template2() { return was_changed_("template2"); }
XProtectedObject *getobject_template2() { return get_object_("template2"); }
void setobject_template2(XProtectedObject *value) { set_object_("template2", value); }
void setobject_template2(XProtectedObject &value) { set_object_("template2", value); }
//Out Object Template3
//Output image.
bool was_changed_template3() { return was_changed_("template3"); }
XProtectedObject *getobject_template3() { return get_object_("template3"); }
void setobject_template3(XProtectedObject *value) { set_object_("template3", value); }
void setobject_template3(XProtectedObject &value) { set_object_("template3", value); }
//Out Object Template4
//Output image.
bool was_changed_template4() { return was_changed_("template4"); }
XProtectedObject *getobject_template4() { return get_object_("template4"); }
void setobject_template4(XProtectedObject *value) { set_object_("template4", value); }
void setobject_template4(XProtectedObject &value) { set_object_("template4", value); }

//Button Save Templates
//Press the button to save current images to template files. Note: you need to create folder by yourself.
bool was_changed_save_templates() { return was_changed_("save_templates"); }
int geti_save_templates() { return geti_("save_templates"); }
QString button_save_templates() { return "save_templates"; }


//Const Int W
//Width of template match image. Normally 8 times less than original images for robustness.
bool was_changed_templ_w() { return was_changed_("templ_w"); }
int geti_templ_w() { return geti_("templ_w"); }

//Const Int H
//Height of template match image. Normally 8 times less than original images for robustness.
bool was_changed_templ_h() { return was_changed_("templ_h"); }
int geti_templ_h() { return geti_("templ_h"); }


//Checkbox Show File Names
//Show file names for template files images.
bool was_changed_show_file_names() { return was_changed_("show_file_names"); }
int geti_show_file_names() { return geti_("show_file_names"); }

//Const Text Template Files
//Template images file names. The folder will be created automatically if necessary.
bool was_changed_template_files() { return was_changed_("template_files"); }
QString gets_template_files() { return gets_("template_files"); }
QStringList get_strings_template_files() { return get_strings_("template_files"); }

//----------------------------------------------------
//Page Settings
//

//Int Ignore Start Frames
//How much ignore frames at project - to let camera do its brightness adjustments.
bool was_changed_ignore_start_frames() { return was_changed_("ignore_start_frames"); }
int geti_ignore_start_frames() { return geti_("ignore_start_frames"); }


//Out Checkbox Started
//Link this value to "Enabled" control of motion detectors, in order they start work only when router is ready.
bool was_changed_started() { return was_changed_("started"); }
int geti_started() { return geti_("started"); }
void seti_started(int value) { seti_("started", value); }

//----------------------------------------------------
