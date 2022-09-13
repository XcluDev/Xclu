//----------------------------------------------------
//Interface for XClassSoundOsc
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Checkbox Enabled
//Generate output sound.
bool was_changed_out_enabled() { return was_changed_("out_enabled"); }
int geti_out_enabled() { return geti_("out_enabled"); }


//Float Frequency
//Oscillator basic frequency.
bool was_changed_freq() { return was_changed_("freq"); }
float getf_freq() { return getf_("freq"); }


//Float Volume
//Main volume.
bool was_changed_volume() { return was_changed_("volume"); }
float getf_volume() { return getf_("volume"); }

//Float Vol mod
//Modulation value.
bool was_changed_volume_mod() { return was_changed_("volume_mod"); }
float getf_volume_mod() { return getf_("volume_mod"); }


//Checkbox FM
//Is FM enabled.
bool was_changed_fm_enabled() { return was_changed_("fm_enabled"); }
int geti_fm_enabled() { return geti_("fm_enabled"); }

//Float Rate
//FM frequency.
bool was_changed_fm_rate() { return was_changed_("fm_rate"); }
float getf_fm_rate() { return getf_("fm_rate"); }

//Float Range
//FM range (instead of index).
bool was_changed_fm_range() { return was_changed_("fm_range"); }
float getf_fm_range() { return getf_("fm_range"); }


//Checkbox AM
//Is AM enabled.
bool was_changed_am_enabled() { return was_changed_("am_enabled"); }
int geti_am_enabled() { return geti_("am_enabled"); }

//Float Rate
//AM frequency.
bool was_changed_am_rate() { return was_changed_("am_rate"); }
float getf_am_rate() { return getf_("am_rate"); }

//Float Range
//AM range.
bool was_changed_am_range() { return was_changed_("am_range"); }
float getf_am_range() { return getf_("am_range"); }

//----------------------------------------------------
//Page Setup Speed
//Updating speed setup.

//Float Volume speed
//Speed of changing volume.
bool was_changed_vol_speed() { return was_changed_("vol_speed"); }
float getf_vol_speed() { return getf_("vol_speed"); }

//Float Freq. speed
//Speed of changing frequency.
bool was_changed_freq_speed() { return was_changed_("freq_speed"); }
float getf_freq_speed() { return getf_("freq_speed"); }

//----------------------------------------------------
