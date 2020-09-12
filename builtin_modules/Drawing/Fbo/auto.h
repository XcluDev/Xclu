//----------------------------------------------------
//Interface for XClassFbo
//Created automatically at 2020.09.12 21:37:01
//----------------------------------------------------
//Page Main
//General settings

//Const Enum Size
//Size of the FBO.

enum enum_size {
    size_Custom = 0,
    size_640x480 = 1,
    size_800x600 = 2,
    size_1024x768 = 3,
    size_1280x720 = 4,
    size_1920x1080 = 5,
    size_1920x1200 = 6,
    size_N__ = 7
};
enum_size en_size() { return enum_size(geti("size")); }

//Const Int Size X
//Width of FBO.
int i_size_x() { return geti("size_x"); }

//Const Int Size Y
//Height of FBO.
int i_size_y() { return geti("size_y"); }


//Enum Channels
//Desired channels of the output image.

enum enum_image_channels {
    image_channels_Grayscale = 0,
    image_channels_RGB = 1,
    image_channels_RGBA = 2,
    image_channels_N__ = 3
};
enum_image_channels en_image_channels() { return enum_image_channels(geti("image_channels")); }

//Enum Data Type
//Desired data type of the output texture, u8bit=0..255, float=[0,1].

enum enum_image_data_type {
    image_data_type_u8bit = 0,
    image_data_type_float = 1,
    image_data_type_N__ = 2
};
enum_image_data_type en_image_data_type() { return enum_image_data_type(geti("image_data_type")); }


//Out Object Fbo
//output FBO, can be used in Window to draw
XDict *obj_fbo() { return get_object("fbo"); }

//----------------------------------------------------
