//----------------------------------------------------
//Interface for XClassMailNotification
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

//Out String Parent
//Parent module name (Window or WLayout) at which this element is placed.
bool was_changed_parent_id() { return was_changed("parent_id"); }
QString gets_parent_id() { return gets("parent_id"); }
QStringList get_strings_parent_id() { return get_strings("parent_id"); }
void sets_parent_id(QString value) { sets("parent_id", value); }
void clear_string_parent_id() { clear_string("parent_id"); }
void append_string_parent_id(QString v, int extra_new_lines_count = 0) { append_string("parent_id", v, extra_new_lines_count); }
void append_string_parent_id(QStringList v, int extra_new_lines_count = 0) { append_string("parent_id", v, extra_new_lines_count); }

//Checkbox Visible
//Is visible.
bool was_changed_visible() { return was_changed("visible"); }
int geti_visible() { return geti("visible"); }


//Enum Value Source
//Source of value: a fixed value, value from GUI, output value from other module, output JS expression.
enum enum_source {
    source_Fixed_Value = 0,
    source_GUI = 1,
    source_Other_Module_Value = 2,
    source_Expression = 3,
    source_N__ = 4
};
bool was_changed_source() { return was_changed("source"); }
enum_source gete_source() { return enum_source(geti("source")); }

//Enum Type
//Type of value.
enum enum_type {
    type_int = 0,
    type_float = 1,
    type_N__ = 2
};
bool was_changed_type() { return was_changed("type"); }
enum_type gete_type() { return enum_type(geti("type")); }

//Int Value
//
bool was_changed_fixed_value() { return was_changed("fixed_value"); }
int geti_fixed_value() { return geti("fixed_value"); }

//String Int Link
//Link to other module's variable.
bool was_changed_int_link() { return was_changed("int_link"); }
QString gets_int_link() { return gets("int_link"); }
QStringList get_strings_int_link() { return get_strings("int_link"); }

//Text Expression
//JS expression for value.
bool was_changed_expression() { return was_changed("expression"); }
QString gets_expression() { return gets("expression"); }
QStringList get_strings_expression() { return get_strings("expression"); }

//----------------------------------------------------
//Page Properties
//Range and visual settings.


//Checkbox Use Min
//Clamp value to specified minimal value.
bool was_changed_use_range_min() { return was_changed("use_range_min"); }
int geti_use_range_min() { return geti("use_range_min"); }

//Int Min
//
bool was_changed_min_value() { return was_changed("min_value"); }
int geti_min_value() { return geti("min_value"); }


//Checkbox Use Max
//Clamp value to specified maxinal value.
bool was_changed_use_range_max() { return was_changed("use_range_max"); }
int geti_use_range_max() { return geti("use_range_max"); }

//Int Max
//
bool was_changed_max_value() { return was_changed("max_value"); }
int geti_max_value() { return geti("max_value"); }


//Const Checkbox Title
//Title, placed at the left of the value.
bool was_changed_title() { return was_changed("title"); }
int geti_title() { return geti("title"); }

//String Title
//Text of title.
bool was_changed_title_text() { return was_changed("title_text"); }
QString gets_title_text() { return gets("title_text"); }
QStringList get_strings_title_text() { return get_strings("title_text"); }

//Const Enum Placement
//Title placement position.
enum enum_title_placement {
    title_placement_Left = 0,
    title_placement_Right = 1,
    title_placement_Top = 2,
    title_placement_Bottom = 3,
    title_placement_N__ = 4
};
bool was_changed_title_placement() { return was_changed("title_placement"); }
enum_title_placement gete_title_placement() { return enum_title_placement(geti("title_placement")); }

//Const Enum Alignment
//Title alignment mode.
enum enum_title_alignment {
    title_alignment_Default = 0,
    title_alignment_Left = 1,
    title_alignment_Center = 2,
    title_alignment_Right = 3,
    title_alignment_N__ = 4
};
bool was_changed_title_alignment() { return was_changed("title_alignment"); }
enum_title_alignment gete_title_alignment() { return enum_title_alignment(geti("title_alignment")); }

//Const Enum Width
//Width of title.
enum enum_title_width {
    title_width_Default = 0,
    title_width_Custom_Range = 1,
    title_width_N__ = 2
};
bool was_changed_title_width() { return was_changed("title_width"); }
enum_title_width gete_title_width() { return enum_title_width(geti("title_width")); }

//Const Int Min
//Minimal title width.
bool was_changed_title_width_min() { return was_changed("title_width_min"); }
int geti_title_width_min() { return geti("title_width_min"); }

//Const Int Max
//Maximal title width.
bool was_changed_title_width_max() { return was_changed("title_width_max"); }
int geti_title_width_max() { return geti("title_width_max"); }


//Const Checkbox Units
//Units, placed at the right of the value.
bool was_changed_units() { return was_changed("units"); }
int geti_units() { return geti("units"); }

//String Units
//Text of units.
bool was_changed_units_text() { return was_changed("units_text"); }
QString gets_units_text() { return gets("units_text"); }
QStringList get_strings_units_text() { return get_strings("units_text"); }

//Const Enum Alignment
//Units alignment mode.
enum enum_units_alignment {
    units_alignment_Default = 0,
    units_alignment_Left = 1,
    units_alignment_Center = 2,
    units_alignment_Right = 3,
    units_alignment_N__ = 4
};
bool was_changed_units_alignment() { return was_changed("units_alignment"); }
enum_units_alignment gete_units_alignment() { return enum_units_alignment(geti("units_alignment")); }

//Const Enum Width
//Width of units.
enum enum_units_width {
    units_width_Default = 0,
    units_width_Custom_Range = 1,
    units_width_N__ = 2
};
bool was_changed_units_width() { return was_changed("units_width"); }
enum_units_width gete_units_width() { return enum_units_width(geti("units_width")); }

//Const Int Min
//Minimal units width.
bool was_changed_units_width_min() { return was_changed("units_width_min"); }
int geti_units_width_min() { return geti("units_width_min"); }

//Const Int Max
//Maximal units width.
bool was_changed_units_width_max() { return was_changed("units_width_max"); }
int geti_units_width_max() { return geti("units_width_max"); }

//----------------------------------------------------
//Page Actions
//Detection of changes and action on changing.

//Out Checkbox Was Changed
//This checkbox is set to true when value was changed, after the module's "update" and until next module's "update".
bool was_changed_was_changed() { return was_changed("was_changed"); }
int geti_was_changed() { return geti("was_changed"); }
void seti_was_changed(int value) { seti("was_changed", value); }


//Enum On Change
//What to do on value change. The event occured after the module's "update".
enum enum_on_change {
    on_change_Do_Nothing = 0,
    on_change_Call_Module = 1,
    on_change_Execute_Script = 2,
    on_change_N__ = 3
};
bool was_changed_on_change() { return was_changed("on_change"); }
enum_on_change gete_on_change() { return enum_on_change(geti("on_change")); }

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
