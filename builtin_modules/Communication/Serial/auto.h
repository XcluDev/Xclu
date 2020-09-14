//----------------------------------------------------
//Interface for XClassSerial
//Created automatically at 2020.09.14 11:01:46
//----------------------------------------------------
//Page Main
//General settings.

//Checkbox Debug
//Debug output to console.
bool was_changed_debug() { return was_changed("debug"); }
int geti_debug() { return geti("debug"); }

//Const Enum Port
//Method of choosing the port.
enum enum_select_port {
    select_port_Default = 0,
    select_port_By_Index = 1,
    select_port_By_Name = 2,
    select_port_N__ = 3
};
bool was_changed_select_port() { return was_changed("select_port"); }
enum_select_port gete_select_port() { return enum_select_port(geti("select_port")); }

//Const Int Port ID From
//Start of id range, will search to first successful.
bool was_changed_port_index0() { return was_changed("port_index0"); }
int geti_port_index0() { return geti("port_index0"); }

//Const Int Port ID To
//End of id range
bool was_changed_port_index1() { return was_changed("port_index1"); }
int geti_port_index1() { return geti("port_index1"); }

//Const String Port Name
//Name of the device (may be specified only part, will be search for the first successful match).
bool was_changed_port_name() { return was_changed("port_name"); }
QString gets_port_name() { return gets("port_name"); }
QStringList get_strings_port_name() { return get_strings("port_name"); }


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
bool was_changed_baud_rate() { return was_changed("baud_rate"); }
enum_baud_rate gete_baud_rate() { return enum_baud_rate(geti("baud_rate")); }


//Out Checkbox Connected
//Is port connected.
bool was_changed_connected() { return was_changed("connected"); }
int geti_connected() { return geti("connected"); }
void seti_connected(int value) { seti("connected", value); }

//Out Text Port Info
//Information about connected port.
bool was_changed_port_info() { return was_changed("port_info"); }
QString gets_port_info() { return gets("port_info"); }
QStringList get_strings_port_info() { return get_strings("port_info"); }
void sets_port_info(QString value) { sets("port_info", value); }
void clear_string_port_info() { clear_string("port_info"); }
void append_string_port_info(QString v, int extra_new_lines_count = 0) { append_string("port_info", v, extra_new_lines_count); }
void append_string_port_info(QStringList v, int extra_new_lines_count = 0) { append_string("port_info", v, extra_new_lines_count); }


//Out Int Total Sent
//How much bytes was sent.
bool was_changed_total_sent() { return was_changed("total_sent"); }
int geti_total_sent() { return geti("total_sent"); }
void seti_total_sent(int value) { seti("total_sent", value); }
void increase_int_total_sent(int increase = 1) { increase_int("total_sent", increase); }

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
bool was_changed_send_type() { return was_changed("send_type"); }
enum_send_type gete_send_type() { return enum_send_type(geti("send_type")); }

//String String To Send
//String for sending.
bool was_changed_send_string() { return was_changed("send_string"); }
QString gets_send_string() { return gets("send_string"); }
QStringList get_strings_send_string() { return get_strings("send_string"); }

//Button Send
//
bool was_changed_send_string_btn() { return was_changed("send_string_btn"); }
int geti_send_string_btn() { return geti("send_string_btn"); }

//String String Link
//Link to string for sending.
bool was_changed_string_link_send() { return was_changed("string_link_send"); }
QString gets_string_link_send() { return gets("string_link_send"); }
QStringList get_strings_string_link_send() { return get_strings("string_link_send"); }

//Button Send
//
bool was_changed_send_string_link_btn() { return was_changed("send_string_link_btn"); }
int geti_send_string_link_btn() { return geti("send_string_link_btn"); }

//Enum Line Terminator
//
enum enum_line_term {
    line_term_None = 0,
    line_term_\n = 1,
    line_term_\r = 2,
    line_term_\r\n = 3,
    line_term_N__ = 4
};
bool was_changed_line_term() { return was_changed("line_term"); }
enum_line_term gete_line_term() { return enum_line_term(geti("line_term")); }

//Int Send Byte
//Byte to send.
bool was_changed_send_byte() { return was_changed("send_byte"); }
int geti_send_byte() { return geti("send_byte"); }

//Button Send
//
bool was_changed_send_bytes_btn() { return was_changed("send_bytes_btn"); }
int geti_send_bytes_btn() { return geti("send_bytes_btn"); }


//Enum Show Received as
//Show received data as text or bytes.
enum enum_show_received {
    show_received_None = 0,
    show_received_Text = 1,
    show_received_Bytes = 2,
    show_received_N__ = 3
};
bool was_changed_show_received() { return was_changed("show_received"); }
enum_show_received gete_show_received() { return enum_show_received(geti("show_received")); }

//Out Text Received Text
//Received data as text.
bool was_changed_received_text() { return was_changed("received_text"); }
QString gets_received_text() { return gets("received_text"); }
QStringList get_strings_received_text() { return get_strings("received_text"); }
void sets_received_text(QString value) { sets("received_text", value); }
void clear_string_received_text() { clear_string("received_text"); }
void append_string_received_text(QString v, int extra_new_lines_count = 0) { append_string("received_text", v, extra_new_lines_count); }
void append_string_received_text(QStringList v, int extra_new_lines_count = 0) { append_string("received_text", v, extra_new_lines_count); }

//Out Text Received Bytes
//Received data as bytes
bool was_changed_received_bytes() { return was_changed("received_bytes"); }
QString gets_received_bytes() { return gets("received_bytes"); }
QStringList get_strings_received_bytes() { return get_strings("received_bytes"); }
void sets_received_bytes(QString value) { sets("received_bytes", value); }
void clear_string_received_bytes() { clear_string("received_bytes"); }
void append_string_received_bytes(QString v, int extra_new_lines_count = 0) { append_string("received_bytes", v, extra_new_lines_count); }
void append_string_received_bytes(QStringList v, int extra_new_lines_count = 0) { append_string("received_bytes", v, extra_new_lines_count); }

//Button Clear
//Clear received data
bool was_changed_clear() { return was_changed("clear"); }
int geti_clear() { return geti("clear"); }

//Enum Auto Clear
//Automatically clear received data before each update
enum enum_auto_clear {
    auto_clear_Off = 0,
    auto_clear_On = 1,
    auto_clear_N__ = 2
};
bool was_changed_auto_clear() { return was_changed("auto_clear"); }
enum_auto_clear gete_auto_clear() { return enum_auto_clear(geti("auto_clear")); }

//Enum Limit Show
//
enum enum_limit_show {
    limit_show_Off = 0,
    limit_show_On = 1,
    limit_show_N__ = 2
};
bool was_changed_limit_show() { return was_changed("limit_show"); }
enum_limit_show gete_limit_show() { return enum_limit_show(geti("limit_show")); }

//Int Limit Show Count
//Limit show by prevent slow down.
bool was_changed_limit_show_count() { return was_changed("limit_show_count"); }
int geti_limit_show_count() { return geti("limit_show_count"); }

//----------------------------------------------------
//Page Devices
//

//Button Print Devices
//
bool was_changed_print_devices() { return was_changed("print_devices"); }
int geti_print_devices() { return geti("print_devices"); }

//Out Text Device List
//
bool was_changed_device_list() { return was_changed("device_list"); }
QString gets_device_list() { return gets("device_list"); }
QStringList get_strings_device_list() { return get_strings("device_list"); }
void sets_device_list(QString value) { sets("device_list", value); }
void clear_string_device_list() { clear_string("device_list"); }
void append_string_device_list(QString v, int extra_new_lines_count = 0) { append_string("device_list", v, extra_new_lines_count); }
void append_string_device_list(QStringList v, int extra_new_lines_count = 0) { append_string("device_list", v, extra_new_lines_count); }

//----------------------------------------------------
