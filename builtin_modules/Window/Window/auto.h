//----------------------------------------------------
//Interface for XClassWindow
//Created automatically at 2020.09.14 11:01:46
//----------------------------------------------------
//Page Properties
//

//String Title
//Title of the window.
bool was_changed_title() { return was_changed("title"); }
QString gets_title() { return gets("title"); }
QStringList get_strings_title() { return get_strings("title"); }

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
bool was_changed_size() { return was_changed("size"); }
enum_size gete_size() { return enum_size(geti("size")); }

//Int Size X
//Width of window.
bool was_changed_size_x() { return was_changed("size_x"); }
int geti_size_x() { return geti("size_x"); }

//Int Size Y
//Height of window.
bool was_changed_size_y() { return was_changed("size_y"); }
int geti_size_y() { return geti("size_y"); }

//Enum Position
//Position of the window.
enum enum_position {
    position_Default = 0,
    position_Custom = 1,
    position_Screen_Center = 2,
    position_N__ = 3
};
bool was_changed_position() { return was_changed("position"); }
enum_position gete_position() { return enum_position(geti("position")); }

//Int Pos X
//X position of window.
bool was_changed_pos_x() { return was_changed("pos_x"); }
int geti_pos_x() { return geti("pos_x"); }

//Int Pos Y
//Y position of window.
bool was_changed_pos_y() { return was_changed("pos_y"); }
int geti_pos_y() { return geti("pos_y"); }


//Checkbox Visible
//Is window visible.
bool was_changed_visible() { return was_changed("visible"); }
int geti_visible() { return geti("visible"); }

//Enum Mode
//Full screen, minimized and maximized settings.
enum enum_mode {
    mode_Minimized = 0,
    mode_Normal_Window = 1,
    mode_Maximized = 2,
    mode_Full_Screen = 3,
    mode_N__ = 4
};
bool was_changed_mode() { return was_changed("mode"); }
enum_mode gete_mode() { return enum_mode(geti("mode")); }


//Const Enum Theme
//Theme of design.
enum enum_theme {
    theme_Standard = 0,
    theme_Dark = 1,
    theme_N__ = 2
};
bool was_changed_theme() { return was_changed("theme"); }
enum_theme gete_theme() { return enum_theme(geti("theme")); }

//Const Enum Font Size
//Font size for elements.
enum enum_font_size {
    font_size_Default = 0,
    font_size_Custom = 1,
    font_size_N__ = 2
};
bool was_changed_font_size() { return was_changed("font_size"); }
enum_font_size gete_font_size() { return enum_font_size(geti("font_size")); }

//Const Int Font Size
//Custom font size.
bool was_changed_font_size_pix() { return was_changed("font_size_pix"); }
int geti_font_size_pix() { return geti("font_size_pix"); }

//----------------------------------------------------
//Page Content
//Window content consisting of layouts and widgets, such as WNumber.

//Const Text Content
//Description of layouts and widgets.
bool was_changed_content() { return was_changed("content"); }
QString gets_content() { return gets("content"); }
QStringList get_strings_content() { return get_strings("content"); }

//Button Edit...
//Press to interactively edit window content.
bool was_changed_edit_btn() { return was_changed("edit_btn"); }
int geti_edit_btn() { return geti("edit_btn"); }

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
bool was_changed_on_close() { return was_changed("on_close"); }
enum_on_close gete_on_close() { return enum_on_close(geti("on_close")); }

//----------------------------------------------------
