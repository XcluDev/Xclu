//----------------------------------------------------
//Interface for XClassJsModule
//Created automatically at 2020.09.12 21:37:01
//----------------------------------------------------
//Page Main
//This page will be replaced with your custom GUI page(s).

//----------------------------------------------------
//Page Parameters
//Parameters GUI description. Also here is Export settings.

//Const Text XGUI
//GUI written in XGUI language.
QString s__xgui_=""() { return gets("_xgui_="""); }

//Button Apply
//Press this button to reload parameters GUI.
int i__gui_apply_() { return geti("_gui_apply_"); }

//Button Edit...
//Edit interface visually.
int i__gui_edit_button_() { return geti("_gui_edit_button_"); }


//Checkbox Advanced
//Adding module to Modules List and export.
int i__advanced_() { return geti("_advanced_"); }

//Const String Class
//Module class name.
QString s__module_class_() { return gets("_module_class_"); }

//Const String Category
//Module category.
QString s__module_category_() { return gets("_module_category_"); }

//Const String Description
//Module description.
QString s__module_description_() { return gets("_module_description_"); }

//Const String Version
//Module version.
QString s__module_version_() { return gets("_module_version_"); }


//Button Export...
//Export as a ready stand-alone module.
int i__export_() { return geti("_export_"); }

//----------------------------------------------------
//Page Functions
//Functions headers list. Each function in the list creates new page for filling the function code.

//Const Text Functions
//Functions list.
QString s__functions_=""() { return gets("_functions_="""); }

//Button Apply
//Press this button to reload function.
int i__functions_apply_() { return geti("_functions_apply_"); }

//Button Edit...
//Edit functions list visually.
int i__functions_edit_button_() { return geti("_functions_edit_button_"); }

//----------------------------------------------------
//Page setup()
//JS code for setup.

//Text Setup
//
QString s__setup_=""() { return gets("_setup_="""); }

//----------------------------------------------------
//Page update()
//JS code for update.

//Text Update
//
QString s__update_=""() { return gets("_update_="""); }

//----------------------------------------------------
