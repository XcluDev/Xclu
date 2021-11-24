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
bool was_changed_send_image() { return was_changed_("send_image"); }
XProtectedObject *getobject_send_image() { return get_object_("send_image"); }
void repaint_send_image() { repaint_("send_image"); }

//Enum Processing
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
bool was_changed_face_count0() { return was_changed_("face_count0"); }
int geti_face_count0() { return geti_("face_count0"); }
void seti_face_count0(int value) { seti_("face_count0", value); }
void increase_int_face_count0(int increase = 1) { increase_int_("face_count0", increase); }
void repaint_face_count0() { repaint_("face_count0"); }


//Checkbox Filter By Size
//Apply size filter.
bool was_changed_filter_by_size() { return was_changed_("filter_by_size"); }
int geti_filter_by_size() { return geti_("filter_by_size"); }
void repaint_filter_by_size() { repaint_("filter_by_size"); }

//Float Min Size
//
bool was_changed_filter_by_size_min() { return was_changed_("filter_by_size_min"); }
float getf_filter_by_size_min() { return getf_("filter_by_size_min"); }
void repaint_filter_by_size_min() { repaint_("filter_by_size_min"); }

//Float Max Size
//
bool was_changed_filter_by_size_max() { return was_changed_("filter_by_size_max"); }
float getf_filter_by_size_max() { return getf_("filter_by_size_max"); }
void repaint_filter_by_size_max() { repaint_("filter_by_size_max"); }


//----------------------------------------------------
