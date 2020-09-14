//----------------------------------------------------
//Interface for XClassButton
//Created automatically at 2020.09.14 11:01:46
//----------------------------------------------------
//Page Value
//Settings of value.

//Out Int Resulted Value
//Resulted value
bool was_changed_value() { return was_changed("value"); }
int geti_value() { return geti("value"); }
void seti_value(int value) { seti("value", value); }
void increase_int_value(int increase = 1) { increase_int("value", increase); }

//Out String Belongs To
//Window/layout this element is placed - specified by window.
bool was_changed_belongs_to() { return was_changed("belongs_to"); }
QString gets_belongs_to() { return gets("belongs_to"); }
QStringList get_strings_belongs_to() { return get_strings("belongs_to"); }
void sets_belongs_to(QString value) { sets("belongs_to", value); }
void clear_string_belongs_to() { clear_string("belongs_to"); }
void append_string_belongs_to(QString v, int extra_new_lines_count = 0) { append_string("belongs_to", v, extra_new_lines_count); }
void append_string_belongs_to(QStringList v, int extra_new_lines_count = 0) { append_string("belongs_to", v, extra_new_lines_count); }

//----------------------------------------------------
//Page Visual
//Settings of visual representation.

//Checkbox Visible
//Is visible
bool was_changed_visible() { return was_changed("visible"); }
int geti_visible() { return geti("visible"); }

//String Title
//Button title
bool was_changed_title_text() { return was_changed("title_text"); }
QString gets_title_text() { return gets("title_text"); }
QStringList get_strings_title_text() { return get_strings("title_text"); }

//Const Enum Width
//Width of button.
enum enum_button_width {
    button_width_Default = 0,
    button_width_Custom_Range = 1,
    button_width_N__ = 2
};
bool was_changed_button_width() { return was_changed("button_width"); }
enum_button_width gete_button_width() { return enum_button_width(geti("button_width")); }

//Const Int Min
//Minimal button width.
bool was_changed_button_width_min() { return was_changed("button_width_min"); }
int geti_button_width_min() { return geti("button_width_min"); }

//Const Int Max
//Maximal button width.
bool was_changed_button_width_max() { return was_changed("button_width_max"); }
int geti_button_width_max() { return geti("button_width_max"); }

//----------------------------------------------------
//Page On Change
//Detection of changes and action on changing.

//Out Checkbox Was Clicked
//This checkbox is set to true when button was clicked, after the module's "update" and until next module's "update".
bool was_changed_was_clicked() { return was_changed("was_clicked"); }
int geti_was_clicked() { return geti("was_clicked"); }
void seti_was_clicked(int value) { seti("was_clicked", value); }


//Enum On Click
//What to do on button click. The event occured after the module's "update".
enum enum_on_click {
    on_click_Do_Nothing = 0,
    on_click_Call_Module = 1,
    on_click_Execute_Script = 2,
    on_click_N__ = 3
};
bool was_changed_on_click() { return was_changed("on_click"); }
enum_on_click gete_on_click() { return enum_on_click(geti("on_click")); }

//String Module Call Link
//Call other module on value change.
bool was_changed_on_change_module_call_link() { return was_changed("on_change_module_call_link"); }
QString gets_on_change_module_call_link() { return gets("on_change_module_call_link"); }
QStringList get_strings_on_change_module_call_link() { return get_strings("on_change_module_call_link"); }

//Text Script
//Script to execute on value change.
bool was_changed_on_change_script() { return was_changed("on_change_script"); }
QString gets_on_change_script() { return gets("on_change_script"); }
QStringList get_strings_on_change_script() { return get_strings("on_change_script"); }

//----------------------------------------------------
