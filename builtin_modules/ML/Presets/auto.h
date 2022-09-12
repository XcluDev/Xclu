//----------------------------------------------------
//Interface for XClassBasePresets
//Created automatically.
//----------------------------------------------------
//Page Parameters
//List of parameters.

//Button Apply
//
bool was_changed_btn_apply_parameters_list() { return was_changed_("btn_apply_parameters_list"); }
int geti_btn_apply_parameters_list() { return geti_("btn_apply_parameters_list"); }
void repaint_btn_apply_parameters_list() { repaint_("btn_apply_parameters_list"); }
QString button_btn_apply_parameters_list() { return "btn_apply_parameters_list"; }

//Text Parameters
//Presets names. Format: name min max
bool was_changed_parameters_list() { return was_changed_("parameters_list"); }
QString gets_parameters_list() { return gets_("parameters_list"); }
QStringList get_strings_parameters_list() { return get_strings_("parameters_list"); }
void repaint_parameters_list() { repaint_("parameters_list"); }

//----------------------------------------------------
//Page Presets
//List of presets.

//Button Apply
//
bool was_changed_btn_apply_presets_names() { return was_changed_("btn_apply_presets_names"); }
int geti_btn_apply_presets_names() { return geti_("btn_apply_presets_names"); }
void repaint_btn_apply_presets_names() { repaint_("btn_apply_presets_names"); }
QString button_btn_apply_presets_names() { return "btn_apply_presets_names"; }

//Text Presets
//Presets names.
bool was_changed_presets_names() { return was_changed_("presets_names"); }
QString gets_presets_names() { return gets_("presets_names"); }
QStringList get_strings_presets_names() { return get_strings_("presets_names"); }
void repaint_presets_names() { repaint_("presets_names"); }

//----------------------------------------------------
//Page Preset Setup
//Setting parameters for each preset.

//Button Send
// Used for sending signal about using preset values from another module.
bool was_changed_btn_send_preset() { return was_changed_("btn_send_preset"); }
int geti_btn_send_preset() { return geti_("btn_send_preset"); }
void repaint_btn_send_preset() { repaint_("btn_send_preset"); }
QString button_btn_send_preset() { return "btn_send_preset"; }

//Int Preset Id
// Choosen preset to edit.
bool was_changed_preset_id() { return was_changed_("preset_id"); }
int geti_preset_id() { return geti_("preset_id"); }
void repaint_preset_id() { repaint_("preset_id"); }

//Out String Preset Name
//Name of the taste.
bool was_changed_preset_name() { return was_changed_("preset_name"); }
QString gets_preset_name() { return gets_("preset_name"); }
QStringList get_strings_preset_name() { return get_strings_("preset_name"); }
void sets_preset_name(QString value) { sets_("preset_name", value); }
void clear_string_preset_name() { clear_string_("preset_name"); }
void append_string_preset_name(QString v, int extra_new_lines_count = 0) { append_string_("preset_name", v, extra_new_lines_count); }
void append_string_preset_name(QStringList v, int extra_new_lines_count = 0) { append_string_("preset_name", v, extra_new_lines_count); }
void repaint_preset_name() { repaint_("preset_name"); }

//Checkbox Auto Load
//Load preset immediately after changing name.
bool was_changed_preset_auto_load() { return was_changed_("preset_auto_load"); }
int geti_preset_auto_load() { return geti_("preset_auto_load"); }
void repaint_preset_auto_load() { repaint_("preset_auto_load"); }

//Button Load
//
bool was_changed_preset_load() { return was_changed_("preset_load"); }
int geti_preset_load() { return geti_("preset_load"); }
void repaint_preset_load() { repaint_("preset_load"); }
QString button_preset_load() { return "preset_load"; }

//Button Save
//
bool was_changed_preset_save() { return was_changed_("preset_save"); }
int geti_preset_save() { return geti_("preset_save"); }
void repaint_preset_save() { repaint_("preset_save"); }
QString button_preset_save() { return "preset_save"; }


//Checkbox 1..10
//
bool was_changed_group1_10() { return was_changed_("group1_10"); }
int geti_group1_10() { return geti_("group1_10"); }
void repaint_group1_10() { repaint_("group1_10"); }

//Float Parameter1
//
bool was_changed_param1() { return was_changed_("param1"); }
float getf_param1() { return getf_("param1"); }
void repaint_param1() { repaint_("param1"); }

//Float Parameter2
//
bool was_changed_param2() { return was_changed_("param2"); }
float getf_param2() { return getf_("param2"); }
void repaint_param2() { repaint_("param2"); }

//Float Parameter3
//
bool was_changed_param3() { return was_changed_("param3"); }
float getf_param3() { return getf_("param3"); }
void repaint_param3() { repaint_("param3"); }

//Float Parameter4
//
bool was_changed_param4() { return was_changed_("param4"); }
float getf_param4() { return getf_("param4"); }
void repaint_param4() { repaint_("param4"); }

//Float Parameter5
//
bool was_changed_param5() { return was_changed_("param5"); }
float getf_param5() { return getf_("param5"); }
void repaint_param5() { repaint_("param5"); }

//Float Parameter6
//
bool was_changed_param6() { return was_changed_("param6"); }
float getf_param6() { return getf_("param6"); }
void repaint_param6() { repaint_("param6"); }

//Float Parameter7
//
bool was_changed_param7() { return was_changed_("param7"); }
float getf_param7() { return getf_("param7"); }
void repaint_param7() { repaint_("param7"); }

//Float Parameter8
//
bool was_changed_param8() { return was_changed_("param8"); }
float getf_param8() { return getf_("param8"); }
void repaint_param8() { repaint_("param8"); }

//Float Parameter9
//
bool was_changed_param9() { return was_changed_("param9"); }
float getf_param9() { return getf_("param9"); }
void repaint_param9() { repaint_("param9"); }

//Float Parameter10
//
bool was_changed_param10() { return was_changed_("param10"); }
float getf_param10() { return getf_("param10"); }
void repaint_param10() { repaint_("param10"); }


//Checkbox 11..20
//
bool was_changed_group11_20() { return was_changed_("group11_20"); }
int geti_group11_20() { return geti_("group11_20"); }
void repaint_group11_20() { repaint_("group11_20"); }

//Float Parameter11
//
bool was_changed_param11() { return was_changed_("param11"); }
float getf_param11() { return getf_("param11"); }
void repaint_param11() { repaint_("param11"); }

//Float Parameter12
//
bool was_changed_param12() { return was_changed_("param12"); }
float getf_param12() { return getf_("param12"); }
void repaint_param12() { repaint_("param12"); }

//Float Parameter13
//
bool was_changed_param13() { return was_changed_("param13"); }
float getf_param13() { return getf_("param13"); }
void repaint_param13() { repaint_("param13"); }

//Float Parameter14
//
bool was_changed_param14() { return was_changed_("param14"); }
float getf_param14() { return getf_("param14"); }
void repaint_param14() { repaint_("param14"); }

//Float Parameter15
//
bool was_changed_param15() { return was_changed_("param15"); }
float getf_param15() { return getf_("param15"); }
void repaint_param15() { repaint_("param15"); }

//Float Parameter16
//
bool was_changed_param16() { return was_changed_("param16"); }
float getf_param16() { return getf_("param16"); }
void repaint_param16() { repaint_("param16"); }

//Float Parameter17
//
bool was_changed_param17() { return was_changed_("param17"); }
float getf_param17() { return getf_("param17"); }
void repaint_param17() { repaint_("param17"); }

//Float Parameter18
//
bool was_changed_param18() { return was_changed_("param18"); }
float getf_param18() { return getf_("param18"); }
void repaint_param18() { repaint_("param18"); }

//Float Parameter19
//
bool was_changed_param19() { return was_changed_("param19"); }
float getf_param19() { return getf_("param19"); }
void repaint_param19() { repaint_("param19"); }

//Float Parameter20
//
bool was_changed_param20() { return was_changed_("param20"); }
float getf_param20() { return getf_("param20"); }
void repaint_param20() { repaint_("param20"); }


//Checkbox 21..30
//
bool was_changed_group21_30() { return was_changed_("group21_30"); }
int geti_group21_30() { return geti_("group21_30"); }
void repaint_group21_30() { repaint_("group21_30"); }

//Float Parameter21
//
bool was_changed_param21() { return was_changed_("param21"); }
float getf_param21() { return getf_("param21"); }
void repaint_param21() { repaint_("param21"); }

//Float Parameter22
//
bool was_changed_param22() { return was_changed_("param22"); }
float getf_param22() { return getf_("param22"); }
void repaint_param22() { repaint_("param22"); }

//Float Parameter23
//
bool was_changed_param23() { return was_changed_("param23"); }
float getf_param23() { return getf_("param23"); }
void repaint_param23() { repaint_("param23"); }

//Float Parameter24
//
bool was_changed_param24() { return was_changed_("param24"); }
float getf_param24() { return getf_("param24"); }
void repaint_param24() { repaint_("param24"); }

//Float Parameter25
//
bool was_changed_param25() { return was_changed_("param25"); }
float getf_param25() { return getf_("param25"); }
void repaint_param25() { repaint_("param25"); }

//Float Parameter26
//
bool was_changed_param26() { return was_changed_("param26"); }
float getf_param26() { return getf_("param26"); }
void repaint_param26() { repaint_("param26"); }

//Float Parameter27
//
bool was_changed_param27() { return was_changed_("param27"); }
float getf_param27() { return getf_("param27"); }
void repaint_param27() { repaint_("param27"); }

//Float Parameter28
//
bool was_changed_param28() { return was_changed_("param28"); }
float getf_param28() { return getf_("param28"); }
void repaint_param28() { repaint_("param28"); }

//Float Parameter29
//
bool was_changed_param29() { return was_changed_("param29"); }
float getf_param29() { return getf_("param29"); }
void repaint_param29() { repaint_("param29"); }

//Float Parameter30
//
bool was_changed_param30() { return was_changed_("param30"); }
float getf_param30() { return getf_("param30"); }
void repaint_param30() { repaint_("param30"); }


//Checkbox 31..40
//
bool was_changed_group31_40() { return was_changed_("group31_40"); }
int geti_group31_40() { return geti_("group31_40"); }
void repaint_group31_40() { repaint_("group31_40"); }

//Float Parameter31
//
bool was_changed_param31() { return was_changed_("param31"); }
float getf_param31() { return getf_("param31"); }
void repaint_param31() { repaint_("param31"); }

//Float Parameter32
//
bool was_changed_param32() { return was_changed_("param32"); }
float getf_param32() { return getf_("param32"); }
void repaint_param32() { repaint_("param32"); }

//Float Parameter33
//
bool was_changed_param33() { return was_changed_("param33"); }
float getf_param33() { return getf_("param33"); }
void repaint_param33() { repaint_("param33"); }

//Float Parameter34
//
bool was_changed_param34() { return was_changed_("param34"); }
float getf_param34() { return getf_("param34"); }
void repaint_param34() { repaint_("param34"); }

//Float Parameter35
//
bool was_changed_param35() { return was_changed_("param35"); }
float getf_param35() { return getf_("param35"); }
void repaint_param35() { repaint_("param35"); }

//Float Parameter36
//
bool was_changed_param36() { return was_changed_("param36"); }
float getf_param36() { return getf_("param36"); }
void repaint_param36() { repaint_("param36"); }

//Float Parameter37
//
bool was_changed_param37() { return was_changed_("param37"); }
float getf_param37() { return getf_("param37"); }
void repaint_param37() { repaint_("param37"); }

//Float Parameter38
//
bool was_changed_param38() { return was_changed_("param38"); }
float getf_param38() { return getf_("param38"); }
void repaint_param38() { repaint_("param38"); }

//Float Parameter39
//
bool was_changed_param39() { return was_changed_("param39"); }
float getf_param39() { return getf_("param39"); }
void repaint_param39() { repaint_("param39"); }

//Float Parameter40
//
bool was_changed_param40() { return was_changed_("param40"); }
float getf_param40() { return getf_("param40"); }
void repaint_param40() { repaint_("param40"); }


//Checkbox 41..50
//
bool was_changed_group41_50() { return was_changed_("group41_50"); }
int geti_group41_50() { return geti_("group41_50"); }
void repaint_group41_50() { repaint_("group41_50"); }

//Float Parameter41
//
bool was_changed_param41() { return was_changed_("param41"); }
float getf_param41() { return getf_("param41"); }
void repaint_param41() { repaint_("param41"); }

//Float Parameter42
//
bool was_changed_param42() { return was_changed_("param42"); }
float getf_param42() { return getf_("param42"); }
void repaint_param42() { repaint_("param42"); }

//Float Parameter43
//
bool was_changed_param43() { return was_changed_("param43"); }
float getf_param43() { return getf_("param43"); }
void repaint_param43() { repaint_("param43"); }

//Float Parameter44
//
bool was_changed_param44() { return was_changed_("param44"); }
float getf_param44() { return getf_("param44"); }
void repaint_param44() { repaint_("param44"); }

//Float Parameter45
//
bool was_changed_param45() { return was_changed_("param45"); }
float getf_param45() { return getf_("param45"); }
void repaint_param45() { repaint_("param45"); }

//Float Parameter46
//
bool was_changed_param46() { return was_changed_("param46"); }
float getf_param46() { return getf_("param46"); }
void repaint_param46() { repaint_("param46"); }

//Float Parameter47
//
bool was_changed_param47() { return was_changed_("param47"); }
float getf_param47() { return getf_("param47"); }
void repaint_param47() { repaint_("param47"); }

//Float Parameter48
//
bool was_changed_param48() { return was_changed_("param48"); }
float getf_param48() { return getf_("param48"); }
void repaint_param48() { repaint_("param48"); }

//Float Parameter49
//
bool was_changed_param49() { return was_changed_("param49"); }
float getf_param49() { return getf_("param49"); }
void repaint_param49() { repaint_("param49"); }

//Float Parameter50
//
bool was_changed_param50() { return was_changed_("param50"); }
float getf_param50() { return getf_("param50"); }
void repaint_param50() { repaint_("param50"); }


//----------------------------------------------------
//Page Output
//

//Button Export
// Export presets to text file.
bool was_changed_btn_export_presets() { return was_changed_("btn_export_presets"); }
int geti_btn_export_presets() { return geti_("btn_export_presets"); }
void repaint_btn_export_presets() { repaint_("btn_export_presets"); }
QString button_btn_export_presets() { return "btn_export_presets"; }

//Out Text Values
// Current presets values; updated after "Send" button.
bool was_changed_values_text() { return was_changed_("values_text"); }
QString gets_values_text() { return gets_("values_text"); }
QStringList get_strings_values_text() { return get_strings_("values_text"); }
void sets_values_text(QString value) { sets_("values_text", value); }
void clear_string_values_text() { clear_string_("values_text"); }
void append_string_values_text(QString v, int extra_new_lines_count = 0) { append_string_("values_text", v, extra_new_lines_count); }
void append_string_values_text(QStringList v, int extra_new_lines_count = 0) { append_string_("values_text", v, extra_new_lines_count); }
void repaint_values_text() { repaint_("values_text"); }

//----------------------------------------------------
