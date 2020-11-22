//----------------------------------------------------
//Interface for XClassWImage
//Created automatically.
//----------------------------------------------------
//Page Main
//Input image

//Object Image
//Input image.
bool was_changed_image() { return was_changed_("image"); }
XProtectedObject *getobject_image() { return get_object_("image"); }

//Checkbox Is New Frame
//Flag that image was changed. You may link it to the flag of an image provider module.
bool was_changed_is_new_frame() { return was_changed_("is_new_frame"); }
int geti_is_new_frame() { return geti_("is_new_frame"); }

//----------------------------------------------------
//Page Visuals
//Visual settings.

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


//Const Int W
//Width of image.
bool was_changed_w() { return was_changed_("w"); }
int geti_w() { return geti_("w"); }

//Const Int H
//Height of image.
bool was_changed_h() { return was_changed_("h"); }
int geti_h() { return geti_("h"); }


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
QString getraw_title_placement() { return getraw_("title_placement");}

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
QString getraw_title_alignment() { return getraw_("title_alignment");}

//Const Enum Width
//Width of title.
enum enum_title_width {
    title_width_Default = 0,
    title_width_Custom_Range = 1,
    title_width_N__ = 2
};
bool was_changed_title_width() { return was_changed_("title_width"); }
enum_title_width gete_title_width() { return enum_title_width(geti_("title_width")); }
QString getraw_title_width() { return getraw_("title_width");}

//Const Int Min
//Minimal title width.
bool was_changed_title_width_min() { return was_changed_("title_width_min"); }
int geti_title_width_min() { return geti_("title_width_min"); }

//Const Int Max
//Maximal title width.
bool was_changed_title_width_max() { return was_changed_("title_width_max"); }
int geti_title_width_max() { return geti_("title_width_max"); }

//----------------------------------------------------
