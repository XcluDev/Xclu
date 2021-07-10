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


//String Output Folder
//Folder for output data - binary file and text file with description.
bool was_changed_join_output_folder() { return was_changed_("join_output_folder"); }
QString gets_join_output_folder() { return gets_("join_output_folder"); }
QStringList get_strings_join_output_folder() { return get_strings_("join_output_folder"); }

//Checkbox Use Absolute Path
//Use absolute path to this folder in scripts.
bool was_changed_train_folder_use_abs() { return was_changed_("train_folder_use_abs"); }
int geti_train_folder_use_abs() { return geti_("train_folder_use_abs"); }


//Button Convert
//Join WAVs to a binary file.
bool was_changed_join_convert() { return was_changed_("join_convert"); }
int geti_join_convert() { return geti_("join_convert"); }
QString button_join_convert() { return "join_convert"; }

//----------------------------------------------------
