//----------------------------------------------------
//Interface for XClassFileCreate
//Created automatically.
//----------------------------------------------------
//Page Main
//General settings.


//Enum Unit
//Type of size measure
enum enum_file_size_unit {
    file_size_unit_Bytes = 0,
    file_size_unit_Kilobytes = 1,
    file_size_unit_Megabytes = 2,
    file_size_unit_Gigabytes = 3,
    file_size_unit_N__ = 4
};
bool was_changed_file_size_unit() { return was_changed_("file_size_unit"); }
enum_file_size_unit gete_file_size_unit() { return enum_file_size_unit(geti_("file_size_unit")); }
QString getraw_file_size_unit() { return getraw_("file_size_unit");}

//Int File Size
//File size.
bool was_changed_file_size_b() { return was_changed_("file_size_b"); }
int geti_file_size_b() { return geti_("file_size_b"); }

//Float File Size
//File size.
bool was_changed_file_size_kb() { return was_changed_("file_size_kb"); }
float getf_file_size_kb() { return getf_("file_size_kb"); }

//Float File Size
//File size.
bool was_changed_file_size_mb() { return was_changed_("file_size_mb"); }
float getf_file_size_mb() { return getf_("file_size_mb"); }

//Float File Size
//File size.
bool was_changed_file_size_gb() { return was_changed_("file_size_gb"); }
float getf_file_size_gb() { return getf_("file_size_gb"); }


//Enum Contents
//How to fill the file - fixed byte or random values.
enum enum_contents {
    contents_Fixed_Byte = 0,
    contents_Random_Bytes = 1,
    contents_N__ = 2
};
bool was_changed_contents() { return was_changed_("contents"); }
enum_contents gete_contents() { return enum_contents(geti_("contents")); }
QString getraw_contents() { return getraw_("contents");}

//Int Value
//Value which use to fill the file.
bool was_changed_fixed_value() { return was_changed_("fixed_value"); }
int geti_fixed_value() { return geti_("fixed_value"); }



//String File Name
//Output file name.
bool was_changed_file_name() { return was_changed_("file_name"); }
QString gets_file_name() { return gets_("file_name"); }
QStringList get_strings_file_name() { return get_strings_("file_name"); }


//Button Create
//Create button. Works even without running.
bool was_changed_create_file_btn() { return was_changed_("create_file_btn"); }
int geti_create_file_btn() { return geti_("create_file_btn"); }
QString button_create_file_btn() { return "create_file_btn"; }



//Out String Last Operation
//Outputs last created file size.
bool was_changed_last_operation() { return was_changed_("last_operation"); }
QString gets_last_operation() { return gets_("last_operation"); }
QStringList get_strings_last_operation() { return get_strings_("last_operation"); }
void sets_last_operation(QString value) { sets_("last_operation", value); }
void clear_string_last_operation() { clear_string_("last_operation"); }
void append_string_last_operation(QString v, int extra_new_lines_count = 0) { append_string_("last_operation", v, extra_new_lines_count); }
void append_string_last_operation(QStringList v, int extra_new_lines_count = 0) { append_string_("last_operation", v, extra_new_lines_count); }


//----------------------------------------------------
