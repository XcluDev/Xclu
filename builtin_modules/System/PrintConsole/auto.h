//----------------------------------------------------
//Interface for XClassPrintConsole
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Checkbox Add Title
//Should add title to output
bool was_changed_add_title() { return was_changed_("add_title"); }
int geti_add_title() { return geti_("add_title"); }

//String Title
//Title string.
bool was_changed_title() { return was_changed_("title"); }
QString gets_title() { return gets_("title"); }
QStringList get_strings_title() { return get_strings_("title"); }


//Checkbox Add Time Stamp
//Should add timestamp to output.
bool was_changed_add_time_stamp() { return was_changed_("add_time_stamp"); }
int geti_add_time_stamp() { return geti_("add_time_stamp"); }


//String String
//String to print.
bool was_changed_str() { return was_changed_("str"); }
QString gets_str() { return gets_("str"); }
QStringList get_strings_str() { return get_strings_("str"); }

//----------------------------------------------------
