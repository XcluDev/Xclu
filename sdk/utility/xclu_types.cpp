#include "xclu_types.h"
#include "console.h"
#include "incl_cpp.h"

//TODO сейчас реализация ведется поиском,
//лучше сделать через maps - для скорости работы

//---------------------------------------------------------------------
void ErrorInfo::throw_error() {    //если есть ошибка - сгенерировать исключение
    if (is_error()) {
        xclu_exception(error_text());
    }
}

//---------------------------------------------------------------------
QString Type_to_string(int i, int N, const QString array[]) {
    xclu_assert(i >= 0 && i < N, QString("Can't convert type index %1 to string %2")
                                         .arg(i).arg(array[0] + "," + array[1] + ",..."));
    return array[i];
}

int string_to_Type(const QString &str, int N, const QString array[]) {
    //TODO ускорить через Map
    for (int i=0; i<N; i++) {
        if (str == array[i]) return i;
    }
    xclu_exception(QString("Can't convert string '%1' to type %2")
                   .arg(str).arg(array[0] + "," + array[1] + ",..."));
    return 0;
}

//---------------------------------------------------------------------
const QString ModuleImplTypeNames[ModuleImplTypeN] = {"?", "C++", "JS", "dynlib", "python"};

QString moduleimpltype_to_string(ModuleImplType moduleimpltype) {
    return Type_to_string(int(moduleimpltype), ModuleImplTypeN, ModuleImplTypeNames);
}

ModuleImplType string_to_moduleimpltype(const QString &moduletypestr) {
    return ModuleImplType(string_to_Type(moduletypestr, ModuleImplTypeN, ModuleImplTypeNames));
}


//---------------------------------------------------------------------
const QString InterfaceTypeNames[XItemTypeN] =
{
    "?",
    "page",
    "group",
    "separator",
    "float",
    "int",
    "string",
    "text",
    "checkbox",
    "button",
    "enum",
    "object"
};

QString interfacetype_to_string(XItemType vartype) {
    return Type_to_string(int(vartype), XItemTypeN, InterfaceTypeNames);
}

XItemType string_to_interfacetype(const QString &vartypestr) {
    return XItemType(string_to_Type(vartypestr, XItemTypeN, InterfaceTypeNames));
}

QString GENERAL_PAGE_marker() {
    return "GENERAL_PAGE";
}

//---------------------------------------------------------------------
const QString ObjectTypeNames[XStructTypeN] =
{
    "empty",
    "custom",
    "image",
    "sound_format",
    "sound_buffer"
};

//---------------------------------------------------------------------
QString object_type_to_string(XStructType type) {
        return Type_to_string(int(type), XStructTypeN, ObjectTypeNames);
}

XStructType string_to_object_type(QString type_str) {
    return XStructType(string_to_Type(type_str, XStructTypeN, ObjectTypeNames));

}

//---------------------------------------------------------------------
const QString VarQualifierNames[VarQualifierN] = {"?", "in", "out", "const"};

QString varqualifier_to_string(VarQualifier varqualifier) {
    return Type_to_string(int(varqualifier), VarQualifierN, VarQualifierNames);
}

VarQualifier string_to_varqualifier(const QString &varqualifierstr) {
    return VarQualifier(string_to_Type(varqualifierstr, VarQualifierN, VarQualifierNames));
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
    return ModuleRunMode(string_to_Type(mode_string, ModuleRunModeN, ModuleRunModeNames));
}
QString ModuleRunMode_to_string(ModuleRunMode mode) {
    return Type_to_string(int(mode), ModuleRunModeN, ModuleRunModeNames);
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
    return Type_to_string(int(stage), ModuleExecuteStageN, ModuleExecuteStageNames);
}

//---------------------------------------------------------------------
