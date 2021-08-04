//----------------------------------------------------
//Interface for XClassMadRobot
//Created automatically.
//----------------------------------------------------
//Page YOLO
//

//Checkbox Input Image
//
bool was_changed_show_input_image() { return was_changed_("show_input_image"); }
int geti_show_input_image() { return geti_("show_input_image"); }
void repaint_show_input_image() { repaint_("show_input_image"); }

//Object Image
//Input webcamera image.
bool was_changed_input_image() { return was_changed_("input_image"); }
XProtectedObject *getobject_input_image() { return get_object_("input_image"); }
void repaint_input_image() { repaint_("input_image"); }

//Checkbox Cropping Setup
//
bool was_changed_show_cropping() { return was_changed_("show_cropping"); }
int geti_show_cropping() { return geti_("show_cropping"); }
void repaint_show_cropping() { repaint_("show_cropping"); }

//Int crop x0
//
bool was_changed_crop_x0() { return was_changed_("crop_x0"); }
int geti_crop_x0() { return geti_("crop_x0"); }
void repaint_crop_x0() { repaint_("crop_x0"); }

//Int crop y0
//
bool was_changed_crop_y0() { return was_changed_("crop_y0"); }
int geti_crop_y0() { return geti_("crop_y0"); }
void repaint_crop_y0() { repaint_("crop_y0"); }

//Int crop x1
//
bool was_changed_crop_x1() { return was_changed_("crop_x1"); }
int geti_crop_x1() { return geti_("crop_x1"); }
void repaint_crop_x1() { repaint_("crop_x1"); }

//Int crop y1
//
bool was_changed_crop_y1() { return was_changed_("crop_y1"); }
int geti_crop_y1() { return geti_("crop_y1"); }
void repaint_crop_y1() { repaint_("crop_y1"); }


//Int resize x
//
bool was_changed_resize_x() { return was_changed_("resize_x"); }
int geti_resize_x() { return geti_("resize_x"); }
void repaint_resize_x() { repaint_("resize_x"); }

//Int resize y
//
bool was_changed_resize_y() { return was_changed_("resize_y"); }
int geti_resize_y() { return geti_("resize_y"); }
void repaint_resize_y() { repaint_("resize_y"); }


//Checkbox YOLO Image
//
bool was_changed_show_yolo_image() { return was_changed_("show_yolo_image"); }
int geti_show_yolo_image() { return geti_("show_yolo_image"); }
void repaint_show_yolo_image() { repaint_("show_yolo_image"); }

//Out Object Image
//Image for sending to YOLO.
bool was_changed_yolo_image() { return was_changed_("yolo_image"); }
XProtectedObject *getobject_yolo_image() { return get_object_("yolo_image"); }
void setobject_yolo_image(XProtectedObject *value) { set_object_("yolo_image", value); }
void setobject_yolo_image(XProtectedObject &value) { set_object_("yolo_image", value); }
void repaint_yolo_image() { repaint_("yolo_image"); }

//Checkbox YOLO Setup
//Setting connection with YOLO. You need to run it manually: ./_image_yolov3.sh
bool was_changed_show_yolo_setup() { return was_changed_("show_yolo_setup"); }
int geti_show_yolo_setup() { return geti_("show_yolo_setup"); }
void repaint_show_yolo_setup() { repaint_("show_yolo_setup"); }

//String Yolo write image
//
bool was_changed_yolo_write_image() { return was_changed_("yolo_write_image"); }
QString gets_yolo_write_image() { return gets_("yolo_write_image"); }
QStringList get_strings_yolo_write_image() { return get_strings_("yolo_write_image"); }
void repaint_yolo_write_image() { repaint_("yolo_write_image"); }

//String Yolo read txt
//
bool was_changed_yolo_read_TXT() { return was_changed_("yolo_read_TXT"); }
QString gets_yolo_read_TXT() { return gets_("yolo_read_TXT"); }
QStringList get_strings_yolo_read_TXT() { return get_strings_("yolo_read_TXT"); }
void repaint_yolo_read_TXT() { repaint_("yolo_read_TXT"); }


//Out Text YOLO Data
//Result obtained from YOLO
bool was_changed_yolo_data() { return was_changed_("yolo_data"); }
QString gets_yolo_data() { return gets_("yolo_data"); }
QStringList get_strings_yolo_data() { return get_strings_("yolo_data"); }
void sets_yolo_data(QString value) { sets_("yolo_data", value); }
void clear_string_yolo_data() { clear_string_("yolo_data"); }
void append_string_yolo_data(QString v, int extra_new_lines_count = 0) { append_string_("yolo_data", v, extra_new_lines_count); }
void append_string_yolo_data(QStringList v, int extra_new_lines_count = 0) { append_string_("yolo_data", v, extra_new_lines_count); }
void repaint_yolo_data() { repaint_("yolo_data"); }


//----------------------------------------------------
//Page Robot
//Motion and grabbing.


//Checkbox Pick Up
//Point for pick up.
bool was_changed_show_pick_up() { return was_changed_("show_pick_up"); }
int geti_show_pick_up() { return geti_("show_pick_up"); }
void repaint_show_pick_up() { repaint_("show_pick_up"); }

//Float Cross X
//
bool was_changed_cross_x() { return was_changed_("cross_x"); }
float getf_cross_x() { return getf_("cross_x"); }
void repaint_cross_x() { repaint_("cross_x"); }

//Float Cross Y
//
bool was_changed_cross_y() { return was_changed_("cross_y"); }
float getf_cross_y() { return getf_("cross_y"); }
void repaint_cross_y() { repaint_("cross_y"); }

//Float Cross W
//
bool was_changed_cross_w() { return was_changed_("cross_w"); }
float getf_cross_w() { return getf_("cross_w"); }
void repaint_cross_w() { repaint_("cross_w"); }

//Float Cross H
//
bool was_changed_cross_h() { return was_changed_("cross_h"); }
float getf_cross_h() { return getf_("cross_h"); }
void repaint_cross_h() { repaint_("cross_h"); }

//Int Cover
//How much area must be covered to enable picking up.
bool was_changed_cross_cover() { return was_changed_("cross_cover"); }
int geti_cross_cover() { return geti_("cross_cover"); }
void repaint_cross_cover() { repaint_("cross_cover"); }


//Checkbox Arduino
//Sending data to Arduino
bool was_changed_show_arduino() { return was_changed_("show_arduino"); }
int geti_show_arduino() { return geti_("show_arduino"); }
void repaint_show_arduino() { repaint_("show_arduino"); }

//String Pick Up
//Arduino button.
bool was_changed_ard_pick_up() { return was_changed_("ard_pick_up"); }
QString gets_ard_pick_up() { return gets_("ard_pick_up"); }
QStringList get_strings_ard_pick_up() { return get_strings_("ard_pick_up"); }
void repaint_ard_pick_up() { repaint_("ard_pick_up"); }

//String Forward
//Arduino button.
bool was_changed_ard_forw() { return was_changed_("ard_forw"); }
QString gets_ard_forw() { return gets_("ard_forw"); }
QStringList get_strings_ard_forw() { return get_strings_("ard_forw"); }
void repaint_ard_forw() { repaint_("ard_forw"); }

//String Backward
//
bool was_changed_ard_back() { return was_changed_("ard_back"); }
QString gets_ard_back() { return gets_("ard_back"); }
QStringList get_strings_ard_back() { return get_strings_("ard_back"); }
void repaint_ard_back() { repaint_("ard_back"); }

//String Left
//
bool was_changed_ard_left() { return was_changed_("ard_left"); }
QString gets_ard_left() { return gets_("ard_left"); }
QStringList get_strings_ard_left() { return get_strings_("ard_left"); }
void repaint_ard_left() { repaint_("ard_left"); }

//String Right
//
bool was_changed_ard_right() { return was_changed_("ard_right"); }
QString gets_ard_right() { return gets_("ard_right"); }
QStringList get_strings_ard_right() { return get_strings_("ard_right"); }
void repaint_ard_right() { repaint_("ard_right"); }

//String Stop
//
bool was_changed_ard_stop() { return was_changed_("ard_stop"); }
QString gets_ard_stop() { return gets_("ard_stop"); }
QStringList get_strings_ard_stop() { return get_strings_("ard_stop"); }
void repaint_ard_stop() { repaint_("ard_stop"); }


//Button Start!
//Run!
bool was_changed_btn_mind_start() { return was_changed_("btn_mind_start"); }
int geti_btn_mind_start() { return geti_("btn_mind_start"); }
void repaint_btn_mind_start() { repaint_("btn_mind_start"); }
QString button_btn_mind_start() { return "btn_mind_start"; }

//Button Stop
//
bool was_changed_btn_mind_stop() { return was_changed_("btn_mind_stop"); }
int geti_btn_mind_stop() { return geti_("btn_mind_stop"); }
void repaint_btn_mind_stop() { repaint_("btn_mind_stop"); }
QString button_btn_mind_stop() { return "btn_mind_stop"; }

//Checkbox auto start
//
bool was_changed_auto_start() { return was_changed_("auto_start"); }
int geti_auto_start() { return geti_("auto_start"); }
void repaint_auto_start() { repaint_("auto_start"); }


//Button Pick Up
//
bool was_changed_btn_pick_up() { return was_changed_("btn_pick_up"); }
int geti_btn_pick_up() { return geti_("btn_pick_up"); }
void repaint_btn_pick_up() { repaint_("btn_pick_up"); }
QString button_btn_pick_up() { return "btn_pick_up"; }

//Button Forward
//
bool was_changed_btn_forw() { return was_changed_("btn_forw"); }
int geti_btn_forw() { return geti_("btn_forw"); }
void repaint_btn_forw() { repaint_("btn_forw"); }
QString button_btn_forw() { return "btn_forw"; }

//Button Left
//
bool was_changed_btn_left() { return was_changed_("btn_left"); }
int geti_btn_left() { return geti_("btn_left"); }
void repaint_btn_left() { repaint_("btn_left"); }
QString button_btn_left() { return "btn_left"; }

//Button Right
//
bool was_changed_btn_right() { return was_changed_("btn_right"); }
int geti_btn_right() { return geti_("btn_right"); }
void repaint_btn_right() { repaint_("btn_right"); }
QString button_btn_right() { return "btn_right"; }

//Button Stop
//
bool was_changed_btn_stop() { return was_changed_("btn_stop"); }
int geti_btn_stop() { return geti_("btn_stop"); }
void repaint_btn_stop() { repaint_("btn_stop"); }
QString button_btn_stop() { return "btn_stop"; }


//----------------------------------------------------
