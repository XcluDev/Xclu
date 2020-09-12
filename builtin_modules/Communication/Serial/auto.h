//----------------------------------------------------
//Interface for XClassSerial
//Created automatically at 2020.09.12 21:37:02
//----------------------------------------------------
//Page Main
//General settings.

//Checkbox Debug
//Debug output to console.
int i_debug() { return geti("debug"); }

//Const Enum Port
//Method of choosing the port.

enum enum_select_port {
    select_port_Default = 0,
    select_port_By_Index = 1,
    select_port_By_Name = 2,
    select_port_N__ = 3
};
enum_select_port en_select_port() { return enum_select_port(geti("select_port")); }

//Const Int Port ID From
//Start of id range, will search to first successful.
int i_port_index0() { return geti("port_index0"); }

//Const Int Port ID To
//End of id range
int i_port_index1() { return geti("port_index1"); }

//Const String Port Name
//Name of the device (may be specified only part, will be search for the first successful match).
QString s_port_name() { return gets("port_name"); }


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
enum_baud_rate en_baud_rate() { return enum_baud_rate(geti("baud_rate")); }


//Out Checkbox Connected
//Is port connected.
int i_connected() { return geti("connected"); }
void i_connected(int value) { seti("connected", value); }

//Out Text Port Info
//Information about connected port.
QString s_port_info() { return gets("port_info"); }
void s_port_info(QString value) { sets("port_info", value); }


//Out Int Total Sent
//How much bytes was sent.
int i_total_sent() { return geti("total_sent"); }
void i_total_sent(int value) { seti("total_sent", value); }

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
enum_send_type en_send_type() { return enum_send_type(geti("send_type")); }

//String String To Send
//String for sending.
QString s_send_string() { return gets("send_string"); }

//Button Send
//
int i_send_string_btn() { return geti("send_string_btn"); }

//String String Link
//Link to string for sending.
QString s_string_link_send() { return gets("string_link_send"); }

//Button Send
//
int i_send_string_link_btn() { return geti("send_string_link_btn"); }

//Enum Line Terminator
//

enum enum_line_term {
    line_term_None = 0,
    line_term_\n = 1,
    line_term_\r = 2,
    line_term_\r\n = 3,
    line_term_N__ = 4
};
enum_line_term en_line_term() { return enum_line_term(geti("line_term")); }

//Int Send Byte
//Byte to send.
int i_send_byte() { return geti("send_byte"); }

//Button Send
//
int i_send_bytes_btn() { return geti("send_bytes_btn"); }


//Enum Show Received as
//Show received data as text or bytes.

enum enum_show_received {
    show_received_None = 0,
    show_received_Text = 1,
    show_received_Bytes = 2,
    show_received_N__ = 3
};
enum_show_received en_show_received() { return enum_show_received(geti("show_received")); }

//Out Text Received Text
//Received data as text.
QString s_received_text() { return gets("received_text"); }
void s_received_text(QString value) { sets("received_text", value); }

//Out Text Received Bytes
//Received data as bytes
QString s_received_bytes() { return gets("received_bytes"); }
void s_received_bytes(QString value) { sets("received_bytes", value); }

//Button Clear
//Clear received data
int i_clear() { return geti("clear"); }

//Enum Auto Clear
//Automatically clear received data before each update

enum enum_auto_clear {
    auto_clear_Off = 0,
    auto_clear_On = 1,
    auto_clear_N__ = 2
};
enum_auto_clear en_auto_clear() { return enum_auto_clear(geti("auto_clear")); }

//Enum Limit Show
//

enum enum_limit_show {
    limit_show_Off = 0,
    limit_show_On = 1,
    limit_show_N__ = 2
};
enum_limit_show en_limit_show() { return enum_limit_show(geti("limit_show")); }

//Int Limit Show Count
//Limit show by prevent slow down.
int i_limit_show_count() { return geti("limit_show_count"); }

//----------------------------------------------------
//Page Devices
//

//Button Print Devices
//
int i_print_devices() { return geti("print_devices"); }

//Out Text Device List
//
QString s_device_list() { return gets("device_list"); }
void s_device_list(QString value) { sets("device_list", value); }

//----------------------------------------------------
