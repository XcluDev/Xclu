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


//Const Checkbox Autostart
//Autostart project after loading.
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


//Out Int Frame Number
//Number of frame from start.
bool was_changed_frame() { return was_changed_("frame"); }
int geti_frame() { return geti_("frame"); }
void seti_frame(int value) { seti_("frame", value); }
void increase_int_frame(int increase = 1) { increase_int_("frame", increase); }
void repaint_frame() { repaint_("frame"); }

//----------------------------------------------------
