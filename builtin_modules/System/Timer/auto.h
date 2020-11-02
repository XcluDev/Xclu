//----------------------------------------------------
//Interface for XClassTimer
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Enum Period
//Delay period measure unit.
enum enum_period {
    period_HMS = 0,
    period_Hours = 1,
    period_Minutes = 2,
    period_Seconds = 3,
    period_N__ = 4
};
bool was_changed_period() { return was_changed_("period"); }
enum_period gete_period() { return enum_period(geti_("period")); }
QString getraw_period() { return getraw_("period");}

//Int Hours
//Delay time in hours.
bool was_changed_hms_hours() { return was_changed_("hms_hours"); }
int geti_hms_hours() { return geti_("hms_hours"); }

//Int Minutes
//Delay time in minutes.
bool was_changed_hms_minutes() { return was_changed_("hms_minutes"); }
int geti_hms_minutes() { return geti_("hms_minutes"); }

//Float Seconds
//Delay time in seconds.
bool was_changed_hms_seconds() { return was_changed_("hms_seconds"); }
float getf_hms_seconds() { return getf_("hms_seconds"); }

//Float Hours
//Delay time in hours.
bool was_changed_hours() { return was_changed_("hours"); }
float getf_hours() { return getf_("hours"); }

//Float Minutes
//Delay time in minutes.
bool was_changed_minutes() { return was_changed_("minutes"); }
float getf_minutes() { return getf_("minutes"); }

//Float Seconds
//Delay time in hours.
bool was_changed_seconds() { return was_changed_("seconds"); }
float getf_seconds() { return getf_("seconds"); }


//Enum Working Mode
//Should we wait during delay, or wait and send bang when timer is gone
enum enum_working_mode {
    working_mode_Pause_Execution = 0,
    working_mode_Bang = 1,
    working_mode_N__ = 2
};
bool was_changed_working_mode() { return was_changed_("working_mode"); }
enum_working_mode gete_working_mode() { return enum_working_mode(geti_("working_mode")); }
QString getraw_working_mode() { return getraw_("working_mode");}

//Checkbox Repeating
//Repeating timer execution.
bool was_changed_repeating() { return was_changed_("repeating"); }
int geti_repeating() { return geti_("repeating"); }

//Button One Shot
//Press to start time counter one time.
bool was_changed_one_shot_button() { return was_changed_("one_shot_button"); }
int geti_one_shot_button() { return geti_("one_shot_button"); }
QString button_one_shot_button() { return "one_shot_button"; }

//Button Stop
//Stop time counter.
bool was_changed_stop_button() { return was_changed_("stop_button"); }
int geti_stop_button() { return geti_("stop_button"); }
QString button_stop_button() { return "stop_button"; }


//Out Checkbox Working
//Is timer working.
bool was_changed_working() { return was_changed_("working"); }
int geti_working() { return geti_("working"); }
void seti_working(int value) { seti_("working", value); }

//Enum Out Time Format
//Output time format - only for showing, but for programming all are available.
enum enum_out_time {
    out_time_Time_Elapsed_sec = 0,
    out_time_Time_Left_sec = 1,
    out_time_Time_Uniform = 2,
    out_time_Time_Left_hms = 3,
    out_time_N__ = 4
};
bool was_changed_out_time() { return was_changed_("out_time"); }
enum_out_time gete_out_time() { return enum_out_time(geti_("out_time")); }
QString getraw_out_time() { return getraw_("out_time");}

//Out Float Time Elapsed
//Time elapsed.
bool was_changed_time_elapsed_sec() { return was_changed_("time_elapsed_sec"); }
float getf_time_elapsed_sec() { return getf_("time_elapsed_sec"); }
void setf_time_elapsed_sec(float value) { setf_("time_elapsed_sec", value); }

//Out Float Time Left
//Time left.
bool was_changed_time_left_sec() { return was_changed_("time_left_sec"); }
float getf_time_left_sec() { return getf_("time_left_sec"); }
void setf_time_left_sec(float value) { setf_("time_left_sec", value); }

//Out Float Time Uniform
//Uniform time.
bool was_changed_time_uniform() { return was_changed_("time_uniform"); }
float getf_time_uniform() { return getf_("time_uniform"); }
void setf_time_uniform(float value) { setf_("time_uniform", value); }

//Out String Time Left
//How much time before next bang.
bool was_changed_time_left_hms() { return was_changed_("time_left_hms"); }
QString gets_time_left_hms() { return gets_("time_left_hms"); }
QStringList get_strings_time_left_hms() { return get_strings_("time_left_hms"); }
void sets_time_left_hms(QString value) { sets_("time_left_hms", value); }
void clear_string_time_left_hms() { clear_string_("time_left_hms"); }
void append_string_time_left_hms(QString v, int extra_new_lines_count = 0) { append_string_("time_left_hms", v, extra_new_lines_count); }
void append_string_time_left_hms(QStringList v, int extra_new_lines_count = 0) { append_string_("time_left_hms", v, extra_new_lines_count); }


//Text Bang List
//Modules to send bang on delay. `#` means comment, can use 'module1' or 'module1->button1'
bool was_changed_bang_list() { return was_changed_("bang_list"); }
QString gets_bang_list() { return gets_("bang_list"); }
QStringList get_strings_bang_list() { return get_strings_("bang_list"); }

//----------------------------------------------------
