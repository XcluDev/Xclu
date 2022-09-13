//----------------------------------------------------
//Interface for XClassTokenize
//Created automatically.
//----------------------------------------------------
//Page Input
//Input text to process.

//Enum Source
//Source of input files.
enum enum_source {
    source_Text = 0,
    source_Text_file = 1,
    source_Var = 2,
    source_URL = 3,
    source_Script = 4,
    source_N__ = 5
};
bool was_changed_source() { return was_changed_("source"); }
enum_source gete_source() { return enum_source(geti_("source")); }
QString getraw_source() { return getraw_("source");}

//Text Text
//Input area.
bool was_changed_input_text() { return was_changed_("input_text"); }
QString gets_input_text() { return gets_("input_text"); }
QStringList get_strings_input_text() { return get_strings_("input_text"); }

//String File
//File name.
bool was_changed_input_file() { return was_changed_("input_file"); }
QString gets_input_file() { return gets_("input_file"); }
QStringList get_strings_input_file() { return get_strings_("input_file"); }

//String Var
//Var name.
bool was_changed_input_var() { return was_changed_("input_var"); }
QString gets_input_var() { return gets_("input_var"); }
QStringList get_strings_input_var() { return get_strings_("input_var"); }

//String URL
//URL for text to download.
bool was_changed_input_url() { return was_changed_("input_url"); }
QString gets_input_url() { return gets_("input_url"); }
QStringList get_strings_input_url() { return get_strings_("input_url"); }

//Text Script
//Script for input.
bool was_changed_input_script() { return was_changed_("input_script"); }
QString gets_input_script() { return gets_("input_script"); }
QStringList get_strings_input_script() { return get_strings_("input_script"); }

//----------------------------------------------------
//Page Process
//Perform html cleaning using readability-lxml.

//Checkbox HTML filter
//Filter HTML using  readability-lxml.
bool was_changed_html_filter() { return was_changed_("html_filter"); }
int geti_html_filter() { return geti_("html_filter"); }

//Checkbox Extract Paragraphs
//Extract paragraphs.
bool was_changed_get_paragraphs() { return was_changed_("get_paragraphs"); }
int geti_get_paragraphs() { return geti_("get_paragraphs"); }

//Checkbox Extract Sentences
//Extract sentences.
bool was_changed_get_sentences() { return was_changed_("get_sentences"); }
int geti_get_sentences() { return geti_("get_sentences"); }

//Checkbox Tokenize
//Extract tokens.
bool was_changed_tokenize() { return was_changed_("tokenize"); }
int geti_tokenize() { return geti_("tokenize"); }

//Checkbox Extract Lexems
//Extract lexems.
bool was_changed_get_lexems() { return was_changed_("get_lexems"); }
int geti_get_lexems() { return geti_("get_lexems"); }


//Enum Result
//Output type - JSON Text is good for small data, JSON Object works faster, Python Generator is useful for further processing with Python.
enum enum_result {
    result_JSON_Text = 0,
    result_JSON_Object = 1,
    result_Python_Generator = 2,
    result_N__ = 3
};
bool was_changed_result() { return was_changed_("result"); }
enum_result gete_result() { return enum_result(geti_("result")); }
QString getraw_result() { return getraw_("result");}

//----------------------------------------------------
