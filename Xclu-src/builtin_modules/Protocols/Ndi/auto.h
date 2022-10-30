//----------------------------------------------------
//Interface for XClassNdi
//Created automatically.
//----------------------------------------------------
//Page Send
//NDI Sender. Initializes the size of the image when the first frame is arrived.

//Const Enum Image Source
//Should we use real image or test image.
enum enum_send_image_source {
    send_image_source_Image = 0,
    send_image_source_Test_Image = 1,
    send_image_source_N__ = 2
};
bool was_changed_send_image_source() { return was_changed_("send_image_source"); }
enum_send_image_source gete_send_image_source() { return enum_send_image_source(geti_("send_image_source")); }
QString getraw_send_image_source() { return getraw_("send_image_source");}

//Object Input Image
//Image size must be fixed after running.
bool was_changed_send_image() { return was_changed_("send_image"); }
XProtectedObject *getobject_send_image() { return get_object_("send_image"); }
void repaint_send_image() { repaint_("send_image"); }
//Const String Sender Name
//NDI sender name.
bool was_changed_sender_name() { return was_changed_("sender_name"); }
QString gets_sender_name() { return gets_("sender_name"); }
QStringList get_strings_sender_name() { return get_strings_("sender_name"); }
void repaint_sender_name() { repaint_("sender_name"); }

//Const Enum Send Mode
//Sending mode.
enum enum_send_mode {
    send_mode_Off = 0,
    send_mode_Each_Frame = 1,
    send_mode_On_Checkbox = 2,
    send_mode_N__ = 3
};
bool was_changed_send_mode() { return was_changed_("send_mode"); }
enum_send_mode gete_send_mode() { return enum_send_mode(geti_("send_mode")); }
QString getraw_send_mode() { return getraw_("send_mode");}

//Checkbox New Frame
//Usually you should link it with the image update flag.
bool was_changed_send_new_frame() { return was_changed_("send_new_frame"); }
int geti_send_new_frame() { return geti_("send_new_frame"); }
void repaint_send_new_frame() { repaint_("send_new_frame"); }


//Out String Send Status
//Current sending status.
bool was_changed_send_status() { return was_changed_("send_status"); }
QString gets_send_status() { return gets_("send_status"); }
QStringList get_strings_send_status() { return get_strings_("send_status"); }
void sets_send_status(QString value) { sets_("send_status", value); }
void clear_string_send_status() { clear_string_("send_status"); }
void append_string_send_status(QString v, int extra_new_lines_count = 0) { append_string_("send_status", v, extra_new_lines_count); }
void append_string_send_status(QStringList v, int extra_new_lines_count = 0) { append_string_("send_status", v, extra_new_lines_count); }
void repaint_send_status() { repaint_("send_status"); }

//----------------------------------------------------
//Page Receive
//Not implemented.

//----------------------------------------------------
