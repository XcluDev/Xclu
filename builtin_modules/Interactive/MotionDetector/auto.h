//----------------------------------------------------
//Interface for XClassMotionDetector
//Created automatically.
//----------------------------------------------------
//Page Main
//General settings

//Checkbox Show Input Image
//
bool was_changed_show_input_image() { return was_changed_("show_input_image"); }
int geti_show_input_image() { return geti_("show_input_image"); }

//Object Input Image
//Image for processing.
bool was_changed_input_image() { return was_changed_("input_image"); }
XProtectedObject *getobject_input_image() { return get_object_("input_image"); }


//Out Object Output Image
//Image with visualization.
bool was_changed_output_image() { return was_changed_("output_image"); }
XProtectedObject *getobject_output_image() { return get_object_("output_image"); }
void setobject_output_image(XProtectedObject *value) { set_object_("output_image", value); }

//Out Object Background Image
//Detected background.
bool was_changed_background_image() { return was_changed_("background_image"); }
XProtectedObject *getobject_background_image() { return get_object_("background_image"); }
void setobject_background_image(XProtectedObject *value) { set_object_("background_image", value); }

//Button Restore Backgr
//Restore background immediately.
bool was_changed_restore_now() { return was_changed_("restore_now"); }
int geti_restore_now() { return geti_("restore_now"); }
QString button_restore_now() { return "restore_now"; }

//Checkbox Detection Area Setup
//
bool was_changed_detection_area_setup() { return was_changed_("detection_area_setup"); }
int geti_detection_area_setup() { return geti_("detection_area_setup"); }

//Float X0
//Detection area left.
bool was_changed_x0() { return was_changed_("x0"); }
float getf_x0() { return getf_("x0"); }

//Float X1
//Detection area right.
bool was_changed_x1() { return was_changed_("x1"); }
float getf_x1() { return getf_("x1"); }

//Float Y0
//Detection area top.
bool was_changed_y0() { return was_changed_("y0"); }
float getf_y0() { return getf_("y0"); }

//Float Y1
//Detection area bottom.
bool was_changed_y1() { return was_changed_("y1"); }
float getf_y1() { return getf_("y1"); }

//Out Checkbox Event
//If detector fires.
bool was_changed_event() { return was_changed_("event"); }
int geti_event() { return geti_("event"); }
void seti_event(int value) { seti_("event", value); }


//Const Enum Mode
//Presense - search objects which are differs from background, Motion - detect instant motion.
enum enum_mode {
    mode_Presense = 0,
    mode_Motion = 1,
    mode_N__ = 2
};
bool was_changed_mode() { return was_changed_("mode"); }
enum_mode gete_mode() { return enum_mode(geti_("mode")); }
QString getraw_mode() { return getraw_("mode");}

//Const Int Block Size
//Block size for analysis.
bool was_changed_block_size() { return was_changed_("block_size"); }
int geti_block_size() { return geti_("block_size"); }

//Float Threshold
//Threshold for block detection.
bool was_changed_thresh_in() { return was_changed_("thresh_in"); }
float getf_thresh_in() { return getf_("thresh_in"); }

//Float Block Event
//How much time block event must be to detect it.
bool was_changed_block_event_sec() { return was_changed_("block_event_sec"); }
float getf_block_event_sec() { return getf_("block_event_sec"); }

//Out Int Blocks on
//How many blocks fired now.
bool was_changed_blocks_on() { return was_changed_("blocks_on"); }
int geti_blocks_on() { return geti_("blocks_on"); }
void seti_blocks_on(int value) { seti_("blocks_on", value); }
void increase_int_blocks_on(int increase = 1) { increase_int_("blocks_on", increase); }

//Int Blocks Threshold
//How many blocks must to fire for event.
bool was_changed_blocks_threshold() { return was_changed_("blocks_threshold"); }
int geti_blocks_threshold() { return geti_("blocks_threshold"); }


//Float Background Restore
//If block image is not changed for this time, then background is restored to that image.
bool was_changed_background_restore_sec() { return was_changed_("background_restore_sec"); }
float getf_background_restore_sec() { return getf_("background_restore_sec"); }

//Out Float Restore Timer
//Debug value for restoring.
bool was_changed_restore_timer() { return was_changed_("restore_timer"); }
float getf_restore_timer() { return getf_("restore_timer"); }
void setf_restore_timer(float value) { setf_("restore_timer", value); }

//----------------------------------------------------
//Page Settings
//

//Int Ignore Start Frames
//How much ignore frames at camera start - to let camera do its brightness adjustments.
bool was_changed_ignore_start_frames() { return was_changed_("ignore_start_frames"); }
int geti_ignore_start_frames() { return geti_("ignore_start_frames"); }


//Float Keep On
//How much seconds be on.
bool was_changed_keep_on_sec() { return was_changed_("keep_on_sec"); }
float getf_keep_on_sec() { return getf_("keep_on_sec"); }

//Float Keep Off
//How much seconds be off.
bool was_changed_keep_off_sec() { return was_changed_("keep_off_sec"); }
float getf_keep_off_sec() { return getf_("keep_off_sec"); }


//Text Bang On
//What to do on "On" event.
bool was_changed_bang_on() { return was_changed_("bang_on"); }
QString gets_bang_on() { return gets_("bang_on"); }
QStringList get_strings_bang_on() { return get_strings_("bang_on"); }

//Text Bang Off
//What to do on "Off" event.
bool was_changed_bang_off() { return was_changed_("bang_off"); }
QString gets_bang_off() { return gets_("bang_off"); }
QStringList get_strings_bang_off() { return get_strings_("bang_off"); }

//----------------------------------------------------
