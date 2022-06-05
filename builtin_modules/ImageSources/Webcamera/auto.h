//----------------------------------------------------
//Interface for XClassWebcamera
//Created automatically.
//----------------------------------------------------
//Page Main
//General settings

//Enum Capture Source
//Source of frames - capture frames from real camera of load images from a disk.
enum enum_capture_source {
    capture_source_Disable = 0,
    capture_source_Camera = 1,
    capture_source_Load_Frames = 2,
    capture_source_N__ = 3
};
bool was_changed_capture_source() { return was_changed_("capture_source"); }
enum_capture_source gete_capture_source() { return enum_capture_source(geti_("capture_source")); }
QString getraw_capture_source() { return getraw_("capture_source");}

//Const Enum Device
//Choose the way for selecting webcamera.
enum enum_select_device {
    select_device_Default = 0,
    select_device_By_Index = 1,
    select_device_By_Name = 2,
    select_device_By_Serial = 3,
    select_device_N__ = 4
};
bool was_changed_select_device() { return was_changed_("select_device"); }
enum_select_device gete_select_device() { return enum_select_device(geti_("select_device")); }
QString getraw_select_device() { return getraw_("select_device");}

//Int Device Index
//Camera index in Operating System. Really it functioning as "const", but because it can be set from Resolver, it's made non-const input.
bool was_changed_device_index() { return was_changed_("device_index"); }
int geti_device_index() { return geti_("device_index"); }
void repaint_device_index() { repaint_("device_index"); }

//Const String Device Name
//Name of the camera to connect (or its part). To see all - go to 'Device Info' and press the button.
bool was_changed_device_name() { return was_changed_("device_name"); }
QString gets_device_name() { return gets_("device_name"); }
QStringList get_strings_device_name() { return get_strings_("device_name"); }
void repaint_device_name() { repaint_("device_name"); }

//Const String Device Serial
//Serial ID of the camera (or its part). To see all - go to 'Device Info', check 'Serial' and press the button.
bool was_changed_device_serial() { return was_changed_("device_serial"); }
QString gets_device_serial() { return gets_("device_serial"); }
QStringList get_strings_device_serial() { return get_strings_("device_serial"); }
void repaint_device_serial() { repaint_("device_serial"); }

//Out Object Image
//Resulted webcamera image.
bool was_changed_image() { return was_changed_("image"); }
XProtectedObject *getobject_image() { return get_object_("image"); }
void setobject_image(XProtectedObject *value) { set_object_("image", value); }
void setobject_image(XProtectedObject &value) { set_object_("image", value); }
void repaint_image() { repaint_("image"); }
//Out Checkbox Is New Frame
//Flag is true when new frame is arrived.
bool was_changed_is_new_frame() { return was_changed_("is_new_frame"); }
int geti_is_new_frame() { return geti_("is_new_frame"); }
void seti_is_new_frame(int value) { seti_("is_new_frame", value); }
void repaint_is_new_frame() { repaint_("is_new_frame"); }


//Checkbox Runtime
//Runtime information
bool was_changed_runtime_info() { return was_changed_("runtime_info"); }
int geti_runtime_info() { return geti_("runtime_info"); }
void repaint_runtime_info() { repaint_("runtime_info"); }

//Out String Device Name
//Name of the connected camera.
bool was_changed_connected_device_name() { return was_changed_("connected_device_name"); }
QString gets_connected_device_name() { return gets_("connected_device_name"); }
QStringList get_strings_connected_device_name() { return get_strings_("connected_device_name"); }
void sets_connected_device_name(QString value) { sets_("connected_device_name", value); }
void clear_string_connected_device_name() { clear_string_("connected_device_name"); }
void append_string_connected_device_name(QString v, int extra_new_lines_count = 0) { append_string_("connected_device_name", v, extra_new_lines_count); }
void append_string_connected_device_name(QStringList v, int extra_new_lines_count = 0) { append_string_("connected_device_name", v, extra_new_lines_count); }
void repaint_connected_device_name() { repaint_("connected_device_name"); }

//Out String Device Serial
//Name of the connected camera.
bool was_changed_connected_device_serial() { return was_changed_("connected_device_serial"); }
QString gets_connected_device_serial() { return gets_("connected_device_serial"); }
QStringList get_strings_connected_device_serial() { return get_strings_("connected_device_serial"); }
void sets_connected_device_serial(QString value) { sets_("connected_device_serial", value); }
void clear_string_connected_device_serial() { clear_string_("connected_device_serial"); }
void append_string_connected_device_serial(QString v, int extra_new_lines_count = 0) { append_string_("connected_device_serial", v, extra_new_lines_count); }
void append_string_connected_device_serial(QStringList v, int extra_new_lines_count = 0) { append_string_("connected_device_serial", v, extra_new_lines_count); }
void repaint_connected_device_serial() { repaint_("connected_device_serial"); }

//Out Checkbox Is Started
//Does capture started.
bool was_changed_is_started() { return was_changed_("is_started"); }
int geti_is_started() { return geti_("is_started"); }
void seti_is_started(int value) { seti_("is_started", value); }
void repaint_is_started() { repaint_("is_started"); }

//Out Int Frames Captured
//How much frames were captured.
bool was_changed_frames_captured() { return was_changed_("frames_captured"); }
int geti_frames_captured() { return geti_("frames_captured"); }
void seti_frames_captured(int value) { seti_("frames_captured", value); }
void increase_int_frames_captured(int increase = 1) { increase_int_("frames_captured", increase); }
void repaint_frames_captured() { repaint_("frames_captured"); }

//Out Int Frames Dropped
//How much frames were dropped.
bool was_changed_frames_dropped() { return was_changed_("frames_dropped"); }
int geti_frames_dropped() { return geti_("frames_dropped"); }
void seti_frames_dropped(int value) { seti_("frames_dropped", value); }
void increase_int_frames_dropped(int increase = 1) { increase_int_("frames_dropped", increase); }
void repaint_frames_dropped() { repaint_("frames_dropped"); }


//Checkbox Settings
//Setting webcamera parameters.
bool was_changed_settings() { return was_changed_("settings"); }
int geti_settings() { return geti_("settings"); }
void repaint_settings() { repaint_("settings"); }

//Const Enum Frame Rate
//Frame rate.
enum enum_frame_rate {
    frame_rate_Camera_Default = 0,
    frame_rate_Custom = 1,
    frame_rate_5 = 2,
    frame_rate_10 = 3,
    frame_rate_15 = 4,
    frame_rate_30 = 5,
    frame_rate_60 = 6,
    frame_rate_N__ = 7
};
bool was_changed_frame_rate() { return was_changed_("frame_rate"); }
enum_frame_rate gete_frame_rate() { return enum_frame_rate(geti_("frame_rate")); }
QString getraw_frame_rate() { return getraw_("frame_rate");}

//Const Int Custom Frame Rate
//Custom frame rate.
bool was_changed_custom_frame_rate() { return was_changed_("custom_frame_rate"); }
int geti_custom_frame_rate() { return geti_("custom_frame_rate"); }
void repaint_custom_frame_rate() { repaint_("custom_frame_rate"); }

//Const Enum Resolution
//Capture resolution.
enum enum_resolution {
    resolution_Camera_Default = 0,
    resolution_Custom = 1,
    resolution_160_x_120 = 2,
    resolution_320_x_240 = 3,
    resolution_640_x_480 = 4,
    resolution_1024_x_768 = 5,
    resolution_1280_x_720 = 6,
    resolution_1920_x_1080 = 7,
    resolution_N__ = 8
};
bool was_changed_resolution() { return was_changed_("resolution"); }
enum_resolution gete_resolution() { return enum_resolution(geti_("resolution")); }
QString getraw_resolution() { return getraw_("resolution");}

//Const Int Resolution X
//Custom resolution X.
bool was_changed_res_x() { return was_changed_("res_x"); }
int geti_res_x() { return geti_("res_x"); }
void repaint_res_x() { repaint_("res_x"); }

//Const Int Resolution Y
//Custom resolution Y.
bool was_changed_res_y() { return was_changed_("res_y"); }
int geti_res_y() { return geti_("res_y"); }
void repaint_res_y() { repaint_("res_y"); }

//Enum Channels
//Desired channels of the output image.
enum enum_image_channels {
    image_channels_Grayscale = 0,
    image_channels_RGB = 1,
    image_channels_BGR = 2,
    image_channels_RGBA = 3,
    image_channels_ABGR = 4,
    image_channels_R = 5,
    image_channels_G = 6,
    image_channels_B = 7,
    image_channels_N__ = 8
};
bool was_changed_image_channels() { return was_changed_("image_channels"); }
enum_image_channels gete_image_channels() { return enum_image_channels(geti_("image_channels")); }
QString getraw_image_channels() { return getraw_("image_channels");}

//Enum Data Type
//Desired data type of the output image, u8=0..255, float=[0,1].
enum enum_image_data_type {
    image_data_type_u8 = 0,
    image_data_type_float = 1,
    image_data_type_N__ = 2
};
bool was_changed_image_data_type() { return was_changed_("image_data_type"); }
enum_image_data_type gete_image_data_type() { return enum_image_data_type(geti_("image_data_type")); }
QString getraw_image_data_type() { return getraw_("image_data_type");}


//Checkbox Ignore Error
//Ignore error with starting.
bool was_changed_ignore_error_on_start() { return was_changed_("ignore_error_on_start"); }
int geti_ignore_error_on_start() { return geti_("ignore_error_on_start"); }
void repaint_ignore_error_on_start() { repaint_("ignore_error_on_start"); }

//Checkbox Auto Restart
//Autorestart if no new frames for a long time.
bool was_changed_auto_restart() { return was_changed_("auto_restart"); }
int geti_auto_restart() { return geti_("auto_restart"); }
void repaint_auto_restart() { repaint_("auto_restart"); }

//Int Wait Seconds
//How much secodsn wait to restart the camera.
bool was_changed_auto_restart_wait_seconds() { return was_changed_("auto_restart_wait_seconds"); }
int geti_auto_restart_wait_seconds() { return geti_("auto_restart_wait_seconds"); }
void repaint_auto_restart_wait_seconds() { repaint_("auto_restart_wait_seconds"); }


//Button Save Image
//Press to save the image to a specified file.
bool was_changed_save_image() { return was_changed_("save_image"); }
int geti_save_image() { return geti_("save_image"); }
void repaint_save_image() { repaint_("save_image"); }
QString button_save_image() { return "save_image"; }

//String File To Save
//File to save the image.
bool was_changed_save_image_file_name() { return was_changed_("save_image_file_name"); }
QString gets_save_image_file_name() { return gets_("save_image_file_name"); }
QStringList get_strings_save_image_file_name() { return get_strings_("save_image_file_name"); }
void repaint_save_image_file_name() { repaint_("save_image_file_name"); }

//----------------------------------------------------
//Page Transform
//


//Checkbox Transform
//Crop, mirror and rotate the image.
bool was_changed_transform() { return was_changed_("transform"); }
int geti_transform() { return geti_("transform"); }
void repaint_transform() { repaint_("transform"); }

//Out Object Transformed Image
//Transformed image.
bool was_changed_image_transformed() { return was_changed_("image_transformed"); }
XProtectedObject *getobject_image_transformed() { return get_object_("image_transformed"); }
void setobject_image_transformed(XProtectedObject *value) { set_object_("image_transformed", value); }
void setobject_image_transformed(XProtectedObject &value) { set_object_("image_transformed", value); }
void repaint_image_transformed() { repaint_("image_transformed"); }

//Checkbox Crop To Square
//Crop to square.
bool was_changed_crop_to_square() { return was_changed_("crop_to_square"); }
int geti_crop_to_square() { return geti_("crop_to_square"); }
void repaint_crop_to_square() { repaint_("crop_to_square"); }

//Checkbox Mirror X
//Mirror by horizontal.
bool was_changed_mirror_x() { return was_changed_("mirror_x"); }
int geti_mirror_x() { return geti_("mirror_x"); }
void repaint_mirror_x() { repaint_("mirror_x"); }

//Enum Rotate
//Rotation.
enum enum_rotate {
    rotate_0 = 0,
    rotate_90 = 1,
    rotate_180 = 2,
    rotate_270 = 3,
    rotate_N__ = 4
};
bool was_changed_rotate() { return was_changed_("rotate"); }
enum_rotate gete_rotate() { return enum_rotate(geti_("rotate")); }
QString getraw_rotate() { return getraw_("rotate");}


//----------------------------------------------------
//Page Device Info
//Print list of cameras and supported formats.

//Button Print Devices
//Print list of all connected devices.
bool was_changed_print_devices() { return was_changed_("print_devices"); }
int geti_print_devices() { return geti_("print_devices"); }
void repaint_print_devices() { repaint_("print_devices"); }
QString button_print_devices() { return "print_devices"; }

//Checkbox Serials
//Output serial ID of devices - useful if you connecting several cameras of the same model.
bool was_changed_print_serials() { return was_changed_("print_serials"); }
int geti_print_serials() { return geti_("print_serials"); }
void repaint_print_serials() { repaint_("print_serials"); }

//Checkbox Formats
//Print list of supported formats for connected device at start.
bool was_changed_print_formats() { return was_changed_("print_formats"); }
int geti_print_formats() { return geti_("print_formats"); }
void repaint_print_formats() { repaint_("print_formats"); }

//Out Text Local Console
//Console output.
bool was_changed_local_console() { return was_changed_("local_console"); }
QString gets_local_console() { return gets_("local_console"); }
QStringList get_strings_local_console() { return get_strings_("local_console"); }
void sets_local_console(QString value) { sets_("local_console", value); }
void clear_string_local_console() { clear_string_("local_console"); }
void append_string_local_console(QString v, int extra_new_lines_count = 0) { append_string_("local_console", v, extra_new_lines_count); }
void append_string_local_console(QStringList v, int extra_new_lines_count = 0) { append_string_("local_console", v, extra_new_lines_count); }
void repaint_local_console() { repaint_("local_console"); }

//----------------------------------------------------
//Page Resolver
//This is capability to properly assign several similar webcameras. See Webcamera/Webcams_resolve example for the more details.

//Const Checkbox Enabled
//Is Resolver enabled.
bool was_changed_resolver_enabled() { return was_changed_("resolver_enabled"); }
int geti_resolver_enabled() { return geti_("resolver_enabled"); }
void repaint_resolver_enabled() { repaint_("resolver_enabled"); }


//Const Int Cameras
//Number of connected cameras to resolve.
bool was_changed_resolver_cameras() { return was_changed_("resolver_cameras"); }
int geti_resolver_cameras() { return geti_("resolver_cameras"); }
void repaint_resolver_cameras() { repaint_("resolver_cameras"); }


//Out Enum Presence 1
//Deduced presence of the camera, "Presented" or "None". Connect it to Capture_Source of the first Webcamera module.
enum enum_resolver_resulted_presence1 {
    resolver_resulted_presence1_None = 0,
    resolver_resulted_presence1_Presented = 1,
    resolver_resulted_presence1_N__ = 2
};
bool was_changed_resolver_resulted_presence1() { return was_changed_("resolver_resulted_presence1"); }
enum_resolver_resulted_presence1 gete_resolver_resulted_presence1() { return enum_resolver_resulted_presence1(geti_("resolver_resulted_presence1")); }
void sete_resolver_resulted_presence1(enum_resolver_resulted_presence1 value) { seti_("resolver_resulted_presence1", value); }
QString getraw_resolver_resulted_presence1() { return getraw_("resolver_resulted_presence1");}

//Out Int Index 1
//Deduced index. Connect it to the Index of the first Webcamera module.
bool was_changed_resolver_resulted_index1() { return was_changed_("resolver_resulted_index1"); }
int geti_resolver_resulted_index1() { return geti_("resolver_resulted_index1"); }
void seti_resolver_resulted_index1(int value) { seti_("resolver_resulted_index1", value); }
void increase_int_resolver_resulted_index1(int increase = 1) { increase_int_("resolver_resulted_index1", increase); }
void repaint_resolver_resulted_index1() { repaint_("resolver_resulted_index1"); }

//Out Enum Presence 2
//Deduced presence of the camera, "Presented" or "None". Connect it to Capture_Source of the second Webcamera module.
enum enum_resolver_resulted_presence2 {
    resolver_resulted_presence2_None = 0,
    resolver_resulted_presence2_Presented = 1,
    resolver_resulted_presence2_N__ = 2
};
bool was_changed_resolver_resulted_presence2() { return was_changed_("resolver_resulted_presence2"); }
enum_resolver_resulted_presence2 gete_resolver_resulted_presence2() { return enum_resolver_resulted_presence2(geti_("resolver_resulted_presence2")); }
void sete_resolver_resulted_presence2(enum_resolver_resulted_presence2 value) { seti_("resolver_resulted_presence2", value); }
QString getraw_resolver_resulted_presence2() { return getraw_("resolver_resulted_presence2");}

//Out Int Index 2
//Deduced index. Connect it to the Index of the second Webcamera module.
bool was_changed_resolver_resulted_index2() { return was_changed_("resolver_resulted_index2"); }
int geti_resolver_resulted_index2() { return geti_("resolver_resulted_index2"); }
void seti_resolver_resulted_index2(int value) { seti_("resolver_resulted_index2", value); }
void increase_int_resolver_resulted_index2(int increase = 1) { increase_int_("resolver_resulted_index2", increase); }
void repaint_resolver_resulted_index2() { repaint_("resolver_resulted_index2"); }

//Out Enum Presence 3
//Deduced presence of the camera, "Presented" or "None". Connect it to Capture_Source of the third Webcamera module.
enum enum_resolver_resulted_presence3 {
    resolver_resulted_presence3_None = 0,
    resolver_resulted_presence3_Presented = 1,
    resolver_resulted_presence3_N__ = 2
};
bool was_changed_resolver_resulted_presence3() { return was_changed_("resolver_resulted_presence3"); }
enum_resolver_resulted_presence3 gete_resolver_resulted_presence3() { return enum_resolver_resulted_presence3(geti_("resolver_resulted_presence3")); }
void sete_resolver_resulted_presence3(enum_resolver_resulted_presence3 value) { seti_("resolver_resulted_presence3", value); }
QString getraw_resolver_resulted_presence3() { return getraw_("resolver_resulted_presence3");}

//Out Int Index 3
//Deduced index. Connect it to the Index of the third Webcamera module.
bool was_changed_resolver_resulted_index3() { return was_changed_("resolver_resulted_index3"); }
int geti_resolver_resulted_index3() { return geti_("resolver_resulted_index3"); }
void seti_resolver_resulted_index3(int value) { seti_("resolver_resulted_index3", value); }
void increase_int_resolver_resulted_index3(int increase = 1) { increase_int_("resolver_resulted_index3", increase); }
void repaint_resolver_resulted_index3() { repaint_("resolver_resulted_index3"); }

//Out Enum Presence 4
//Deduced presence of the camera, "Presented" or "None". Connect it to Capture_Source of the fourth Webcamera module.
enum enum_resolver_resulted_presence4 {
    resolver_resulted_presence4_None = 0,
    resolver_resulted_presence4_Presented = 1,
    resolver_resulted_presence4_N__ = 2
};
bool was_changed_resolver_resulted_presence4() { return was_changed_("resolver_resulted_presence4"); }
enum_resolver_resulted_presence4 gete_resolver_resulted_presence4() { return enum_resolver_resulted_presence4(geti_("resolver_resulted_presence4")); }
void sete_resolver_resulted_presence4(enum_resolver_resulted_presence4 value) { seti_("resolver_resulted_presence4", value); }
QString getraw_resolver_resulted_presence4() { return getraw_("resolver_resulted_presence4");}

//Out Int Index 4
//Deduced index. Connect it to the Index of the fourth Webcamera module.
bool was_changed_resolver_resulted_index4() { return was_changed_("resolver_resulted_index4"); }
int geti_resolver_resulted_index4() { return geti_("resolver_resulted_index4"); }
void seti_resolver_resulted_index4(int value) { seti_("resolver_resulted_index4", value); }
void increase_int_resolver_resulted_index4(int increase = 1) { increase_int_("resolver_resulted_index4", increase); }
void repaint_resolver_resulted_index4() { repaint_("resolver_resulted_index4"); }


//Const String Camera 1 Name Part
//Part of name of the camera 1.
bool was_changed_resolver_name1() { return was_changed_("resolver_name1"); }
QString gets_resolver_name1() { return gets_("resolver_name1"); }
QStringList get_strings_resolver_name1() { return get_strings_("resolver_name1"); }
void repaint_resolver_name1() { repaint_("resolver_name1"); }

//Const String Camera 1 Serials Parts
//Part of serials of the camera 1, connected to different USB, with computer restarting, such as 14de4f85 2798002a 2249ee0.
bool was_changed_resolver_serials1() { return was_changed_("resolver_serials1"); }
QString gets_resolver_serials1() { return gets_("resolver_serials1"); }
QStringList get_strings_resolver_serials1() { return get_strings_("resolver_serials1"); }
void repaint_resolver_serials1() { repaint_("resolver_serials1"); }


//Const String Camera 2 Name Part
//Part of name of the camera 2.
bool was_changed_resolver_name2() { return was_changed_("resolver_name2"); }
QString gets_resolver_name2() { return gets_("resolver_name2"); }
QStringList get_strings_resolver_name2() { return get_strings_("resolver_name2"); }
void repaint_resolver_name2() { repaint_("resolver_name2"); }

//Const String Camera 2 Serials Parts
//Part of serials of the camera 2.
bool was_changed_resolver_serials2() { return was_changed_("resolver_serials2"); }
QString gets_resolver_serials2() { return gets_("resolver_serials2"); }
QStringList get_strings_resolver_serials2() { return get_strings_("resolver_serials2"); }
void repaint_resolver_serials2() { repaint_("resolver_serials2"); }


//Const String Camera 3 Name Part
//Part of name of the camera 3.
bool was_changed_resolver_name3() { return was_changed_("resolver_name3"); }
QString gets_resolver_name3() { return gets_("resolver_name3"); }
QStringList get_strings_resolver_name3() { return get_strings_("resolver_name3"); }
void repaint_resolver_name3() { repaint_("resolver_name3"); }

//Const String Camera 3 Serials Parts
//Part of serials of the camera 3.
bool was_changed_resolver_serials3() { return was_changed_("resolver_serials3"); }
QString gets_resolver_serials3() { return gets_("resolver_serials3"); }
QStringList get_strings_resolver_serials3() { return get_strings_("resolver_serials3"); }
void repaint_resolver_serials3() { repaint_("resolver_serials3"); }


//Const String Camera 4 Name Part
//Part of name of the camera 4.
bool was_changed_resolver_name4() { return was_changed_("resolver_name4"); }
QString gets_resolver_name4() { return gets_("resolver_name4"); }
QStringList get_strings_resolver_name4() { return get_strings_("resolver_name4"); }
void repaint_resolver_name4() { repaint_("resolver_name4"); }

//Const String Camera 4 Serials Parts
//Part of serials of the camera 4.
bool was_changed_resolver_serials4() { return was_changed_("resolver_serials4"); }
QString gets_resolver_serials4() { return gets_("resolver_serials4"); }
QStringList get_strings_resolver_serials4() { return get_strings_("resolver_serials4"); }
void repaint_resolver_serials4() { repaint_("resolver_serials4"); }


//----------------------------------------------------
//Page Draw
//Draw to RenderArea.

//Const String Render Area
//Render area for drawing into.
bool was_changed_render_area() { return was_changed_("render_area"); }
QString gets_render_area() { return gets_("render_area"); }
QStringList get_strings_render_area() { return get_strings_("render_area"); }
void repaint_render_area() { repaint_("render_area"); }


//Checkbox Draw
//
bool was_changed_draw_enabled() { return was_changed_("draw_enabled"); }
int geti_draw_enabled() { return geti_("draw_enabled"); }
void repaint_draw_enabled() { repaint_("draw_enabled"); }

//Float X
//
bool was_changed_draw_x() { return was_changed_("draw_x"); }
float getf_draw_x() { return getf_("draw_x"); }
void repaint_draw_x() { repaint_("draw_x"); }

//Float Y
//
bool was_changed_draw_y() { return was_changed_("draw_y"); }
float getf_draw_y() { return getf_("draw_y"); }
void repaint_draw_y() { repaint_("draw_y"); }

//Float Size
//
bool was_changed_draw_size() { return was_changed_("draw_size"); }
float getf_draw_size() { return getf_("draw_size"); }
void repaint_draw_size() { repaint_("draw_size"); }

//----------------------------------------------------
