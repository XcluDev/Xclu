//----------------------------------------------------
//Interface for XClassBciNeuroplay
//Created automatically.
//----------------------------------------------------
//Page Connect
//Connecting to device. Please start NeuroplayPro app before connecting.

//Button Connect
// Press to connect to NeuroplayPro app.
bool was_changed_btn_connect() { return was_changed_("btn_connect"); }
int geti_btn_connect() { return geti_("btn_connect"); }
void repaint_btn_connect() { repaint_("btn_connect"); }
QString button_btn_connect() { return "btn_connect"; }

//Button Disconnect
// Press to disconnect from NeuroplayPro app.
bool was_changed_btn_disconnect() { return was_changed_("btn_disconnect"); }
int geti_btn_disconnect() { return geti_("btn_disconnect"); }
void repaint_btn_disconnect() { repaint_("btn_disconnect"); }
QString button_btn_disconnect() { return "btn_disconnect"; }

//Checkbox Autoconnect
//Connect to NeuroplayPro at start.
bool was_changed_autoconnect() { return was_changed_("autoconnect"); }
int geti_autoconnect() { return geti_("autoconnect"); }
void repaint_autoconnect() { repaint_("autoconnect"); }


//Out Checkbox Connected
//Is device connected.
bool was_changed_connected() { return was_changed_("connected"); }
int geti_connected() { return geti_("connected"); }
void seti_connected(int value) { seti_("connected", value); }
void repaint_connected() { repaint_("connected"); }

//Out Text Device Info
//Information about connected device.
bool was_changed_device_info() { return was_changed_("device_info"); }
QString gets_device_info() { return gets_("device_info"); }
QStringList get_strings_device_info() { return get_strings_("device_info"); }
void sets_device_info(QString value) { sets_("device_info", value); }
void clear_string_device_info() { clear_string_("device_info"); }
void append_string_device_info(QString v, int extra_new_lines_count = 0) { append_string_("device_info", v, extra_new_lines_count); }
void append_string_device_info(QStringList v, int extra_new_lines_count = 0) { append_string_("device_info", v, extra_new_lines_count); }
void repaint_device_info() { repaint_("device_info"); }


//Out String Requests Stat
//How much requests were sent, received, lost.
bool was_changed_requests_stat() { return was_changed_("requests_stat"); }
QString gets_requests_stat() { return gets_("requests_stat"); }
QStringList get_strings_requests_stat() { return get_strings_("requests_stat"); }
void sets_requests_stat(QString value) { sets_("requests_stat", value); }
void clear_string_requests_stat() { clear_string_("requests_stat"); }
void append_string_requests_stat(QString v, int extra_new_lines_count = 0) { append_string_("requests_stat", v, extra_new_lines_count); }
void append_string_requests_stat(QStringList v, int extra_new_lines_count = 0) { append_string_("requests_stat", v, extra_new_lines_count); }
void repaint_requests_stat() { repaint_("requests_stat"); }

//----------------------------------------------------
//Page Console
//

//Enum Send
//Choose what to send manually.
enum enum_send_type {
    send_type_String = 0,
    send_type_Byte = 1,
    send_type_String_Link = 2,
    send_type_N__ = 3
};
bool was_changed_send_type() { return was_changed_("send_type"); }
enum_send_type gete_send_type() { return enum_send_type(geti_("send_type")); }
QString getraw_send_type() { return getraw_("send_type");}

//String String To Send
//String for sending.
bool was_changed_send_string() { return was_changed_("send_string"); }
QString gets_send_string() { return gets_("send_string"); }
QStringList get_strings_send_string() { return get_strings_("send_string"); }
void repaint_send_string() { repaint_("send_string"); }

//Button Send
//
bool was_changed_send_string_btn() { return was_changed_("send_string_btn"); }
int geti_send_string_btn() { return geti_("send_string_btn"); }
void repaint_send_string_btn() { repaint_("send_string_btn"); }
QString button_send_string_btn() { return "send_string_btn"; }

//Checkbox Send
//Check to send each frame or link to other value.
bool was_changed_send_string_checkbox() { return was_changed_("send_string_checkbox"); }
int geti_send_string_checkbox() { return geti_("send_string_checkbox"); }
void repaint_send_string_checkbox() { repaint_("send_string_checkbox"); }


//Checkbox More Strings
//You can prepare several additional strings to send for convenience.
bool was_changed_show_additional_strings() { return was_changed_("show_additional_strings"); }
int geti_show_additional_strings() { return geti_("show_additional_strings"); }
void repaint_show_additional_strings() { repaint_("show_additional_strings"); }

//String String To Send2
//String for sending.
bool was_changed_send_string2() { return was_changed_("send_string2"); }
QString gets_send_string2() { return gets_("send_string2"); }
QStringList get_strings_send_string2() { return get_strings_("send_string2"); }
void repaint_send_string2() { repaint_("send_string2"); }

//Button Send
//
bool was_changed_send_string2_btn() { return was_changed_("send_string2_btn"); }
int geti_send_string2_btn() { return geti_("send_string2_btn"); }
void repaint_send_string2_btn() { repaint_("send_string2_btn"); }
QString button_send_string2_btn() { return "send_string2_btn"; }

//String String To Send3
//String for sending.
bool was_changed_send_string3() { return was_changed_("send_string3"); }
QString gets_send_string3() { return gets_("send_string3"); }
QStringList get_strings_send_string3() { return get_strings_("send_string3"); }
void repaint_send_string3() { repaint_("send_string3"); }

//Button Send
//
bool was_changed_send_string3_btn() { return was_changed_("send_string3_btn"); }
int geti_send_string3_btn() { return geti_("send_string3_btn"); }
void repaint_send_string3_btn() { repaint_("send_string3_btn"); }
QString button_send_string3_btn() { return "send_string3_btn"; }

//String String To Send4
//String for sending.
bool was_changed_send_string4() { return was_changed_("send_string4"); }
QString gets_send_string4() { return gets_("send_string4"); }
QStringList get_strings_send_string4() { return get_strings_("send_string4"); }
void repaint_send_string4() { repaint_("send_string4"); }

//Button Send
//
bool was_changed_send_string4_btn() { return was_changed_("send_string4_btn"); }
int geti_send_string4_btn() { return geti_("send_string4_btn"); }
void repaint_send_string4_btn() { repaint_("send_string4_btn"); }
QString button_send_string4_btn() { return "send_string4_btn"; }

//String String To Send5
//String for sending.
bool was_changed_send_string5() { return was_changed_("send_string5"); }
QString gets_send_string5() { return gets_("send_string5"); }
QStringList get_strings_send_string5() { return get_strings_("send_string5"); }
void repaint_send_string5() { repaint_("send_string5"); }

//Button Send
//
bool was_changed_send_string5_btn() { return was_changed_("send_string5_btn"); }
int geti_send_string5_btn() { return geti_("send_string5_btn"); }
void repaint_send_string5_btn() { repaint_("send_string5_btn"); }
QString button_send_string5_btn() { return "send_string5_btn"; }

//String String To Send6
//String for sending.
bool was_changed_send_string6() { return was_changed_("send_string6"); }
QString gets_send_string6() { return gets_("send_string6"); }
QStringList get_strings_send_string6() { return get_strings_("send_string6"); }
void repaint_send_string6() { repaint_("send_string6"); }

//Button Send
//
bool was_changed_send_string6_btn() { return was_changed_("send_string6_btn"); }
int geti_send_string6_btn() { return geti_("send_string6_btn"); }
void repaint_send_string6_btn() { repaint_("send_string6_btn"); }
QString button_send_string6_btn() { return "send_string6_btn"; }

//String String To Send7
//String for sending.
bool was_changed_send_string7() { return was_changed_("send_string7"); }
QString gets_send_string7() { return gets_("send_string7"); }
QStringList get_strings_send_string7() { return get_strings_("send_string7"); }
void repaint_send_string7() { repaint_("send_string7"); }

//Button Send
//
bool was_changed_send_string7_btn() { return was_changed_("send_string7_btn"); }
int geti_send_string7_btn() { return geti_("send_string7_btn"); }
void repaint_send_string7_btn() { repaint_("send_string7_btn"); }
QString button_send_string7_btn() { return "send_string7_btn"; }

//String String To Send8
//String for sending.
bool was_changed_send_string8() { return was_changed_("send_string8"); }
QString gets_send_string8() { return gets_("send_string8"); }
QStringList get_strings_send_string8() { return get_strings_("send_string8"); }
void repaint_send_string8() { repaint_("send_string8"); }

//Button Send
//
bool was_changed_send_string8_btn() { return was_changed_("send_string8_btn"); }
int geti_send_string8_btn() { return geti_("send_string8_btn"); }
void repaint_send_string8_btn() { repaint_("send_string8_btn"); }
QString button_send_string8_btn() { return "send_string8_btn"; }

//String String Link
//Link to string for sending.
bool was_changed_string_link_send() { return was_changed_("string_link_send"); }
QString gets_string_link_send() { return gets_("string_link_send"); }
QStringList get_strings_string_link_send() { return get_strings_("string_link_send"); }
void repaint_string_link_send() { repaint_("string_link_send"); }

//Button Send
//
bool was_changed_send_string_link_btn() { return was_changed_("send_string_link_btn"); }
int geti_send_string_link_btn() { return geti_("send_string_link_btn"); }
void repaint_send_string_link_btn() { repaint_("send_string_link_btn"); }
QString button_send_string_link_btn() { return "send_string_link_btn"; }


//Enum Line Terminator
//
enum enum_line_term {
    line_term_None = 0,
    line_term__n = 1,
    line_term__r = 2,
    line_term__r_n = 3,
    line_term_N__ = 4
};
bool was_changed_line_term() { return was_changed_("line_term"); }
enum_line_term gete_line_term() { return enum_line_term(geti_("line_term")); }
QString getraw_line_term() { return getraw_("line_term");}

//Int Send Byte
//Byte to send.
bool was_changed_send_byte() { return was_changed_("send_byte"); }
int geti_send_byte() { return geti_("send_byte"); }
void repaint_send_byte() { repaint_("send_byte"); }

//Button Send
//
bool was_changed_send_bytes_btn() { return was_changed_("send_bytes_btn"); }
int geti_send_bytes_btn() { return geti_("send_bytes_btn"); }
void repaint_send_bytes_btn() { repaint_("send_bytes_btn"); }
QString button_send_bytes_btn() { return "send_bytes_btn"; }



//Checkbox Receive
//Enable receiving data.
bool was_changed_receive() { return was_changed_("receive"); }
int geti_receive() { return geti_("receive"); }
void repaint_receive() { repaint_("receive"); }

//Enum Receive As
//Format of working with received data.
enum enum_receive_as {
    receive_as_None = 0,
    receive_as_Last_Line = 1,
    receive_as_Lines = 2,
    receive_as_Line_Callback = 3,
    receive_as_Text = 4,
    receive_as_Bytes = 5,
    receive_as_N__ = 6
};
bool was_changed_receive_as() { return was_changed_("receive_as"); }
enum_receive_as gete_receive_as() { return enum_receive_as(geti_("receive_as")); }
QString getraw_receive_as() { return getraw_("receive_as");}

//Out String Line
//Received data as last line, separated by '\n'. '\r' are ignored. Good for continuous sensors.
bool was_changed_received_line() { return was_changed_("received_line"); }
QString gets_received_line() { return gets_("received_line"); }
QStringList get_strings_received_line() { return get_strings_("received_line"); }
void sets_received_line(QString value) { sets_("received_line", value); }
void clear_string_received_line() { clear_string_("received_line"); }
void append_string_received_line(QString v, int extra_new_lines_count = 0) { append_string_("received_line", v, extra_new_lines_count); }
void append_string_received_line(QStringList v, int extra_new_lines_count = 0) { append_string_("received_line", v, extra_new_lines_count); }
void repaint_received_line() { repaint_("received_line"); }

//Out Text Received Text
//Received data as text.
bool was_changed_received_text() { return was_changed_("received_text"); }
QString gets_received_text() { return gets_("received_text"); }
QStringList get_strings_received_text() { return get_strings_("received_text"); }
void sets_received_text(QString value) { sets_("received_text", value); }
void clear_string_received_text() { clear_string_("received_text"); }
void append_string_received_text(QString v, int extra_new_lines_count = 0) { append_string_("received_text", v, extra_new_lines_count); }
void append_string_received_text(QStringList v, int extra_new_lines_count = 0) { append_string_("received_text", v, extra_new_lines_count); }
void repaint_received_text() { repaint_("received_text"); }

//Out Text Received Bytes
//Received data as bytes
bool was_changed_received_bytes() { return was_changed_("received_bytes"); }
QString gets_received_bytes() { return gets_("received_bytes"); }
QStringList get_strings_received_bytes() { return get_strings_("received_bytes"); }
void sets_received_bytes(QString value) { sets_("received_bytes", value); }
void clear_string_received_bytes() { clear_string_("received_bytes"); }
void append_string_received_bytes(QString v, int extra_new_lines_count = 0) { append_string_("received_bytes", v, extra_new_lines_count); }
void append_string_received_bytes(QStringList v, int extra_new_lines_count = 0) { append_string_("received_bytes", v, extra_new_lines_count); }
void repaint_received_bytes() { repaint_("received_bytes"); }

//Button Clear
//Clear received data
bool was_changed_clear() { return was_changed_("clear"); }
int geti_clear() { return geti_("clear"); }
void repaint_clear() { repaint_("clear"); }
QString button_clear() { return "clear"; }

//Enum Auto Clear
//Automatically clear received data before each update
enum enum_auto_clear {
    auto_clear_Off = 0,
    auto_clear_On = 1,
    auto_clear_N__ = 2
};
bool was_changed_auto_clear() { return was_changed_("auto_clear"); }
enum_auto_clear gete_auto_clear() { return enum_auto_clear(geti_("auto_clear")); }
QString getraw_auto_clear() { return getraw_("auto_clear");}

//Enum Limit Show
//
enum enum_limit_show {
    limit_show_Off = 0,
    limit_show_On = 1,
    limit_show_N__ = 2
};
bool was_changed_limit_show() { return was_changed_("limit_show"); }
enum_limit_show gete_limit_show() { return enum_limit_show(geti_("limit_show")); }
QString getraw_limit_show() { return getraw_("limit_show");}

//Int Limit Show Count
//Limit show by prevent slow down.
bool was_changed_limit_show_count() { return was_changed_("limit_show_count"); }
int geti_limit_show_count() { return geti_("limit_show_count"); }
void repaint_limit_show_count() { repaint_("limit_show_count"); }

//----------------------------------------------------
//Page Watchdog
//Saying Arduino that we are live, and receiving from Arduino that it's live.


//Checkbox Watchdog Send
//Should we send something to Arduino with given period to show that we are live.
bool was_changed_watchdog_send() { return was_changed_("watchdog_send"); }
int geti_watchdog_send() { return geti_("watchdog_send"); }
void repaint_watchdog_send() { repaint_("watchdog_send"); }

//String Watchdog Message
//Sending message.
bool was_changed_watchdog_message() { return was_changed_("watchdog_message"); }
QString gets_watchdog_message() { return gets_("watchdog_message"); }
QStringList get_strings_watchdog_message() { return get_strings_("watchdog_message"); }
void repaint_watchdog_message() { repaint_("watchdog_message"); }

//Float Send Period
//Time period for sending watchdog ticks.
bool was_changed_watchdog_send_period() { return was_changed_("watchdog_send_period"); }
float getf_watchdog_send_period() { return getf_("watchdog_send_period"); }
void repaint_watchdog_send_period() { repaint_("watchdog_send_period"); }


//Checkbox Watchdog Receive
//Receiving watchdog - TODO not implemented yet!
bool was_changed_watchdog_receive() { return was_changed_("watchdog_receive"); }
int geti_watchdog_receive() { return geti_("watchdog_receive"); }
void repaint_watchdog_receive() { repaint_("watchdog_receive"); }


//----------------------------------------------------
//Page Devices
//

//Button Print Devices
//
bool was_changed_print_devices() { return was_changed_("print_devices"); }
int geti_print_devices() { return geti_("print_devices"); }
void repaint_print_devices() { repaint_("print_devices"); }
QString button_print_devices() { return "print_devices"; }

//Out Text Device List
//
bool was_changed_device_list() { return was_changed_("device_list"); }
QString gets_device_list() { return gets_("device_list"); }
QStringList get_strings_device_list() { return get_strings_("device_list"); }
void sets_device_list(QString value) { sets_("device_list", value); }
void clear_string_device_list() { clear_string_("device_list"); }
void append_string_device_list(QString v, int extra_new_lines_count = 0) { append_string_("device_list", v, extra_new_lines_count); }
void append_string_device_list(QStringList v, int extra_new_lines_count = 0) { append_string_("device_list", v, extra_new_lines_count); }
void repaint_device_list() { repaint_("device_list"); }

//----------------------------------------------------
