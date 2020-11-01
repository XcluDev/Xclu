//----------------------------------------------------
//Interface for XClassRandom
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Enum Output Type
//Output value type.
enum enum_output_type {
    output_type_Float = 0,
    output_type_Int = 1,
    output_type_String = 2,
    output_type_N__ = 3
};
bool was_changed_output_type() { return was_changed_("output_type"); }
enum_output_type gete_output_type() { return enum_output_type(geti_("output_type")); }
QString getraw_output_type() { return getraw_("output_type");}

//Enum Distribution
//Type of distribution
enum enum_distr_float {
    distr_float_Uniform = 0,
    distr_float_N__ = 1
};
bool was_changed_distr_float() { return was_changed_("distr_float"); }
enum_distr_float gete_distr_float() { return enum_distr_float(geti_("distr_float")); }
QString getraw_distr_float() { return getraw_("distr_float");}

//Float From
//Minimum value.
bool was_changed_from_float() { return was_changed_("from_float"); }
float getf_from_float() { return getf_("from_float"); }

//Float To Excluded
//Maximum value (excluded).
bool was_changed_to_excluded_float() { return was_changed_("to_excluded_float"); }
float getf_to_excluded_float() { return getf_("to_excluded_float"); }

//Int From
//Minimum value.
bool was_changed_from_int() { return was_changed_("from_int"); }
int geti_from_int() { return geti_("from_int"); }

//Int To
//Maximum value (included).
bool was_changed_to_int() { return was_changed_("to_int"); }
int geti_to_int() { return geti_("to_int"); }

//Text Values
//String values. Note: empty lines and comments are ignored.
bool was_changed_values() { return was_changed_("values"); }
QString gets_values() { return gets_("values"); }
QStringList get_strings_values() { return get_strings_("values"); }


//Out String Result
//Resulted value.
bool was_changed_result() { return was_changed_("result"); }
QString gets_result() { return gets_("result"); }
QStringList get_strings_result() { return get_strings_("result"); }
void sets_result(QString value) { sets_("result", value); }
void clear_string_result() { clear_string_("result"); }
void append_string_result(QString v, int extra_new_lines_count = 0) { append_string_("result", v, extra_new_lines_count); }
void append_string_result(QStringList v, int extra_new_lines_count = 0) { append_string_("result", v, extra_new_lines_count); }

//----------------------------------------------------
