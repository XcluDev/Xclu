//----------------------------------------------------
//Interface for XClassWDialog
//Created automatically at 2020.09.12 21:37:02
//----------------------------------------------------
//Page Main
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

//Const Int Font Size
//Default font size for elements.
int i_font_size() { return geti("font_size"); }

//----------------------------------------------------
//Page Structure
//Window contents consisting of layouts and widgets, such as IntGui.

//Const Text Struct.
//Description of layouts and widgets.
QString s_structure() { return gets("structure"); }

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
