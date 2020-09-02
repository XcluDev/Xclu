#include "xclass.h"
#include "incl_cpp.h"
#include "module.h"
#include "xcluobject.h"

//---------------------------------------------------------------------
XClass::XClass(Module *module) {
    set_module(module);
}

//---------------------------------------------------------------------
void XClass::set_module(Module *module) {
    xclu_assert(module, "Error at XClass::set_module(): module is nullptr");
    module_ = module;
}

//---------------------------------------------------------------------
//Variables access
int XClass::geti(QString name, int index1, int index2) {
    xclu_assert(module_, "Error at XClass::geti(): module is nullptr");
    return module_->geti(name, index1, index2);
}

//---------------------------------------------------------------------
void XClass::seti(QString name, int v) {
    xclu_assert(module_, "Error at XClass::seti(): module is nullptr");
    module_->seti(name, v);
}

//---------------------------------------------------------------------
float XClass::getf(QString name, int index1, int index2) {
    xclu_assert(module_, "Error at XClass::getf(): module is nullptr");
    return module_->getf(name, index1, index2);
}

//---------------------------------------------------------------------
void XClass::setf(QString name, float v) {
    xclu_assert(module_, "Error at XClass::setf(): module is nullptr");
    module_->setf(name, v);
}

//---------------------------------------------------------------------
QString XClass::gets(QString name, int index1, int index2) {
    xclu_assert(module_, "Error at XClass::gets(): module is nullptr");
    return module_->gets(name, index1, index2);
}

//---------------------------------------------------------------------
void XClass::sets(QString name, QString v) {
    xclu_assert(module_, "Error at XClass::sets(): module is nullptr");
    module_->sets(name, v);
}

//---------------------------------------------------------------------
QStringList XClass::get_strings(QString name) {     //splits text using "\n"
    xclu_assert(module_, "Error at XClass::get_strings(): module is nullptr");
    return module_->get_strings(name);
}

//---------------------------------------------------------------------
XcluObject *XClass::get_object(QString name) {
    xclu_assert(module_, "Error at XClass::get_object(): module is nullptr");
    return module_->get_object(name);
}

//---------------------------------------------------------------------
