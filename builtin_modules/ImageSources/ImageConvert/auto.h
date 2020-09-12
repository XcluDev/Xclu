//----------------------------------------------------
//Interface for XClassImageConvert
//Created automatically at 2020.09.12 21:37:01
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
enum_output_mode en_output_mode() { return enum_output_mode(geti("output_mode")); }

//Enum Output Format
//

enum enum_output_format {
    output_format_u8bit = 0,
    output_format_float = 1,
    output_format_N__ = 2
};
enum_output_format en_output_format() { return enum_output_format(geti("output_format")); }


//Checkbox Resize and Crop
//Resizing and cropping options
int i_resize_crop() { return geti("resize_crop"); }

//Enum Resize
//Resize image

enum enum_resize {
    resize_No = 0,
    resize_Percent = 1,
    resize_Pixels = 2,
    resize_N__ = 3
};
enum_resize en_resize() { return enum_resize(geti("resize")); }

//Float Resize Percent
//
float f_resize_percent() { return getf("resize_percent"); }

//Int Resize X
//
int i_resize_x() { return geti("resize_x"); }

//Int Resize Y
//
int i_resize_y() { return geti("resize_y"); }

//Enum Crop
//Crop...

enum enum_crop {
    crop_No = 0,
    crop_Percent = 1,
    crop_Pixels = 2,
    crop_N__ = 3
};
enum_crop en_crop() { return enum_crop(geti("crop")); }

//----------------------------------------------------
