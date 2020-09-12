//----------------------------------------------------
//Interface for XClassSynthFromImage
//Created automatically at 2020.09.12 21:37:02
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
enum_image_source en_image_source() { return enum_image_source(geti("image_source")); }

//String Image File Name
//Image File.
QString s_image_file() { return gets("image_file"); }

//String Image Link
//Reference to image in another module.
QString s_image_link() { return gets("image_link"); }

//Out Object Image
//Input image.
XDict *obj_image() { return get_object("image"); }


//Checkbox Scan Area Setup
//Scanning area setup.
int i_scan_area_setup() { return geti("scan_area_setup"); }

//Enum Scan Shape
//Shape of scanning.

enum enum_scan_shape {
    scan_shape_Horizontal_Rectangle = 0,
    scan_shape_Vertical_Rectangle = 1,
    scan_shape_Radar = 2,
    scan_shape_N__ = 3
};
enum_scan_shape en_scan_shape() { return enum_scan_shape(geti("scan_shape")); }

//Float Scan X
//X position of scanning area's center.
float f_scan_x() { return getf("scan_x"); }

//Float Scan Y
//Y position of scanning area's center.
float f_scan_y() { return getf("scan_y"); }

//Float Scan Rad X
//X radius of scanning area.
float f_rad_x() { return getf("rad_x"); }

//Float Scan Rad Y
//Y radius of scanning area.
float f_rad_y() { return getf("rad_y"); }

//Float Scan Rad X
//Radius of scanning area.
float f_rad() { return getf("rad"); }


//Checkbox Interpretation
//Tools for transforming brightness value to sound value.
int i_interpr() { return geti("interpr"); }

//Out Object Image Sound
//Image depicting the sound values.
XDict *obj_image_sound() { return get_object("image_sound"); }

//Out Float Min Brightness
//Maximal brightness value.
float f_min_value() { return getf("min_value"); }
void f_min_value(float value) { setf("min_value", value); }

//Out Float Max Brightness
//Maximal brightness value.
float f_max_value() { return getf("max_value"); }
void f_max_value(float value) { setf("max_value", value); }

//Out Float Mean Brightness
//Statistical center.
float f_center_value() { return getf("center_value"); }
void f_center_value(float value) { setf("center_value", value); }

//Out Float Brightness Range
//Statistical range.
float f_range_value() { return getf("range_value"); }
void f_range_value(float value) { setf("range_value", value); }

//Float Contrast
//Contrast parameter for converting brightness to sound values. Center is defined automatically.
float f_contrast() { return getf("contrast"); }


//Enum Interpretation Method
//Interpretation method: pixels slices are PCM samples or sonogram.

enum enum_method {
    method_PCM = 0,
    method_Sonogram = 1,
    method_N__ = 2
};
enum_method en_method() { return enum_method(geti("method")); }

//Enum Scan Speed Measure
//Speed of scanning.

enum enum_pcm_speed_measure {
    pcm_speed_measure_Hz = 0,
    pcm_speed_measure_Seconds = 1,
    pcm_speed_measure_MIDI_note = 2,
    pcm_speed_measure_N__ = 3
};
enum_pcm_speed_measure en_pcm_speed_measure() { return enum_pcm_speed_measure(geti("pcm_speed_measure")); }

//Float Speed
//
float f_pcm_speed_hz() { return getf("pcm_speed_hz"); }

//Float Speed
//
float f_pcm_speed_sec() { return getf("pcm_speed_sec"); }

//Enum Scan Speed Measure
//Speed of scanning.

enum enum_sono_speed_measure {
    sono_speed_measure_Seconds = 0,
    sono_speed_measure_BPM = 1,
    sono_speed_measure_N__ = 2
};
enum_sono_speed_measure en_sono_speed_measure() { return enum_sono_speed_measure(geti("sono_speed_measure")); }

//Float Speed Seconds
//
float f_sono_speed_sec() { return getf("sono_speed_sec"); }

//Int Oscillators
//Number of oscillators for sound generation.
int i_oscillators() { return geti("oscillators"); }

//Enum Oscillator Shape
//Waveshape of the ocsillator.

enum enum_oscillator_shape {
    oscillator_shape_Sine = 0,
    oscillator_shape_Square = 1,
    oscillator_shape_N__ = 2
};
enum_oscillator_shape en_oscillator_shape() { return enum_oscillator_shape(geti("oscillator_shape")); }

//Int MIDI Note Low
//Note for setting frequency of low values.
int i_note_low() { return geti("note_low"); }

//Int MIDI Note High
//Note for setting frequency of high values.
int i_note_high() { return geti("note_high"); }

//----------------------------------------------------
