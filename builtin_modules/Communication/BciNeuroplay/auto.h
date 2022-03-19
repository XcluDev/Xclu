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

//----------------------------------------------------
//Page Rhythms
//Read brain rhythms.

//Const Checkbox rhythms
//Enable reading brain rhythms.
bool was_changed_rhythm_enabled() { return was_changed_("rhythm_enabled"); }
int geti_rhythm_enabled() { return geti_("rhythm_enabled"); }
void repaint_rhythm_enabled() { repaint_("rhythm_enabled"); }

//Out Float Alpha
//Alpha rhythm.
bool was_changed_rhythm_alpha() { return was_changed_("rhythm_alpha"); }
float getf_rhythm_alpha() { return getf_("rhythm_alpha"); }
void setf_rhythm_alpha(float value) { setf_("rhythm_alpha", value); }
void repaint_rhythm_alpha() { repaint_("rhythm_alpha"); }

//Out Float Beta
//Beta rhythm.
bool was_changed_rhythm_beta() { return was_changed_("rhythm_beta"); }
float getf_rhythm_beta() { return getf_("rhythm_beta"); }
void setf_rhythm_beta(float value) { setf_("rhythm_beta", value); }
void repaint_rhythm_beta() { repaint_("rhythm_beta"); }

//Out Float Delta
//Delta rhythm.
bool was_changed_rhythm_delta() { return was_changed_("rhythm_delta"); }
float getf_rhythm_delta() { return getf_("rhythm_delta"); }
void setf_rhythm_delta(float value) { setf_("rhythm_delta", value); }
void repaint_rhythm_delta() { repaint_("rhythm_delta"); }

//Out Float Gamma
//Gamma rhythm.
bool was_changed_rhythm_gamma() { return was_changed_("rhythm_gamma"); }
float getf_rhythm_gamma() { return getf_("rhythm_gamma"); }
void setf_rhythm_gamma(float value) { setf_("rhythm_gamma", value); }
void repaint_rhythm_gamma() { repaint_("rhythm_gamma"); }

//Out Float Theta
//Theta rhythm.
bool was_changed_rhythm_theta() { return was_changed_("rhythm_theta"); }
float getf_rhythm_theta() { return getf_("rhythm_theta"); }
void setf_rhythm_theta(float value) { setf_("rhythm_theta", value); }
void repaint_rhythm_theta() { repaint_("rhythm_theta"); }

//Out Float Time
//Time stamp.
bool was_changed_rhythm_t() { return was_changed_("rhythm_t"); }
float getf_rhythm_t() { return getf_("rhythm_t"); }
void setf_rhythm_t(float value) { setf_("rhythm_t", value); }
void repaint_rhythm_t() { repaint_("rhythm_t"); }

//----------------------------------------------------
//Page Spectrum
//Read EEG spectrum.

//Const Checkbox Spectrum Frame
//Enable reading EEG spectrum frame, updated 0.1 sec by default. Note: it puts device into the grabbing mode.
bool was_changed_spectrum_frame_enabled() { return was_changed_("spectrum_frame_enabled"); }
int geti_spectrum_frame_enabled() { return geti_("spectrum_frame_enabled"); }
void repaint_spectrum_frame_enabled() { repaint_("spectrum_frame_enabled"); }

//Out Object Frame
//Moving frame of spectrum.
bool was_changed_spectrum_frame() { return was_changed_("spectrum_frame"); }
XProtectedObject *getobject_spectrum_frame() { return get_object_("spectrum_frame"); }
void setobject_spectrum_frame(XProtectedObject *value) { set_object_("spectrum_frame", value); }
void setobject_spectrum_frame(XProtectedObject &value) { set_object_("spectrum_frame", value); }
void repaint_spectrum_frame() { repaint_("spectrum_frame"); }

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

//Const Checkbox Graphs Frame
//Enable reading EEG graphs frame.
bool was_changed_graphs_frame_enabled() { return was_changed_("graphs_frame_enabled"); }
int geti_graphs_frame_enabled() { return geti_("graphs_frame_enabled"); }
void repaint_graphs_frame_enabled() { repaint_("graphs_frame_enabled"); }

//Out Object Frame
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
