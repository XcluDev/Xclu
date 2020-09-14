//----------------------------------------------------
//Interface for XClassScanFolder
//Created automatically.
//----------------------------------------------------
//Page Main
//General settings.

//String Folder
//Folder to scan.
bool was_changed_folder() { return was_changed_("folder"); }
QString gets_folder() { return gets_("folder"); }
QStringList get_strings_folder() { return get_strings_("folder"); }

//Enum Filter
//Type of content we are searching for.
enum enum_filter {
    filter_All = 0,
    filter_Files = 1,
    filter_Folders = 2,
    filter_Images = 3,
    filter_Videos = 4,
    filter_Txt = 5,
    filter_Csv = 6,
    filter_Ini = 7,
    filter_Xml = 8,
    filter_Json = 9,
    filter_Custom = 10,
    filter_N__ = 11
};
bool was_changed_filter() { return was_changed_("filter"); }
enum_filter gete_filter() { return enum_filter(geti_("filter")); }

//String Custom Filter
//Custom filter specification.
bool was_changed_custom_filter() { return was_changed_("custom_filter"); }
QString gets_custom_filter() { return gets_("custom_filter"); }
QStringList get_strings_custom_filter() { return get_strings_("custom_filter"); }


//Const Enum Run Mode
//
enum enum_run_mode {
    run_mode_By_Button_Press = 0,
    run_mode_At_Project_Start = 1,
    run_mode_N__ = 2
};
bool was_changed_run_mode() { return was_changed_("run_mode"); }
enum_run_mode gete_run_mode() { return enum_run_mode(geti_("run_mode")); }

//Button Run
//Press to start scanning.
bool was_changed_run_button() { return was_changed_("run_button"); }
int geti_run_button() { return geti_("run_button"); }
QString button_run_button() { return "run_button"; }


//Enum Result Type
//Represent results as a list of all or several found files, or one-by-one as a string.
enum enum_result_type {
    result_type_List_Whole = 0,
    result_type_List_Batch = 1,
    result_type_One_String_By_Update = 2,
    result_type_Burst_of_Strings = 3,
    result_type_N__ = 4
};
bool was_changed_result_type() { return was_changed_("result_type"); }
enum_result_type gete_result_type() { return enum_result_type(geti_("result_type")); }

//Enum On New Data
//
enum enum_on_data {
    on_data_Checkbox = 0,
    on_data_Send_Press = 1,
    on_data_N__ = 2
};
bool was_changed_on_data() { return was_changed_("on_data"); }
enum_on_data gete_on_data() { return enum_on_data(geti_("on_data")); }

//Enum On End
//
enum enum_on_end {
    on_end_Do_Nothing = 0,
    on_end_Stop_Project = 1,
    on_end_N__ = 2
};
bool was_changed_on_end() { return was_changed_("on_end"); }
enum_on_end gete_on_end() { return enum_on_end(geti_("on_end")); }


//Out Int Items Processed
//How much items are processed.
bool was_changed_items_processed() { return was_changed_("items_processed"); }
int geti_items_processed() { return geti_("items_processed"); }
void seti_items_processed(int value) { seti_("items_processed", value); }
void increase_int_items_processed(int increase = 1) { increase_int_("items_processed", increase); }

//Out Text Output Items
//Output list of found files.
bool was_changed_output_items() { return was_changed_("output_items"); }
QString gets_output_items() { return gets_("output_items"); }
QStringList get_strings_output_items() { return get_strings_("output_items"); }
void sets_output_items(QString value) { sets_("output_items", value); }
void clear_string_output_items() { clear_string_("output_items"); }
void append_string_output_items(QString v, int extra_new_lines_count = 0) { append_string_("output_items", v, extra_new_lines_count); }
void append_string_output_items(QStringList v, int extra_new_lines_count = 0) { append_string_("output_items", v, extra_new_lines_count); }

//Out String Output Item
//Output string.
bool was_changed_output_item() { return was_changed_("output_item"); }
QString gets_output_item() { return gets_("output_item"); }
QStringList get_strings_output_item() { return get_strings_("output_item"); }
void sets_output_item(QString value) { sets_("output_item", value); }
void clear_string_output_item() { clear_string_("output_item"); }
void append_string_output_item(QString v, int extra_new_lines_count = 0) { append_string_("output_item", v, extra_new_lines_count); }
void append_string_output_item(QStringList v, int extra_new_lines_count = 0) { append_string_("output_item", v, extra_new_lines_count); }

//----------------------------------------------------
