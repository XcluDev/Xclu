//----------------------------------------------------
//Interface for XClassTextVariation
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Text Text
//Text such as [A|B|C[D|E]]. Module will generate randomly A,B,CD,CE.
bool was_changed_input_text() { return was_changed_("input_text"); }
QString gets_input_text() { return gets_("input_text"); }
QStringList get_strings_input_text() { return get_strings_("input_text"); }


//Out Text Output
//Generated text.
bool was_changed_output_text() { return was_changed_("output_text"); }
QString gets_output_text() { return gets_("output_text"); }
QStringList get_strings_output_text() { return get_strings_("output_text"); }
void sets_output_text(QString value) { sets_("output_text", value); }
void clear_string_output_text() { clear_string_("output_text"); }
void append_string_output_text(QString v, int extra_new_lines_count = 0) { append_string_("output_text", v, extra_new_lines_count); }
void append_string_output_text(QStringList v, int extra_new_lines_count = 0) { append_string_("output_text", v, extra_new_lines_count); }

//----------------------------------------------------
