//----------------------------------------------------
//Interface for XClassFragmentShader
//Created automatically at 2020.09.14 11:01:46
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
bool was_changed_size() { return was_changed("size"); }
enum_size gete_size() { return enum_size(geti("size")); }

//Const Int Size X
//Width of FBO.
bool was_changed_size_x() { return was_changed("size_x"); }
int geti_size_x() { return geti("size_x"); }

//Const Int Size Y
//Height of FBO.
bool was_changed_size_y() { return was_changed("size_y"); }
int geti_size_y() { return geti("size_y"); }

//----------------------------------------------------
//Page Inputs
//

//Const Checkbox Texture1
//Use texture 1
bool was_changed_texture1() { return was_changed("texture1"); }
int geti_texture1() { return geti("texture1"); }

//Enum Source
//Image source - file or image from other module.
enum enum_tex1_source {
    tex1_source_Image_File = 0,
    tex1_source_Other_Module_Image = 1,
    tex1_source_N__ = 2
};
bool was_changed_tex1_source() { return was_changed("tex1_source"); }
enum_tex1_source gete_tex1_source() { return enum_tex1_source(geti("tex1_source")); }

//String Image File Name
//Image File.
bool was_changed_image1_file() { return was_changed("image1_file"); }
QString gets_image1_file() { return gets("image1_file"); }
QStringList get_strings_image1_file() { return get_strings("image1_file"); }

//String Image Link
//Reference to image in another module.
bool was_changed_image1_link() { return was_changed("image1_link"); }
QString gets_image1_link() { return gets("image1_link"); }
QStringList get_strings_image1_link() { return get_strings("image1_link"); }

//----------------------------------------------------
//Page Shader
//

//Out Object Fbo
//output FBO, can be used in Screen to draw
bool was_changed_fbo() { return was_changed("fbo"); }
XDict *getobj_fbo() { return get_object("fbo"); }


//Text Code
//Shader's code.
bool was_changed_fragment_code() { return was_changed("fragment_code"); }
QString gets_fragment_code() { return gets("fragment_code"); }
QStringList get_strings_fragment_code() { return get_strings("fragment_code"); }

//----------------------------------------------------
