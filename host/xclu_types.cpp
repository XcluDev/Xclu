#include "xclu_types.h"
#include "xhandlingerrors.h"
#include "incl_cpp.h"
#include "xtypeutils.h"

//---------------------------------------------------------------------
const QString ModuleImplTypeNames[ModuleImplTypeN] = {"?", "C++", "JS", "dynlib", "python"};

QString moduleimpltype_to_string(ModuleImplType moduleimpltype) {
    return XTypeUtils::to_string(int(moduleimpltype), ModuleImplTypeN, ModuleImplTypeNames);
}

ModuleImplType string_to_moduleimpltype(const QString &moduletypestr) {
    return ModuleImplType(XTypeUtils::to_type(moduletypestr, ModuleImplTypeN, ModuleImplTypeNames));
}


//---------------------------------------------------------------------
/*
    "?",
    "page",
    "group",
    "separator",
    "line",
    "float",
    "int",
    "string",
    "text",
    "checkbox",
    "button",
    "enum",
    "array",
    "image",
    "soundbuffer",
    "object"
*/


//---------------------------------------------------------------------
QString xitem_group() {
    return "group";
}

QString xitem_separator() {
    return "separator";
}

QString xitem_line() {
    return "line";
}

QString xitem_page() {
    return "page";
}

QString xitem_button() {
    return "button";
}

QString GENERAL_PAGE_marker() {
    return "GENERAL_PAGE";
}

//---------------------------------------------------------------------
const QString XQualifierNames[XQualifierN] = {"?", "in", "out", "const"};

QString xqualifier_to_string(XQualifier xqualifier) {
    return XTypeUtils::to_string(int(xqualifier), XQualifierN, XQualifierNames);
}

XQualifier string_to_xqualifier(const QString &xqualifierstr) {
    return XQualifier(XTypeUtils::to_type(xqualifierstr, XQualifierN, XQualifierNames));
}

//---------------------------------------------------------------------
/*const QString ModuleRunModeNames[ModuleRunModeN] =
{
    "Main_Loop",
    "Callback",
    "One_Shot_After_Start",
    "One_Shot_Before_Stop",
    "One_Shot_Callback"
};
ModuleRunMode string_to_ModuleRunMode(QString mode_string) {
    return ModuleRunMode(XTypeUtils::to_type(mode_string, ModuleRunModeN, ModuleRunModeNames));
}
QString ModuleRunMode_to_string(ModuleRunMode mode) {
    return XTypeUtils::to_string(int(mode), ModuleRunModeN, ModuleRunModeNames);
}*/

//---------------------------------------------------------------------
const QString ModuleExecuteStageNames[ModuleExecuteStageN] =
{
    "Starting",
    "After Start",
    "Update",
    "Before Stop",
    "Stopping"
    //"Callback"
};

QString ModuleExecuteStage_to_string(ModuleExecuteStage stage) {
    return XTypeUtils::to_string(int(stage), ModuleExecuteStageN, ModuleExecuteStageNames);
}

//---------------------------------------------------------------------
