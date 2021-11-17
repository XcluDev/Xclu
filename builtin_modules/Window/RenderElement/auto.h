//----------------------------------------------------
//Interface for XClassRenderElement
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Const Enum Type
//Type of element.
enum enum_type {
    type_Text = 0,
    type_Button = 1,
    type_Slider = 2,
    type_Fader = 3,
    type_Image = 4,
    type_Circle = 5,
    type_Rectangle = 6,
    type_Line = 7,
    type_N__ = 8
};
bool was_changed_type() { return was_changed_("type"); }
enum_type gete_type() { return enum_type(geti_("type")); }
QString getraw_type() { return getraw_("type");}

//Const Enum Shape
//Shape of the button.
enum enum_button_shape {
    button_shape_Rectangle = 0,
    button_shape_Circle = 1,
    button_shape_N__ = 2
};
bool was_changed_button_shape() { return was_changed_("button_shape"); }
enum_button_shape gete_button_shape() { return enum_button_shape(geti_("button_shape")); }
QString getraw_button_shape() { return getraw_("button_shape");}


//Const Checkbox Repeats
//Repeating the element, if enabled - see Repeats page.
bool was_changed_repeats() { return was_changed_("repeats"); }
int geti_repeats() { return geti_("repeats"); }
void repaint_repeats() { repaint_("repeats"); }

//String Title
//Title of element.
bool was_changed_title() { return was_changed_("title"); }
QString gets_title() { return gets_("title"); }
QStringList get_strings_title() { return get_strings_("title"); }
void repaint_title() { repaint_("title"); }


//Checkbox Title Setup
//
bool was_changed_title_setup() { return was_changed_("title_setup"); }
int geti_title_setup() { return geti_("title_setup"); }
void repaint_title_setup() { repaint_("title_setup"); }

//Int Title Size
//Title font size.
bool was_changed_title_size() { return was_changed_("title_size"); }
int geti_title_size() { return geti_("title_size"); }
void repaint_title_size() { repaint_("title_size"); }

//Int Title Red
//
bool was_changed_title_red() { return was_changed_("title_red"); }
int geti_title_red() { return geti_("title_red"); }
void repaint_title_red() { repaint_("title_red"); }

//Int Title Green
//
bool was_changed_title_green() { return was_changed_("title_green"); }
int geti_title_green() { return geti_("title_green"); }
void repaint_title_green() { repaint_("title_green"); }

//Int Title Blue
//
bool was_changed_title_blue() { return was_changed_("title_blue"); }
int geti_title_blue() { return geti_("title_blue"); }
void repaint_title_blue() { repaint_("title_blue"); }


//Int X
//
bool was_changed_x_int2000() { return was_changed_("x_int2000"); }
int geti_x_int2000() { return geti_("x_int2000"); }
void repaint_x_int2000() { repaint_("x_int2000"); }

//Int Y
//
bool was_changed_y_int2000() { return was_changed_("y_int2000"); }
int geti_y_int2000() { return geti_("y_int2000"); }
void repaint_y_int2000() { repaint_("y_int2000"); }

//Int W
//
bool was_changed_w_int2000() { return was_changed_("w_int2000"); }
int geti_w_int2000() { return geti_("w_int2000"); }
void repaint_w_int2000() { repaint_("w_int2000"); }

//Int H
//
bool was_changed_h_int2000() { return was_changed_("h_int2000"); }
int geti_h_int2000() { return geti_("h_int2000"); }
void repaint_h_int2000() { repaint_("h_int2000"); }


//Int Border Width
//Border width.
bool was_changed_border_width() { return was_changed_("border_width"); }
int geti_border_width() { return geti_("border_width"); }
void repaint_border_width() { repaint_("border_width"); }

//Int Border Red
//
bool was_changed_border_red() { return was_changed_("border_red"); }
int geti_border_red() { return geti_("border_red"); }
void repaint_border_red() { repaint_("border_red"); }

//Int Border Green
//
bool was_changed_border_green() { return was_changed_("border_green"); }
int geti_border_green() { return geti_("border_green"); }
void repaint_border_green() { repaint_("border_green"); }

//Int Border Blue
//
bool was_changed_border_blue() { return was_changed_("border_blue"); }
int geti_border_blue() { return geti_("border_blue"); }
void repaint_border_blue() { repaint_("border_blue"); }

//----------------------------------------------------
//Page Repeats
//Setting repeating the element. To edit, enable "Repeats" at Main page.

//Const Int Repeat X
//
bool was_changed_repeat_x() { return was_changed_("repeat_x"); }
int geti_repeat_x() { return geti_("repeat_x"); }
void repaint_repeat_x() { repaint_("repeat_x"); }

//Const Int Repeat Y
//
bool was_changed_repeat_y() { return was_changed_("repeat_y"); }
int geti_repeat_y() { return geti_("repeat_y"); }
void repaint_repeat_y() { repaint_("repeat_y"); }

//Const Int Step X
//
bool was_changed_step_x() { return was_changed_("step_x"); }
int geti_step_x() { return geti_("step_x"); }
void repaint_step_x() { repaint_("step_x"); }

//Const Int Step Y
//
bool was_changed_step_y() { return was_changed_("step_y"); }
int geti_step_y() { return geti_("step_y"); }
void repaint_step_y() { repaint_("step_y"); }

//Const Text Titles
//Titles of elements.
bool was_changed_titles() { return was_changed_("titles"); }
QString gets_titles() { return gets_("titles"); }
QStringList get_strings_titles() { return get_strings_("titles"); }
void repaint_titles() { repaint_("titles"); }

//----------------------------------------------------
