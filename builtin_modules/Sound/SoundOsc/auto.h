//----------------------------------------------------
//Interface for XClassSoundOsc
//Created automatically at 2020.09.12 21:37:02
//----------------------------------------------------
//Page Main
//

//Checkbox Enabled
//Generate output sound.
int i_out_enabled() { return geti("out_enabled"); }

//Checkbox External Modulation
//Should apply external modulation for controlling from other modules.
int i_mod_enabled() { return geti("mod_enabled"); }


//Float Frequency
//Oscillator basic frequency.
float f_freq() { return getf("freq"); }


//Float Volume
//Main volume.
float f_volume() { return getf("volume"); }

//Out Float vol mod
//Modulation value.
float f_volume_mod() { return getf("volume_mod"); }
void f_volume_mod(float value) { setf("volume_mod", value); }


//Checkbox FM
//Is FM enabled.
int i_fm_enabled() { return geti("fm_enabled"); }

//Float Rate
//FM frequency.
float f_fm_rate() { return getf("fm_rate"); }

//Float Range
//FM range (instead of index).
float f_fm_range() { return getf("fm_range"); }

//Out Float fm rate
//
float f_fm_rate_mod() { return getf("fm_rate_mod"); }
void f_fm_rate_mod(float value) { setf("fm_rate_mod", value); }

//Out Float fm range
//
float f_fm_range_mod() { return getf("fm_range_mod"); }
void f_fm_range_mod(float value) { setf("fm_range_mod", value); }


//Checkbox AM
//Is AM enabled.
int i_am_enabled() { return geti("am_enabled"); }

//Float Rate
//AM frequency.
float f_am_rate() { return getf("am_rate"); }

//Float Range
//AM range.
float f_am_range() { return getf("am_range"); }

//Out Float am rate
//
float f_am_rate_mod() { return getf("am_rate_mod"); }
void f_am_rate_mod(float value) { setf("am_rate_mod", value); }

//Out Float am range
//
float f_am_range_mod() { return getf("am_range_mod"); }
void f_am_range_mod(float value) { setf("am_range_mod", value); }

//----------------------------------------------------
//Page Modulation Setup
//

//String volume link
//Modulation link, such as module1->volumes(0,2)
QString s_volume_link() { return gets("volume_link"); }

//String fm rate link
//
QString s_fm_rate_link() { return gets("fm_rate_link"); }

//String fm range link
//
QString s_fm_range_link() { return gets("fm_range_link"); }

//String am rate link
//
QString s_am_rate_link() { return gets("am_rate_link"); }

//String am range link
//
QString s_am_range_link() { return gets("am_range_link"); }

//----------------------------------------------------
//Page Setup Speed
//Updating speed setup.

//Float Volume speed
//Speed of changing volume.
float f_vol_speed() { return getf("vol_speed"); }

//Float Freq. speed
//Speed of changing frequency.
float f_freq_speed() { return getf("freq_speed"); }

//----------------------------------------------------
