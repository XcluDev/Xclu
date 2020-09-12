//----------------------------------------------------
//Interface for XClassProject
//Created automatically at 2020.09.12 21:37:02
//----------------------------------------------------
//Page Main
//General settings.

//Const Int Frame Rate
//Project frame rate.
int i_frame_rate() { return geti("frame_rate"); }

//Const Checkbox Autostart
//Autostart project after loading.
int i_autostart() { return geti("autostart"); }


//Out Float Elapsed Time
//Time in seconds from project start.
float f_elapsed_time_sec() { return getf("elapsed_time_sec"); }
void f_elapsed_time_sec(float value) { setf("elapsed_time_sec", value); }

//Out Float dt
//Time step between frames.
float f_dt() { return getf("dt"); }
void f_dt(float value) { setf("dt", value); }

//Out Float Measured Fr Rate
//Measured frame rate.
float f_measured_frame_rate() { return getf("measured_frame_rate"); }
void f_measured_frame_rate(float value) { setf("measured_frame_rate", value); }

//----------------------------------------------------
