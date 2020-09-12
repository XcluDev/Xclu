//----------------------------------------------------
//Interface for XClassRealsenseCamera
//Created automatically at 2020.09.12 21:37:02
//----------------------------------------------------
//Page Main
//General settings.

//Const Enum Capture Source
//Source of frames - capture frames from real camera of load BAG recording from a disk.

enum enum_capture_source {
    capture_source_Disable = 0,
    capture_source_Camera = 1,
    capture_source_Bag_File = 2,
    capture_source_N__ = 3
};
enum_capture_source en_capture_source() { return enum_capture_source(geti("capture_source")); }

//Const Enum Device
//Choose the way for selecting the camera.

enum enum_select_device {
    select_device_Default = 0,
    select_device_By_Index = 1,
    select_device_By_Serial = 2,
    select_device_N__ = 3
};
enum_select_device en_select_device() { return enum_select_device(geti("select_device")); }

//Const Int Device Index
//Camera index in Operating System.
int i_device_index() { return geti("device_index"); }

//Const String Device Serial
//Serial of the camera to connect (or part of the serial), go to 'Device Info' to see the list.
QString s_device_serial() { return gets("device_serial"); }

//Const String Bag File
//Choose BAG file. You can record it using Intel Realsense Viewer application.
QString s_bag_file() { return gets("bag_file"); }


//Checkbox Runtime Details
//Runtime variables.
int i_runtime() { return geti("runtime"); }

//Out String Device Info
//Information about connected camera.
QString s_connected_device_info() { return gets("connected_device_info"); }
void s_connected_device_info(QString value) { sets("connected_device_info", value); }

//Out Checkbox Is Started
//Does capture started.
int i_is_started() { return geti("is_started"); }
void i_is_started(int value) { seti("is_started", value); }

//Out String Frames Captured
//How much frames were captured and processed after last start.
QString s_frames_captured() { return gets("frames_captured"); }
void s_frames_captured(QString value) { sets("frames_captured", value); }


//Checkbox Show Color
//Generate color image preview. Please disable is not required for speed optimization.
int i_show_color() { return geti("show_color"); }

//Out Object Color
//Resulted Color image.
XDict *obj_color_image() { return get_object("color_image"); }

//Checkbox Show Depth
//Generate Depth image preview. Please disable is not required for speed optimization.
int i_show_depth() { return geti("show_depth"); }

//Out Object Depth
//Resulted Depth image.
XDict *obj_depth_image() { return get_object("depth_image"); }

//Checkbox Show IR
//Generate IR image preview. Please disable is not required for speed optimization.
int i_show_ir() { return geti("show_ir"); }

//Out Object IR
//Resulted IR image.
XDict *obj_ir_image() { return get_object("ir_image"); }

//Out Checkbox Is New Frame
//Flag is true when new frame is arrived.
int i_is_new_frame() { return geti("is_new_frame"); }
void i_is_new_frame(int value) { seti("is_new_frame", value); }

//----------------------------------------------------
//Page Color
//Settings for color stream.

//Const Checkbox Color Stream
//Capture color stream.
int i_color_stream_enabled() { return geti("color_stream_enabled"); }

//Const Enum Resolution
//Resolution for color stream.

enum enum_color_resolution {
    color_resolution_320_x_180 = 0,
    color_resolution_320_x_240 = 1,
    color_resolution_424_x_240 = 2,
    color_resolution_640_x_360 = 3,
    color_resolution_640_x_480 = 4,
    color_resolution_848_x_480 = 5,
    color_resolution_960_x_540 = 6,
    color_resolution_1280_x_720 = 7,
    color_resolution_1920_x_1080 = 8,
    color_resolution_N__ = 9
};
enum_color_resolution en_color_resolution() { return enum_color_resolution(geti("color_resolution")); }

//Const Enum Frame Rate
//Frame rate for color stream.

enum enum_color_frame_rate {
    color_frame_rate_6 = 0,
    color_frame_rate_15 = 1,
    color_frame_rate_30 = 2,
    color_frame_rate_60 = 3,
    color_frame_rate_N__ = 4
};
enum_color_frame_rate en_color_frame_rate() { return enum_color_frame_rate(geti("color_frame_rate")); }

//Const Checkbox Aligh to Depth
//Should color frames to be aligned to depth frames.
int i_align_to_depth() { return geti("align_to_depth"); }


//----------------------------------------------------
//Page Depth + IR
//Settings for Depth and IR stream.

//Const Checkbox Depth Stream
//Capture Depth stream.
int i_depth_stream_enabled() { return geti("depth_stream_enabled"); }

//Const Checkbox IR Stream
//Capture IR stream.
int i_ir_stream_enabled() { return geti("ir_stream_enabled"); }

//Const Enum Preset
//Depth preset.

enum enum_depth_preset {
    depth_preset_Custom = 0,
    depth_preset_Default = 1,
    depth_preset_Hand = 2,
    depth_preset_High_Accuracy = 3,
    depth_preset_High_Density = 4,
    depth_preset_Medium_Density = 5,
    depth_preset_Remove_IR_Pattern = 6,
    depth_preset_N__ = 7
};
enum_depth_preset en_depth_preset() { return enum_depth_preset(geti("depth_preset")); }

//Const Enum Resolution
//Resolution for Depth/IR stream.

enum enum_depth_resolution {
    depth_resolution_424_x_240 = 0,
    depth_resolution_480_x_270 = 1,
    depth_resolution_640_x_360 = 2,
    depth_resolution_640_x_480 = 3,
    depth_resolution_848_x_480 = 4,
    depth_resolution_1280_x_720 = 5,
    depth_resolution_1280_x_800 = 6,
    depth_resolution_N__ = 7
};
enum_depth_resolution en_depth_resolution() { return enum_depth_resolution(geti("depth_resolution")); }

//Const Enum Frame Rate
//Frame rate for Depth/IR stream.

enum enum_depth_frame_rate {
    depth_frame_rate_6 = 0,
    depth_frame_rate_15 = 1,
    depth_frame_rate_25 = 2,
    depth_frame_rate_30 = 3,
    depth_frame_rate_60 = 4,
    depth_frame_rate_90 = 5,
    depth_frame_rate_N__ = 6
};
enum_depth_frame_rate en_depth_frame_rate() { return enum_depth_frame_rate(geti("depth_frame_rate")); }


//Const Checkbox Emitter
//Enabling IR laser emitter.
int i_emitter() { return geti("emitter"); }

//----------------------------------------------------
//Page Devices
//Here you can get list of connected cameras.

//Button Print Devices
//Print list of all connected devices
int i_print_devices() { return geti("print_devices"); }

//Out Text Device list
//Console with device list
QString s_device_list() { return gets("device_list"); }
void s_device_list(QString value) { sets("device_list", value); }

//----------------------------------------------------
//Page Save Frames
//Saving frames to disk

//Button Save Frames
//Press the button to save images to a given folder
int i_save_frames_button() { return geti("save_frames_button"); }

//String Folder
//Folder for saving frames.
QString s_save_folder() { return gets("save_folder"); }

//Out Text Saved To
//Path to last saving.
QString s_saved_to() { return gets("saved_to"); }
void s_saved_to(QString value) { sets("saved_to", value); }

//----------------------------------------------------
