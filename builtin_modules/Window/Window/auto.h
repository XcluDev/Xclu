//----------------------------------------------------
//Interface for XClassWindow
//Created automatically at 2020.09.12 21:37:02
//----------------------------------------------------
//Page Properties
//

//String Title
//Title of the window.
QString s_title() { return gets("title"); }

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
enum_size en_size() { return enum_size(geti("size")); }

//Int Size X
//Width of window.
int i_size_x() { return geti("size_x"); }

//Int Size Y
//Height of window.
int i_size_y() { return geti("size_y"); }

//Enum Position
//Position of the window.

enum enum_position {
    position_Default = 0,
    position_Custom = 1,
    position_Screen_Center = 2,
    position_N__ = 3
};
enum_position en_position() { return enum_position(geti("position")); }

//Int Pos X
//X position of window.
int i_pos_x() { return geti("pos_x"); }

//Int Pos Y
//Y position of window.
int i_pos_y() { return geti("pos_y"); }


//Checkbox Visible
//Is window visible.
int i_visible() { return geti("visible"); }

//Enum Mode
//Full screen, minimized and maximized settings.

enum enum_mode {
    mode_Minimized = 0,
    mode_Normal_Window = 1,
    mode_Maximized = 2,
    mode_Full_Screen = 3,
    mode_N__ = 4
};
enum_mode en_mode() { return enum_mode(geti("mode")); }


//Const Enum Theme
//Theme of design.

enum enum_theme {
    theme_Standard = 0,
    theme_Dark = 1,
    theme_N__ = 2
};
enum_theme en_theme() { return enum_theme(geti("theme")); }

//Const Enum Font Size
//Font size for elements.

enum enum_font_size {
    font_size_Default = 0,
    font_size_Custom = 1,
    font_size_N__ = 2
};
enum_font_size en_font_size() { return enum_font_size(geti("font_size")); }

//Const Int Font Size
//Custom font size.
int i_font_size_pix() { return geti("font_size_pix"); }

//----------------------------------------------------
//Page Content
//Window content consisting of layouts and widgets, such as WNumber.

//Const Text Content
//Description of layouts and widgets.
QString s_content() { return gets("content"); }

//Button Edit...
//Press to interactively edit window content.
int i_edit_btn() { return geti("edit_btn"); }

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
enum_on_close en_on_close() { return enum_on_close(geti("on_close")); }

//----------------------------------------------------
