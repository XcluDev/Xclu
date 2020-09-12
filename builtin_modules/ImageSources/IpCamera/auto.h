//----------------------------------------------------
//Interface for XClassIpCamera
//Created automatically at 2020.09.12 21:37:01
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
enum_capture_source en_capture_source() { return enum_capture_source(geti("capture_source")); }

//Const Enum Device
//Choose the way for selecting webcamera.

enum enum_select_device {
    select_device_Default = 0,
    select_device_By_Index = 1,
    select_device_By_Name = 2,
    select_device_N__ = 3
};
enum_select_device en_select_device() { return enum_select_device(geti("select_device")); }

//Const Int Device Index
//Camera index in Operating System.
int i_device_index() { return geti("device_index"); }

//Const String Device Name
//Name of the camera to connect (or part of the name), press 'Show Devices' to see the list.
QString s_device_name() { return gets("device_name"); }

//Out Object Image
//Resulted webcamera image.
XDict *obj_image() { return get_object("image"); }

//Out Checkbox Is New Frame
//Flag is true when new frame is arrived.
int i_is_new_frame() { return geti("is_new_frame"); }
void i_is_new_frame(int value) { seti("is_new_frame", value); }


//Checkbox Settings
//Setting webcamera parameters.
int i_settings() { return geti("settings"); }

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
enum_frame_rate en_frame_rate() { return enum_frame_rate(geti("frame_rate")); }

//Const Int Custom Frame Rate
//Custom frame rate.
int i_custom_frame_rate() { return geti("custom_frame_rate"); }

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
enum_resolution en_resolution() { return enum_resolution(geti("resolution")); }

//Const Int Resolution X
//Custom resolution X.
int i_res_x() { return geti("res_x"); }

//Const Int Resolution Y
//Custom resolution Y.
int i_res_y() { return geti("res_y"); }

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
enum_image_channels en_image_channels() { return enum_image_channels(geti("image_channels")); }

//Enum Data Type
//Desired data type of the output image, u8bit=0..255, float=[0,1].

enum enum_image_data_type {
    image_data_type_u8bit = 0,
    image_data_type_float = 1,
    image_data_type_N__ = 2
};
enum_image_data_type en_image_data_type() { return enum_image_data_type(geti("image_data_type")); }


//Checkbox Runtime Details
//Runtime variables.
int i_runtime() { return geti("runtime"); }

//Out String Device Name
//Name of the connected camera.
QString s_connected_device_name() { return gets("connected_device_name"); }
void s_connected_device_name(QString value) { sets("connected_device_name", value); }

//Out Checkbox Is Started
//Does capture started.
int i_is_started() { return geti("is_started"); }
void i_is_started(int value) { seti("is_started", value); }

//Out String Frames Captured
//How much frames were captured and processed after last start.
QString s_frames_captured() { return gets("frames_captured"); }
void s_frames_captured(QString value) { sets("frames_captured", value); }

//----------------------------------------------------
//Page Devices
//Print list of cameras and supported formats

//Checkbox Print Devices
//Print list of all connected webcams
int i_print_devices() { return geti("print_devices"); }

//Checkbox Print Formats
//Print once list of supported formats of connected camera
int i_print_formats() { return geti("print_formats"); }

//Out Text Local Console
//Console output
QString s_local_console() { return gets("local_console"); }
void s_local_console(QString value) { sets("local_console", value); }

//----------------------------------------------------
