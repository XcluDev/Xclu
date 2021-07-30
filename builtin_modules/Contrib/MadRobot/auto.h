//----------------------------------------------------
//Interface for XClassxclucpp
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Object Image
//Webcamera image.
bool was_changed_input_image() { return was_changed_("input_image"); }
XProtectedObject *getobject_input_image() { return get_object_("input_image"); }
//String Python String
//Data from Python with face position and emotions array.
bool was_changed_python_string() { return was_changed_("python_string"); }
QString gets_python_string() { return gets_("python_string"); }
QStringList get_strings_python_string() { return get_strings_("python_string"); }

//Int Python Received
//Number of data packets received from Python - used for writing "Running..." while waiting.
bool was_changed_python_received() { return was_changed_("python_received"); }
int geti_python_received() { return geti_("python_received"); }


//Int Image Face W
//Width of image sent to python for processing.
bool was_changed_image_face_w() { return was_changed_("image_face_w"); }
int geti_image_face_w() { return geti_("image_face_w"); }

//Int Image FaceH
//Height of image sent to python for processing.
bool was_changed_image_face_h() { return was_changed_("image_face_h"); }
int geti_image_face_h() { return geti_("image_face_h"); }


//Const String Emotions List
//List of emotions.
bool was_changed_emotions_list() { return was_changed_("emotions_list"); }
QString gets_emotions_list() { return gets_("emotions_list"); }
QStringList get_strings_emotions_list() { return get_strings_("emotions_list"); }

//Out Int Num Emotions
//Number of emotions.
bool was_changed_num_emotions() { return was_changed_("num_emotions"); }
int geti_num_emotions() { return geti_("num_emotions"); }
void seti_num_emotions(int value) { seti_("num_emotions", value); }
void increase_int_num_emotions(int increase = 1) { increase_int_("num_emotions", increase); }

//----------------------------------------------------
//Page Global
//

//Int Spacing
//Spacing between squares.
bool was_changed_spacing() { return was_changed_("spacing"); }
int geti_spacing() { return geti_("spacing"); }

//Float Border Color
//Color of border.
bool was_changed_border_color() { return was_changed_("border_color"); }
float getf_border_color() { return getf_("border_color"); }


//Float Track Red
//Red component for face track.
bool was_changed_track_red() { return was_changed_("track_red"); }
float getf_track_red() { return getf_("track_red"); }

//Float Track Green
//Green component for face track.
bool was_changed_track_green() { return was_changed_("track_green"); }
float getf_track_green() { return getf_("track_green"); }

//Float Track Blue
//Blue component for face track.
bool was_changed_track_blue() { return was_changed_("track_blue"); }
float getf_track_blue() { return getf_("track_blue"); }


//Float Field Size
//Relative size of attractor field.
bool was_changed_attr_field_size() { return was_changed_("attr_field_size"); }
float getf_attr_field_size() { return getf_("attr_field_size"); }


//Text Attr Points
//Positions of emotions on attractor plane, [0..1]
bool was_changed_attr_points() { return was_changed_("attr_points"); }
QString gets_attr_points() { return gets_("attr_points"); }
QStringList get_strings_attr_points() { return get_strings_("attr_points"); }

//----------------------------------------------------
//Page Vector Field
//

//Float Attr R0
//Minimal radius of attractor point.
bool was_changed_attr_r0() { return was_changed_("attr_r0"); }
float getf_attr_r0() { return getf_("attr_r0"); }

//Float Attr R1
//Maximal radius of attractor point.
bool was_changed_attr_r1() { return was_changed_("attr_r1"); }
float getf_attr_r1() { return getf_("attr_r1"); }

//Float Attr Color
//Color of attractor point.
bool was_changed_attr_color() { return was_changed_("attr_color"); }
float getf_attr_color() { return getf_("attr_color"); }

//Float Label Color
//Color of attractor label.
bool was_changed_attr_font_color() { return was_changed_("attr_font_color"); }
float getf_attr_font_color() { return getf_("attr_font_color"); }

//Int Label Font
//Attractor label font size.
bool was_changed_attr_font_size() { return was_changed_("attr_font_size"); }
int geti_attr_font_size() { return geti_("attr_font_size"); }

//Float Label Y
//Attractor label position.
bool was_changed_attr_font_y() { return was_changed_("attr_font_y"); }
float getf_attr_font_y() { return getf_("attr_font_y"); }


//Int Vector Grid
//Number of grid points of vector field.
bool was_changed_vf_n() { return was_changed_("vf_n"); }
int geti_vf_n() { return geti_("vf_n"); }

//Float Vector Len
//Drawing length of vector.
bool was_changed_vf_len() { return was_changed_("vf_len"); }
float getf_vf_len() { return getf_("vf_len"); }

//Float Vector Color
//Vector color.
bool was_changed_vf_color() { return was_changed_("vf_color"); }
float getf_vf_color() { return getf_("vf_color"); }

//Float Vector Base R
//Vector base radius.
bool was_changed_vf_base_rad() { return was_changed_("vf_base_rad"); }
float getf_vf_base_rad() { return getf_("vf_base_rad"); }



//Float vf safe
//Denominator adder.
bool was_changed_vf_safe() { return was_changed_("vf_safe"); }
float getf_vf_safe() { return getf_("vf_safe"); }

//----------------------------------------------------
//Page Point
//Flying point.

//Float Pnt Rad
//Radius of flying point.
bool was_changed_pnt_rad() { return was_changed_("pnt_rad"); }
float getf_pnt_rad() { return getf_("pnt_rad"); }

//Float Pnt Color
//Color of flying point.
bool was_changed_pnt_color() { return was_changed_("pnt_color"); }
float getf_pnt_color() { return getf_("pnt_color"); }



//Float Force
//Force coefficient.
bool was_changed_pnt_force() { return was_changed_("pnt_force"); }
float getf_pnt_force() { return getf_("pnt_force"); }

//Float Friction
//Friction coefficient.
bool was_changed_pnt_friction() { return was_changed_("pnt_friction"); }
float getf_pnt_friction() { return getf_("pnt_friction"); }

//----------------------------------------------------
//Page Morph
//Morphing - third square.

//Checkbox Main Settings
//Global morph settings - normally not need to change.
bool was_changed_morph_global_setup() { return was_changed_("morph_global_setup"); }
int geti_morph_global_setup() { return geti_("morph_global_setup"); }


//Float Crop Speed
//Moving of cropped image.
bool was_changed_morph_crop_speed() { return was_changed_("morph_crop_speed"); }
float getf_morph_crop_speed() { return getf_("morph_crop_speed"); }

//Const Int morph image size
//Size of image for morphing.
bool was_changed_morph_size() { return was_changed_("morph_size"); }
int geti_morph_size() { return geti_("morph_size"); }


//Float Bright Slider
//Additional brightness regulator.
bool was_changed_morph_brightness_slider() { return was_changed_("morph_brightness_slider"); }
float getf_morph_brightness_slider() { return getf_("morph_brightness_slider"); }

//Checkbox Use Presets
//Use presets or manual control.
bool was_changed_morph_use_presets() { return was_changed_("morph_use_presets"); }
int geti_morph_use_presets() { return geti_("morph_use_presets"); }


//Float Blur
//Blurring webcam image.
bool was_changed_morph_blur() { return was_changed_("morph_blur"); }
float getf_morph_blur() { return getf_("morph_blur"); }

//Float Flow0
//Motion of old image.
bool was_changed_morph_flow0() { return was_changed_("morph_flow0"); }
float getf_morph_flow0() { return getf_("morph_flow0"); }

//Float Flow1
//Motion of old image.
bool was_changed_morph_flow1() { return was_changed_("morph_flow1"); }
float getf_morph_flow1() { return getf_("morph_flow1"); }

//Float Flow Blend0
//Blending of moved old image.
bool was_changed_morph_flow_blend0() { return was_changed_("morph_flow_blend0"); }
float getf_morph_flow_blend0() { return getf_("morph_flow_blend0"); }

//Float Flow Blend1
//Blending of new image.
bool was_changed_morph_flow_blend1() { return was_changed_("morph_flow_blend1"); }
float getf_morph_flow_blend1() { return getf_("morph_flow_blend1"); }


//Float Brightness
//Tool for increasing the brightness.
bool was_changed_morph_brightness() { return was_changed_("morph_brightness"); }
float getf_morph_brightness() { return getf_("morph_brightness"); }

//Float Contrast
//Tool for changing contrast.
bool was_changed_morph_contrast() { return was_changed_("morph_contrast"); }
float getf_morph_contrast() { return getf_("morph_contrast"); }

//Float Saturation
//Tool for changing saturation.
bool was_changed_morph_saturation() { return was_changed_("morph_saturation"); }
float getf_morph_saturation() { return getf_("morph_saturation"); }


//Out Float Blur
//Blurring webcam image.
bool was_changed_morph_blur_() { return was_changed_("morph_blur_"); }
float getf_morph_blur_() { return getf_("morph_blur_"); }
void setf_morph_blur_(float value) { setf_("morph_blur_", value); }

//Out Float Flow0
//Motion of old image.
bool was_changed_morph_flow0_() { return was_changed_("morph_flow0_"); }
float getf_morph_flow0_() { return getf_("morph_flow0_"); }
void setf_morph_flow0_(float value) { setf_("morph_flow0_", value); }

//Out Float Flow1
//Motion of old image.
bool was_changed_morph_flow1_() { return was_changed_("morph_flow1_"); }
float getf_morph_flow1_() { return getf_("morph_flow1_"); }
void setf_morph_flow1_(float value) { setf_("morph_flow1_", value); }

//Out Float Flow Blend0
//Blending of moved old image.
bool was_changed_morph_flow_blend0_() { return was_changed_("morph_flow_blend0_"); }
float getf_morph_flow_blend0_() { return getf_("morph_flow_blend0_"); }
void setf_morph_flow_blend0_(float value) { setf_("morph_flow_blend0_", value); }

//Out Float Flow Blend1
//Blending of new image.
bool was_changed_morph_flow_blend1_() { return was_changed_("morph_flow_blend1_"); }
float getf_morph_flow_blend1_() { return getf_("morph_flow_blend1_"); }
void setf_morph_flow_blend1_(float value) { setf_("morph_flow_blend1_", value); }


//Out Float Brightness
//Tool for increasing the brightness.
bool was_changed_morph_brightness_() { return was_changed_("morph_brightness_"); }
float getf_morph_brightness_() { return getf_("morph_brightness_"); }
void setf_morph_brightness_(float value) { setf_("morph_brightness_", value); }

//Out Float Contrast
//Tool for changing contrast.
bool was_changed_morph_contrast_() { return was_changed_("morph_contrast_"); }
float getf_morph_contrast_() { return getf_("morph_contrast_"); }
void setf_morph_contrast_(float value) { setf_("morph_contrast_", value); }

//Out Float Saturation
//Tool for changing saturation.
bool was_changed_morph_saturation_() { return was_changed_("morph_saturation_"); }
float getf_morph_saturation_() { return getf_("morph_saturation_"); }
void setf_morph_saturation_(float value) { setf_("morph_saturation_", value); }


//Checkbox Test Emotion
//Should we run test emotion.
bool was_changed_test_emotion() { return was_changed_("test_emotion"); }
int geti_test_emotion() { return geti_("test_emotion"); }

//Enum Emotion
//Choosen emotion for testing
enum enum_test_emotion_choose {
    test_emotion_choose_angry = 0,
    test_emotion_choose_disgust = 1,
    test_emotion_choose_scared = 2,
    test_emotion_choose_happy = 3,
    test_emotion_choose_sad = 4,
    test_emotion_choose_surprised = 5,
    test_emotion_choose_neutral = 6,
    test_emotion_choose_N__ = 7
};
bool was_changed_test_emotion_choose() { return was_changed_("test_emotion_choose"); }
enum_test_emotion_choose gete_test_emotion_choose() { return enum_test_emotion_choose(geti_("test_emotion_choose")); }
QString getraw_test_emotion_choose() { return getraw_("test_emotion_choose");}


//Text Presets
//Presets for morph.
bool was_changed_morph_presets() { return was_changed_("morph_presets"); }
QString gets_morph_presets() { return gets_("morph_presets"); }
QStringList get_strings_morph_presets() { return get_strings_("morph_presets"); }

//----------------------------------------------------
//Page Sound
//Sound synth.

//Text Presets1
//Presets for the first generator.
bool was_changed_sound_presets1() { return was_changed_("sound_presets1"); }
QString gets_sound_presets1() { return gets_("sound_presets1"); }
QStringList get_strings_sound_presets1() { return get_strings_("sound_presets1"); }

//Text Presets2
//Presets for the second generator.
bool was_changed_sound_presets2() { return was_changed_("sound_presets2"); }
QString gets_sound_presets2() { return gets_("sound_presets2"); }
QStringList get_strings_sound_presets2() { return get_strings_("sound_presets2"); }


//Out String Sound1
//Data for the first sound. Depends on Morph->Emotion.
bool was_changed_sound_data1() { return was_changed_("sound_data1"); }
QString gets_sound_data1() { return gets_("sound_data1"); }
QStringList get_strings_sound_data1() { return get_strings_("sound_data1"); }
void sets_sound_data1(QString value) { sets_("sound_data1", value); }
void clear_string_sound_data1() { clear_string_("sound_data1"); }
void append_string_sound_data1(QString v, int extra_new_lines_count = 0) { append_string_("sound_data1", v, extra_new_lines_count); }
void append_string_sound_data1(QStringList v, int extra_new_lines_count = 0) { append_string_("sound_data1", v, extra_new_lines_count); }

//Out String Sound2
//Data for the second sound. Depends on Morph->Emotion.
bool was_changed_sound_data2() { return was_changed_("sound_data2"); }
QString gets_sound_data2() { return gets_("sound_data2"); }
QStringList get_strings_sound_data2() { return get_strings_("sound_data2"); }
void sets_sound_data2(QString value) { sets_("sound_data2", value); }
void clear_string_sound_data2() { clear_string_("sound_data2"); }
void append_string_sound_data2(QString v, int extra_new_lines_count = 0) { append_string_("sound_data2", v, extra_new_lines_count); }
void append_string_sound_data2(QStringList v, int extra_new_lines_count = 0) { append_string_("sound_data2", v, extra_new_lines_count); }

//----------------------------------------------------
