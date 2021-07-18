//----------------------------------------------------
//Interface for XClassSoundSamplesML
//Created automatically.
//----------------------------------------------------
//Page Make Database
//Create database from folder containing equal-length WAV files into a single binary file and text file with the details.

//String Input WAVs Folder
//Folder for input wav files.
bool was_changed_join_input_folder() { return was_changed_("join_input_folder"); }
QString gets_join_input_folder() { return gets_("join_input_folder"); }
QStringList get_strings_join_input_folder() { return get_strings_("join_input_folder"); }
void repaint_join_input_folder() { repaint_("join_input_folder"); }


//String Resulted Database Folder
//Folder for created database - binary file and text file with description.
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

//Int Input Sample Rate
//Expected WAVs sample rate.
bool was_changed_join_sample_rate() { return was_changed_("join_sample_rate"); }
int geti_join_sample_rate() { return geti_("join_sample_rate"); }
void repaint_join_sample_rate() { repaint_("join_sample_rate"); }


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
//Page Load Database
//Load database (created on the prevoius page).

//String Database Folder
//Folder for input database binary file and text file with description.
bool was_changed_db_folder() { return was_changed_("db_folder"); }
QString gets_db_folder() { return gets_("db_folder"); }
QStringList get_strings_db_folder() { return get_strings_("db_folder"); }
void repaint_db_folder() { repaint_("db_folder"); }

//Button Load
//Load database.
bool was_changed_db_load() { return was_changed_("db_load"); }
int geti_db_load() { return geti_("db_load"); }
void repaint_db_load() { repaint_("db_load"); }
QString button_db_load() { return "db_load"; }

//Checkbox Autoload
//Autoload database at start, if exists.
bool was_changed_db_autoload() { return was_changed_("db_autoload"); }
int geti_db_autoload() { return geti_("db_autoload"); }
void repaint_db_autoload() { repaint_("db_autoload"); }


//Out Int Sounds
//Number of sounds.
bool was_changed_db_sounds() { return was_changed_("db_sounds"); }
int geti_db_sounds() { return geti_("db_sounds"); }
void seti_db_sounds(int value) { seti_("db_sounds", value); }
void increase_int_db_sounds(int increase = 1) { increase_int_("db_sounds", increase); }
void repaint_db_sounds() { repaint_("db_sounds"); }

//Out Int Length
//Audio samples in one sound.
bool was_changed_db_length() { return was_changed_("db_length"); }
int geti_db_length() { return geti_("db_length"); }
void seti_db_length(int value) { seti_("db_length", value); }
void increase_int_db_length(int increase = 1) { increase_int_("db_length", increase); }
void repaint_db_length() { repaint_("db_length"); }

//Out Int Sample Rate
//Sample Rate.
bool was_changed_db_sample_rate() { return was_changed_("db_sample_rate"); }
int geti_db_sample_rate() { return geti_("db_sample_rate"); }
void seti_db_sample_rate(int value) { seti_("db_sample_rate", value); }
void increase_int_db_sample_rate(int increase = 1) { increase_int_("db_sample_rate", increase); }
void repaint_db_sample_rate() { repaint_("db_sample_rate"); }

//Out Int Channels
//Audio samples in one sound.
bool was_changed_db_channels() { return was_changed_("db_channels"); }
int geti_db_channels() { return geti_("db_channels"); }
void seti_db_channels(int value) { seti_("db_channels", value); }
void increase_int_db_channels(int increase = 1) { increase_int_("db_channels", increase); }
void repaint_db_channels() { repaint_("db_channels"); }

//----------------------------------------------------
//Page Visualize
//Analyze and draw sounds using various methods, and play them by mouse clicking.

//Enum Method
//Drawing method
enum enum_draw_method {
    draw_method_File_Order = 0,
    draw_method_Simple = 1,
    draw_method_tSNE = 2,
    draw_method_N__ = 3
};
bool was_changed_draw_method() { return was_changed_("draw_method"); }
enum_draw_method gete_draw_method() { return enum_draw_method(geti_("draw_method")); }
QString getraw_draw_method() { return getraw_("draw_method");}

//----------------------------------------------------
