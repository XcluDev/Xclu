//----------------------------------------------------
//Interface for XClassExecute
//Created automatically.
//----------------------------------------------------
//Page Main
//

//String Working Folder
//Folder for running the file.
bool was_changed_folder_name() { return was_changed_("folder_name"); }
QString gets_folder_name() { return gets_("folder_name"); }
QStringList get_strings_folder_name() { return get_strings_("folder_name"); }

//String Command Or File
//Command or file to execute.
bool was_changed_file_name() { return was_changed_("file_name"); }
QString gets_file_name() { return gets_("file_name"); }
QStringList get_strings_file_name() { return get_strings_("file_name"); }

//Checkbox File Must Exists
//This is file name and it's must exists. Uncheck for running commands such as 'python' or similar.
bool was_changed_file_must_exists() { return was_changed_("file_must_exists"); }
int geti_file_must_exists() { return geti_("file_must_exists"); }

//String Arguments
//Optional command line arguments
bool was_changed_args() { return was_changed_("args"); }
QString gets_args() { return gets_("args"); }
QStringList get_strings_args() { return get_strings_("args"); }

//----------------------------------------------------
//Page Run
//Running controls and error output.

//Enum Execute
//When start execution.
enum enum_execute_event {
    execute_event_At_First_Frame = 0,
    execute_event_Each_Frame = 1,
    execute_event_On_Button = 2,
    execute_event_N__ = 3
};
bool was_changed_execute_event() { return was_changed_("execute_event"); }
enum_execute_event gete_execute_event() { return enum_execute_event(geti_("execute_event")); }
QString getraw_execute_event() { return getraw_("execute_event");}

//Enum Thread Mode
//Should we wait for execution finish or run in a separate thread.
enum enum_thread_mode {
    thread_mode_Wait_Finishing = 0,
    thread_mode_Run_At_Separate_Thread = 1,
    thread_mode_N__ = 2
};
bool was_changed_thread_mode() { return was_changed_("thread_mode"); }
enum_thread_mode gete_thread_mode() { return enum_thread_mode(geti_("thread_mode")); }
QString getraw_thread_mode() { return getraw_("thread_mode");}

//Checkbox Enable Timeout
//Use timeout for stopping execution or wait infinitely
bool was_changed_enable_timeout() { return was_changed_("enable_timeout"); }
int geti_enable_timeout() { return geti_("enable_timeout"); }

//Float Timeout
//Timeout duration
bool was_changed_timeout_sec() { return was_changed_("timeout_sec"); }
float getf_timeout_sec() { return getf_("timeout_sec"); }



//Button Run
//Run execution immediately.
bool was_changed_run_button() { return was_changed_("run_button"); }
int geti_run_button() { return geti_("run_button"); }
QString button_run_button() { return "run_button"; }

//Button Stop
//Stop execution immediately.
bool was_changed_stop_button() { return was_changed_("stop_button"); }
int geti_stop_button() { return geti_("stop_button"); }
QString button_stop_button() { return "stop_button"; }

//Out Enum Status
//Status of the current execution.
enum enum_status {
    status_Not_Started = 0,
    status_Running = 1,
    status_Success = 2,
    status_Error = 3,
    status_Timeout = 4,
    status_Crashed = 5,
    status_N__ = 6
};
bool was_changed_status() { return was_changed_("status"); }
enum_status gete_status() { return enum_status(geti_("status")); }
void sete_status(enum_status value) { seti_("status", value); }
QString getraw_status() { return getraw_("status");}

//Out Int Exit Code
//The code returned by program, '0' means no error.
bool was_changed_exit_code() { return was_changed_("exit_code"); }
int geti_exit_code() { return geti_("exit_code"); }
void seti_exit_code(int value) { seti_("exit_code", value); }
void increase_int_exit_code(int increase = 1) { increase_int_("exit_code", increase); }

//Out String Error Details
//Details about Crash
bool was_changed_error_details() { return was_changed_("error_details"); }
QString gets_error_details() { return gets_("error_details"); }
QStringList get_strings_error_details() { return get_strings_("error_details"); }
void sets_error_details(QString value) { sets_("error_details", value); }
void clear_string_error_details() { clear_string_("error_details"); }
void append_string_error_details(QString v, int extra_new_lines_count = 0) { append_string_("error_details", v, extra_new_lines_count); }
void append_string_error_details(QStringList v, int extra_new_lines_count = 0) { append_string_("error_details", v, extra_new_lines_count); }



//Enum Console Errors
//When read data from process console.
enum enum_console_errors {
    console_errors_Ignore = 0,
    console_errors_Show = 1,
    console_errors_Show_And_Stop = 2,
    console_errors_N__ = 3
};
bool was_changed_console_errors() { return was_changed_("console_errors"); }
enum_console_errors gete_console_errors() { return enum_console_errors(geti_("console_errors")); }
QString getraw_console_errors() { return getraw_("console_errors");}

//Out Text Text
//Errors output from process console.
bool was_changed_console_errors_text() { return was_changed_("console_errors_text"); }
QString gets_console_errors_text() { return gets_("console_errors_text"); }
QStringList get_strings_console_errors_text() { return get_strings_("console_errors_text"); }
void sets_console_errors_text(QString value) { sets_("console_errors_text", value); }
void clear_string_console_errors_text() { clear_string_("console_errors_text"); }
void append_string_console_errors_text(QString v, int extra_new_lines_count = 0) { append_string_("console_errors_text", v, extra_new_lines_count); }
void append_string_console_errors_text(QStringList v, int extra_new_lines_count = 0) { append_string_("console_errors_text", v, extra_new_lines_count); }

//----------------------------------------------------
//Page Read
//Reading from the process console.

//Enum Console Read
//When read data from process console.
enum enum_read {
    read_Disabled = 0,
    read_Each_Frame = 1,
    read_After_Finished = 2,
    read_On_Button = 3,
    read_N__ = 4
};
bool was_changed_read() { return was_changed_("read"); }
enum_read gete_read() { return enum_read(geti_("read")); }
QString getraw_read() { return getraw_("read");}

//Button Read
//Read from process console right now.
bool was_changed_read_button() { return was_changed_("read_button"); }
int geti_read_button() { return geti_("read_button"); }
QString button_read_button() { return "read_button"; }

//Enum Data Type
//Data type for console read.
enum enum_read_type {
    read_type_String = 0,
    read_type_Text = 1,
    read_type_Image = 2,
    read_type_N__ = 3
};
bool was_changed_read_type() { return was_changed_("read_type"); }
enum_read_type gete_read_type() { return enum_read_type(geti_("read_type")); }
QString getraw_read_type() { return getraw_("read_type");}

//Out Checkbox Received
//Flag that data is received. Note, for multiple data it stores only the last data
bool was_changed_console_read_received() { return was_changed_("console_read_received"); }
int geti_console_read_received() { return geti_("console_read_received"); }
void seti_console_read_received(int value) { seti_("console_read_received", value); }

//Text Bang On Received
//List of actions which should be performed when data is received. Current implementation runs this only in the main thread, not as callback.
bool was_changed_console_bang_on_received() { return was_changed_("console_bang_on_received"); }
QString gets_console_bang_on_received() { return gets_("console_bang_on_received"); }
QStringList get_strings_console_bang_on_received() { return get_strings_("console_bang_on_received"); }

//Out String String
//String to write to process console.
bool was_changed_console_read_string() { return was_changed_("console_read_string"); }
QString gets_console_read_string() { return gets_("console_read_string"); }
QStringList get_strings_console_read_string() { return get_strings_("console_read_string"); }
void sets_console_read_string(QString value) { sets_("console_read_string", value); }
void clear_string_console_read_string() { clear_string_("console_read_string"); }
void append_string_console_read_string(QString v, int extra_new_lines_count = 0) { append_string_("console_read_string", v, extra_new_lines_count); }
void append_string_console_read_string(QStringList v, int extra_new_lines_count = 0) { append_string_("console_read_string", v, extra_new_lines_count); }

//Checkbox Append
//If enabled, append all input text. If disables - clear each frame.
bool was_changed_console_read_text_append() { return was_changed_("console_read_text_append"); }
int geti_console_read_text_append() { return geti_("console_read_text_append"); }

//Out Text Text
//Text to write to process console.
bool was_changed_console_read_text() { return was_changed_("console_read_text"); }
QString gets_console_read_text() { return gets_("console_read_text"); }
QStringList get_strings_console_read_text() { return get_strings_("console_read_text"); }
void sets_console_read_text(QString value) { sets_("console_read_text", value); }
void clear_string_console_read_text() { clear_string_("console_read_text"); }
void append_string_console_read_text(QString v, int extra_new_lines_count = 0) { append_string_("console_read_text", v, extra_new_lines_count); }
void append_string_console_read_text(QStringList v, int extra_new_lines_count = 0) { append_string_("console_read_text", v, extra_new_lines_count); }

//Out Object Image
//Image to read to process console. It's read as uint16: w,h,channels, and then data array as uint8.
bool was_changed_console_read_image() { return was_changed_("console_read_image"); }
XProtectedObject *getobject_console_read_image() { return get_object_("console_read_image"); }
void setobject_console_read_image(XProtectedObject *value) { set_object_("console_read_image", value); }
void setobject_console_read_image(XProtectedObject &value) { set_object_("console_read_image", value); }
//----------------------------------------------------
//Page Write
//Writing to the process console.

//Checkbox Write At Process Start
//Write data to process console at process start.
bool was_changed_write_at_start() { return was_changed_("write_at_start"); }
int geti_write_at_start() { return geti_("write_at_start"); }

//Checkbox Write Each Frame
//Write data to process console each frame.
bool was_changed_write_each_frame() { return was_changed_("write_each_frame"); }
int geti_write_each_frame() { return geti_("write_each_frame"); }

//Checkbox Write On Receive
//Write data to process console after receiving answer.
bool was_changed_write_on_receive() { return was_changed_("write_on_receive"); }
int geti_write_on_receive() { return geti_("write_on_receive"); }

//Button Write
//Write to process console right now.
bool was_changed_write_button() { return was_changed_("write_button"); }
int geti_write_button() { return geti_("write_button"); }
QString button_write_button() { return "write_button"; }

//Enum Data Type
//Data type for console write.
enum enum_write_type {
    write_type_String = 0,
    write_type_Text = 1,
    write_type_Image = 2,
    write_type_N__ = 3
};
bool was_changed_write_type() { return was_changed_("write_type"); }
enum_write_type gete_write_type() { return enum_write_type(geti_("write_type")); }
QString getraw_write_type() { return getraw_("write_type");}

//String String
//String to write to process console.
bool was_changed_console_write_string() { return was_changed_("console_write_string"); }
QString gets_console_write_string() { return gets_("console_write_string"); }
QStringList get_strings_console_write_string() { return get_strings_("console_write_string"); }

//Enum Line Terminator
//
enum enum_line_term {
    line_term_None = 0,
    line_term__n = 1,
    line_term__r = 2,
    line_term__r_n = 3,
    line_term_N__ = 4
};
bool was_changed_line_term() { return was_changed_("line_term"); }
enum_line_term gete_line_term() { return enum_line_term(geti_("line_term")); }
QString getraw_line_term() { return getraw_("line_term");}

//Text Text
//Text to write to process console.
bool was_changed_console_write_text() { return was_changed_("console_write_text"); }
QString gets_console_write_text() { return gets_("console_write_text"); }
QStringList get_strings_console_write_text() { return get_strings_("console_write_text"); }

//Object Image
//Image to write to process console. It's sent as uint16: w,h,channels, and then data array as uint8.
bool was_changed_console_write_image() { return was_changed_("console_write_image"); }
XProtectedObject *getobject_console_write_image() { return get_object_("console_write_image"); }
//Checkbox Transform Image
//Convert to grayscale or resize image.
bool was_changed_console_write_image_transform() { return was_changed_("console_write_image_transform"); }
int geti_console_write_image_transform() { return geti_("console_write_image_transform"); }

//Checkbox To Grayscale
//Convert image to grayscale.
bool was_changed_console_write_image_to_grayscale() { return was_changed_("console_write_image_to_grayscale"); }
int geti_console_write_image_to_grayscale() { return geti_("console_write_image_to_grayscale"); }

//Enum Resize
//Resize mode.
enum enum_console_write_image_resize {
    console_write_image_resize_No = 0,
    console_write_image_resize_Rescale = 1,
    console_write_image_resize_Pixel_Size = 2,
    console_write_image_resize_N__ = 3
};
bool was_changed_console_write_image_resize() { return was_changed_("console_write_image_resize"); }
enum_console_write_image_resize gete_console_write_image_resize() { return enum_console_write_image_resize(geti_("console_write_image_resize")); }
QString getraw_console_write_image_resize() { return getraw_("console_write_image_resize");}

//Float Scale
//Scale of output image, 1 - don't rescale.
bool was_changed_console_write_image_resize_scale() { return was_changed_("console_write_image_resize_scale"); }
float getf_console_write_image_resize_scale() { return getf_("console_write_image_resize_scale"); }

//Int Size X
//X-size of output image.
bool was_changed_console_write_image_sizex() { return was_changed_("console_write_image_sizex"); }
int geti_console_write_image_sizex() { return geti_("console_write_image_sizex"); }

//Int Size Y
//Y-size of output image.
bool was_changed_console_write_image_sizey() { return was_changed_("console_write_image_sizey"); }
int geti_console_write_image_sizey() { return geti_("console_write_image_sizey"); }

//Out Object Transformed
//Transformed image.
bool was_changed_console_write_image_transformed() { return was_changed_("console_write_image_transformed"); }
XProtectedObject *getobject_console_write_image_transformed() { return get_object_("console_write_image_transformed"); }
void setobject_console_write_image_transformed(XProtectedObject *value) { set_object_("console_write_image_transformed", value); }
void setobject_console_write_image_transformed(XProtectedObject &value) { set_object_("console_write_image_transformed", value); }
//----------------------------------------------------
//Page Debug
//

//Out Int Executed Times
//How much times process was executed.
bool was_changed_executed_times() { return was_changed_("executed_times"); }
int geti_executed_times() { return geti_("executed_times"); }
void seti_executed_times(int value) { seti_("executed_times", value); }
void increase_int_executed_times(int increase = 1) { increase_int_("executed_times", increase); }

//Out Text Working Folder Abs Path
//Absolute path to the working folder
bool was_changed_folder_path() { return was_changed_("folder_path"); }
QString gets_folder_path() { return gets_("folder_path"); }
QStringList get_strings_folder_path() { return get_strings_("folder_path"); }
void sets_folder_path(QString value) { sets_("folder_path", value); }
void clear_string_folder_path() { clear_string_("folder_path"); }
void append_string_folder_path(QString v, int extra_new_lines_count = 0) { append_string_("folder_path", v, extra_new_lines_count); }
void append_string_folder_path(QStringList v, int extra_new_lines_count = 0) { append_string_("folder_path", v, extra_new_lines_count); }

//Out Text File Name Abs Path
//Absolute path to the executable file
bool was_changed_file_path() { return was_changed_("file_path"); }
QString gets_file_path() { return gets_("file_path"); }
QStringList get_strings_file_path() { return get_strings_("file_path"); }
void sets_file_path(QString value) { sets_("file_path", value); }
void clear_string_file_path() { clear_string_("file_path"); }
void append_string_file_path(QString v, int extra_new_lines_count = 0) { append_string_("file_path", v, extra_new_lines_count); }
void append_string_file_path(QStringList v, int extra_new_lines_count = 0) { append_string_("file_path", v, extra_new_lines_count); }

//----------------------------------------------------
