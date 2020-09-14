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


//Enum Work Mode
//Should we execute file at each frame or on Bang signal
enum enum_work_mode {
    work_mode_Each_Frame = 0,
    work_mode_On_Bang = 1,
    work_mode_N__ = 2
};
bool was_changed_work_mode() { return was_changed_("work_mode"); }
enum_work_mode gete_work_mode() { return enum_work_mode(geti_("work_mode")); }

//Checkbox Bang
//Start execution
bool was_changed_bang_signal() { return was_changed_("bang_signal"); }
int geti_bang_signal() { return geti_("bang_signal"); }

//Button Bang
//Start execution
bool was_changed_bang_button() { return was_changed_("bang_button"); }
int geti_bang_button() { return geti_("bang_button"); }
QString button_bang_button() { return "bang_button"; }



//Checkbox Settings
//Settings for timeout
bool was_changed_settings() { return was_changed_("settings"); }
int geti_settings() { return geti_("settings"); }

//Checkbox Set Timeout
//Use timeout for stopping execution or wait infinitely
bool was_changed_set_timeout() { return was_changed_("set_timeout"); }
int geti_set_timeout() { return geti_("set_timeout"); }

//Float Timeout
//Timeout duration
bool was_changed_timeout_sec() { return was_changed_("timeout_sec"); }
float getf_timeout_sec() { return getf_("timeout_sec"); }


//Checkbox Runtime
//Runtime variables
bool was_changed_runtime() { return was_changed_("runtime"); }
int geti_runtime() { return geti_("runtime"); }

//Out Checkbox Success
//Momentary value which is set to 1 if executiion was successful in the current frame
bool was_changed_success() { return was_changed_("success"); }
int geti_success() { return geti_("success"); }
void seti_success(int value) { seti_("success", value); }

//Out Int Exit Code
//The code returned by program, '0' means no error
bool was_changed_exit_code() { return was_changed_("exit_code"); }
int geti_exit_code() { return geti_("exit_code"); }
void seti_exit_code(int value) { seti_("exit_code", value); }
void increase_int_exit_code(int increase = 1) { increase_int_("exit_code", increase); }

//Out Checkbox Last Success
//Success of last execution, stored here until next execution
bool was_changed_last_success() { return was_changed_("last_success"); }
int geti_last_success() { return geti_("last_success"); }
void seti_last_success(int value) { seti_("last_success", value); }

//Out Float Last Execute Time
//Last time of the execution start measured from the project start
bool was_changed_last_time() { return was_changed_("last_time"); }
float getf_last_time() { return getf_("last_time"); }
void setf_last_time(float value) { setf_("last_time", value); }

//Out Float Last Duration
//Last duration of the execution
bool was_changed_last_duration() { return was_changed_("last_duration"); }
float getf_last_duration() { return getf_("last_duration"); }
void setf_last_duration(float value) { setf_("last_duration", value); }


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


//Checkbox Show Local Console
//Show local console for printing there output of executed program
bool was_changed_show_console() { return was_changed_("show_console"); }
int geti_show_console() { return geti_("show_console"); }

//Out Text Local Console
//Console output
bool was_changed_local_console() { return was_changed_("local_console"); }
QString gets_local_console() { return gets_("local_console"); }
QStringList get_strings_local_console() { return get_strings_("local_console"); }
void sets_local_console(QString value) { sets_("local_console", value); }
void clear_string_local_console() { clear_string_("local_console"); }
void append_string_local_console(QString v, int extra_new_lines_count = 0) { append_string_("local_console", v, extra_new_lines_count); }
void append_string_local_console(QStringList v, int extra_new_lines_count = 0) { append_string_("local_console", v, extra_new_lines_count); }

//----------------------------------------------------
