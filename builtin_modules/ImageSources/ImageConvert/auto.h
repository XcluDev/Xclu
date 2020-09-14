//----------------------------------------------------
//Interface for XClassImageConvert
//Created automatically.
//----------------------------------------------------
//Page Main
//General settings

//Enum Output Mode
//
enum enum_output_mode {
    output_mode_Grayscale = 0,
    output_mode_RGB = 1,
    output_mode_BGR = 2,
    output_mode_RGBA = 3,
    output_mode_BGRA = 4,
    output_mode_HSL = 5,
    output_mode_R = 6,
    output_mode_G = 7,
    output_mode_B = 8,
    output_mode_H = 9,
    output_mode_S = 10,
    output_mode_L = 11,
    output_mode_N__ = 12
};
bool was_changed_output_mode() { return was_changed_("output_mode"); }
enum_output_mode gete_output_mode() { return enum_output_mode(geti_("output_mode")); }

//Enum Output Format
//
enum enum_output_format {
    output_format_u8bit = 0,
    output_format_float = 1,
    output_format_N__ = 2
};
bool was_changed_output_format() { return was_changed_("output_format"); }
enum_output_format gete_output_format() { return enum_output_format(geti_("output_format")); }


//Checkbox Resize and Crop
//Resizing and cropping options
bool was_changed_resize_crop() { return was_changed_("resize_crop"); }
int geti_resize_crop() { return geti_("resize_crop"); }

//Enum Resize
//Resize image
enum enum_resize {
    resize_No = 0,
    resize_Percent = 1,
    resize_Pixels = 2,
    resize_N__ = 3
};
bool was_changed_resize() { return was_changed_("resize"); }
enum_resize gete_resize() { return enum_resize(geti_("resize")); }

//Float Resize Percent
//
bool was_changed_resize_percent() { return was_changed_("resize_percent"); }
float getf_resize_percent() { return getf_("resize_percent"); }

//Int Resize X
//
bool was_changed_resize_x() { return was_changed_("resize_x"); }
int geti_resize_x() { return geti_("resize_x"); }

//Int Resize Y
//
bool was_changed_resize_y() { return was_changed_("resize_y"); }
int geti_resize_y() { return geti_("resize_y"); }

//Enum Crop
//Crop...
enum enum_crop {
    crop_No = 0,
    crop_Percent = 1,
    crop_Pixels = 2,
    crop_N__ = 3
};
bool was_changed_crop() { return was_changed_("crop"); }
enum_crop gete_crop() { return enum_crop(geti_("crop")); }

//----------------------------------------------------
