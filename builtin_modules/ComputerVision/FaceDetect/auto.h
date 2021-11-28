//----------------------------------------------------
//Interface for XClassFaceDetect
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Const Enum Image Source
//Should we use real image or test image.
enum enum_send_image_source {
    send_image_source_Image = 0,
    send_image_source_Test_Image = 1,
    send_image_source_N__ = 2
};
bool was_changed_send_image_source() { return was_changed_("send_image_source"); }
enum_send_image_source gete_send_image_source() { return enum_send_image_source(geti_("send_image_source")); }
QString getraw_send_image_source() { return getraw_("send_image_source");}

//Object Input Image
//Image size must be fixed after running.
bool was_changed_input_image() { return was_changed_("input_image"); }
XProtectedObject *getobject_input_image() { return get_object_("input_image"); }
void repaint_input_image() { repaint_("input_image"); }

//Enum Search Faces
//Processing mode.
enum enum_processing_mode {
    processing_mode_Off = 0,
    processing_mode_Each_Frame = 1,
    processing_mode_On_Checkbox = 2,
    processing_mode_N__ = 3
};
bool was_changed_processing_mode() { return was_changed_("processing_mode"); }
enum_processing_mode gete_processing_mode() { return enum_processing_mode(geti_("processing_mode")); }
QString getraw_processing_mode() { return getraw_("processing_mode");}

//Checkbox New Frame
//Usually you should link it with the image update flag.
bool was_changed_process_new_frame() { return was_changed_("process_new_frame"); }
int geti_process_new_frame() { return geti_("process_new_frame"); }
void repaint_process_new_frame() { repaint_("process_new_frame"); }


//Out Int Face Count
//Number of faces detected.
bool was_changed_face_count() { return was_changed_("face_count"); }
int geti_face_count() { return geti_("face_count"); }
void seti_face_count(int value) { seti_("face_count", value); }
void increase_int_face_count(int increase = 1) { increase_int_("face_count", increase); }
void repaint_face_count() { repaint_("face_count"); }


//----------------------------------------------------
//Page Setup
//

//String Cascade File
//Cascade XML file.
bool was_changed_cascade_file() { return was_changed_("cascade_file"); }
QString gets_cascade_file() { return gets_("cascade_file"); }
QStringList get_strings_cascade_file() { return get_strings_("cascade_file"); }
void repaint_cascade_file() { repaint_("cascade_file"); }



//Float Min Size
//
bool was_changed_filter_by_size_min() { return was_changed_("filter_by_size_min"); }
float getf_filter_by_size_min() { return getf_("filter_by_size_min"); }
void repaint_filter_by_size_min() { repaint_("filter_by_size_min"); }


//----------------------------------------------------
//Page Draw
//Draw results at RenderArea.

//Checkbox Draw
//
bool was_changed_draw_enabled() { return was_changed_("draw_enabled"); }
int geti_draw_enabled() { return geti_("draw_enabled"); }
void repaint_draw_enabled() { repaint_("draw_enabled"); }


//Float X
//Drawing X position.
bool was_changed_draw_x() { return was_changed_("draw_x"); }
float getf_draw_x() { return getf_("draw_x"); }
void repaint_draw_x() { repaint_("draw_x"); }

//Float Y
//Drawing Y position.
bool was_changed_draw_y() { return was_changed_("draw_y"); }
float getf_draw_y() { return getf_("draw_y"); }
void repaint_draw_y() { repaint_("draw_y"); }

//Float Size
//Size of drawing, 1 means fit to area
bool was_changed_draw_size() { return was_changed_("draw_size"); }
float getf_draw_size() { return getf_("draw_size"); }
void repaint_draw_size() { repaint_("draw_size"); }

//----------------------------------------------------
