//----------------------------------------------------
//Interface for XClassScanFolder
//Created automatically at 2020.09.12 21:37:02
//----------------------------------------------------
//Page Main
//General settings.

//String Folder
//Folder to scan.
QString s_folder() { return gets("folder"); }

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
enum_filter en_filter() { return enum_filter(geti("filter")); }

//String Custom Filter
//Custom filter specification.
QString s_custom_filter() { return gets("custom_filter"); }


//Const Enum Run Mode
//

enum enum_run_mode {
    run_mode_By_Button_Press = 0,
    run_mode_At_Project_Start = 1,
    run_mode_N__ = 2
};
enum_run_mode en_run_mode() { return enum_run_mode(geti("run_mode")); }

//Button Run
//Press to start scanning.
int i_run_button() { return geti("run_button"); }


//Enum Result Type
//Represent results as a list of all or several found files, or one-by-one as a string.

enum enum_result_type {
    result_type_List_Whole = 0,
    result_type_List_Batch = 1,
    result_type_One_String_By_Update = 2,
    result_type_Burst_of_Strings = 3,
    result_type_N__ = 4
};
enum_result_type en_result_type() { return enum_result_type(geti("result_type")); }

//Enum On New Data
//

enum enum_on_data {
    on_data_Checkbox = 0,
    on_data_Send_Press = 1,
    on_data_N__ = 2
};
enum_on_data en_on_data() { return enum_on_data(geti("on_data")); }

//Enum On End
//

enum enum_on_end {
    on_end_Do_Nothing = 0,
    on_end_Stop_Project = 1,
    on_end_N__ = 2
};
enum_on_end en_on_end() { return enum_on_end(geti("on_end")); }


//Out Int Items Processed
//How much items are processed.
int i_items_processed() { return geti("items_processed"); }
void i_items_processed(int value) { seti("items_processed", value); }

//Out Text Output Items
//Output list of found files.
QString s_output_items() { return gets("output_items"); }
void s_output_items(QString value) { sets("output_items", value); }

//Out String Output Item
//Output string.
QString s_output_item() { return gets("output_item"); }
void s_output_item(QString value) { sets("output_item", value); }

//----------------------------------------------------
