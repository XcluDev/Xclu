//----------------------------------------------------
//Interface for XClassDelay
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

//Button Bang Now
//Press to banging and restart time counter.
bool was_changed_bang_now() { return was_changed_("bang_now"); }
int geti_bang_now() { return geti_("bang_now"); }
QString button_bang_now() { return "bang_now"; }

//Button Restart
//Restart time counter without bang.
bool was_changed_restart() { return was_changed_("restart"); }
int geti_restart() { return geti_("restart"); }
QString button_restart() { return "restart"; }

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
//Modules to send bang on delay. `#` means comment
bool was_changed_bang_list() { return was_changed_("bang_list"); }
QString gets_bang_list() { return gets_("bang_list"); }
QStringList get_strings_bang_list() { return get_strings_("bang_list"); }

//----------------------------------------------------
