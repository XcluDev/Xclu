//----------------------------------------------------
//Interface for XClassSoundPlay
//Created automatically.
//----------------------------------------------------
//Page Main
//General settings.

//Enum Mode
//Single file or playlist.
enum enum_mode {
    mode_Single_File = 0,
    mode_Playlist = 1,
    mode_N__ = 2
};
bool was_changed_mode() { return was_changed_("mode"); }
enum_mode gete_mode() { return enum_mode(geti_("mode")); }
QString getraw_mode() { return getraw_("mode");}

//Button Play
//Start playing.
bool was_changed_play_button() { return was_changed_("play_button"); }
int geti_play_button() { return geti_("play_button"); }
QString button_play_button() { return "play_button"; }

//Button Stop
//Stop playing.
bool was_changed_stop_button() { return was_changed_("stop_button"); }
int geti_stop_button() { return geti_("stop_button"); }
QString button_stop_button() { return "stop_button"; }

//Button Next File
//Play next file.
bool was_changed_next_file() { return was_changed_("next_file"); }
int geti_next_file() { return geti_("next_file"); }
QString button_next_file() { return "next_file"; }

//Out Checkbox Playing
//Playing status.
bool was_changed_playing() { return was_changed_("playing"); }
int geti_playing() { return geti_("playing"); }
void seti_playing(int value) { seti_("playing", value); }

//Out String Playing File
//Which file plays now.
bool was_changed_playing_file() { return was_changed_("playing_file"); }
QString gets_playing_file() { return gets_("playing_file"); }
QStringList get_strings_playing_file() { return get_strings_("playing_file"); }
void sets_playing_file(QString value) { sets_("playing_file", value); }
void clear_string_playing_file() { clear_string_("playing_file"); }
void append_string_playing_file(QString v, int extra_new_lines_count = 0) { append_string_("playing_file", v, extra_new_lines_count); }
void append_string_playing_file(QStringList v, int extra_new_lines_count = 0) { append_string_("playing_file", v, extra_new_lines_count); }


//Enum Loop
//Looping mode.
enum enum_loop_mode_file {
    loop_mode_file_None = 0,
    loop_mode_file_Loop = 1,
    loop_mode_file_N__ = 2
};
bool was_changed_loop_mode_file() { return was_changed_("loop_mode_file"); }
enum_loop_mode_file gete_loop_mode_file() { return enum_loop_mode_file(geti_("loop_mode_file")); }
QString getraw_loop_mode_file() { return getraw_("loop_mode_file");}

//String File
//File to play.
bool was_changed_file_name() { return was_changed_("file_name"); }
QString gets_file_name() { return gets_("file_name"); }
QStringList get_strings_file_name() { return get_strings_("file_name"); }

//----------------------------------------------------
//Page Volume
//Volume and fading

//Float Volume
//Volume.
bool was_changed_volume() { return was_changed_("volume"); }
float getf_volume() { return getf_("volume"); }


//Float Fade Out
//Fade out - only when press "Stop" button.
bool was_changed_fade_out_sec() { return was_changed_("fade_out_sec"); }
float getf_fade_out_sec() { return getf_("fade_out_sec"); }

//----------------------------------------------------
