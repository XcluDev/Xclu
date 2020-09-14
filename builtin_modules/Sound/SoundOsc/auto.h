//----------------------------------------------------
//Interface for XClassSoundOsc
//Created automatically at 2020.09.14 11:01:46
//----------------------------------------------------
//Page Main
//

//Checkbox Enabled
//Generate output sound.
bool was_changed_out_enabled() { return was_changed("out_enabled"); }
int geti_out_enabled() { return geti("out_enabled"); }

//Checkbox External Modulation
//Should apply external modulation for controlling from other modules.
bool was_changed_mod_enabled() { return was_changed("mod_enabled"); }
int geti_mod_enabled() { return geti("mod_enabled"); }


//Float Frequency
//Oscillator basic frequency.
bool was_changed_freq() { return was_changed("freq"); }
float getf_freq() { return getf("freq"); }


//Float Volume
//Main volume.
bool was_changed_volume() { return was_changed("volume"); }
float getf_volume() { return getf("volume"); }

//Out Float vol mod
//Modulation value.
bool was_changed_volume_mod() { return was_changed("volume_mod"); }
float getf_volume_mod() { return getf("volume_mod"); }
void setf_volume_mod(float value) { setf("volume_mod", value); }


//Checkbox FM
//Is FM enabled.
bool was_changed_fm_enabled() { return was_changed("fm_enabled"); }
int geti_fm_enabled() { return geti("fm_enabled"); }

//Float Rate
//FM frequency.
bool was_changed_fm_rate() { return was_changed("fm_rate"); }
float getf_fm_rate() { return getf("fm_rate"); }

//Float Range
//FM range (instead of index).
bool was_changed_fm_range() { return was_changed("fm_range"); }
float getf_fm_range() { return getf("fm_range"); }

//Out Float fm rate
//
bool was_changed_fm_rate_mod() { return was_changed("fm_rate_mod"); }
float getf_fm_rate_mod() { return getf("fm_rate_mod"); }
void setf_fm_rate_mod(float value) { setf("fm_rate_mod", value); }

//Out Float fm range
//
bool was_changed_fm_range_mod() { return was_changed("fm_range_mod"); }
float getf_fm_range_mod() { return getf("fm_range_mod"); }
void setf_fm_range_mod(float value) { setf("fm_range_mod", value); }


//Checkbox AM
//Is AM enabled.
bool was_changed_am_enabled() { return was_changed("am_enabled"); }
int geti_am_enabled() { return geti("am_enabled"); }

//Float Rate
//AM frequency.
bool was_changed_am_rate() { return was_changed("am_rate"); }
float getf_am_rate() { return getf("am_rate"); }

//Float Range
//AM range.
bool was_changed_am_range() { return was_changed("am_range"); }
float getf_am_range() { return getf("am_range"); }

//Out Float am rate
//
bool was_changed_am_rate_mod() { return was_changed("am_rate_mod"); }
float getf_am_rate_mod() { return getf("am_rate_mod"); }
void setf_am_rate_mod(float value) { setf("am_rate_mod", value); }

//Out Float am range
//
bool was_changed_am_range_mod() { return was_changed("am_range_mod"); }
float getf_am_range_mod() { return getf("am_range_mod"); }
void setf_am_range_mod(float value) { setf("am_range_mod", value); }

//----------------------------------------------------
//Page Modulation Setup
//

//String volume link
//Modulation link, such as module1->volumes(0,2)
bool was_changed_volume_link() { return was_changed("volume_link"); }
QString gets_volume_link() { return gets("volume_link"); }
QStringList get_strings_volume_link() { return get_strings("volume_link"); }

//String fm rate link
//
bool was_changed_fm_rate_link() { return was_changed("fm_rate_link"); }
QString gets_fm_rate_link() { return gets("fm_rate_link"); }
QStringList get_strings_fm_rate_link() { return get_strings("fm_rate_link"); }

//String fm range link
//
bool was_changed_fm_range_link() { return was_changed("fm_range_link"); }
QString gets_fm_range_link() { return gets("fm_range_link"); }
QStringList get_strings_fm_range_link() { return get_strings("fm_range_link"); }

//String am rate link
//
bool was_changed_am_rate_link() { return was_changed("am_rate_link"); }
QString gets_am_rate_link() { return gets("am_rate_link"); }
QStringList get_strings_am_rate_link() { return get_strings("am_rate_link"); }

//String am range link
//
bool was_changed_am_range_link() { return was_changed("am_range_link"); }
QString gets_am_range_link() { return gets("am_range_link"); }
QStringList get_strings_am_range_link() { return get_strings("am_range_link"); }

//----------------------------------------------------
//Page Setup Speed
//Updating speed setup.

//Float Volume speed
//Speed of changing volume.
bool was_changed_vol_speed() { return was_changed("vol_speed"); }
float getf_vol_speed() { return getf("vol_speed"); }

//Float Freq. speed
//Speed of changing frequency.
bool was_changed_freq_speed() { return was_changed("freq_speed"); }
float getf_freq_speed() { return getf("freq_speed"); }

//----------------------------------------------------
