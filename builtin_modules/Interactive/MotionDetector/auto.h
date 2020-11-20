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

//----------------------------------------------------
//Page Settings
//

//----------------------------------------------------
