//----------------------------------------------------
//Interface for XClassFbo
//Created automatically.
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
bool was_changed_size() { return was_changed_("size"); }
enum_size gete_size() { return enum_size(geti_("size")); }
QString getraw_size() { return getraw_("size");}

//Const Int Size X
//Width of FBO.
bool was_changed_size_x() { return was_changed_("size_x"); }
int geti_size_x() { return geti_("size_x"); }

//Const Int Size Y
//Height of FBO.
bool was_changed_size_y() { return was_changed_("size_y"); }
int geti_size_y() { return geti_("size_y"); }


//Enum Channels
//Desired channels of the output image.
enum enum_image_channels {
    image_channels_Grayscale = 0,
    image_channels_RGB = 1,
    image_channels_RGBA = 2,
    image_channels_N__ = 3
};
bool was_changed_image_channels() { return was_changed_("image_channels"); }
enum_image_channels gete_image_channels() { return enum_image_channels(geti_("image_channels")); }
QString getraw_image_channels() { return getraw_("image_channels");}

//Enum Data Type
//Desired data type of the output texture, u8=0..255, float=[0,1].
enum enum_image_data_type {
    image_data_type_u8 = 0,
    image_data_type_float = 1,
    image_data_type_N__ = 2
};
bool was_changed_image_data_type() { return was_changed_("image_data_type"); }
enum_image_data_type gete_image_data_type() { return enum_image_data_type(geti_("image_data_type")); }
QString getraw_image_data_type() { return getraw_("image_data_type");}


//Out Object Fbo
//output FBO, can be used in Window to draw
bool was_changed_fbo() { return was_changed_("fbo"); }
XProtectedObject *getobject_fbo() { return get_object_("fbo"); }

//----------------------------------------------------
