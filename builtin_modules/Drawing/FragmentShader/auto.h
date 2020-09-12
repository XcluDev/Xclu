//----------------------------------------------------
//Interface for XClassFragmentShader
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

//----------------------------------------------------
//Page Inputs
//

//Const Checkbox Texture1
//Use texture 1
int i_texture1() { return geti("texture1"); }

//Enum Source
//Image source - file or image from other module.

enum enum_tex1_source {
    tex1_source_Image_File = 0,
    tex1_source_Other_Module_Image = 1,
    tex1_source_N__ = 2
};
enum_tex1_source en_tex1_source() { return enum_tex1_source(geti("tex1_source")); }

//String Image File Name
//Image File.
QString s_image1_file() { return gets("image1_file"); }

//String Image Link
//Reference to image in another module.
QString s_image1_link() { return gets("image1_link"); }

//----------------------------------------------------
//Page Shader
//

//Out Object Fbo
//output FBO, can be used in Screen to draw
XDict *obj_fbo() { return get_object("fbo"); }


//Text Code
//Shader's code.
QString s_fragment_code() { return gets("fragment_code"); }

//----------------------------------------------------
