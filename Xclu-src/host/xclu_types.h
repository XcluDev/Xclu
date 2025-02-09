#pragma once

//Xclu enums and converting to string and back.

#include <QString>
#include "int2.h"

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

QString xitem_group();
QString xitem_separator();
QString xitem_line();
QString xitem_page();
QString xitem_button();
QString GENERAL_PAGE_marker();

//Способ использования переменной
enum class XQualifier : int {
    None = 0,
    In = 1,
    Out = 2,
    Const = 3,
    N = 4
};

QString xqualifier_to_string(XQualifier xqualifier);
XQualifier string_to_xqualifier(const QString &xqualifierstr, bool throw_exception = true);

//Qualifiers mask - used for GUI-module interaction
struct XQualifierMask {
    static XQualifierMask get_all() { return XQualifierMask(true,true,true,true); }
    static XQualifierMask get_const_in() { return XQualifierMask(true,true,false,false); }
    static XQualifierMask get_out_link() { return XQualifierMask(false,false,true,true); }
    XQualifierMask() {}
    XQualifierMask(XQualifier qual) {
        qual_const = (qual == XQualifier::Const);
        qual_in = (qual == XQualifier::In);
        qual_out = (qual == XQualifier::Out);
        qual_link = false;
    }
    XQualifierMask(bool qual_const, bool qual_in, bool qual_out = false, bool qual_link = false) {
        this->qual_const = qual_const;
        this->qual_in = qual_in;
        this->qual_out = qual_out;
        this->qual_link = qual_link;
    }
    bool qual_const = false;
    bool qual_in = false;
    bool qual_out = false;
    bool qual_link = false;
};

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


//Mouse and keyboard events
enum XWidgetEvent_Type : int {
    XWidgetEvent_none = 0,
    XWidgetEvent_mouse_moved = 1,
    XWidgetEvent_mouse_pressed = 2,
    XWidgetEvent_mouse_dragged = 3,
    XWidgetEvent_mouse_released = 4,
    XWidgetEvent_mouse_double_clicked = 5,
    XWidgetEvent_key_pressed = 6,
    XWidgetEvent_key_released = 7
};
enum XMouseButton : int {
    XMouseButton_none = -1,
    XMouseButton_left = 0,
    XMouseButton_middle = 1,
    XMouseButton_right = 2
};
struct XWidgetEvent {
    XWidgetEvent_Type type = XWidgetEvent_none;
    int2 pos = int2(0,0);
    XMouseButton button = XMouseButton_none;
    int key = -1;
};

