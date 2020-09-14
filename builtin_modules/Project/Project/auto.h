//----------------------------------------------------
//Interface for XClassProject
//Created automatically at 2020.09.14 11:01:46
//----------------------------------------------------
//Page Main
//General settings.

//Const Int Frame Rate
//Project frame rate.
bool was_changed_frame_rate() { return was_changed("frame_rate"); }
int geti_frame_rate() { return geti("frame_rate"); }

//Const Checkbox Autostart
//Autostart project after loading.
bool was_changed_autostart() { return was_changed("autostart"); }
int geti_autostart() { return geti("autostart"); }


//Out Float Elapsed Time
//Time in seconds from project start.
bool was_changed_elapsed_time_sec() { return was_changed("elapsed_time_sec"); }
float getf_elapsed_time_sec() { return getf("elapsed_time_sec"); }
void setf_elapsed_time_sec(float value) { setf("elapsed_time_sec", value); }

//Out Float dt
//Time step between frames.
bool was_changed_dt() { return was_changed("dt"); }
float getf_dt() { return getf("dt"); }
void setf_dt(float value) { setf("dt", value); }

//Out Float Measured Fr Rate
//Measured frame rate.
bool was_changed_measured_frame_rate() { return was_changed("measured_frame_rate"); }
float getf_measured_frame_rate() { return getf("measured_frame_rate"); }
void setf_measured_frame_rate(float value) { setf("measured_frame_rate", value); }

//----------------------------------------------------
