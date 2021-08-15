//----------------------------------------------------
//Interface for XClassSoundOut
//Created automatically.
//----------------------------------------------------
//Page Main
//General settings

//Float Volume
//Output sound volume.
bool was_changed_volume() { return was_changed_("volume"); }
float getf_volume() { return getf_("volume"); }
void repaint_volume() { repaint_("volume"); }

//Float Device Volume
//Output device volume.
bool was_changed_device_volume() { return was_changed_("device_volume"); }
float getf_device_volume() { return getf_("device_volume"); }
void repaint_device_volume() { repaint_("device_volume"); }


//Const Enum Sound Device
//Choose the way for selecting sound output device
enum enum_select_device {
    select_device_Default = 0,
    select_device_By_Index = 1,
    select_device_By_Name = 2,
    select_device_N__ = 3
};
bool was_changed_select_device() { return was_changed_("select_device"); }
enum_select_device gete_select_device() { return enum_select_device(geti_("select_device")); }
QString getraw_select_device() { return getraw_("select_device");}

//Const Int Device Index
//Sound device index in Operating System.
bool was_changed_device_index() { return was_changed_("device_index"); }
int geti_device_index() { return geti_("device_index"); }
void repaint_device_index() { repaint_("device_index"); }

//Const String Device Name
//Name of the sound output device to connect (or part of the name), press 'Show Devices' to see the list
bool was_changed_device_name() { return was_changed_("device_name"); }
QString gets_device_name() { return gets_("device_name"); }
QStringList get_strings_device_name() { return get_strings_("device_name"); }
void repaint_device_name() { repaint_("device_name"); }


//Checkbox Settings
//Setting sound output parameters
bool was_changed_settings() { return was_changed_("settings"); }
int geti_settings() { return geti_("settings"); }
void repaint_settings() { repaint_("settings"); }

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
bool was_changed_sample_rate() { return was_changed_("sample_rate"); }
enum_sample_rate gete_sample_rate() { return enum_sample_rate(geti_("sample_rate")); }
QString getraw_sample_rate() { return getraw_("sample_rate");}

//Const Int Custom Sample Rate
//Custom sample rate
bool was_changed_custom_sample_rate() { return was_changed_("custom_sample_rate"); }
int geti_custom_sample_rate() { return geti_("custom_sample_rate"); }
void repaint_custom_sample_rate() { repaint_("custom_sample_rate"); }

//Const Int Channels
//Number of output channels
bool was_changed_channels() { return was_changed_("channels"); }
int geti_channels() { return geti_("channels"); }
void repaint_channels() { repaint_("channels"); }

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
bool was_changed_buffer_size_desired() { return was_changed_("buffer_size_desired"); }
enum_buffer_size_desired gete_buffer_size_desired() { return enum_buffer_size_desired(geti_("buffer_size_desired")); }
QString getraw_buffer_size_desired() { return getraw_("buffer_size_desired");}


//Checkbox Runtime
//Runtime variables
bool was_changed_runtime() { return was_changed_("runtime"); }
int geti_runtime() { return geti_("runtime"); }
void repaint_runtime() { repaint_("runtime"); }

//Out String Connected Device Name
//Name of the connected sound device.
bool was_changed_connected_device_name() { return was_changed_("connected_device_name"); }
QString gets_connected_device_name() { return gets_("connected_device_name"); }
QStringList get_strings_connected_device_name() { return get_strings_("connected_device_name"); }
void sets_connected_device_name(QString value) { sets_("connected_device_name", value); }
void clear_string_connected_device_name() { clear_string_("connected_device_name"); }
void append_string_connected_device_name(QString v, int extra_new_lines_count = 0) { append_string_("connected_device_name", v, extra_new_lines_count); }
void append_string_connected_device_name(QStringList v, int extra_new_lines_count = 0) { append_string_("connected_device_name", v, extra_new_lines_count); }
void repaint_connected_device_name() { repaint_("connected_device_name"); }

//Out Checkbox Is Started
//Does sound output started.
bool was_changed_is_started() { return was_changed_("is_started"); }
int geti_is_started() { return geti_("is_started"); }
void seti_is_started(int value) { seti_("is_started", value); }
void repaint_is_started() { repaint_("is_started"); }

//Out Object Sound Format
//Used sound format.
bool was_changed_sound_format() { return was_changed_("sound_format"); }
XProtectedObject *getobject_sound_format() { return get_object_("sound_format"); }
void setobject_sound_format(XProtectedObject *value) { set_object_("sound_format", value); }
void setobject_sound_format(XProtectedObject &value) { set_object_("sound_format", value); }
void repaint_sound_format() { repaint_("sound_format"); }
//Out Int Buffer Size
//Buffer size.
bool was_changed_buffer_size() { return was_changed_("buffer_size"); }
int geti_buffer_size() { return geti_("buffer_size"); }
void seti_buffer_size(int value) { seti_("buffer_size", value); }
void increase_int_buffer_size(int increase = 1) { increase_int_("buffer_size", increase); }
void repaint_buffer_size() { repaint_("buffer_size"); }


//----------------------------------------------------
//Page Sources
//

//Text Sound Sources
//List of modules to which will be sent callback for sound buffer
bool was_changed_modules_list() { return was_changed_("modules_list"); }
QString gets_modules_list() { return gets_("modules_list"); }
QStringList get_strings_modules_list() { return get_strings_("modules_list"); }
void repaint_modules_list() { repaint_("modules_list"); }


//----------------------------------------------------
//Page Channels
//Control channels sound.

//Float Left Volume
//Volume for the left channel.
bool was_changed_volume_ch1() { return was_changed_("volume_ch1"); }
float getf_volume_ch1() { return getf_("volume_ch1"); }
void repaint_volume_ch1() { repaint_("volume_ch1"); }

//Float Right Volume
//Volume for the right channel.
bool was_changed_volume_ch2() { return was_changed_("volume_ch2"); }
float getf_volume_ch2() { return getf_("volume_ch2"); }
void repaint_volume_ch2() { repaint_("volume_ch2"); }

//----------------------------------------------------
//Page Test Sound
//Output test sound

//Checkbox Generate Test Sound
//Enable generating the test sinewave sound. Note, other sounds will be muted.
bool was_changed_gen_test() { return was_changed_("gen_test"); }
int geti_gen_test() { return geti_("gen_test"); }
void repaint_gen_test() { repaint_("gen_test"); }

//Checkbox Left Channel
//Should generate sound for left channel.
bool was_changed_gen_left() { return was_changed_("gen_left"); }
int geti_gen_left() { return geti_("gen_left"); }
void repaint_gen_left() { repaint_("gen_left"); }

//Checkbox Right Channel
//Should generate sound for right channel.
bool was_changed_gen_right() { return was_changed_("gen_right"); }
int geti_gen_right() { return geti_("gen_right"); }
void repaint_gen_right() { repaint_("gen_right"); }

//Float Volume
//Volume of generated sound.
bool was_changed_gen_volume() { return was_changed_("gen_volume"); }
float getf_gen_volume() { return getf_("gen_volume"); }
void repaint_gen_volume() { repaint_("gen_volume"); }

//Int Freq
//Frequency of generated sinewave.
bool was_changed_gen_freq() { return was_changed_("gen_freq"); }
int geti_gen_freq() { return geti_("gen_freq"); }
void repaint_gen_freq() { repaint_("gen_freq"); }

//----------------------------------------------------
//Page Devices
//Print list of output audio devices and supported formats of the selected device

//Button Print Devices
//Print list of all connected devices.
bool was_changed_print_devices() { return was_changed_("print_devices"); }
int geti_print_devices() { return geti_("print_devices"); }
void repaint_print_devices() { repaint_("print_devices"); }
QString button_print_devices() { return "print_devices"; }

//Checkbox Print Formats
//Print list of supported formats for connected device at start.
bool was_changed_print_formats() { return was_changed_("print_formats"); }
int geti_print_formats() { return geti_("print_formats"); }
void repaint_print_formats() { repaint_("print_formats"); }

//Out Text Local Console
//Console output
bool was_changed_local_console() { return was_changed_("local_console"); }
QString gets_local_console() { return gets_("local_console"); }
QStringList get_strings_local_console() { return get_strings_("local_console"); }
void sets_local_console(QString value) { sets_("local_console", value); }
void clear_string_local_console() { clear_string_("local_console"); }
void append_string_local_console(QString v, int extra_new_lines_count = 0) { append_string_("local_console", v, extra_new_lines_count); }
void append_string_local_console(QStringList v, int extra_new_lines_count = 0) { append_string_("local_console", v, extra_new_lines_count); }
void repaint_local_console() { repaint_("local_console"); }

//----------------------------------------------------
