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

//String File Name
//File to execute.
bool was_changed_file_name() { return was_changed_("file_name"); }
QString gets_file_name() { return gets_("file_name"); }
QStringList get_strings_file_name() { return get_strings_("file_name"); }

//String Arguments
//Optional command line arguments
bool was_changed_args() { return was_changed_("args"); }
QString gets_args() { return gets_("args"); }
QStringList get_strings_args() { return get_strings_("args"); }


//Enum Execute
//When start execution.
enum enum_execute {
    execute_At_First_Frame = 0,
    execute_Each_Frame = 1,
    execute_On_Button = 2,
    execute_N__ = 3
};
bool was_changed_execute() { return was_changed_("execute"); }
enum_execute gete_execute() { return enum_execute(geti_("execute")); }
QString getraw_execute() { return getraw_("execute");}

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

//Button Run
//Run execution immediately.
bool was_changed_run_button() { return was_changed_("run_button"); }
int geti_run_button() { return geti_("run_button"); }
QString button_run_button() { return "run_button"; }

//----------------------------------------------------
//Page Settings
//

//Checkbox Enable Timeout
//Use timeout for stopping execution or wait infinitely
bool was_changed_enable_timeout() { return was_changed_("enable_timeout"); }
int geti_enable_timeout() { return geti_("enable_timeout"); }

//Float Timeout
//Timeout duration
bool was_changed_timeout_sec() { return was_changed_("timeout_sec"); }
float getf_timeout_sec() { return getf_("timeout_sec"); }

//----------------------------------------------------
//Page Console
//Exhange data using console. It's a way to use Python programs for ML processing in realtime.

//Enum Write
//When write data to process console.
enum enum_write {
    write_Disabled = 0,
    write_After_Run = 1,
    write_Each_Frame = 2,
    write_On_Button = 3,
    write_N__ = 4
};
bool was_changed_write() { return was_changed_("write"); }
enum_write gete_write() { return enum_write(geti_("write")); }
QString getraw_write() { return getraw_("write");}

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
bool was_changed_string_write() { return was_changed_("string_write"); }
QString gets_string_write() { return gets_("string_write"); }
QStringList get_strings_string_write() { return get_strings_("string_write"); }

//Text Text
//Text to write to process console.
bool was_changed_text_write() { return was_changed_("text_write"); }
QString gets_text_write() { return gets_("text_write"); }
QStringList get_strings_text_write() { return get_strings_("text_write"); }

//Object Image
//Image to write to process console. It's sent as uint16: w,h,channels, and then data array as uint8.
bool was_changed_image_write() { return was_changed_("image_write"); }
XProtectedObject *getobject_image_write() { return get_object_("image_write"); }


//Enum Read
//When read data from process console.
enum enum_read {
    read_Disabled = 0,
    read_After_Run = 1,
    read_Each_Frame = 2,
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

//String String
//String to write to process console.
bool was_changed_string_read() { return was_changed_("string_read"); }
QString gets_string_read() { return gets_("string_read"); }
QStringList get_strings_string_read() { return get_strings_("string_read"); }

//Text Text
//Text to write to process console.
bool was_changed_text_read() { return was_changed_("text_read"); }
QString gets_text_read() { return gets_("text_read"); }
QStringList get_strings_text_read() { return get_strings_("text_read"); }

//Out Object Image
//Image to read to process console. It's read as uint16: w,h,channels, and then data array as uint8.
bool was_changed_image_read() { return was_changed_("image_read"); }
XProtectedObject *getobject_image_read() { return get_object_("image_read"); }
void setobject_image_read(XProtectedObject *value) { set_object_("image_read", value); }
void setobject_image_read(XProtectedObject &value) { set_object_("image_read", value); }


//Checkbox Show Errors
//When read data from process console.
bool was_changed_show_errors() { return was_changed_("show_errors"); }
int geti_show_errors() { return geti_("show_errors"); }

//Out Text Errors
//Errors.
bool was_changed_text_errors() { return was_changed_("text_errors"); }
QString gets_text_errors() { return gets_("text_errors"); }
QStringList get_strings_text_errors() { return get_strings_("text_errors"); }
void sets_text_errors(QString value) { sets_("text_errors", value); }
void clear_string_text_errors() { clear_string_("text_errors"); }
void append_string_text_errors(QString v, int extra_new_lines_count = 0) { append_string_("text_errors", v, extra_new_lines_count); }
void append_string_text_errors(QStringList v, int extra_new_lines_count = 0) { append_string_("text_errors", v, extra_new_lines_count); }

//----------------------------------------------------
//Page Details
//

//Checkbox Runtime
//Runtime variables
bool was_changed_runtime() { return was_changed_("runtime"); }
int geti_runtime() { return geti_("runtime"); }

//Out Checkbox Success
//Momentary value which is set to 1 if executiion was successful at the current frame
bool was_changed_success() { return was_changed_("success"); }
int geti_success() { return geti_("success"); }
void seti_success(int value) { seti_("success", value); }

//Out Int Exit Code
//The code returned by program, '0' means no error
bool was_changed_exit_code() { return was_changed_("exit_code"); }
int geti_exit_code() { return geti_("exit_code"); }
void seti_exit_code(int value) { seti_("exit_code", value); }
void increase_int_exit_code(int increase = 1) { increase_int_("exit_code", increase); }


//Checkbox Show Absolute Paths
//Show full path for working folder and file used for execution
bool was_changed_show_abs_paths() { return was_changed_("show_abs_paths"); }
int geti_show_abs_paths() { return geti_("show_abs_paths"); }

//Out Text Folder Path
//Absolute path to the working folder
bool was_changed_folder_path() { return was_changed_("folder_path"); }
QString gets_folder_path() { return gets_("folder_path"); }
QStringList get_strings_folder_path() { return get_strings_("folder_path"); }
void sets_folder_path(QString value) { sets_("folder_path", value); }
void clear_string_folder_path() { clear_string_("folder_path"); }
void append_string_folder_path(QString v, int extra_new_lines_count = 0) { append_string_("folder_path", v, extra_new_lines_count); }
void append_string_folder_path(QStringList v, int extra_new_lines_count = 0) { append_string_("folder_path", v, extra_new_lines_count); }

//Out Text File Path
//Absolute path to the executable file
bool was_changed_file_path() { return was_changed_("file_path"); }
QString gets_file_path() { return gets_("file_path"); }
QStringList get_strings_file_path() { return get_strings_("file_path"); }
void sets_file_path(QString value) { sets_("file_path", value); }
void clear_string_file_path() { clear_string_("file_path"); }
void append_string_file_path(QString v, int extra_new_lines_count = 0) { append_string_("file_path", v, extra_new_lines_count); }
void append_string_file_path(QStringList v, int extra_new_lines_count = 0) { append_string_("file_path", v, extra_new_lines_count); }

//----------------------------------------------------
