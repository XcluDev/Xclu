//----------------------------------------------------
//Interface for XClassBaseGraphs
//Created automatically.
//----------------------------------------------------
//Page Output
//

//Const String Render Area
//Name of render area for drawing into.
bool was_changed_render_area() { return was_changed_("render_area"); }
QString gets_render_area() { return gets_("render_area"); }
QStringList get_strings_render_area() { return get_strings_("render_area"); }
void repaint_render_area() { repaint_("render_area"); }



//Float X
//
bool was_changed_draw_graphs_x() { return was_changed_("draw_graphs_x"); }
float getf_draw_graphs_x() { return getf_("draw_graphs_x"); }
void repaint_draw_graphs_x() { repaint_("draw_graphs_x"); }

//Float Y
//
bool was_changed_draw_graphs_y() { return was_changed_("draw_graphs_y"); }
float getf_draw_graphs_y() { return getf_("draw_graphs_y"); }
void repaint_draw_graphs_y() { repaint_("draw_graphs_y"); }

//Float W
//
bool was_changed_draw_graphs_w() { return was_changed_("draw_graphs_w"); }
float getf_draw_graphs_w() { return getf_("draw_graphs_w"); }
void repaint_draw_graphs_w() { repaint_("draw_graphs_w"); }

//Float H
//
bool was_changed_draw_graphs_h() { return was_changed_("draw_graphs_h"); }
float getf_draw_graphs_h() { return getf_("draw_graphs_h"); }
void repaint_draw_graphs_h() { repaint_("draw_graphs_h"); }

//----------------------------------------------------
//Page Input
//

//Const Enum Data Source
//Get graps values from Data value of read from file.
enum enum_data_source {
    data_source_Input_Value = 0,
    data_source_File = 1,
    data_source_N__ = 2
};
bool was_changed_data_source() { return was_changed_("data_source"); }
enum_data_source gete_data_source() { return enum_data_source(geti_("data_source")); }
QString getraw_data_source() { return getraw_("data_source");}

//Checkbox Is New Data
//Signal for adding data to the history.
bool was_changed_is_new_data() { return was_changed_("is_new_data"); }
int geti_is_new_data() { return geti_("is_new_data"); }
void repaint_is_new_data() { repaint_("is_new_data"); }

//Text Data
//Input data - one or several lines of numeric values separated by Separator symbol.
bool was_changed_data() { return was_changed_("data"); }
QString gets_data() { return gets_("data"); }
QStringList get_strings_data() { return get_strings_("data"); }
void repaint_data() { repaint_("data"); }

//Const String Read From File
//Text file to read.
bool was_changed_read_file_name() { return was_changed_("read_file_name"); }
QString gets_read_file_name() { return gets_("read_file_name"); }
QStringList get_strings_read_file_name() { return get_strings_("read_file_name"); }
void repaint_read_file_name() { repaint_("read_file_name"); }

//Const Int Read Rate
//How much lines read per second.
bool was_changed_read_file_rate() { return was_changed_("read_file_rate"); }
int geti_read_file_rate() { return geti_("read_file_rate"); }
void repaint_read_file_rate() { repaint_("read_file_rate"); }


//Out Checkbox Is New Data
//Is new values added to graphs at this frame.
bool was_changed_is_file_new_data() { return was_changed_("is_file_new_data"); }
int geti_is_file_new_data() { return geti_("is_file_new_data"); }
void seti_is_file_new_data(int value) { seti_("is_file_new_data", value); }
void repaint_is_file_new_data() { repaint_("is_file_new_data"); }

//Out Text Data
//Data read from file - one or several lines of numeric values separated by Separator symbol.
bool was_changed_file_data() { return was_changed_("file_data"); }
QString gets_file_data() { return gets_("file_data"); }
QStringList get_strings_file_data() { return get_strings_("file_data"); }
void sets_file_data(QString value) { sets_("file_data", value); }
void clear_string_file_data() { clear_string_("file_data"); }
void append_string_file_data(QString v, int extra_new_lines_count = 0) { append_string_("file_data", v, extra_new_lines_count); }
void append_string_file_data(QStringList v, int extra_new_lines_count = 0) { append_string_("file_data", v, extra_new_lines_count); }
void repaint_file_data() { repaint_("file_data"); }


//Const String Separator
//Separator of data columns.
bool was_changed_separator() { return was_changed_("separator"); }
QString gets_separator() { return gets_("separator"); }
QStringList get_strings_separator() { return get_strings_("separator"); }
void repaint_separator() { repaint_("separator"); }


//Out Int Columns Count
//Number of colums of last received data.
bool was_changed_last_data_columns_count() { return was_changed_("last_data_columns_count"); }
int geti_last_data_columns_count() { return geti_("last_data_columns_count"); }
void seti_last_data_columns_count(int value) { seti_("last_data_columns_count", value); }
void increase_int_last_data_columns_count(int increase = 1) { increase_int_("last_data_columns_count", increase); }
void repaint_last_data_columns_count() { repaint_("last_data_columns_count"); }

//Out Float Max Value
//Maximal value of last used data columns.
bool was_changed_last_data_max_value() { return was_changed_("last_data_max_value"); }
float getf_last_data_max_value() { return getf_("last_data_max_value"); }
void setf_last_data_max_value(float value) { setf_("last_data_max_value", value); }
void repaint_last_data_max_value() { repaint_("last_data_max_value"); }


//Out Float File Position
//File position.
bool was_changed_read_file_position() { return was_changed_("read_file_position"); }
float getf_read_file_position() { return getf_("read_file_position"); }
void setf_read_file_position(float value) { setf_("read_file_position", value); }
void repaint_read_file_position() { repaint_("read_file_position"); }

//----------------------------------------------------
//Page Draw
//

//Const Int History Size
//Number of records to draw.
bool was_changed_history_size() { return was_changed_("history_size"); }
int geti_history_size() { return geti_("history_size"); }
void repaint_history_size() { repaint_("history_size"); }

//Const Checkbox Draw All Columns
//Draw all or only specified columns.
bool was_changed_draw_all_columns() { return was_changed_("draw_all_columns"); }
int geti_draw_all_columns() { return geti_("draw_all_columns"); }
void repaint_draw_all_columns() { repaint_("draw_all_columns"); }

//Const Text Columns To Draw
//Each line contains indices of of columns to draw, starting from 1.
bool was_changed_columns_to_draw() { return was_changed_("columns_to_draw"); }
QString gets_columns_to_draw() { return gets_("columns_to_draw"); }
QStringList get_strings_columns_to_draw() { return get_strings_("columns_to_draw"); }
void repaint_columns_to_draw() { repaint_("columns_to_draw"); }


//Float Min Value
//Minimal value for drawing on each graph area.
bool was_changed_min_value() { return was_changed_("min_value"); }
float getf_min_value() { return getf_("min_value"); }
void repaint_min_value() { repaint_("min_value"); }

//Float Max Value
//Maximal value for drawing on each graph area.
bool was_changed_max_value() { return was_changed_("max_value"); }
float getf_max_value() { return getf_("max_value"); }
void repaint_max_value() { repaint_("max_value"); }


//Float Margin X
//
bool was_changed_margin_x() { return was_changed_("margin_x"); }
float getf_margin_x() { return getf_("margin_x"); }
void repaint_margin_x() { repaint_("margin_x"); }

//Float Margin Y
//
bool was_changed_margin_y() { return was_changed_("margin_y"); }
float getf_margin_y() { return getf_("margin_y"); }
void repaint_margin_y() { repaint_("margin_y"); }


//Int Line Width
//Width of drawn graphs.
bool was_changed_line_width() { return was_changed_("line_width"); }
int geti_line_width() { return geti_("line_width"); }
void repaint_line_width() { repaint_("line_width"); }


//Int Pen Red
//
bool was_changed_pen_red() { return was_changed_("pen_red"); }
int geti_pen_red() { return geti_("pen_red"); }
void repaint_pen_red() { repaint_("pen_red"); }

//Int Pen Green
//
bool was_changed_pen_green() { return was_changed_("pen_green"); }
int geti_pen_green() { return geti_("pen_green"); }
void repaint_pen_green() { repaint_("pen_green"); }

//Int Pen Blue
//
bool was_changed_pen_blue() { return was_changed_("pen_blue"); }
int geti_pen_blue() { return geti_("pen_blue"); }
void repaint_pen_blue() { repaint_("pen_blue"); }

//----------------------------------------------------
