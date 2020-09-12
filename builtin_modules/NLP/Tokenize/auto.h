//----------------------------------------------------
//Interface for XClassTokenize
//Created automatically at 2020.09.12 21:37:02
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
enum_source en_source() { return enum_source(geti("source")); }

//Text Text
//Input area.
QString s_input_text() { return gets("input_text"); }

//String File
//File name.
QString s_input_file() { return gets("input_file"); }

//String Var
//Var name.
QString s_input_var() { return gets("input_var"); }

//String URL
//URL for text to download.
QString s_input_url() { return gets("input_url"); }

//Text Script
//Script for input.
QString s_input_script() { return gets("input_script"); }

//----------------------------------------------------
//Page Process
//Perform html cleaning using readability-lxml.

//Checkbox HTML filter
//Filter HTML using  readability-lxml.
int i_html_filter() { return geti("html_filter"); }

//Checkbox Extract Paragraphs
//Extract paragraphs.
int i_get_paragraphs() { return geti("get_paragraphs"); }

//Checkbox Extract Sentences
//Extract sentences.
int i_get_sentences() { return geti("get_sentences"); }

//Checkbox Tokenize
//Extract tokens.
int i_tokenize() { return geti("tokenize"); }

//Checkbox Extract Lexems
//Extract lexems.
int i_get_lexems() { return geti("get_lexems"); }


//Enum Result
//Output type - JSON Text is good for small data, JSON Object works faster, Python Generator is useful for further processing with Python.

enum enum_result {
    result_JSON_Text = 0,
    result_JSON_Object = 1,
    result_Python_Generator = 2,
    result_N__ = 3
};
enum_result en_result() { return enum_result(geti("result")); }

//----------------------------------------------------
