//----------------------------------------------------
//Interface for XClassWindow
//Created automatically.
//----------------------------------------------------
//Page Properties
//

//String Title
//Title of the window.
bool was_changed_title() { return was_changed_("title"); }
QString gets_title() { return gets_("title"); }
QStringList get_strings_title() { return get_strings_("title"); }

//Enum Size
//Size of the window.
enum enum_size {
    size_Default = 0,
    size_Custom = 1,
    size_640x480 = 2,
    size_800x600 = 3,
    size_1024x768 = 4,
    size_1280x720 = 5,
    size_1920x1080 = 6,
    size_1920x1200 = 7,
    size_N__ = 8
};
bool was_changed_size() { return was_changed_("size"); }
enum_size gete_size() { return enum_size(geti_("size")); }
QString getraw_size() { return getraw_("size");}

//Int Size X
//Width of window.
bool was_changed_size_x() { return was_changed_("size_x"); }
int geti_size_x() { return geti_("size_x"); }

//Int Size Y
//Height of window.
bool was_changed_size_y() { return was_changed_("size_y"); }
int geti_size_y() { return geti_("size_y"); }

//Enum Position
//Position of the window.
enum enum_position {
    position_Default = 0,
    position_Custom = 1,
    position_Screen_Center = 2,
    position_N__ = 3
};
bool was_changed_position() { return was_changed_("position"); }
enum_position gete_position() { return enum_position(geti_("position")); }
QString getraw_position() { return getraw_("position");}

//Int Pos X
//X position of window.
bool was_changed_pos_x() { return was_changed_("pos_x"); }
int geti_pos_x() { return geti_("pos_x"); }

//Int Pos Y
//Y position of window.
bool was_changed_pos_y() { return was_changed_("pos_y"); }
int geti_pos_y() { return geti_("pos_y"); }


//Checkbox Visible
//Is window visible.
bool was_changed_visible() { return was_changed_("visible"); }
int geti_visible() { return geti_("visible"); }

//Const Enum Initial State
//State at start - normal, full screen, minimized or maximized.
enum enum_initial_state {
    initial_state_Minimized = 0,
    initial_state_Normal_Window = 1,
    initial_state_Maximized = 2,
    initial_state_Full_Screen = 3,
    initial_state_N__ = 4
};
bool was_changed_initial_state() { return was_changed_("initial_state"); }
enum_initial_state gete_initial_state() { return enum_initial_state(geti_("initial_state")); }
QString getraw_initial_state() { return getraw_("initial_state");}


//Const Enum Theme
//Theme of design.
enum enum_theme {
    theme_Standard = 0,
    theme_Dark = 1,
    theme_N__ = 2
};
bool was_changed_theme() { return was_changed_("theme"); }
enum_theme gete_theme() { return enum_theme(geti_("theme")); }
QString getraw_theme() { return getraw_("theme");}

//Const Enum Font Size
//Font size for elements.
enum enum_font_size {
    font_size_Default = 0,
    font_size_Custom = 1,
    font_size_N__ = 2
};
bool was_changed_font_size() { return was_changed_("font_size"); }
enum_font_size gete_font_size() { return enum_font_size(geti_("font_size")); }
QString getraw_font_size() { return getraw_("font_size");}

//Const Int Font Size
//Custom font size.
bool was_changed_font_size_pix() { return was_changed_("font_size_pix"); }
int geti_font_size_pix() { return geti_("font_size_pix"); }

//----------------------------------------------------
//Page Content
//Window content consisting of layouts and widgets, such as WNumber.

//Const Text Content
//Description of layouts and widgets.
bool was_changed_content() { return was_changed_("content"); }
QString gets_content() { return gets_("content"); }
QStringList get_strings_content() { return get_strings_("content"); }

//Const Int Margin
//Margin for layouts.
bool was_changed_global_margin() { return was_changed_("global_margin"); }
int geti_global_margin() { return geti_("global_margin"); }

//Const Int Spacing
//Spacing for layouts.
bool was_changed_global_spacing() { return was_changed_("global_spacing"); }
int geti_global_spacing() { return geti_("global_spacing"); }


//Button Edit...
//Press to interactively edit window content.
bool was_changed_edit_btn() { return was_changed_("edit_btn"); }
int geti_edit_btn() { return geti_("edit_btn"); }
QString button_edit_btn() { return "edit_btn"; }

//----------------------------------------------------
//Page Actions
//Action on closing window

//Enum On Close
//What to do when user closes the window.
enum enum_on_close {
    on_close_Ignore = 0,
    on_close_Stop = 1,
    on_close_N__ = 2
};
bool was_changed_on_close() { return was_changed_("on_close"); }
enum_on_close gete_on_close() { return enum_on_close(geti_("on_close")); }
QString getraw_on_close() { return getraw_("on_close");}

//----------------------------------------------------
