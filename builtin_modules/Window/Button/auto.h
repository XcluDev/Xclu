//----------------------------------------------------
//Interface for XClassButton
//Created automatically.
//----------------------------------------------------
//Page Value
//Settings of value.

//Out Int Resulted Value
//Resulted value
bool was_changed_value() { return was_changed_("value"); }
int geti_value() { return geti_("value"); }
void seti_value(int value) { seti_("value", value); }
void increase_int_value(int increase = 1) { increase_int_("value", increase); }

//Out String Belongs To
//Window/layout this element is placed - specified by window.
bool was_changed_belongs_to() { return was_changed_("belongs_to"); }
QString gets_belongs_to() { return gets_("belongs_to"); }
QStringList get_strings_belongs_to() { return get_strings_("belongs_to"); }
void sets_belongs_to(QString value) { sets_("belongs_to", value); }
void clear_string_belongs_to() { clear_string_("belongs_to"); }
void append_string_belongs_to(QString v, int extra_new_lines_count = 0) { append_string_("belongs_to", v, extra_new_lines_count); }
void append_string_belongs_to(QStringList v, int extra_new_lines_count = 0) { append_string_("belongs_to", v, extra_new_lines_count); }

//----------------------------------------------------
//Page Visual
//Settings of visual representation.

//Checkbox Visible
//Is visible
bool was_changed_visible() { return was_changed_("visible"); }
int geti_visible() { return geti_("visible"); }

//String Title
//Button title
bool was_changed_title_text() { return was_changed_("title_text"); }
QString gets_title_text() { return gets_("title_text"); }
QStringList get_strings_title_text() { return get_strings_("title_text"); }

//Const Enum Width
//Width of button.
enum enum_button_width {
    button_width_Default = 0,
    button_width_Custom_Range = 1,
    button_width_N__ = 2
};
bool was_changed_button_width() { return was_changed_("button_width"); }
enum_button_width gete_button_width() { return enum_button_width(geti_("button_width")); }
QString getraw_button_width() { return getraw_("button_width");}

//Const Int Min
//Minimal button width.
bool was_changed_button_width_min() { return was_changed_("button_width_min"); }
int geti_button_width_min() { return geti_("button_width_min"); }

//Const Int Max
//Maximal button width.
bool was_changed_button_width_max() { return was_changed_("button_width_max"); }
int geti_button_width_max() { return geti_("button_width_max"); }

//----------------------------------------------------
//Page On Change
//Detection of changes and action on changing.

//Out Checkbox Was Clicked
//This checkbox is set to true when button was clicked, after the module's "update" and until next module's "update".
bool was_changed_was_clicked() { return was_changed_("was_clicked"); }
int geti_was_clicked() { return geti_("was_clicked"); }
void seti_was_clicked(int value) { seti_("was_clicked", value); }


//Enum On Click
//What to do on button click. The event occured after the module's "update".
enum enum_on_click {
    on_click_Do_Nothing = 0,
    on_click_Call_Module = 1,
    on_click_Execute_Script = 2,
    on_click_N__ = 3
};
bool was_changed_on_click() { return was_changed_("on_click"); }
enum_on_click gete_on_click() { return enum_on_click(geti_("on_click")); }
QString getraw_on_click() { return getraw_("on_click");}

//String Module Call Link
//Call other module on value change.
bool was_changed_on_change_module_call_link() { return was_changed_("on_change_module_call_link"); }
QString gets_on_change_module_call_link() { return gets_("on_change_module_call_link"); }
QStringList get_strings_on_change_module_call_link() { return get_strings_("on_change_module_call_link"); }

//Text Script
//Script to execute on value change.
bool was_changed_on_change_script() { return was_changed_("on_change_script"); }
QString gets_on_change_script() { return gets_("on_change_script"); }
QStringList get_strings_on_change_script() { return get_strings_("on_change_script"); }

//----------------------------------------------------
