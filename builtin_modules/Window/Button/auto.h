//----------------------------------------------------
//Interface for XClassButton
//Created automatically at 2020.09.12 21:37:01
//----------------------------------------------------
//Page Value
//Settings of value.

//Out Int Resulted Value
//Resulted value
int i_value() { return geti("value"); }
void i_value(int value) { seti("value", value); }

//Out String Belongs To
//Window/layout this element is placed - specified by window.
QString s_belongs_to() { return gets("belongs_to"); }
void s_belongs_to(QString value) { sets("belongs_to", value); }

//----------------------------------------------------
//Page Visual
//Settings of visual representation.

//Checkbox Visible
//Is visible
int i_visible() { return geti("visible"); }

//String Title
//Button title
QString s_title_text() { return gets("title_text"); }

//Const Enum Width
//Width of button.

enum enum_button_width {
    button_width_Default = 0,
    button_width_Custom_Range = 1,
    button_width_N__ = 2
};
enum_button_width en_button_width() { return enum_button_width(geti("button_width")); }

//Const Int Min
//Minimal button width.
int i_button_width_min() { return geti("button_width_min"); }

//Const Int Max
//Maximal button width.
int i_button_width_max() { return geti("button_width_max"); }

//----------------------------------------------------
//Page On Change
//Detection of changes and action on changing.

//Out Checkbox Was Clicked
//This checkbox is set to true when button was clicked, after the module's "update" and until next module's "update".
int i_was_clicked() { return geti("was_clicked"); }
void i_was_clicked(int value) { seti("was_clicked", value); }


//Enum On Click
//What to do on button click. The event occured after the module's "update".

enum enum_on_click {
    on_click_Do_Nothing = 0,
    on_click_Call_Module = 1,
    on_click_Execute_Script = 2,
    on_click_N__ = 3
};
enum_on_click en_on_click() { return enum_on_click(geti("on_click")); }

//String Module Call Link
//Call other module on value change.
QString s_on_change_module_call_link() { return gets("on_change_module_call_link"); }

//Text Script
//Script to execute on value change.
QString s_on_change_script() { return gets("on_change_script"); }

//----------------------------------------------------
