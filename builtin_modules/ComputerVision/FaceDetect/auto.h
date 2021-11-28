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
//Low boundary for the size of smallest detected face, 0 - not use the boundary.
bool was_changed_face_min_size() { return was_changed_("face_min_size"); }
float getf_face_min_size() { return getf_("face_min_size"); }
void repaint_face_min_size() { repaint_("face_min_size"); }


//Checkbox Canny Pruning
//Regions without edges are ignored.
bool was_changed_haar_canny_pruning() { return was_changed_("haar_canny_pruning"); }
int geti_haar_canny_pruning() { return geti_("haar_canny_pruning"); }
void repaint_haar_canny_pruning() { repaint_("haar_canny_pruning"); }

//Checkbox Scale Image
//Scale the image rather than the detector (sometimes yields speed increases).
bool was_changed_haar_scale_image() { return was_changed_("haar_scale_image"); }
int geti_haar_scale_image() { return geti_("haar_scale_image"); }
void repaint_haar_scale_image() { repaint_("haar_scale_image"); }

//Checkbox Only Biggest Face
//Only return the largest result.
bool was_changed_haar_only_biggest_face() { return was_changed_("haar_only_biggest_face"); }
int geti_haar_only_biggest_face() { return geti_("haar_only_biggest_face"); }
void repaint_haar_only_biggest_face() { repaint_("haar_only_biggest_face"); }

//Checkbox Rough Search
//When Only Biggest Face is enabled, stop at the first scale for which multiple results are found.
bool was_changed_haar_rough_search() { return was_changed_("haar_rough_search"); }
int geti_haar_rough_search() { return geti_("haar_rough_search"); }
void repaint_haar_rough_search() { repaint_("haar_rough_search"); }


//Float Haar Scale
//The default value is 1.1. For accuracy, bring it closer but not equal to 1.0. To make it faster, use a larger value.
bool was_changed_haar_scale() { return was_changed_("haar_scale"); }
float getf_haar_scale() { return getf_("haar_scale"); }
void repaint_haar_scale() { repaint_("haar_scale"); }


//Int Haar Neighbors
//How many neighbors can be grouped into a face, 0 means no grouping, and can use Threshold.
bool was_changed_haar_neighbors() { return was_changed_("haar_neighbors"); }
int geti_haar_neighbors() { return geti_("haar_neighbors"); }
void repaint_haar_neighbors() { repaint_("haar_neighbors"); }


//Int Haar Threshold
//How much rectangles must cover a pixel to treat it as a face. Used when "Haar neighbors" is 0.
bool was_changed_haar_threshold() { return was_changed_("haar_threshold"); }
int geti_haar_threshold() { return geti_("haar_threshold"); }
void repaint_haar_threshold() { repaint_("haar_threshold"); }


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
