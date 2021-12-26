//----------------------------------------------------
//Interface for XClassProject
//Created automatically.
//----------------------------------------------------
//Page Main
//General settings.

//Const Int Frame Rate
//Project frame rate.
bool was_changed_frame_rate() { return was_changed_("frame_rate"); }
int geti_frame_rate() { return geti_("frame_rate"); }
void repaint_frame_rate() { repaint_("frame_rate"); }


//Checkbox Autostart
//Const. Autostart project after loading.
bool was_changed_autostart() { return was_changed_("autostart"); }
int geti_autostart() { return geti_("autostart"); }
void repaint_autostart() { repaint_("autostart"); }

//Const Int Wait Seconds
//(Sliently) wait after autostart - useful if the program autostarts and it's required to wait some USB devices to activate.
bool was_changed_autostart_wait_sec() { return was_changed_("autostart_wait_sec"); }
int geti_autostart_wait_sec() { return geti_("autostart_wait_sec"); }
void repaint_autostart_wait_sec() { repaint_("autostart_wait_sec"); }


//Const Checkbox Don't Save At Exit
//Disable "Save changes?" warning at project exit.
bool was_changed_dont_save_at_exit() { return was_changed_("dont_save_at_exit"); }
int geti_dont_save_at_exit() { return geti_("dont_save_at_exit"); }
void repaint_dont_save_at_exit() { repaint_("dont_save_at_exit"); }



//Out Float Elapsed Time
//Time in seconds from project start.
bool was_changed_elapsed_time_sec() { return was_changed_("elapsed_time_sec"); }
float getf_elapsed_time_sec() { return getf_("elapsed_time_sec"); }
void setf_elapsed_time_sec(float value) { setf_("elapsed_time_sec", value); }
void repaint_elapsed_time_sec() { repaint_("elapsed_time_sec"); }

//Out Float dt
//Time step between frames.
bool was_changed_dt() { return was_changed_("dt"); }
float getf_dt() { return getf_("dt"); }
void setf_dt(float value) { setf_("dt", value); }
void repaint_dt() { repaint_("dt"); }

//Out Float Measured Fr Rate
//Measured frame rate.
bool was_changed_measured_frame_rate() { return was_changed_("measured_frame_rate"); }
float getf_measured_frame_rate() { return getf_("measured_frame_rate"); }
void setf_measured_frame_rate(float value) { setf_("measured_frame_rate", value); }
void repaint_measured_frame_rate() { repaint_("measured_frame_rate"); }


//Out Int Frame
//Number of frame from start.
bool was_changed_frame() { return was_changed_("frame"); }
int geti_frame() { return geti_("frame"); }
void seti_frame(int value) { seti_("frame", value); }
void increase_int_frame(int increase = 1) { increase_int_("frame", increase); }
void repaint_frame() { repaint_("frame"); }

//----------------------------------------------------
//Page Watchdog
//Watchdog for killing application (expected to be reloaded if required by your BAT/SH in loop).

//Const Checkbox Watchdog
//
bool was_changed_watchdog_enabled() { return was_changed_("watchdog_enabled"); }
int geti_watchdog_enabled() { return geti_("watchdog_enabled"); }
void repaint_watchdog_enabled() { repaint_("watchdog_enabled"); }


//Int Frame To Check
//Link here project frame or camera frame.
bool was_changed_watchdog_frame() { return was_changed_("watchdog_frame"); }
int geti_watchdog_frame() { return geti_("watchdog_frame"); }
void repaint_watchdog_frame() { repaint_("watchdog_frame"); }

//Out Float Measured Fps
//Measured FPS are activated after initial pause.
bool was_changed_watchdog_measured_fps() { return was_changed_("watchdog_measured_fps"); }
float getf_watchdog_measured_fps() { return getf_("watchdog_measured_fps"); }
void setf_watchdog_measured_fps(float value) { setf_("watchdog_measured_fps", value); }
void repaint_watchdog_measured_fps() { repaint_("watchdog_measured_fps"); }


//Int Wait Sec
//Const. How much wait before start checking frames.
bool was_changed_watchdog_wait_sec() { return was_changed_("watchdog_wait_sec"); }
int geti_watchdog_wait_sec() { return geti_("watchdog_wait_sec"); }
void repaint_watchdog_wait_sec() { repaint_("watchdog_wait_sec"); }

//Int Tick Period
//Const. Period of checking.
bool was_changed_watchdog_tick_sec() { return was_changed_("watchdog_tick_sec"); }
int geti_watchdog_tick_sec() { return geti_("watchdog_tick_sec"); }
void repaint_watchdog_tick_sec() { repaint_("watchdog_tick_sec"); }

//Float Threshold Framerate
//Const. Minimal allowed frame rate to continue work, else kill this app.
bool was_changed_watchdog_threshold_rate() { return was_changed_("watchdog_threshold_rate"); }
float getf_watchdog_threshold_rate() { return getf_("watchdog_threshold_rate"); }
void repaint_watchdog_threshold_rate() { repaint_("watchdog_threshold_rate"); }


//Checkbox Test Pause
//Pause execution by 3 seconds. Don't forget check it out after testing.
bool was_changed_test_pause() { return was_changed_("test_pause"); }
int geti_test_pause() { return geti_("test_pause"); }
void repaint_test_pause() { repaint_("test_pause"); }

//----------------------------------------------------
