#include "xclassbase.h"
#include "incl_cpp.h"
#include "module.h"
#include "xobject.h"
#include "project_props.h"

//---------------------------------------------------------------------
XClassBase::XClassBase(Module *module) {
    set_module(module);
}

//---------------------------------------------------------------------
void XClassBase::set_module(Module *module) {
    xc_assert(module, "Error at XClassBase::set_module(): module is nullptr");
    module_ = module;
}

//---------------------------------------------------------------------
Module *XClassBase::module() {
    return module_;
}

//---------------------------------------------------------------------
//General (Control) page
bool XClassBase::is_enabled() {
    return module()->is_enabled();
}

//---------------------------------------------------------------------
bool XClassBase::is_auto_update() {
    return module()->is_auto_update();
}

//---------------------------------------------------------------------
//Check if value was changed
//It's important, that for objects this function obtain access using XObjectRead,
//hence it should not be called for already active XObjectRead[Write] for this object
bool XClassBase::was_changed_(QString name, XWasChangedChecker &checker) {
    return module()->interf()->var(name)->was_changed(checker);
}

//---------------------------------------------------------------------
//This was_changed is checks changes between `update` calls
bool XClassBase::was_changed_(QString name) {
    return module()->interf()->var(name)->was_changed_simple();
}

//---------------------------------------------------------------------
//Repaint - force GUI widget to refresh, useful for long operations for updating numbers/texts
//TODO: check it's called from proper thread, and emit message if from another

void XClassBase::repaint_(QString name) {
    module()->interf()->var(name)->redraw();
}

//---------------------------------------------------------------------
//Variables access
//int, checkbox, button, enum (index), string, text
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
QString XClassBase::gets_(QString name, int index, int index2) {
    xc_assert(module_, "Error at XClassBase::gets(): module is nullptr");
    return module()->gets(name, index, index2);
}

//---------------------------------------------------------------------
//splits text using "\n"
QStringList XClassBase::get_strings_(QString name) {
    xc_assert(module_, "Error at XClassBase::get_strings(): module is nullptr");
    return module()->get_strings(name);
}

//---------------------------------------------------------------------
//только out: int, checkbox, enum (index), string, text
void XClassBase::sets_(QString name, QString v) {
    xc_assert(module_, "Error at XClassBase::sets(): module is nullptr");
    module()->sets(name, v);
}

//---------------------------------------------------------------------
void XClassBase::clear_string_(QString name) {
    xc_assert(module_, "Error at XClassBase::clear_string(): module is nullptr");
    module()->clear_string(name);
}

//---------------------------------------------------------------------
//дописать к строке, применимо где sets
void XClassBase::append_string_(QString name, QString v, int extra_new_lines_count) {
    xc_assert(module_, "Error at XClassBase::append_string(): module is nullptr");
    module()->append_string(name, v, extra_new_lines_count);
}

//---------------------------------------------------------------------
void XClassBase::append_string_(QString name, QStringList v, int extra_new_lines_count) { //дописать к строке, применимо где sets
    xc_assert(module_, "Error at XClassBase::append_string(): module is nullptr");
    module()->append_string(name, v, extra_new_lines_count);
}

//---------------------------------------------------------------------
//int, checkbox, button, enum (index)
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
int XClassBase::geti_(QString name, int index, int index2) {
    xc_assert(module_, "Error at XClassBase::geti(): module is nullptr");
    return module()->geti(name, index, index2);
}

//---------------------------------------------------------------------
//только out: int, checkbox, enum (index)
void XClassBase::seti_(QString name, int v) {
    xc_assert(module_, "Error at XClassBase::seti(): module is nullptr");
    module()->seti(name, v);
}

//---------------------------------------------------------------------
//увеличение значения
void XClassBase::increase_int_(QString name, int increase) { //value+=increase
    xc_assert(module_, "Error at XClassBase::increase_int(): module is nullptr");
    module()->increase_int(name, increase);
}

//---------------------------------------------------------------------
//float
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
float XClassBase::getf_(QString name, int index, int index2) {
    xc_assert(module_, "Error at XClassBase::getf(): module is nullptr");
    return module()->getf(name, index, index2);
}

//---------------------------------------------------------------------
//только out: float
void XClassBase::setf_(QString name, float v) {
    xc_assert(module_, "Error at XClassBase::setf(): module is nullptr");
    module()->setf(name, v);
}

//---------------------------------------------------------------------
QString XClassBase::getraw_(QString name) {  //enum (rawtext)
    xc_assert(module_, "Error at XClassBase::getraw_(): module is nullptr");
    return module()->getraw(name);
}

//---------------------------------------------------------------------
void XClassBase::set_raw_(QString name, QString v) { //только out: enum (rawtext)
    xc_assert(module_, "Error at XClassBase::set_raw_(): module is nullptr");
    module()->set_raw(name, v);
}

//---------------------------------------------------------------------
//enum (title)
QString XClassBase::get_title_value_(QString name) {
    xc_assert(module_, "Error at XClassBase::get_title_value_(): module is nullptr");
    return module()->get_title_value(name);

}

//---------------------------------------------------------------------
//только out: enum (title)
void XClassBase::set_title_value_(QString name, QString v) {
    xc_assert(module_, "Error at XClassBase::set_title_value_(): module is nullptr");
    module()->set_title_value(name, v);
}

//---------------------------------------------------------------------
//Access to objects is only by pointers - because we are required not to copy data, it can be large
XProtectedObject *XClassBase::get_object_(QString name) {
    xc_assert(module_, "Error at XClassBase::get_object_(): module is nullptr");
    return module()->get_object(name);
}

//---------------------------------------------------------------------
//Set pointer to object
//Note: object must be persistent, because only pointer to it is stored
void XClassBase::set_object_(QString name, XProtectedObject *object) {
    xc_assert(module_, "Error at XClassBase::set_object_(): module is nullptr");
    module()->set_object(name, object);
}

//---------------------------------------------------------------------
//Set reference to object
//Note: object must be persistent, because only pointer to it is stored
void XClassBase::set_object_(QString name, XProtectedObject &object) {
    set_object_(name, &object);
}

//---------------------------------------------------------------------
