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


//Out String Stat
//How much requests were sent, received, lost.
bool was_changed_stat() { return was_changed_("stat"); }
QString gets_stat() { return gets_("stat"); }
QStringList get_strings_stat() { return get_strings_("stat"); }
void sets_stat(QString value) { sets_("stat", value); }
void clear_string_stat() { clear_string_("stat"); }
void append_string_stat(QString v, int extra_new_lines_count = 0) { append_string_("stat", v, extra_new_lines_count); }
void append_string_stat(QStringList v, int extra_new_lines_count = 0) { append_string_("stat", v, extra_new_lines_count); }
void repaint_stat() { repaint_("stat"); }

//----------------------------------------------------
//Page Record
//Recording data.

//Enum Source
//Source for recording.
enum enum_recording_source {
    recording_source_Rhythms_Avg = 0,
    recording_source_Rhytms_All_Channels = 1,
    recording_source_N__ = 2
};
bool was_changed_recording_source() { return was_changed_("recording_source"); }
enum_recording_source gete_recording_source() { return enum_recording_source(geti_("recording_source")); }
QString getraw_recording_source() { return getraw_("recording_source");}

//String Folder
//Folder for recordings.
bool was_changed_recording_folder() { return was_changed_("recording_folder"); }
QString gets_recording_folder() { return gets_("recording_folder"); }
QStringList get_strings_recording_folder() { return get_strings_("recording_folder"); }
void repaint_recording_folder() { repaint_("recording_folder"); }

//Button Start
// Press to start recording.
bool was_changed_btn_recording_start() { return was_changed_("btn_recording_start"); }
int geti_btn_recording_start() { return geti_("btn_recording_start"); }
void repaint_btn_recording_start() { repaint_("btn_recording_start"); }
QString button_btn_recording_start() { return "btn_recording_start"; }

//Button Stop
// Press to stop recording.
bool was_changed_btn_recording_stop() { return was_changed_("btn_recording_stop"); }
int geti_btn_recording_stop() { return geti_("btn_recording_stop"); }
void repaint_btn_recording_stop() { repaint_("btn_recording_stop"); }
QString button_btn_recording_stop() { return "btn_recording_stop"; }

//Out Text Status
// Recording status.
bool was_changed_recording_status() { return was_changed_("recording_status"); }
QString gets_recording_status() { return gets_("recording_status"); }
QStringList get_strings_recording_status() { return get_strings_("recording_status"); }
void sets_recording_status(QString value) { sets_("recording_status", value); }
void clear_string_recording_status() { clear_string_("recording_status"); }
void append_string_recording_status(QString v, int extra_new_lines_count = 0) { append_string_("recording_status", v, extra_new_lines_count); }
void append_string_recording_status(QStringList v, int extra_new_lines_count = 0) { append_string_("recording_status", v, extra_new_lines_count); }
void repaint_recording_status() { repaint_("recording_status"); }

//----------------------------------------------------
//Page Values
//Read meditation and concentration.

//Const Checkbox Values
//Enable reading meditation and concentration.
bool was_changed_values_enabled() { return was_changed_("values_enabled"); }
int geti_values_enabled() { return geti_("values_enabled"); }
void repaint_values_enabled() { repaint_("values_enabled"); }

//Out Float Meditation
//Meditation value.
bool was_changed_value_meditation() { return was_changed_("value_meditation"); }
float getf_value_meditation() { return getf_("value_meditation"); }
void setf_value_meditation(float value) { setf_("value_meditation", value); }
void repaint_value_meditation() { repaint_("value_meditation"); }

//Out Float Concentration
//Concentration value.
bool was_changed_value_concentration() { return was_changed_("value_concentration"); }
float getf_value_concentration() { return getf_("value_concentration"); }
void setf_value_concentration(float value) { setf_("value_concentration", value); }
void repaint_value_concentration() { repaint_("value_concentration"); }


//Checkbox OSC
//Send values by OSC.
bool was_changed_values_osc_group() { return was_changed_("values_osc_group"); }
int geti_values_osc_group() { return geti_("values_osc_group"); }
void repaint_values_osc_group() { repaint_("values_osc_group"); }

//Checkbox Enabled
//
bool was_changed_values_osc_enabled() { return was_changed_("values_osc_enabled"); }
int geti_values_osc_enabled() { return geti_("values_osc_enabled"); }
void repaint_values_osc_enabled() { repaint_("values_osc_enabled"); }

//String Address
//Sending address and port; use "127.0.0.1:..." instead "localhost:...".
bool was_changed_values_osc_address() { return was_changed_("values_osc_address"); }
QString gets_values_osc_address() { return gets_("values_osc_address"); }
QStringList get_strings_values_osc_address() { return get_strings_("values_osc_address"); }
void repaint_values_osc_address() { repaint_("values_osc_address"); }

//String Meditation Name
//OSC address for Meditation value.
bool was_changed_values_osc_meditation() { return was_changed_("values_osc_meditation"); }
QString gets_values_osc_meditation() { return gets_("values_osc_meditation"); }
QStringList get_strings_values_osc_meditation() { return get_strings_("values_osc_meditation"); }
void repaint_values_osc_meditation() { repaint_("values_osc_meditation"); }

//String Concentration Name
//OSC address for Concentration value.
bool was_changed_values_osc_concentration() { return was_changed_("values_osc_concentration"); }
QString gets_values_osc_concentration() { return gets_("values_osc_concentration"); }
QStringList get_strings_values_osc_concentration() { return get_strings_("values_osc_concentration"); }
void repaint_values_osc_concentration() { repaint_("values_osc_concentration"); }

//Out Int Send Frames
//
bool was_changed_values_osc_sent() { return was_changed_("values_osc_sent"); }
int geti_values_osc_sent() { return geti_("values_osc_sent"); }
void seti_values_osc_sent(int value) { seti_("values_osc_sent", value); }
void increase_int_values_osc_sent(int increase = 1) { increase_int_("values_osc_sent", increase); }
void repaint_values_osc_sent() { repaint_("values_osc_sent"); }

//----------------------------------------------------
//Page Rhythms
//Read brain rhythms.

//Const Checkbox Rhythms
//Enable reading brain rhythms.
bool was_changed_rhythms_enabled() { return was_changed_("rhythms_enabled"); }
int geti_rhythms_enabled() { return geti_("rhythms_enabled"); }
void repaint_rhythms_enabled() { repaint_("rhythms_enabled"); }

//String Averaging Channels
//List of channels for averaging, such as 1 2 3 4 5 6 7 8.
bool was_changed_rhythms_avg_channels() { return was_changed_("rhythms_avg_channels"); }
QString gets_rhythms_avg_channels() { return gets_("rhythms_avg_channels"); }
QStringList get_strings_rhythms_avg_channels() { return get_strings_("rhythms_avg_channels"); }
void repaint_rhythms_avg_channels() { repaint_("rhythms_avg_channels"); }

//Out Float Avg Delta
//Averaged delta rhythm.
bool was_changed_rhythm_avg_delta() { return was_changed_("rhythm_avg_delta"); }
float getf_rhythm_avg_delta() { return getf_("rhythm_avg_delta"); }
void setf_rhythm_avg_delta(float value) { setf_("rhythm_avg_delta", value); }
void repaint_rhythm_avg_delta() { repaint_("rhythm_avg_delta"); }

//Out Float Avg Theta
//Averaged theta rhythm.
bool was_changed_rhythm_avg_theta() { return was_changed_("rhythm_avg_theta"); }
float getf_rhythm_avg_theta() { return getf_("rhythm_avg_theta"); }
void setf_rhythm_avg_theta(float value) { setf_("rhythm_avg_theta", value); }
void repaint_rhythm_avg_theta() { repaint_("rhythm_avg_theta"); }

//Out Float Avg Alpha
//Averaged alpha rhythm.
bool was_changed_rhythm_avg_alpha() { return was_changed_("rhythm_avg_alpha"); }
float getf_rhythm_avg_alpha() { return getf_("rhythm_avg_alpha"); }
void setf_rhythm_avg_alpha(float value) { setf_("rhythm_avg_alpha", value); }
void repaint_rhythm_avg_alpha() { repaint_("rhythm_avg_alpha"); }

//Out Float Avg Beta
//Averaged beta rhythm.
bool was_changed_rhythm_avg_beta() { return was_changed_("rhythm_avg_beta"); }
float getf_rhythm_avg_beta() { return getf_("rhythm_avg_beta"); }
void setf_rhythm_avg_beta(float value) { setf_("rhythm_avg_beta", value); }
void repaint_rhythm_avg_beta() { repaint_("rhythm_avg_beta"); }

//Out Float Avg Gamma
//Averaged gamma rhythm.
bool was_changed_rhythm_avg_gamma() { return was_changed_("rhythm_avg_gamma"); }
float getf_rhythm_avg_gamma() { return getf_("rhythm_avg_gamma"); }
void setf_rhythm_avg_gamma(float value) { setf_("rhythm_avg_gamma", value); }
void repaint_rhythm_avg_gamma() { repaint_("rhythm_avg_gamma"); }


//Out String Delta
//Delta rhythms for all channels.
bool was_changed_rhythms_delta() { return was_changed_("rhythms_delta"); }
QString gets_rhythms_delta() { return gets_("rhythms_delta"); }
QStringList get_strings_rhythms_delta() { return get_strings_("rhythms_delta"); }
void sets_rhythms_delta(QString value) { sets_("rhythms_delta", value); }
void clear_string_rhythms_delta() { clear_string_("rhythms_delta"); }
void append_string_rhythms_delta(QString v, int extra_new_lines_count = 0) { append_string_("rhythms_delta", v, extra_new_lines_count); }
void append_string_rhythms_delta(QStringList v, int extra_new_lines_count = 0) { append_string_("rhythms_delta", v, extra_new_lines_count); }
void repaint_rhythms_delta() { repaint_("rhythms_delta"); }

//Out String Theta
//Theta rhythms for all channels.
bool was_changed_rhythms_theta() { return was_changed_("rhythms_theta"); }
QString gets_rhythms_theta() { return gets_("rhythms_theta"); }
QStringList get_strings_rhythms_theta() { return get_strings_("rhythms_theta"); }
void sets_rhythms_theta(QString value) { sets_("rhythms_theta", value); }
void clear_string_rhythms_theta() { clear_string_("rhythms_theta"); }
void append_string_rhythms_theta(QString v, int extra_new_lines_count = 0) { append_string_("rhythms_theta", v, extra_new_lines_count); }
void append_string_rhythms_theta(QStringList v, int extra_new_lines_count = 0) { append_string_("rhythms_theta", v, extra_new_lines_count); }
void repaint_rhythms_theta() { repaint_("rhythms_theta"); }

//Out String Alpha
//Alpha rhythms for all channels.
bool was_changed_rhythms_alpha() { return was_changed_("rhythms_alpha"); }
QString gets_rhythms_alpha() { return gets_("rhythms_alpha"); }
QStringList get_strings_rhythms_alpha() { return get_strings_("rhythms_alpha"); }
void sets_rhythms_alpha(QString value) { sets_("rhythms_alpha", value); }
void clear_string_rhythms_alpha() { clear_string_("rhythms_alpha"); }
void append_string_rhythms_alpha(QString v, int extra_new_lines_count = 0) { append_string_("rhythms_alpha", v, extra_new_lines_count); }
void append_string_rhythms_alpha(QStringList v, int extra_new_lines_count = 0) { append_string_("rhythms_alpha", v, extra_new_lines_count); }
void repaint_rhythms_alpha() { repaint_("rhythms_alpha"); }

//Out String Delta
//Delta rhythms for all channels.
bool was_changed_rhythms_beta() { return was_changed_("rhythms_beta"); }
QString gets_rhythms_beta() { return gets_("rhythms_beta"); }
QStringList get_strings_rhythms_beta() { return get_strings_("rhythms_beta"); }
void sets_rhythms_beta(QString value) { sets_("rhythms_beta", value); }
void clear_string_rhythms_beta() { clear_string_("rhythms_beta"); }
void append_string_rhythms_beta(QString v, int extra_new_lines_count = 0) { append_string_("rhythms_beta", v, extra_new_lines_count); }
void append_string_rhythms_beta(QStringList v, int extra_new_lines_count = 0) { append_string_("rhythms_beta", v, extra_new_lines_count); }
void repaint_rhythms_beta() { repaint_("rhythms_beta"); }

//Out String Gamma
//Gamma rhythms for all channels.
bool was_changed_rhythms_gamma() { return was_changed_("rhythms_gamma"); }
QString gets_rhythms_gamma() { return gets_("rhythms_gamma"); }
QStringList get_strings_rhythms_gamma() { return get_strings_("rhythms_gamma"); }
void sets_rhythms_gamma(QString value) { sets_("rhythms_gamma", value); }
void clear_string_rhythms_gamma() { clear_string_("rhythms_gamma"); }
void append_string_rhythms_gamma(QString v, int extra_new_lines_count = 0) { append_string_("rhythms_gamma", v, extra_new_lines_count); }
void append_string_rhythms_gamma(QStringList v, int extra_new_lines_count = 0) { append_string_("rhythms_gamma", v, extra_new_lines_count); }
void repaint_rhythms_gamma() { repaint_("rhythms_gamma"); }

//----------------------------------------------------
//Page Spectrum
//Read EEG spectrum.

//Const Checkbox Spectrum
//Enable reading EEG spectrum frame, updated 0.1 sec by default. Note: it puts device into the grabbing mode.
bool was_changed_spectrum_enabled() { return was_changed_("spectrum_enabled"); }
int geti_spectrum_enabled() { return geti_("spectrum_enabled"); }
void repaint_spectrum_enabled() { repaint_("spectrum_enabled"); }

//Out Object Spectrum Data
//Moving frame of spectrum.
bool was_changed_spectrum_data() { return was_changed_("spectrum_data"); }
XProtectedObject *getobject_spectrum_data() { return get_object_("spectrum_data"); }
void setobject_spectrum_data(XProtectedObject *value) { set_object_("spectrum_data", value); }
void setobject_spectrum_data(XProtectedObject &value) { set_object_("spectrum_data", value); }
void repaint_spectrum_data() { repaint_("spectrum_data"); }

//Const Checkbox Spectrum Record
//Enable recording spectrum, after disabling the object is ready. Note: it puts device into the grabbing mode.
bool was_changed_spectrum_record_enabled() { return was_changed_("spectrum_record_enabled"); }
int geti_spectrum_record_enabled() { return geti_("spectrum_record_enabled"); }
void repaint_spectrum_record_enabled() { repaint_("spectrum_record_enabled"); }

//Out Object Recording
//Recorded spectrum.
bool was_changed_spectrum_recording() { return was_changed_("spectrum_recording"); }
XProtectedObject *getobject_spectrum_recording() { return get_object_("spectrum_recording"); }
void setobject_spectrum_recording(XProtectedObject *value) { set_object_("spectrum_recording", value); }
void setobject_spectrum_recording(XProtectedObject &value) { set_object_("spectrum_recording", value); }
void repaint_spectrum_recording() { repaint_("spectrum_recording"); }
//Button Save As
//
bool was_changed_btn_spectrum_save() { return was_changed_("btn_spectrum_save"); }
int geti_btn_spectrum_save() { return geti_("btn_spectrum_save"); }
void repaint_btn_spectrum_save() { repaint_("btn_spectrum_save"); }
QString button_btn_spectrum_save() { return "btn_spectrum_save"; }

//Button Load
//
bool was_changed_btn_spectrum_load() { return was_changed_("btn_spectrum_load"); }
int geti_btn_spectrum_load() { return geti_("btn_spectrum_load"); }
void repaint_btn_spectrum_load() { repaint_("btn_spectrum_load"); }
QString button_btn_spectrum_load() { return "btn_spectrum_load"; }

//Out Text Frequencies
//Frequencies.
bool was_changed_spectrum_freqs() { return was_changed_("spectrum_freqs"); }
QString gets_spectrum_freqs() { return gets_("spectrum_freqs"); }
QStringList get_strings_spectrum_freqs() { return get_strings_("spectrum_freqs"); }
void sets_spectrum_freqs(QString value) { sets_("spectrum_freqs", value); }
void clear_string_spectrum_freqs() { clear_string_("spectrum_freqs"); }
void append_string_spectrum_freqs(QString v, int extra_new_lines_count = 0) { append_string_("spectrum_freqs", v, extra_new_lines_count); }
void append_string_spectrum_freqs(QStringList v, int extra_new_lines_count = 0) { append_string_("spectrum_freqs", v, extra_new_lines_count); }
void repaint_spectrum_freqs() { repaint_("spectrum_freqs"); }

//----------------------------------------------------
//Page Graphs
//Read EEG graphs.

//Const Checkbox Graphs
//Enable reading EEG graphs frame.
bool was_changed_graphs_enabled() { return was_changed_("graphs_enabled"); }
int geti_graphs_enabled() { return geti_("graphs_enabled"); }
void repaint_graphs_enabled() { repaint_("graphs_enabled"); }

//Out Object Graphs Data
//Moving frame of graphs.
bool was_changed_graphs_frame() { return was_changed_("graphs_frame"); }
XProtectedObject *getobject_graphs_frame() { return get_object_("graphs_frame"); }
void setobject_graphs_frame(XProtectedObject *value) { set_object_("graphs_frame", value); }
void setobject_graphs_frame(XProtectedObject &value) { set_object_("graphs_frame", value); }
void repaint_graphs_frame() { repaint_("graphs_frame"); }

//Const Checkbox Graphs Record
//Enable recording graphs, after disabling the object is ready. Note: it puts device into the grabbing mode.
bool was_changed_graphs_record_enabled() { return was_changed_("graphs_record_enabled"); }
int geti_graphs_record_enabled() { return geti_("graphs_record_enabled"); }
void repaint_graphs_record_enabled() { repaint_("graphs_record_enabled"); }

//Out Object Recording
//Recorded graphs.
bool was_changed_graphs_recording() { return was_changed_("graphs_recording"); }
XProtectedObject *getobject_graphs_recording() { return get_object_("graphs_recording"); }
void setobject_graphs_recording(XProtectedObject *value) { set_object_("graphs_recording", value); }
void setobject_graphs_recording(XProtectedObject &value) { set_object_("graphs_recording", value); }
void repaint_graphs_recording() { repaint_("graphs_recording"); }
//Button Save As
//
bool was_changed_btn_graphs_save() { return was_changed_("btn_graphs_save"); }
int geti_btn_graphs_save() { return geti_("btn_graphs_save"); }
void repaint_btn_graphs_save() { repaint_("btn_graphs_save"); }
QString button_btn_graphs_save() { return "btn_graphs_save"; }

//Button Load
//
bool was_changed_btn_graphs_load() { return was_changed_("btn_graphs_load"); }
int geti_btn_graphs_load() { return geti_("btn_graphs_load"); }
void repaint_btn_graphs_load() { repaint_("btn_graphs_load"); }
QString button_btn_graphs_load() { return "btn_graphs_load"; }

//----------------------------------------------------
