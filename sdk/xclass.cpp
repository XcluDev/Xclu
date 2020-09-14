#include "xclass.h"
#include "incl_cpp.h"
#include "module.h"
#include "xdict.h"
#include "projectruntime.h"

//---------------------------------------------------------------------
XClass::XClass(Module *module) {
    set_module(module);
}

//---------------------------------------------------------------------
double XClass::rt_elapsed_time_sec() {
    return RUNTIME.elapsed_time_sec();
}

//---------------------------------------------------------------------
float XClass::rt_dt() {
    return RUNTIME.dt();
}

//---------------------------------------------------------------------
QString XClass::rt_project_folder() {   //full path to project folder
    return RUNTIME.project_folder();
}

//---------------------------------------------------------------------
//get absolute path to folder, given relative to project
QString XClass::rt_path(QString relative_path, bool create_folder) {
    return RUNTIME.absolute_path_from_project(relative_path, create_folder);
}

//---------------------------------------------------------------------
void XClass::set_module(Module *module) {
    xclu_assert(module, "Error at XClass::set_module(): module is nullptr");
    module_ = module;
}

//---------------------------------------------------------------------
Module *XClass::module() {
    return module_;
}


//---------------------------------------------------------------------
//Check if value was changed
//It's important, that for objects this function obtain access using XDictRead,
//hence it should not be called for already active XDictRead[Write] for this object
bool XClass::was_changed_(QString name) {
    return module()->interf()->var(name)->was_changed();
}

//---------------------------------------------------------------------
//Variables access
//int, checkbox, button, enum (rawtext), string, text
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
QString XClass::gets_(QString name, int index, int index2) {
    xclu_assert(module_, "Error at XClass::gets(): module is nullptr");
    return module()->gets(name, index, index2);
}

//---------------------------------------------------------------------
//splits text using "\n"
QStringList XClass::get_strings_(QString name) {
    xclu_assert(module_, "Error at XClass::get_strings(): module is nullptr");
    return module()->get_strings(name);
}

//---------------------------------------------------------------------
//только out: int, checkbox, enum (rawtext), string, text
void XClass::sets_(QString name, QString v) {
    xclu_assert(module_, "Error at XClass::sets(): module is nullptr");
    module()->sets(name, v);
}

//---------------------------------------------------------------------
void XClass::clear_string_(QString name) {
    xclu_assert(module_, "Error at XClass::clear_string(): module is nullptr");
    module()->clear_string(name);
}

//---------------------------------------------------------------------
//дописать к строке, применимо где sets
void XClass::append_string_(QString name, QString v, int extra_new_lines_count) {
    xclu_assert(module_, "Error at XClass::append_string(): module is nullptr");
    module()->append_string(name, v, extra_new_lines_count);
}

//---------------------------------------------------------------------
void XClass::append_string_(QString name, QStringList v, int extra_new_lines_count) { //дописать к строке, применимо где sets
    xclu_assert(module_, "Error at XClass::append_string(): module is nullptr");
    module()->append_string(name, v, extra_new_lines_count);
}

//---------------------------------------------------------------------
//int, checkbox, button, enum (index)
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
int XClass::geti_(QString name, int index, int index2) {
    xclu_assert(module_, "Error at XClass::geti(): module is nullptr");
    return module()->geti(name, index, index2);
}

//---------------------------------------------------------------------
//только out: int, checkbox, enum (index)
void XClass::seti_(QString name, int v) {
    xclu_assert(module_, "Error at XClass::seti(): module is nullptr");
    module()->seti(name, v);
}

//---------------------------------------------------------------------
//увеличение значения
void XClass::increase_int_(QString name, int increase) { //value+=increase
    xclu_assert(module_, "Error at XClass::increase_int(): module is nullptr");
    module()->increase_int(name, increase);
}

//---------------------------------------------------------------------
//float
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
float XClass::getf_(QString name, int index, int index2) {
    xclu_assert(module_, "Error at XClass::getf(): module is nullptr");
    return module()->getf(name, index, index2);
}

//---------------------------------------------------------------------
//только out: float
void XClass::setf_(QString name, float v) {
    xclu_assert(module_, "Error at XClass::setf(): module is nullptr");
    module()->setf(name, v);
}

//---------------------------------------------------------------------
//enum (title)
QString XClass::get_title_value_(QString name) {
    xclu_assert(module_, "Error at XClass::get_title_value(): module is nullptr");
    return module()->get_title_value(name);

}

//---------------------------------------------------------------------
//только out: enum (title)
void XClass::set_title_value_(QString name, QString v) {
    xclu_assert(module_, "Error at XClass::set_title_value(): module is nullptr");
    module()->set_title_value(name, v);
}

//---------------------------------------------------------------------
//доступ к объектам идет только по указателям -
//так как объекты могут быть очень большими, и поэтому с ними работаем непосредтсвенно,
//без копирования
//в объектах пока нет mutex - так как предполагается,
//что в gui посылается информация об обновлении объектов только из основного потока
XDict *XClass::get_object_(QString name) {
    xclu_assert(module_, "Error at XClass::get_object(): module is nullptr");
    return module()->get_object(name);
}

//---------------------------------------------------------------------
