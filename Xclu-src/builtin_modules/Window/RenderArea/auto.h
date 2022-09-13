//----------------------------------------------------
//Interface for XClassRenderArea
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Const Enum Size
//Size mode.
enum enum_size_mode {
    size_mode_Maximize = 0,
    size_mode_Fixed = 1,
    size_mode_N__ = 2
};
bool was_changed_size_mode() { return was_changed_("size_mode"); }
enum_size_mode gete_size_mode() { return enum_size_mode(geti_("size_mode")); }
QString getraw_size_mode() { return getraw_("size_mode");}

//Out Int Width
//Width of widget.
bool was_changed_w() { return was_changed_("w"); }
int geti_w() { return geti_("w"); }
void seti_w(int value) { seti_("w", value); }
void increase_int_w(int increase = 1) { increase_int_("w", increase); }
void repaint_w() { repaint_("w"); }

//Out Int Height
//Height of widget.
bool was_changed_h() { return was_changed_("h"); }
int geti_h() { return geti_("h"); }
void seti_h(int value) { seti_("h", value); }
void increase_int_h(int increase = 1) { increase_int_("h", increase); }
void repaint_h() { repaint_("h"); }

//Const Int Width
//Width of widget.
bool was_changed_fixed_w() { return was_changed_("fixed_w"); }
int geti_fixed_w() { return geti_("fixed_w"); }
void repaint_fixed_w() { repaint_("fixed_w"); }

//Const Int Height
//Height of widget.
bool was_changed_fixed_h() { return was_changed_("fixed_h"); }
int geti_fixed_h() { return geti_("fixed_h"); }
void repaint_fixed_h() { repaint_("fixed_h"); }


//Out Text Connected Modules
//Here is populated list of connected modules.
bool was_changed_connected_modules() { return was_changed_("connected_modules"); }
QString gets_connected_modules() { return gets_("connected_modules"); }
QStringList get_strings_connected_modules() { return get_strings_("connected_modules"); }
void sets_connected_modules(QString value) { sets_("connected_modules", value); }
void clear_string_connected_modules() { clear_string_("connected_modules"); }
void append_string_connected_modules(QString v, int extra_new_lines_count = 0) { append_string_("connected_modules", v, extra_new_lines_count); }
void append_string_connected_modules(QStringList v, int extra_new_lines_count = 0) { append_string_("connected_modules", v, extra_new_lines_count); }
void repaint_connected_modules() { repaint_("connected_modules"); }

//----------------------------------------------------
//Page Rendering
//Measurement settings and background.

//Const Enum Measurement
//how to measure positions - relative to a fixed value or in pixels.
enum enum_measurement {
    measurement_Scaling = 0,
    measurement_Pixels = 1,
    measurement_N__ = 2
};
bool was_changed_measurement() { return was_changed_("measurement"); }
enum_measurement gete_measurement() { return enum_measurement(geti_("measurement")); }
QString getraw_measurement() { return getraw_("measurement");}

//Const Int ScalingX
//Base size for vector rescaling.
bool was_changed_scaling_x() { return was_changed_("scaling_x"); }
int geti_scaling_x() { return geti_("scaling_x"); }
void repaint_scaling_x() { repaint_("scaling_x"); }

//Const Int ScalingY
//Base size for vector rescaling.
bool was_changed_scaling_y() { return was_changed_("scaling_y"); }
int geti_scaling_y() { return geti_("scaling_y"); }
void repaint_scaling_y() { repaint_("scaling_y"); }


//Int Back Red
//Background red component.
bool was_changed_back_red() { return was_changed_("back_red"); }
int geti_back_red() { return geti_("back_red"); }
void repaint_back_red() { repaint_("back_red"); }

//Int Back Green
//Background green component.
bool was_changed_back_green() { return was_changed_("back_green"); }
int geti_back_green() { return geti_("back_green"); }
void repaint_back_green() { repaint_("back_green"); }

//Int Back Blue
//Background blue component.
bool was_changed_back_blue() { return was_changed_("back_blue"); }
int geti_back_blue() { return geti_("back_blue"); }
void repaint_back_blue() { repaint_("back_blue"); }

//----------------------------------------------------
