//----------------------------------------------------
//Interface for XClassSerial
//Created automatically.
//----------------------------------------------------
//Page Main
//General settings.

//Checkbox Debug
//Debug output to console.
bool was_changed_debug() { return was_changed_("debug"); }
int geti_debug() { return geti_("debug"); }

//Const Enum Port
//Method of choosing the port.
enum enum_select_port {
    select_port_Default = 0,
    select_port_By_Index = 1,
    select_port_By_Name = 2,
    select_port_N__ = 3
};
bool was_changed_select_port() { return was_changed_("select_port"); }
enum_select_port gete_select_port() { return enum_select_port(geti_("select_port")); }
QString getraw_select_port() { return getraw_("select_port");}

//Const Int Port ID From
//Start of id range, will search to first successful.
bool was_changed_port_index0() { return was_changed_("port_index0"); }
int geti_port_index0() { return geti_("port_index0"); }

//Const Int Port ID To
//End of id range
bool was_changed_port_index1() { return was_changed_("port_index1"); }
int geti_port_index1() { return geti_("port_index1"); }

//Const String Port Name
//Name of the device (may be specified only part, will be search for the first successful match).
bool was_changed_port_name() { return was_changed_("port_name"); }
QString gets_port_name() { return gets_("port_name"); }
QStringList get_strings_port_name() { return get_strings_("port_name"); }


//Const Enum Baud Rate
//
enum enum_baud_rate {
    baud_rate_2400 = 0,
    baud_rate_4800 = 1,
    baud_rate_9600 = 2,
    baud_rate_19200 = 3,
    baud_rate_38400 = 4,
    baud_rate_57600 = 5,
    baud_rate_115200 = 6,
    baud_rate_230400 = 7,
    baud_rate_460800 = 8,
    baud_rate_N__ = 9
};
bool was_changed_baud_rate() { return was_changed_("baud_rate"); }
enum_baud_rate gete_baud_rate() { return enum_baud_rate(geti_("baud_rate")); }
QString getraw_baud_rate() { return getraw_("baud_rate");}


//Out Checkbox Connected
//Is port connected.
bool was_changed_connected() { return was_changed_("connected"); }
int geti_connected() { return geti_("connected"); }
void seti_connected(int value) { seti_("connected", value); }

//Out Text Port Info
//Information about connected port.
bool was_changed_port_info() { return was_changed_("port_info"); }
QString gets_port_info() { return gets_("port_info"); }
QStringList get_strings_port_info() { return get_strings_("port_info"); }
void sets_port_info(QString value) { sets_("port_info", value); }
void clear_string_port_info() { clear_string_("port_info"); }
void append_string_port_info(QString v, int extra_new_lines_count = 0) { append_string_("port_info", v, extra_new_lines_count); }
void append_string_port_info(QStringList v, int extra_new_lines_count = 0) { append_string_("port_info", v, extra_new_lines_count); }


//Out Int Total Sent
//How much bytes was sent.
bool was_changed_total_sent() { return was_changed_("total_sent"); }
int geti_total_sent() { return geti_("total_sent"); }
void seti_total_sent(int value) { seti_("total_sent", value); }
void increase_int_total_sent(int increase = 1) { increase_int_("total_sent", increase); }

//----------------------------------------------------
//Page Console
//

//Enum Send
//Choose what to send manually.
enum enum_send_type {
    send_type_String = 0,
    send_type_Bytes = 1,
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

//Button Send
//
bool was_changed_send_string_btn() { return was_changed_("send_string_btn"); }
int geti_send_string_btn() { return geti_("send_string_btn"); }
QString button_send_string_btn() { return "send_string_btn"; }

//Checkbox More Strings
//You can prepare several additional strings to send for convenience.
bool was_changed_show_additional_strings() { return was_changed_("show_additional_strings"); }
int geti_show_additional_strings() { return geti_("show_additional_strings"); }

//String String To Send
//String for sending.
bool was_changed_send_string2() { return was_changed_("send_string2"); }
QString gets_send_string2() { return gets_("send_string2"); }
QStringList get_strings_send_string2() { return get_strings_("send_string2"); }

//Button Send
//
bool was_changed_send_string2_btn() { return was_changed_("send_string2_btn"); }
int geti_send_string2_btn() { return geti_("send_string2_btn"); }
QString button_send_string2_btn() { return "send_string2_btn"; }

//String String To Send
//String for sending.
bool was_changed_send_string3() { return was_changed_("send_string3"); }
QString gets_send_string3() { return gets_("send_string3"); }
QStringList get_strings_send_string3() { return get_strings_("send_string3"); }

//Button Send
//
bool was_changed_send_string3_btn() { return was_changed_("send_string3_btn"); }
int geti_send_string3_btn() { return geti_("send_string3_btn"); }
QString button_send_string3_btn() { return "send_string3_btn"; }


//String String Link
//Link to string for sending.
bool was_changed_string_link_send() { return was_changed_("string_link_send"); }
QString gets_string_link_send() { return gets_("string_link_send"); }
QStringList get_strings_string_link_send() { return get_strings_("string_link_send"); }

//Button Send
//
bool was_changed_send_string_link_btn() { return was_changed_("send_string_link_btn"); }
int geti_send_string_link_btn() { return geti_("send_string_link_btn"); }
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

//Button Send
//
bool was_changed_send_bytes_btn() { return was_changed_("send_bytes_btn"); }
int geti_send_bytes_btn() { return geti_("send_bytes_btn"); }
QString button_send_bytes_btn() { return "send_bytes_btn"; }


//Checkbox Receive
//Enable receiving data.
bool was_changed_receive() { return was_changed_("receive"); }
int geti_receive() { return geti_("receive"); }

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

//Out Text Received Text
//Received data as text.
bool was_changed_received_text() { return was_changed_("received_text"); }
QString gets_received_text() { return gets_("received_text"); }
QStringList get_strings_received_text() { return get_strings_("received_text"); }
void sets_received_text(QString value) { sets_("received_text", value); }
void clear_string_received_text() { clear_string_("received_text"); }
void append_string_received_text(QString v, int extra_new_lines_count = 0) { append_string_("received_text", v, extra_new_lines_count); }
void append_string_received_text(QStringList v, int extra_new_lines_count = 0) { append_string_("received_text", v, extra_new_lines_count); }

//Out Text Received Bytes
//Received data as bytes
bool was_changed_received_bytes() { return was_changed_("received_bytes"); }
QString gets_received_bytes() { return gets_("received_bytes"); }
QStringList get_strings_received_bytes() { return get_strings_("received_bytes"); }
void sets_received_bytes(QString value) { sets_("received_bytes", value); }
void clear_string_received_bytes() { clear_string_("received_bytes"); }
void append_string_received_bytes(QString v, int extra_new_lines_count = 0) { append_string_("received_bytes", v, extra_new_lines_count); }
void append_string_received_bytes(QStringList v, int extra_new_lines_count = 0) { append_string_("received_bytes", v, extra_new_lines_count); }

//Button Clear
//Clear received data
bool was_changed_clear() { return was_changed_("clear"); }
int geti_clear() { return geti_("clear"); }
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

//----------------------------------------------------
//Page Watchdog
//Saying Arduino that we are live, and receiving from Arduino that it's live.

//Checkbox Watchdog Send
//Should we send something to Arduino with given period to show that we are live.
bool was_changed_watchdog_send() { return was_changed_("watchdog_send"); }
int geti_watchdog_send() { return geti_("watchdog_send"); }

//String Watchdog Message
//Sending message.
bool was_changed_watchdog_message() { return was_changed_("watchdog_message"); }
QString gets_watchdog_message() { return gets_("watchdog_message"); }
QStringList get_strings_watchdog_message() { return get_strings_("watchdog_message"); }

//Float Send Period
//Time period for sending watchdog ticks.
bool was_changed_watchdog_send_period() { return was_changed_("watchdog_send_period"); }
float getf_watchdog_send_period() { return getf_("watchdog_send_period"); }

//Checkbox Watchdog Receive
//Receiving watchdog - TODO not implemented yet!
bool was_changed_watchdog_receive() { return was_changed_("watchdog_receive"); }
int geti_watchdog_receive() { return geti_("watchdog_receive"); }

//----------------------------------------------------
//Page Devices
//

//Button Print Devices
//
bool was_changed_print_devices() { return was_changed_("print_devices"); }
int geti_print_devices() { return geti_("print_devices"); }
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

//----------------------------------------------------
