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
//
bool was_changed_show_yolo_setup() { return was_changed_("show_yolo_setup"); }
int geti_show_yolo_setup() { return geti_("show_yolo_setup"); }
void repaint_show_yolo_setup() { repaint_("show_yolo_setup"); }

//String Python String
//Data from Python with YOLO positions.
bool was_changed_python_string() { return was_changed_("python_string"); }
QString gets_python_string() { return gets_("python_string"); }
QStringList get_strings_python_string() { return get_strings_("python_string"); }
void repaint_python_string() { repaint_("python_string"); }

//Int Python Received
//Number of data packets received from Python - used for writing "Running..." while waiting.
bool was_changed_python_received() { return was_changed_("python_received"); }
int geti_python_received() { return geti_("python_received"); }
void repaint_python_received() { repaint_("python_received"); }


//----------------------------------------------------
