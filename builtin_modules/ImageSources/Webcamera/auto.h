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

//Const Int Device Index
//Camera index in Operating System.
bool was_changed_device_index() { return was_changed_("device_index"); }
int geti_device_index() { return geti_("device_index"); }

//Const String Device Name
//Name of the camera to connect (or its part). To see all - go to 'Device Info' and press the button.
bool was_changed_device_name() { return was_changed_("device_name"); }
QString gets_device_name() { return gets_("device_name"); }
QStringList get_strings_device_name() { return get_strings_("device_name"); }

//Const String Device Serial
//Serial ID of the camera (or its part). To see all - go to 'Device Info', check 'Serial' and press the button.
bool was_changed_device_serial() { return was_changed_("device_serial"); }
QString gets_device_serial() { return gets_("device_serial"); }
QStringList get_strings_device_serial() { return get_strings_("device_serial"); }

//Out Object Image
//Resulted webcamera image.
bool was_changed_image() { return was_changed_("image"); }
XProtectedObject *getobject_image() { return get_object_("image"); }
void setobject_image(XProtectedObject *value) { set_object_("image", value); }
void setobject_image(XProtectedObject &value) { set_object_("image", value); }
//Out Checkbox Is New Frame
//Flag is true when new frame is arrived.
bool was_changed_is_new_frame() { return was_changed_("is_new_frame"); }
int geti_is_new_frame() { return geti_("is_new_frame"); }
void seti_is_new_frame(int value) { seti_("is_new_frame", value); }


//Checkbox Settings
//Setting webcamera parameters.
bool was_changed_settings() { return was_changed_("settings"); }
int geti_settings() { return geti_("settings"); }

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

//Const Int Resolution Y
//Custom resolution Y.
bool was_changed_res_y() { return was_changed_("res_y"); }
int geti_res_y() { return geti_("res_y"); }

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

//----------------------------------------------------
//Page Transform
//

//Checkbox Transform
//Crop and mirror the image.
bool was_changed_transform() { return was_changed_("transform"); }
int geti_transform() { return geti_("transform"); }


//Out Object Transformed Image
//Transformed image.
bool was_changed_image_transformed() { return was_changed_("image_transformed"); }
XProtectedObject *getobject_image_transformed() { return get_object_("image_transformed"); }
void setobject_image_transformed(XProtectedObject *value) { set_object_("image_transformed", value); }
void setobject_image_transformed(XProtectedObject &value) { set_object_("image_transformed", value); }

//Checkbox Crop To Square
//Crop to square.
bool was_changed_crop_to_square() { return was_changed_("crop_to_square"); }
int geti_crop_to_square() { return geti_("crop_to_square"); }

//Checkbox Mirror X
//Mirror by horizontal.
bool was_changed_mirror_x() { return was_changed_("mirror_x"); }
int geti_mirror_x() { return geti_("mirror_x"); }

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
QString button_print_devices() { return "print_devices"; }

//Checkbox Serials
//Output serial ID of devices - useful if you connecting several cameras of the same model.
bool was_changed_print_serials() { return was_changed_("print_serials"); }
int geti_print_serials() { return geti_("print_serials"); }

//Checkbox Formats
//Print list of supported formats for connected device at start.
bool was_changed_print_formats() { return was_changed_("print_formats"); }
int geti_print_formats() { return geti_("print_formats"); }

//Out Text Local Console
//Console output.
bool was_changed_local_console() { return was_changed_("local_console"); }
QString gets_local_console() { return gets_("local_console"); }
QStringList get_strings_local_console() { return get_strings_("local_console"); }
void sets_local_console(QString value) { sets_("local_console", value); }
void clear_string_local_console() { clear_string_("local_console"); }
void append_string_local_console(QString v, int extra_new_lines_count = 0) { append_string_("local_console", v, extra_new_lines_count); }
void append_string_local_console(QStringList v, int extra_new_lines_count = 0) { append_string_("local_console", v, extra_new_lines_count); }

//----------------------------------------------------
//Page Debug
//Debug information.

//Out String Device Name
//Name of the connected camera.
bool was_changed_connected_device_name() { return was_changed_("connected_device_name"); }
QString gets_connected_device_name() { return gets_("connected_device_name"); }
QStringList get_strings_connected_device_name() { return get_strings_("connected_device_name"); }
void sets_connected_device_name(QString value) { sets_("connected_device_name", value); }
void clear_string_connected_device_name() { clear_string_("connected_device_name"); }
void append_string_connected_device_name(QString v, int extra_new_lines_count = 0) { append_string_("connected_device_name", v, extra_new_lines_count); }
void append_string_connected_device_name(QStringList v, int extra_new_lines_count = 0) { append_string_("connected_device_name", v, extra_new_lines_count); }

//Out Checkbox Is Started
//Does capture started.
bool was_changed_is_started() { return was_changed_("is_started"); }
int geti_is_started() { return geti_("is_started"); }
void seti_is_started(int value) { seti_("is_started", value); }

//Out String Frames Captured
//How much frames were captured and processed after last start.
bool was_changed_frames_captured() { return was_changed_("frames_captured"); }
QString gets_frames_captured() { return gets_("frames_captured"); }
QStringList get_strings_frames_captured() { return get_strings_("frames_captured"); }
void sets_frames_captured(QString value) { sets_("frames_captured", value); }
void clear_string_frames_captured() { clear_string_("frames_captured"); }
void append_string_frames_captured(QString v, int extra_new_lines_count = 0) { append_string_("frames_captured", v, extra_new_lines_count); }
void append_string_frames_captured(QStringList v, int extra_new_lines_count = 0) { append_string_("frames_captured", v, extra_new_lines_count); }

//----------------------------------------------------
