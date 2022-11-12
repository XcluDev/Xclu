//----------------------------------------------------
//Interface for XClassBaseGraphs
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Const Checkbox Render To Area
//Render to render area.
bool was_changed_render_to_area() { return was_changed_("render_to_area"); }
int geti_render_to_area() { return geti_("render_to_area"); }
void repaint_render_to_area() { repaint_("render_to_area"); }

//Const String Render Area
//Name of render area for drawing into.
bool was_changed_render_area() { return was_changed_("render_area"); }
QString gets_render_area() { return gets_("render_area"); }
QStringList get_strings_render_area() { return get_strings_("render_area"); }
void repaint_render_area() { repaint_("render_area"); }


//Const Checkbox Render To Image
//Render to image.
bool was_changed_render_to_image() { return was_changed_("render_to_image"); }
int geti_render_to_image() { return geti_("render_to_image"); }
void repaint_render_to_image() { repaint_("render_to_image"); }

//Const Int Image Width
//Width of image.
bool was_changed_image_width() { return was_changed_("image_width"); }
int geti_image_width() { return geti_("image_width"); }
void repaint_image_width() { repaint_("image_width"); }

//Const Int Image Height
//Height of image.
bool was_changed_image_height() { return was_changed_("image_height"); }
int geti_image_height() { return geti_("image_height"); }
void repaint_image_height() { repaint_("image_height"); }



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
