//----------------------------------------------------
//Interface for XClassBaseUdp
//Created automatically.
//----------------------------------------------------
//Page Main
//Main functionality.

//Const Enum Mode
// Mode of the module.
enum enum_mode {
    mode_Send = 0,
    mode_Receive = 1,
    mode_N__ = 2
};
bool was_changed_mode() { return was_changed_("mode"); }
enum_mode gete_mode() { return enum_mode(geti_("mode")); }
QString getraw_mode() { return getraw_("mode");}

//Const String Send Address
//Address with port: localhost:12345.
bool was_changed_send_address() { return was_changed_("send_address"); }
QString gets_send_address() { return gets_("send_address"); }
QStringList get_strings_send_address() { return get_strings_("send_address"); }
void repaint_send_address() { repaint_("send_address"); }


//Const Checkbox Send File
// Send data from a given text file.
bool was_changed_send_from_file() { return was_changed_("send_from_file"); }
int geti_send_from_file() { return geti_("send_from_file"); }
void repaint_send_from_file() { repaint_("send_from_file"); }

//Const Checkbox Emulate
// Emulate receiving from text file.
bool was_changed_receive_emulate() { return was_changed_("receive_emulate"); }
int geti_receive_emulate() { return geti_("receive_emulate"); }
void repaint_receive_emulate() { repaint_("receive_emulate"); }

//Const Int Receive Port
// Port for receiving.
bool was_changed_receive_port() { return was_changed_("receive_port"); }
int geti_receive_port() { return geti_("receive_port"); }
void repaint_receive_port() { repaint_("receive_port"); }

//Const Checkbox Only Last Packet
//If several packets were received, keep only the latest one.
bool was_changed_receive_only_last_packet() { return was_changed_("receive_only_last_packet"); }
int geti_receive_only_last_packet() { return geti_("receive_only_last_packet"); }
void repaint_receive_only_last_packet() { repaint_("receive_only_last_packet"); }

//Const String File To Send
//Text file to load for emulating.
bool was_changed_send_file_name() { return was_changed_("send_file_name"); }
QString gets_send_file_name() { return gets_("send_file_name"); }
QStringList get_strings_send_file_name() { return get_strings_("send_file_name"); }
void repaint_send_file_name() { repaint_("send_file_name"); }

//Int Rate
//How much lines read per second.
bool was_changed_send_rate() { return was_changed_("send_rate"); }
int geti_send_rate() { return geti_("send_rate"); }
void repaint_send_rate() { repaint_("send_rate"); }

//Const String Read From File
//Text file to load for emulating.
bool was_changed_receive_emulate_file_name() { return was_changed_("receive_emulate_file_name"); }
QString gets_receive_emulate_file_name() { return gets_("receive_emulate_file_name"); }
QStringList get_strings_receive_emulate_file_name() { return get_strings_("receive_emulate_file_name"); }
void repaint_receive_emulate_file_name() { repaint_("receive_emulate_file_name"); }

//Int Rate
//How much lines read per second.
bool was_changed_receive_emulate_rate() { return was_changed_("receive_emulate_rate"); }
int geti_receive_emulate_rate() { return geti_("receive_emulate_rate"); }
void repaint_receive_emulate_rate() { repaint_("receive_emulate_rate"); }


//Out Float File Position
//File position.
bool was_changed_receive_file_position() { return was_changed_("receive_file_position"); }
float getf_receive_file_position() { return getf_("receive_file_position"); }
void setf_receive_file_position(float value) { setf_("receive_file_position", value); }
void repaint_receive_file_position() { repaint_("receive_file_position"); }


//Out Int Sent Packets
// Amount of data packets sent.
bool was_changed_send_packets() { return was_changed_("send_packets"); }
int geti_send_packets() { return geti_("send_packets"); }
void seti_send_packets(int value) { seti_("send_packets", value); }
void increase_int_send_packets(int increase = 1) { increase_int_("send_packets", increase); }
void repaint_send_packets() { repaint_("send_packets"); }

//Checkbox Is New Data
// Is new data to send at this frame.
bool was_changed_send_new_data() { return was_changed_("send_new_data"); }
int geti_send_new_data() { return geti_("send_new_data"); }
void repaint_send_new_data() { repaint_("send_new_data"); }

//Text Send Data
//Data to send.
bool was_changed_send_data() { return was_changed_("send_data"); }
QString gets_send_data() { return gets_("send_data"); }
QStringList get_strings_send_data() { return get_strings_("send_data"); }
void repaint_send_data() { repaint_("send_data"); }

//Button Send
//Send data immediately.
bool was_changed_btn_send() { return was_changed_("btn_send"); }
int geti_btn_send() { return geti_("btn_send"); }
void repaint_btn_send() { repaint_("btn_send"); }
QString button_btn_send() { return "btn_send"; }

//Out Text Send Data
//Data to send from a file.
bool was_changed_send_emulated_data() { return was_changed_("send_emulated_data"); }
QString gets_send_emulated_data() { return gets_("send_emulated_data"); }
QStringList get_strings_send_emulated_data() { return get_strings_("send_emulated_data"); }
void sets_send_emulated_data(QString value) { sets_("send_emulated_data", value); }
void clear_string_send_emulated_data() { clear_string_("send_emulated_data"); }
void append_string_send_emulated_data(QString v, int extra_new_lines_count = 0) { append_string_("send_emulated_data", v, extra_new_lines_count); }
void append_string_send_emulated_data(QStringList v, int extra_new_lines_count = 0) { append_string_("send_emulated_data", v, extra_new_lines_count); }
void repaint_send_emulated_data() { repaint_("send_emulated_data"); }

//Out Int Received Packets
// Amount of data packets received.
bool was_changed_received_packets() { return was_changed_("received_packets"); }
int geti_received_packets() { return geti_("received_packets"); }
void seti_received_packets(int value) { seti_("received_packets", value); }
void increase_int_received_packets(int increase = 1) { increase_int_("received_packets", increase); }
void repaint_received_packets() { repaint_("received_packets"); }

//Out Checkbox Is New Data
// Is new data received at this frame.
bool was_changed_received_new_data() { return was_changed_("received_new_data"); }
int geti_received_new_data() { return geti_("received_new_data"); }
void seti_received_new_data(int value) { seti_("received_new_data", value); }
void repaint_received_new_data() { repaint_("received_new_data"); }

//Out Text Received Data
//Received data.
bool was_changed_received_data() { return was_changed_("received_data"); }
QString gets_received_data() { return gets_("received_data"); }
QStringList get_strings_received_data() { return get_strings_("received_data"); }
void sets_received_data(QString value) { sets_("received_data", value); }
void clear_string_received_data() { clear_string_("received_data"); }
void append_string_received_data(QString v, int extra_new_lines_count = 0) { append_string_("received_data", v, extra_new_lines_count); }
void append_string_received_data(QStringList v, int extra_new_lines_count = 0) { append_string_("received_data", v, extra_new_lines_count); }
void repaint_received_data() { repaint_("received_data"); }

//----------------------------------------------------
