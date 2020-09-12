//----------------------------------------------------
//Interface for XClassWPanoramaView
//Created automatically at 2020.09.12 21:37:02
//----------------------------------------------------
//Page Value
//Settings of value.

//Out Int Resulted Value
//Resulted value
int i_value() { return geti("value"); }
void i_value(int value) { seti("value", value); }

//Out String Parent
//Parent module name (Window or WLayout) at which this element is placed.
QString s_parent_id() { return gets("parent_id"); }
void s_parent_id(QString value) { sets("parent_id", value); }

//Checkbox Visible
//Is visible.
int i_visible() { return geti("visible"); }


//Enum Value Source
//Source of value: a fixed value, value from GUI, output value from other module, output JS expression.

enum enum_source {
    source_Fixed_Value = 0,
    source_GUI = 1,
    source_Other_Module_Value = 2,
    source_Expression = 3,
    source_N__ = 4
};
enum_source en_source() { return enum_source(geti("source")); }

//Enum Type
//Type of value.

enum enum_type {
    type_int = 0,
    type_float = 1,
    type_N__ = 2
};
enum_type en_type() { return enum_type(geti("type")); }

//Int Value
//
int i_fixed_value() { return geti("fixed_value"); }

//String Int Link
//Link to other module's variable.
QString s_int_link() { return gets("int_link"); }

//Text Expression
//JS expression for value.
QString s_expression() { return gets("expression"); }

//----------------------------------------------------
//Page Properties
//Range and visual settings.


//Checkbox Use Min
//Clamp value to specified minimal value.
int i_use_range_min() { return geti("use_range_min"); }

//Int Min
//
int i_min_value() { return geti("min_value"); }


//Checkbox Use Max
//Clamp value to specified maxinal value.
int i_use_range_max() { return geti("use_range_max"); }

//Int Max
//
int i_max_value() { return geti("max_value"); }


//Const Checkbox Title
//Title, placed at the left of the value.
int i_title() { return geti("title"); }

//String Title
//Text of title.
QString s_title_text() { return gets("title_text"); }

//Const Enum Placement
//Title placement position.

enum enum_title_placement {
    title_placement_Left = 0,
    title_placement_Right = 1,
    title_placement_Top = 2,
    title_placement_Bottom = 3,
    title_placement_N__ = 4
};
enum_title_placement en_title_placement() { return enum_title_placement(geti("title_placement")); }

//Const Enum Alignment
//Title alignment mode.

enum enum_title_alignment {
    title_alignment_Default = 0,
    title_alignment_Left = 1,
    title_alignment_Center = 2,
    title_alignment_Right = 3,
    title_alignment_N__ = 4
};
enum_title_alignment en_title_alignment() { return enum_title_alignment(geti("title_alignment")); }

//Const Enum Width
//Width of title.

enum enum_title_width {
    title_width_Default = 0,
    title_width_Custom_Range = 1,
    title_width_N__ = 2
};
enum_title_width en_title_width() { return enum_title_width(geti("title_width")); }

//Const Int Min
//Minimal title width.
int i_title_width_min() { return geti("title_width_min"); }

//Const Int Max
//Maximal title width.
int i_title_width_max() { return geti("title_width_max"); }


//Const Checkbox Units
//Units, placed at the right of the value.
int i_units() { return geti("units"); }

//String Units
//Text of units.
QString s_units_text() { return gets("units_text"); }

//Const Enum Alignment
//Units alignment mode.

enum enum_units_alignment {
    units_alignment_Default = 0,
    units_alignment_Left = 1,
    units_alignment_Center = 2,
    units_alignment_Right = 3,
    units_alignment_N__ = 4
};
enum_units_alignment en_units_alignment() { return enum_units_alignment(geti("units_alignment")); }

//Const Enum Width
//Width of units.

enum enum_units_width {
    units_width_Default = 0,
    units_width_Custom_Range = 1,
    units_width_N__ = 2
};
enum_units_width en_units_width() { return enum_units_width(geti("units_width")); }

//Const Int Min
//Minimal units width.
int i_units_width_min() { return geti("units_width_min"); }

//Const Int Max
//Maximal units width.
int i_units_width_max() { return geti("units_width_max"); }

//----------------------------------------------------
//Page Actions
//Detection of changes and action on changing.

//Out Checkbox Was Changed
//This checkbox is set to true when value was changed, after the module's "update" and until next module's "update".
int i_was_changed() { return geti("was_changed"); }
void i_was_changed(int value) { seti("was_changed", value); }


//Enum On Change
//What to do on value change. The event occured after the module's "update".

enum enum_on_change {
    on_change_Do_Nothing = 0,
    on_change_Call_Module = 1,
    on_change_Execute_Script = 2,
    on_change_N__ = 3
};
enum_on_change en_on_change() { return enum_on_change(geti("on_change")); }

//String Module Call Link
//Call other module on value change.
QString s_on_change_module_call_link() { return gets("on_change_module_call_link"); }

//Text Script
//Script to execute on value change.
QString s_on_change_script() { return gets("on_change_script"); }

//----------------------------------------------------
