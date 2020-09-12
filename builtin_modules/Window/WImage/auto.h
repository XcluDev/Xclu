//----------------------------------------------------
//Interface for XClassWImage
//Created automatically at 2020.09.12 21:37:02
//----------------------------------------------------
//Page Value
//Settings of value.

//Out Object Image
//Resulted image.
XDict *obj_image() { return get_object("image"); }

//Out Checkbox Is New Frame
//Flag is true when new frame is arrived during current 'update' step.
int i_is_new_frame() { return geti("is_new_frame"); }
void i_is_new_frame(int value) { seti("is_new_frame", value); }


//Enum Value Source
//Source of value: a fixed value, value from GUI, output value from other module, output JS expression.

enum enum_source {
    source_File = 0,
    source_Link = 1,
    source_Expression = 2,
    source_N__ = 3
};
enum_source en_source() { return enum_source(geti("source")); }

//String Image Link
//Link to other module's image.
QString s_image_link() { return gets("image_link"); }

//String Is New Frame Link
//Link to flag that image was changed.
QString s_is_new_frame_link() { return gets("is_new_frame_link"); }

//Text Expression
//JS expression for image source.
QString s_expression() { return gets("expression"); }

//----------------------------------------------------
//Page Visuals
//Visual settings.

//Out String Parent
//Parent module name (Window or WLayout) at which this element is placed.
QString s_parent_id() { return gets("parent_id"); }
void s_parent_id(QString value) { sets("parent_id", value); }

//Checkbox Visible
//Is visible.
int i_visible() { return geti("visible"); }


//Const Int W
//Width of image.
int i_w() { return geti("w"); }

//Const Int H
//Height of image.
int i_h() { return geti("h"); }


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

//----------------------------------------------------
