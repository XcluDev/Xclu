//----------------------------------------------------
//Interface for XClassImageLoader
//Created automatically.
//----------------------------------------------------
//Page Main
//General settings

//Enum Image Source
//
enum enum_image_source {
    image_source_File = 0,
    image_source_Folder = 1,
    image_source_N__ = 2
};
bool was_changed_image_source() { return was_changed_("image_source"); }
enum_image_source gete_image_source() { return enum_image_source(geti_("image_source")); }
QString getraw_image_source() { return getraw_("image_source");}

//String File
//Image file.
bool was_changed_file_name() { return was_changed_("file_name"); }
QString gets_file_name() { return gets_("file_name"); }
QStringList get_strings_file_name() { return get_strings_("file_name"); }

//String Folder
//Image folder.
bool was_changed_folder_name() { return was_changed_("folder_name"); }
QString gets_folder_name() { return gets_("folder_name"); }
QStringList get_strings_folder_name() { return get_strings_("folder_name"); }

//Int Image Index
//Image index in folder, is warped.
bool was_changed_folder_index() { return was_changed_("folder_index"); }
int geti_folder_index() { return geti_("folder_index"); }

//Checkbox Show Image
//
bool was_changed_show_image() { return was_changed_("show_image"); }
int geti_show_image() { return geti_("show_image"); }

//Out Checkbox New Frame
//1 when image was updated.
bool was_changed_is_new_frame() { return was_changed_("is_new_frame"); }
int geti_is_new_frame() { return geti_("is_new_frame"); }
void seti_is_new_frame(int value) { seti_("is_new_frame", value); }

//Out Object Image
//Loaded image image.
bool was_changed_image() { return was_changed_("image"); }
XProtectedObject *getobject_image() { return get_object_("image"); }
void setobject_image(XProtectedObject *value) { set_object_("image", value); }

//----------------------------------------------------
