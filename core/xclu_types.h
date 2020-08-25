#ifndef XCLUTYPES_H
#define XCLUTYPES_H

//Описание констант для типов переменных, модулей,
//и их преобразование в строки и обратно - для парсинга
//также, см. типы объектов в "xclu_types_objects.h"

#include <QString>

//универсальная конвертация
QString Type_to_string(int i, int N, const QString array[]);
int string_to_Type(const QString &str, int N, const QString array[]);


//Типы реализации модулей
enum ModuleImplType : int {
    ModuleImplTypeNone = 0,
    ModuleImplTypeCPP = 1,
    ModuleImplTypeJS = 2,
    ModuleImplTypeDynlib = 3,
    ModuleImplTypePython = 4,
    ModuleImplTypeN = 5
};

QString moduleimpltype_to_string(ModuleImplType moduleimpltype);
ModuleImplType string_to_moduleimpltype(const QString &moduleimpltypestr);

//Состояние редактора модуля - номер страницы
class EditorModuleState {
public:
    //Внимание, при изменении - требуется скорректировать
    //запись/считывание json в moduleinterface.cpp

    int tab_index = 0; //номер страницы
};


//Типы элементов интерфейса
enum InterfaceItemType : int {
    InterfaceItemTypeNone       = 0,
    InterfaceItemTypePage       = 1,
    InterfaceItemTypeGroup      = 2,
    InterfaceItemTypeSeparator  = 3,
    InterfaceItemTypeFloat      = 4,
    InterfaceItemTypeInt        = 5,
    InterfaceItemTypeString     = 6,
    InterfaceItemTypeText       = 7,
    InterfaceItemTypeCheckbox   = 8,
    InterfaceItemTypeButton     = 9,
    InterfaceItemTypeStringlist = 10,
    InterfaceItemTypeObject     = 11,
    InterfaceItemTypeN          = 12
};

QString interfacetype_to_string(InterfaceItemType vartype);
InterfaceItemType string_to_interfacetype(const QString &vartypestr);

//Способ использования переменной
enum VarQualifier : int {
    VarQualifierNone = 0,
    VarQualifierIn = 1,
    VarQualifierOut = 2,
    VarQualifierConst = 3,
    VarQualifierN = 4
};

QString varqualifier_to_string(VarQualifier varqualifier);
VarQualifier string_to_varqualifier(const QString &varqualifierstr);


//Этапы работы проекта
enum ProjectRunState : int {
    ProjectRunStateLoading = 0,
    ProjectRunStateStopped = 1,
    ProjectRunStateStarting = 2,
    ProjectRunStateRunning = 3,
    ProjectRunStateStopping = 4,
    ProjectRunStateN = 5
};

//Бинарное состояние запуска проекта
enum ProjectRunStateBinary: int {
    ProjectRunStateBinaryStopped = 0,
    ProjectRunStateBinaryRunning = 1
};

//Этап работы программы, используется для установки значений переменных в GUI и обратно
enum GuiStage : int {
    GuiStageProjectAfterLoading = 0,    //Project properties -> GUI

    GuiStageAfterGuiAttached = 1,       //const, in, out -> GUI

    GuiStageBeforeStart = 2,            //то же

    GuiStageBeforeUpdate = 3,           //GUI -> in; expressions
    GuiStageAfterUpdate = 4,            //out-> GUI

    GuiStageAfterStop = 5,              //GUI -> const, in;  out -> GUI

    GuiStageProjectBeforeSaving = 6,    //GUI -> const, in
    GuiStageBeforeGuiDetached = 7,      //то же

    GuiStageN = 8
};


//Варианты работы модуля
/*enum ModuleRunMode : int {
    ModuleRunMode_Main_Loop = 0,
    ModuleRunMode_Callback = 1,
    ModuleRunMode_One_Shot_After_Start = 2,
    ModuleRunMode_One_Shot_Before_Stop = 3,
    ModuleRunMode_One_Shot_Callback = 4,
    //ModuleRunMode_Callback_One_Shot_in_Separate_Thread = 5,
    ModuleRunModeN = 5
};
ModuleRunMode string_to_ModuleRunMode(QString mode_string);
QString ModuleRunMode_to_string(ModuleRunMode mode);
*/


//Режимы запуска модуля
enum ModuleExecuteStage :int {
    ModuleExecuteStageLoaded = 0,
    ModuleExecuteStageStart = 1,
    ModuleExecuteStageAfterStart = 2,
    ModuleExecuteStageUpdate = 3,
    ModuleExecuteStageBeforeStop = 4,
    ModuleExecuteStageStop = 5,
    //ModuleExecuteStageCallback = 5,
    ModuleExecuteStageN = 6
};
QString ModuleExecuteStage_to_string(ModuleExecuteStage stage);


//Действия при ошибке при работе модуля
enum ModuleActionOnError : int {
    ModuleActionOnErrorIgnore = 0,
    ModuleActionOnErrorPrint_To_Console = 1,
    ModuleActionOnErrorShow_Message_Box = 2,
    ModuleActionOnErrorStop = 3,
    ModuleActioneOnErrorShow_Message_Box_and_Stop = 4,
    ModuleActioneOnErrorN = 5
};


//Типы для объектов XcluObject
//При добавлении новых типов объектов дописывать их визуализацию в систему XcluObjectWrapper
enum XcluObjectType : int {
    XcluObjectTypeEmpty = 0,            //пустой объект
    XcluObjectTypeCustom = 1,           //специальный объект, без определенного типа
    XcluObjectTypeImage = 2,            //изображение
    XcluObjectTypeSoundFormat = 3,      //формат звука
    XcluObjectTypeSoundBuffer = 4,      //звуковой буфер
    XcluObjectTypeN = 5
};

QString object_type_to_string(XcluObjectType type);
XcluObjectType string_to_object_type(QString type_str);


//Тип ошибки
struct ErrorInfo {
    ErrorInfo() {}

    //очистить
    void clear() {
        is_error_ = false;
        error_text_.clear();
    }

    //создать с текстом
    ErrorInfo(QString text) {
        setup(text);
    }
    void setup(QString text) {
        is_error_ = true;
        error_text_ = text;
    }
    //добавить к тексту ошибки предысторию с "\n" - полезно при передаче ошибок между уровнями, дописывая подробности
    ErrorInfo(QString prepend_text, const ErrorInfo &err) {
        prepend(prepend_text, err);
    }
    void prepend(QString prepend_text, const ErrorInfo &err) {
        is_error_ = true;
        error_text_ = prepend_text + "\n" + err.error_text();
    }

    //извлечение информации о том, есть ли ошибка
    bool is_error() const { return is_error_; }
    QString error_text() const { return error_text_; }
    void throw_error();  //если есть ошибка - сгенерировать исключение

protected:
    bool is_error_ = false;
    QString error_text_;

};

//Популярные названия для call-функций
//вызов:
//call_function_name::sound_buffer_add()
class call_function_name {
public:
    static QString sound_buffer_add() { return "sound_buffer_add"; }
    static QString get_widget_pointer() { return "get_widget_pointer";}
};



#endif // XCLUTYPES_H
