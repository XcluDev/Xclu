//----------------------------------------------------
//Interface for XClassWSweetArea
//Created automatically.
//----------------------------------------------------
//Page Structure
//Window contents consisting of layouts and widgets, such as IntGui.

//Const Text Struct.
//Description of layouts and widgets.
bool was_changed_structure() { return was_changed_("structure"); }
QString gets_structure() { return gets_("structure"); }
QStringList get_strings_structure() { return get_strings_("structure"); }

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

//Enum Mode
//Full screen, minimized and maximized settings.
enum enum_mode {
    mode_Minimized = 0,
    mode_Normal_Window = 1,
    mode_Maximized = 2,
    mode_Full_Screen = 3,
    mode_N__ = 4
};
bool was_changed_mode() { return was_changed_("mode"); }
enum_mode gete_mode() { return enum_mode(geti_("mode")); }
QString getraw_mode() { return getraw_("mode");}


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
