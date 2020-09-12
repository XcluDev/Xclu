//----------------------------------------------------
//Interface for XClassExecute
//Created automatically at 2020.09.12 21:37:01
//----------------------------------------------------
//Page Main
//

//String Working Folder
//Folder for running the file.
QString s_folder_name() { return gets("folder_name"); }

//String File Name
//File to execute.
QString s_file_name() { return gets("file_name"); }

//String Arguments
//Optional command line arguments
QString s_args() { return gets("args"); }


//Enum Work Mode
//Should we execute file at each frame or on Bang signal

enum enum_work_mode {
    work_mode_Each_Frame = 0,
    work_mode_On_Bang = 1,
    work_mode_N__ = 2
};
enum_work_mode en_work_mode() { return enum_work_mode(geti("work_mode")); }

//Checkbox Bang
//Start execution
int i_bang_signal() { return geti("bang_signal"); }

//Button Bang
//Start execution
int i_bang_button() { return geti("bang_button"); }



//Checkbox Settings
//Settings for timeout
int i_settings() { return geti("settings"); }

//Checkbox Set Timeout
//Use timeout for stopping execution or wait infinitely
int i_set_timeout() { return geti("set_timeout"); }

//Float Timeout
//Timeout duration
float f_timeout_sec() { return getf("timeout_sec"); }


//Checkbox Runtime
//Runtime variables
int i_runtime() { return geti("runtime"); }

//Out Checkbox Success
//Momentary value which is set to 1 if executiion was successful in the current frame
int i_success() { return geti("success"); }
void i_success(int value) { seti("success", value); }

//Out Int Exit Code
//The code returned by program, '0' means no error
int i_exit_code() { return geti("exit_code"); }
void i_exit_code(int value) { seti("exit_code", value); }

//Out Checkbox Last Success
//Success of last execution, stored here until next execution
int i_last_success() { return geti("last_success"); }
void i_last_success(int value) { seti("last_success", value); }

//Out Float Last Execute Time
//Last time of the execution start measured from the project start
float f_last_time() { return getf("last_time"); }
void f_last_time(float value) { setf("last_time", value); }

//Out Float Last Duration
//Last duration of the execution
float f_last_duration() { return getf("last_duration"); }
void f_last_duration(float value) { setf("last_duration", value); }


//Checkbox Show Absolute Paths
//Show full path for working folder and file used for execution
int i_show_abs_paths() { return geti("show_abs_paths"); }

//Out Text Folder Path
//Absolute path to the working folder
QString s_folder_path() { return gets("folder_path"); }
void s_folder_path(QString value) { sets("folder_path", value); }

//Out Text File Path
//Absolute path to the executable file
QString s_file_path() { return gets("file_path"); }
void s_file_path(QString value) { sets("file_path", value); }


//Checkbox Show Local Console
//Show local console for printing there output of executed program
int i_show_console() { return geti("show_console"); }

//Out Text Local Console
//Console output
QString s_local_console() { return gets("local_console"); }
void s_local_console(QString value) { sets("local_console", value); }

//----------------------------------------------------
