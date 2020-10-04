//----------------------------------------------------
//Interface for XClassSynthFromImage
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Enum Image Source
//Image source - file or image from other module.
enum enum_image_source {
    image_source_Image_File = 0,
    image_source_Other_Module_Image = 1,
    image_source_N__ = 2
};
bool was_changed_image_source() { return was_changed_("image_source"); }
enum_image_source gete_image_source() { return enum_image_source(geti_("image_source")); }

//String Image File Name
//Image File.
bool was_changed_image_file() { return was_changed_("image_file"); }
QString gets_image_file() { return gets_("image_file"); }
QStringList get_strings_image_file() { return get_strings_("image_file"); }

//String Image Link
//Reference to image in another module.
bool was_changed_image_link() { return was_changed_("image_link"); }
QString gets_image_link() { return gets_("image_link"); }
QStringList get_strings_image_link() { return get_strings_("image_link"); }

//Out Object Image
//Input image.
bool was_changed_image() { return was_changed_("image"); }
XProtectedStruct *getstruct_image() { return get_struct_("image"); }


//Checkbox Scan Area Setup
//Scanning area setup.
bool was_changed_scan_area_setup() { return was_changed_("scan_area_setup"); }
int geti_scan_area_setup() { return geti_("scan_area_setup"); }

//Enum Scan Shape
//Shape of scanning.
enum enum_scan_shape {
    scan_shape_Horizontal_Rectangle = 0,
    scan_shape_Vertical_Rectangle = 1,
    scan_shape_Radar = 2,
    scan_shape_N__ = 3
};
bool was_changed_scan_shape() { return was_changed_("scan_shape"); }
enum_scan_shape gete_scan_shape() { return enum_scan_shape(geti_("scan_shape")); }

//Float Scan X
//X position of scanning area's center.
bool was_changed_scan_x() { return was_changed_("scan_x"); }
float getf_scan_x() { return getf_("scan_x"); }

//Float Scan Y
//Y position of scanning area's center.
bool was_changed_scan_y() { return was_changed_("scan_y"); }
float getf_scan_y() { return getf_("scan_y"); }

//Float Scan Rad X
//X radius of scanning area.
bool was_changed_rad_x() { return was_changed_("rad_x"); }
float getf_rad_x() { return getf_("rad_x"); }

//Float Scan Rad Y
//Y radius of scanning area.
bool was_changed_rad_y() { return was_changed_("rad_y"); }
float getf_rad_y() { return getf_("rad_y"); }

//Float Scan Rad X
//Radius of scanning area.
bool was_changed_rad() { return was_changed_("rad"); }
float getf_rad() { return getf_("rad"); }


//Checkbox Interpretation
//Tools for transforming brightness value to sound value.
bool was_changed_interpr() { return was_changed_("interpr"); }
int geti_interpr() { return geti_("interpr"); }

//Out Object Image Sound
//Image depicting the sound values.
bool was_changed_image_sound() { return was_changed_("image_sound"); }
XProtectedStruct *getstruct_image_sound() { return get_struct_("image_sound"); }

//Out Float Min Brightness
//Maximal brightness value.
bool was_changed_min_value() { return was_changed_("min_value"); }
float getf_min_value() { return getf_("min_value"); }
void setf_min_value(float value) { setf_("min_value", value); }

//Out Float Max Brightness
//Maximal brightness value.
bool was_changed_max_value() { return was_changed_("max_value"); }
float getf_max_value() { return getf_("max_value"); }
void setf_max_value(float value) { setf_("max_value", value); }

//Out Float Mean Brightness
//Statistical center.
bool was_changed_center_value() { return was_changed_("center_value"); }
float getf_center_value() { return getf_("center_value"); }
void setf_center_value(float value) { setf_("center_value", value); }

//Out Float Brightness Range
//Statistical range.
bool was_changed_range_value() { return was_changed_("range_value"); }
float getf_range_value() { return getf_("range_value"); }
void setf_range_value(float value) { setf_("range_value", value); }

//Float Contrast
//Contrast parameter for converting brightness to sound values. Center is defined automatically.
bool was_changed_contrast() { return was_changed_("contrast"); }
float getf_contrast() { return getf_("contrast"); }


//Enum Interpretation Method
//Interpretation method: pixels slices are PCM samples or sonogram.
enum enum_method {
    method_PCM = 0,
    method_Sonogram = 1,
    method_N__ = 2
};
bool was_changed_method() { return was_changed_("method"); }
enum_method gete_method() { return enum_method(geti_("method")); }

//Enum Scan Speed Measure
//Speed of scanning.
enum enum_pcm_speed_measure {
    pcm_speed_measure_Hz = 0,
    pcm_speed_measure_Seconds = 1,
    pcm_speed_measure_MIDI_note = 2,
    pcm_speed_measure_N__ = 3
};
bool was_changed_pcm_speed_measure() { return was_changed_("pcm_speed_measure"); }
enum_pcm_speed_measure gete_pcm_speed_measure() { return enum_pcm_speed_measure(geti_("pcm_speed_measure")); }

//Float Speed
//
bool was_changed_pcm_speed_hz() { return was_changed_("pcm_speed_hz"); }
float getf_pcm_speed_hz() { return getf_("pcm_speed_hz"); }

//Float Speed
//
bool was_changed_pcm_speed_sec() { return was_changed_("pcm_speed_sec"); }
float getf_pcm_speed_sec() { return getf_("pcm_speed_sec"); }

//Enum Scan Speed Measure
//Speed of scanning.
enum enum_sono_speed_measure {
    sono_speed_measure_Seconds = 0,
    sono_speed_measure_BPM = 1,
    sono_speed_measure_N__ = 2
};
bool was_changed_sono_speed_measure() { return was_changed_("sono_speed_measure"); }
enum_sono_speed_measure gete_sono_speed_measure() { return enum_sono_speed_measure(geti_("sono_speed_measure")); }

//Float Speed Seconds
//
bool was_changed_sono_speed_sec() { return was_changed_("sono_speed_sec"); }
float getf_sono_speed_sec() { return getf_("sono_speed_sec"); }

//Int Oscillators
//Number of oscillators for sound generation.
bool was_changed_oscillators() { return was_changed_("oscillators"); }
int geti_oscillators() { return geti_("oscillators"); }

//Enum Oscillator Shape
//Waveshape of the ocsillator.
enum enum_oscillator_shape {
    oscillator_shape_Sine = 0,
    oscillator_shape_Square = 1,
    oscillator_shape_N__ = 2
};
bool was_changed_oscillator_shape() { return was_changed_("oscillator_shape"); }
enum_oscillator_shape gete_oscillator_shape() { return enum_oscillator_shape(geti_("oscillator_shape")); }

//Int MIDI Note Low
//Note for setting frequency of low values.
bool was_changed_note_low() { return was_changed_("note_low"); }
int geti_note_low() { return geti_("note_low"); }

//Int MIDI Note High
//Note for setting frequency of high values.
bool was_changed_note_high() { return was_changed_("note_high"); }
int geti_note_high() { return geti_("note_high"); }

//----------------------------------------------------
