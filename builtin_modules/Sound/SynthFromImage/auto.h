//----------------------------------------------------
//Interface for XClassSynthFromImage
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Checkbox Show Input Image
//
bool was_changed_show_input_image() { return was_changed_("show_input_image"); }
int geti_show_input_image() { return geti_("show_input_image"); }

//Object Input Image
//Image for processing.
bool was_changed_input_image() { return was_changed_("input_image"); }
XProtectedObject *getobject_input_image() { return get_object_("input_image"); }


//Out Object Output Image
//Image with visualization.
bool was_changed_output_image() { return was_changed_("output_image"); }
XProtectedObject *getobject_output_image() { return get_object_("output_image"); }
void setobject_output_image(XProtectedObject *value) { set_object_("output_image", value); }

//Button Freeze
//Freeze input image.
bool was_changed_freeze_btn() { return was_changed_("freeze_btn"); }
int geti_freeze_btn() { return geti_("freeze_btn"); }
QString button_freeze_btn() { return "freeze_btn"; }

//Button Unfreeze
//Unfreeze input image.
bool was_changed_unfreeze_btn() { return was_changed_("unfreeze_btn"); }
int geti_unfreeze_btn() { return geti_("unfreeze_btn"); }
QString button_unfreeze_btn() { return "unfreeze_btn"; }


//Float Scan Y
//Y position of scanning area's center.
bool was_changed_scan_y() { return was_changed_("scan_y"); }
float getf_scan_y() { return getf_("scan_y"); }

//Float Scan W
//Scanning width.
bool was_changed_scan_w() { return was_changed_("scan_w"); }
float getf_scan_w() { return getf_("scan_w"); }


//Int Sample Rate
//Sample rate.
bool was_changed_sample_rate() { return was_changed_("sample_rate"); }
int geti_sample_rate() { return geti_("sample_rate"); }

//Checkbox Ignore Borders
//Ignore black borders - affect tone of the line (if shorter - tone is higher). For Realsense using.
bool was_changed_ignore_borders() { return was_changed_("ignore_borders"); }
int geti_ignore_borders() { return geti_("ignore_borders"); }

//Checkbox Put To Zero
//Make boundaries zero-valued, for reducing cracking sound.
bool was_changed_put_to_zero() { return was_changed_("put_to_zero"); }
int geti_put_to_zero() { return geti_("put_to_zero"); }

//Enum Loop Mode
//Loop by repeat or ping-pong.
enum enum_loop_mode {
    loop_mode_Repeat = 0,
    loop_mode_Ping_Pong = 1,
    loop_mode_N__ = 2
};
bool was_changed_loop_mode() { return was_changed_("loop_mode"); }
enum_loop_mode gete_loop_mode() { return enum_loop_mode(geti_("loop_mode")); }
QString getraw_loop_mode() { return getraw_("loop_mode");}

//Float Volume
//Volume of the resulted sound.
bool was_changed_volume() { return was_changed_("volume"); }
float getf_volume() { return getf_("volume"); }

//----------------------------------------------------
