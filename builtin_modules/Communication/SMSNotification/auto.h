//----------------------------------------------------
//Interface for XClassSMSNotification
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

//Out String Parent
//Parent module name (Window or WLayout) at which this element is placed.
bool was_changed_parent_id() { return was_changed_("parent_id"); }
QString gets_parent_id() { return gets_("parent_id"); }
QStringList get_strings_parent_id() { return get_strings_("parent_id"); }
void sets_parent_id(QString value) { sets_("parent_id", value); }
void clear_string_parent_id() { clear_string_("parent_id"); }
void append_string_parent_id(QString v, int extra_new_lines_count = 0) { append_string_("parent_id", v, extra_new_lines_count); }
void append_string_parent_id(QStringList v, int extra_new_lines_count = 0) { append_string_("parent_id", v, extra_new_lines_count); }

//Checkbox Visible
//Is visible.
bool was_changed_visible() { return was_changed_("visible"); }
int geti_visible() { return geti_("visible"); }


//Enum Value Source
//Source of value: a fixed value, value from GUI, output value from other module, output JS expression.
enum enum_source {
    source_Fixed_Value = 0,
    source_GUI = 1,
    source_Other_Module_Value = 2,
    source_Expression = 3,
    source_N__ = 4
};
bool was_changed_source() { return was_changed_("source"); }
enum_source gete_source() { return enum_source(geti_("source")); }

//Enum Type
//Type of value.
enum enum_type {
    type_int = 0,
    type_float = 1,
    type_N__ = 2
};
bool was_changed_type() { return was_changed_("type"); }
enum_type gete_type() { return enum_type(geti_("type")); }

//Int Value
//
bool was_changed_fixed_value() { return was_changed_("fixed_value"); }
int geti_fixed_value() { return geti_("fixed_value"); }

//String Int Link
//Link to other module's variable.
bool was_changed_int_link() { return was_changed_("int_link"); }
QString gets_int_link() { return gets_("int_link"); }
QStringList get_strings_int_link() { return get_strings_("int_link"); }

//Text Expression
//JS expression for value.
bool was_changed_expression() { return was_changed_("expression"); }
QString gets_expression() { return gets_("expression"); }
QStringList get_strings_expression() { return get_strings_("expression"); }

//----------------------------------------------------
//Page Properties
//Range and visual settings.


//Checkbox Use Min
//Clamp value to specified minimal value.
bool was_changed_use_range_min() { return was_changed_("use_range_min"); }
int geti_use_range_min() { return geti_("use_range_min"); }

//Int Min
//
bool was_changed_min_value() { return was_changed_("min_value"); }
int geti_min_value() { return geti_("min_value"); }


//Checkbox Use Max
//Clamp value to specified maxinal value.
bool was_changed_use_range_max() { return was_changed_("use_range_max"); }
int geti_use_range_max() { return geti_("use_range_max"); }

//Int Max
//
bool was_changed_max_value() { return was_changed_("max_value"); }
int geti_max_value() { return geti_("max_value"); }


//Const Checkbox Title
//Title, placed at the left of the value.
bool was_changed_title() { return was_changed_("title"); }
int geti_title() { return geti_("title"); }

//String Title
//Text of title.
bool was_changed_title_text() { return was_changed_("title_text"); }
QString gets_title_text() { return gets_("title_text"); }
QStringList get_strings_title_text() { return get_strings_("title_text"); }

//Const Enum Placement
//Title placement position.
enum enum_title_placement {
    title_placement_Left = 0,
    title_placement_Right = 1,
    title_placement_Top = 2,
    title_placement_Bottom = 3,
    title_placement_N__ = 4
};
bool was_changed_title_placement() { return was_changed_("title_placement"); }
enum_title_placement gete_title_placement() { return enum_title_placement(geti_("title_placement")); }

//Const Enum Alignment
//Title alignment mode.
enum enum_title_alignment {
    title_alignment_Default = 0,
    title_alignment_Left = 1,
    title_alignment_Center = 2,
    title_alignment_Right = 3,
    title_alignment_N__ = 4
};
bool was_changed_title_alignment() { return was_changed_("title_alignment"); }
enum_title_alignment gete_title_alignment() { return enum_title_alignment(geti_("title_alignment")); }

//Const Enum Width
//Width of title.
enum enum_title_width {
    title_width_Default = 0,
    title_width_Custom_Range = 1,
    title_width_N__ = 2
};
bool was_changed_title_width() { return was_changed_("title_width"); }
enum_title_width gete_title_width() { return enum_title_width(geti_("title_width")); }

//Const Int Min
//Minimal title width.
bool was_changed_title_width_min() { return was_changed_("title_width_min"); }
int geti_title_width_min() { return geti_("title_width_min"); }

//Const Int Max
//Maximal title width.
bool was_changed_title_width_max() { return was_changed_("title_width_max"); }
int geti_title_width_max() { return geti_("title_width_max"); }


//Const Checkbox Units
//Units, placed at the right of the value.
bool was_changed_units() { return was_changed_("units"); }
int geti_units() { return geti_("units"); }

//String Units
//Text of units.
bool was_changed_units_text() { return was_changed_("units_text"); }
QString gets_units_text() { return gets_("units_text"); }
QStringList get_strings_units_text() { return get_strings_("units_text"); }

//Const Enum Alignment
//Units alignment mode.
enum enum_units_alignment {
    units_alignment_Default = 0,
    units_alignment_Left = 1,
    units_alignment_Center = 2,
    units_alignment_Right = 3,
    units_alignment_N__ = 4
};
bool was_changed_units_alignment() { return was_changed_("units_alignment"); }
enum_units_alignment gete_units_alignment() { return enum_units_alignment(geti_("units_alignment")); }

//Const Enum Width
//Width of units.
enum enum_units_width {
    units_width_Default = 0,
    units_width_Custom_Range = 1,
    units_width_N__ = 2
};
bool was_changed_units_width() { return was_changed_("units_width"); }
enum_units_width gete_units_width() { return enum_units_width(geti_("units_width")); }

//Const Int Min
//Minimal units width.
bool was_changed_units_width_min() { return was_changed_("units_width_min"); }
int geti_units_width_min() { return geti_("units_width_min"); }

//Const Int Max
//Maximal units width.
bool was_changed_units_width_max() { return was_changed_("units_width_max"); }
int geti_units_width_max() { return geti_("units_width_max"); }

//----------------------------------------------------
//Page Actions
//Detection of changes and action on changing.

//Out Checkbox Was Changed
//This checkbox is set to true when value was changed, after the module's "update" and until next module's "update".
bool was_changed_was_changed() { return was_changed_("was_changed"); }
int geti_was_changed() { return geti_("was_changed"); }
void seti_was_changed(int value) { seti_("was_changed", value); }


//Enum On Change
//What to do on value change. The event occured after the module's "update".
enum enum_on_change {
    on_change_Do_Nothing = 0,
    on_change_Call_Module = 1,
    on_change_Execute_Script = 2,
    on_change_N__ = 3
};
bool was_changed_on_change() { return was_changed_("on_change"); }
enum_on_change gete_on_change() { return enum_on_change(geti_("on_change")); }

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
