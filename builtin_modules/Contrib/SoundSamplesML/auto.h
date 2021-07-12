//----------------------------------------------------
//Interface for XClassSoundSamplesML
//Created automatically.
//----------------------------------------------------
//Page Wav To Bin
//Convert folder with equal-length WAV files into a single binary file and text file with the details.

//String Input Folder
//Folder for input wav files.
bool was_changed_join_input_folder() { return was_changed_("join_input_folder"); }
QString gets_join_input_folder() { return gets_("join_input_folder"); }
QStringList get_strings_join_input_folder() { return get_strings_("join_input_folder"); }
void repaint_join_input_folder() { repaint_("join_input_folder"); }


//String Output Folder
//Folder for output data - binary file and text file with description.
bool was_changed_join_output_folder() { return was_changed_("join_output_folder"); }
QString gets_join_output_folder() { return gets_("join_output_folder"); }
QStringList get_strings_join_output_folder() { return get_strings_("join_output_folder"); }
void repaint_join_output_folder() { repaint_("join_output_folder"); }


//Int WAV Parts
//Number of parts in each WAV.
bool was_changed_join_wav_parts() { return was_changed_("join_wav_parts"); }
int geti_join_wav_parts() { return geti_("join_wav_parts"); }
void repaint_join_wav_parts() { repaint_("join_wav_parts"); }

//Checkbox Discard Silence
//Discard silent sound parts.
bool was_changed_join_discard_empty() { return was_changed_("join_discard_empty"); }
int geti_join_discard_empty() { return geti_("join_discard_empty"); }
void repaint_join_discard_empty() { repaint_("join_discard_empty"); }


//Button Convert
//Join WAVs to a binary file.
bool was_changed_join_convert() { return was_changed_("join_convert"); }
int geti_join_convert() { return geti_("join_convert"); }
void repaint_join_convert() { repaint_("join_convert"); }
QString button_join_convert() { return "join_convert"; }


//Out Text Console
//Conversion details.
bool was_changed_join_console() { return was_changed_("join_console"); }
QString gets_join_console() { return gets_("join_console"); }
QStringList get_strings_join_console() { return get_strings_("join_console"); }
void sets_join_console(QString value) { sets_("join_console", value); }
void clear_string_join_console() { clear_string_("join_console"); }
void append_string_join_console(QString v, int extra_new_lines_count = 0) { append_string_("join_console", v, extra_new_lines_count); }
void append_string_join_console(QStringList v, int extra_new_lines_count = 0) { append_string_("join_console", v, extra_new_lines_count); }
void repaint_join_console() { repaint_("join_console"); }

//----------------------------------------------------
