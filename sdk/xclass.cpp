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
//Variables access
//int, checkbox, button, enum (rawtext), string, text
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
QString XClass::gets(QString name, int index, int index2) {
    xclu_assert(module_, "Error at XClass::gets(): module is nullptr");
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->supports_string(), "variable '" + name + "' doesn't supports string");
    QString value = var->value_string();
    if (index2 == -1) {
        if (index == -1) {  //plain string: "aaa"
            return value;
        }
        else {
            QStringList list = value.split(" "); //string, separated by spaces: "a b c"
            if (index < list.size()) {
                return list.at(index);
            }
            //No error, just empty string
            //For future improvement: exception text:
            //QString("Can't get value from `%1` with index %2, because value is `%3`")
            //.arg(name).arg(index).arg(value));
            return "";
        }
    }
    else {
        //string, separated by '\n' and spaces: "a b c\nc d e"
        QStringList list = value.split("\n");
        if (index < list.size()) {
            QStringList list2 = list[index].split(" ");
            if (index2 < list2.size()) {
                return list2.at(index2);
            }
        }
        return "";
    }
}

//---------------------------------------------------------------------
//splits text using "\n"
QStringList XClass::get_strings(QString name) {
    return gets(name).split("\n");
}

//---------------------------------------------------------------------
//только out: int, checkbox, enum (rawtext), string, text
void XClass::sets(QString name, QString v) {
    xclu_assert(module_, "Error at XClass::gets(): module is nullptr");
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xclu_assert(var->supports_string(), "variable '" + name + "' doesn't supports string");
    var->set_value_string(v);
}

//---------------------------------------------------------------------
void XClass::clear_string(QString name) {
    sets(name, "");
}

//---------------------------------------------------------------------
//дописать к строке, применимо где sets
void XClass::append_string(QString name, QString v, int extra_new_lines_count) {
    QString value = gets(name);
    value.append(v);
    for (int i=0; i<1 + extra_new_lines_count; i++) {
        value.append("\n");
    }
    sets(name, value);
}

//---------------------------------------------------------------------
void XClass::append_string(QString name, QStringList v, int extra_new_lines_count) { //дописать к строке, применимо где sets
    append_string(name, v.join("\n"), extra_new_lines_count);
}

//---------------------------------------------------------------------
//int, checkbox, button, enum (index)
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
int XClass::geti(QString name, int index, int index2) {
    xclu_assert(module_, "Error at XClass::geti(): module is nullptr");
    if (index == -1) {
        InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
        xclu_assert(var->supports_int(), "variable '" + name + "' doesn't supports int");
        return var->value_int();
    }
    else {
        return gets(name, index, index2).toInt();
    }
}

//---------------------------------------------------------------------
//только out: int, checkbox, enum (index)
void XClass::seti(QString name, int v) {
    xclu_assert(module_, "Error at XClass::seti(): module is nullptr");
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xclu_assert(var->supports_int(), "variable '" + name + "' doesn't supports int");
    var->set_value_int(v);
}

//---------------------------------------------------------------------
//увеличение значения
void XClass::increase_int(QString name, int increase) { //value+=increase
    seti(name, geti(name) + increase);
}

//---------------------------------------------------------------------
//float
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
float XClass::getf(QString name, int index, int index2) {
    xclu_assert(module_, "Error at XClass::getf(): module is nullptr");
    if (index == -1) {
        InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
        xclu_assert(var->supports_float(), "variable '" + name + "' doesn't supports float");
        return var->value_float();
    }
    else {
        return gets(name, index, index2).toFloat();
    }
}

//---------------------------------------------------------------------
//только out: float
void XClass::setf(QString name, float v) {
    xclu_assert(module_, "Error at XClass::setf(): module is nullptr");
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xclu_assert(var->supports_float(), "variable '" + name + "' doesn't supports float");
    var->set_value_float(v);
}

//---------------------------------------------------------------------
//enum (title)
QString XClass::get_title_value(QString name) {
    xclu_assert(module_, "Error at XClass::get_title_value(): module is nullptr");
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->supports_value_title(), "variable '" + name + "' doesn't supports title value");
    return var->value_title();

}

//---------------------------------------------------------------------
//только out: enum (title)
void XClass::set_title_value(QString name, QString v) {
    xclu_assert(module_, "Error at XClass::set_title_value(): module is nullptr");
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xclu_assert(var->supports_value_title(), "variable '" + name + "' doesn't supports title value");
    var->set_value_title(v);
}

//---------------------------------------------------------------------
//доступ к объектам идет только по указателям -
//так как объекты могут быть очень большими, и поэтому с ними работаем непосредтсвенно,
//без копирования
//в объектах пока нет mutex - так как предполагается,
//что в gui посылается информация об обновлении объектов только из основного потока
XDict *XClass::get_object(QString name) {
    xclu_assert(module_, "Error at XClass::get_object(): module is nullptr");
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->supports_object(), "variable '" + name + "' doesn't supports object");
    XDict *object = var->get_object();
    return object;
}

//---------------------------------------------------------------------
