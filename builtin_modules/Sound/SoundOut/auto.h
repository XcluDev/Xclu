//----------------------------------------------------
//Interface for XClassSoundOut
//Created automatically at 2020.09.12 21:37:02
//----------------------------------------------------
//Page Main
//General settings

//Text Sound Sources
//List of modules to which will be sent callback for sound buffer
QString s_modules_list() { return gets("modules_list"); }

//Button Edit...
//Press to interactively edit sound sources.
int i_edit_btn() { return geti("edit_btn"); }


//Float Volume
//Output sound volume.
float f_volume() { return getf("volume"); }

//Float Device Volume
//Output device volume.
float f_device_volume() { return getf("device_volume"); }


//Const Enum Sound Device
//Choose the way for selecting sound output device

enum enum_select_device {
    select_device_Default = 0,
    select_device_By_Index = 1,
    select_device_By_Name = 2,
    select_device_N__ = 3
};
enum_select_device en_select_device() { return enum_select_device(geti("select_device")); }

//Const Int Device Index
//Sound device index in Operating System.
int i_device_index() { return geti("device_index"); }

//Const String Device Name
//Name of the sound output device to connect (or part of the name), press 'Show Devices' to see the list
QString s_device_name() { return gets("device_name"); }


//Checkbox Settings
//Setting sound output parameters
int i_settings() { return geti("settings"); }

//Const Enum Sample Rate
//Frame rate

enum enum_sample_rate {
    sample_rate_Default = 0,
    sample_rate_Custom = 1,
    sample_rate_8000 = 2,
    sample_rate_11025 = 3,
    sample_rate_22050 = 4,
    sample_rate_32000 = 5,
    sample_rate_44100 = 6,
    sample_rate_48000 = 7,
    sample_rate_96000 = 8,
    sample_rate_N__ = 9
};
enum_sample_rate en_sample_rate() { return enum_sample_rate(geti("sample_rate")); }

//Const Int Custom Sample Rate
//Custom sample rate
int i_custom_sample_rate() { return geti("custom_sample_rate"); }

//Const Int Channels
//Number of output channels
int i_channels() { return geti("channels"); }

//Const Enum Buffer Size
//Desired buffer size for sound generation. Larger values increase stability but decrease response time.

enum enum_buffer_size_desired {
    buffer_size_desired_Default = 0,
    buffer_size_desired_32 = 1,
    buffer_size_desired_64 = 2,
    buffer_size_desired_128 = 3,
    buffer_size_desired_256 = 4,
    buffer_size_desired_512 = 5,
    buffer_size_desired_1024 = 6,
    buffer_size_desired_2048 = 7,
    buffer_size_desired_4096 = 8,
    buffer_size_desired_8192 = 9,
    buffer_size_desired_16384 = 10,
    buffer_size_desired_32768 = 11,
    buffer_size_desired_N__ = 12
};
enum_buffer_size_desired en_buffer_size_desired() { return enum_buffer_size_desired(geti("buffer_size_desired")); }


//Checkbox Runtime
//Runtime variables
int i_runtime() { return geti("runtime"); }

//Out String Connected Device Name
//Name of the connected camera
QString s_connected_device_name() { return gets("connected_device_name"); }
void s_connected_device_name(QString value) { sets("connected_device_name", value); }

//Out Checkbox Is Started
//Does capture started
int i_is_started() { return geti("is_started"); }
void i_is_started(int value) { seti("is_started", value); }

//Out Object Sound Format
//Used sound format
XDict *obj_sound_format() { return get_object("sound_format"); }

//Out Int Buffer Size
//Buffer size
int i_buffer_size() { return geti("buffer_size"); }
void i_buffer_size(int value) { seti("buffer_size", value); }

//----------------------------------------------------
//Page Device Info
//Print list of output audio devices and supported formats of the selected device

//Checkbox Print Devices
//Print list of all connected output audio devices
int i_print_devices() { return geti("print_devices"); }

//Const Checkbox Print Formats
//Print once list of supported formats of connected audio device
int i_print_formats() { return geti("print_formats"); }

//Out Text Local Console
//Console output
QString s_local_console() { return gets("local_console"); }
void s_local_console(QString value) { sets("local_console", value); }

//----------------------------------------------------
//Page Test Sound
//Output test sound

//Checkbox Generate Test Sound
//Enable generating the test sinewave sound. Note, other sounds will be muted.
int i_gen_test() { return geti("gen_test"); }

//----------------------------------------------------
