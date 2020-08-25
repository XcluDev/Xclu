#include "rtmodule.h"
#include "moduleinterface.h"
#include "module.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
RtModule::RtModule(QString class_name) {
    class_name_ = class_name;
}

//---------------------------------------------------------------------
RtModule::~RtModule() {

}

//---------------------------------------------------------------------
QString RtModule::class_name() {
    return class_name_;
}

//---------------------------------------------------------------------
void RtModule::set_module(Module *module) {
    module_ = module;
}

//---------------------------------------------------------------------
Module *RtModule::module() {
    return module_;
}

//---------------------------------------------------------------------
QString RtModule::name() {
    return module()->name();
}

//---------------------------------------------------------------------
void RtModule::internal_loaded() {     //действия при загрузке модуля
    execute_loaded_internal();
}

//---------------------------------------------------------------------
//выполнить update, и если нужно - start
void RtModule::internal_update() {
    if (is_enabled()) {
        if (!status_.was_started) {
            execute_start_internal();
            status_.was_started = true;
        }
        execute_update_internal();
    }
}

//---------------------------------------------------------------------
//выполнить stop, и если нужно - start
void RtModule::internal_stop() {
    if (status_.was_started) {
        status_.was_started = false;
        execute_stop_internal();
    }
    status_.enabled__ = false;
}

//---------------------------------------------------------------------
//выполнить только один раз - в начале или конце
void RtModule::internal_one_shot() {
    internal_update();
    internal_stop();
}

//---------------------------------------------------------------------
//единая функция исполнения
void RtModule::execute(ModuleExecuteStage stage) {
    //отлов исключений путем обработки ошибок, и реакция соответственно настройках
    try {
        //обновление enabled__
        status_.enabled__ = get_int("enabled");

        reset_stop_out();
        reset_error_values();

        //auto mode = run_mode();
        //bool enabled = is_enabled();
        switch (stage) {
        case ModuleExecuteStageLoaded:
            internal_loaded();
            break;
        case ModuleExecuteStageStart:
            //if (enabled && mode == ModuleRunMode_Main_Loop)
            internal_update();
            break;

        case ModuleExecuteStageAfterStart:
            //Сразу после старта - TODO Executor
            //if (enabled && mode == ModuleRunMode_One_Shot_After_Start) internal_one_shot();

            break;

        case ModuleExecuteStageUpdate:
            //if (enabled && mode == ModuleRunMode_Main_Loop)
            internal_update();
            break;

        case ModuleExecuteStageBeforeStop:
             //Прямо перед остановкой - TODO Executor
            //if (enabled && mode == ModuleRunMode_One_Shot_Before_Stop) internal_one_shot();
            break;

        case ModuleExecuteStageStop:
            //останавливаем всегда
            internal_stop();
            break;

        /*case ModuleExecuteStageCallback:
            if (enabled) {
                xclu_assert(mode == ModuleRunMode_Callback, "Module is called by callback, but it's Run Mode is not Callback!");
                internal_update();
            }
            break;*/

        default:
            xclu_exception(QString("Unknown execute stage %1").arg(stage));
        }
    }
    catch(XCluException& e) {
        //отлов исключений путем обработки ошибок, и реакция соответственно настройках
        process_error(e.whatQt());
    }
}

//---------------------------------------------------------------------
//нажатие кнопки - это можно делать и во время остановки всего
//внимание, обычно вызывается из основного потока как callback
void RtModule::button_pressed(QString button_id) {
    button_pressed_internal(button_id);
}

//---------------------------------------------------------------------
//функция вызова между модулями, вызывает call_internal
//важно, что эта функция может вызываться из других потоков - модули должны быть к этому готовы
void RtModule::call(QString function, ErrorInfo &err, XcluObject *input, XcluObject *output) {
    try {
        if (err.is_error()) return;
        //if (is_enabled()) {
        call_internal(function, input, output);
        //}
    }
    catch (XCluException &e) {
        err.prepend(QString("Error during executing function '%1' in module '%2':")
                  .arg(function).arg(name()), e.err());
    }
}

//---------------------------------------------------------------------
void RtModule::call_internal(QString /*function*/, XcluObject * /*input*/, XcluObject * /*output*/) {
    xclu_exception("Calls processing is not implemented for module " + name());
}

//---------------------------------------------------------------------
bool RtModule::is_running() {
    return status_.running;
}

//---------------------------------------------------------------------
bool RtModule::is_enabled() {
    return status_.enabled__;
}

//---------------------------------------------------------------------
void RtModule::reset_stop_out() {
    status_.request_stop_out = false;
}

//---------------------------------------------------------------------
void RtModule::set_stop_out() {
    status_.request_stop_out = true;
}

//---------------------------------------------------------------------
bool RtModule::is_stop_out() {
    return status_.request_stop_out;
}

//---------------------------------------------------------------------
//обработка ошибки в соответствие с настройками модуля
void RtModule::process_error(QString message) {
    int action = get_int("action_on_error");
    bool ignore = false;
    bool print_console = false;
    bool show_message = false;
    bool send_stop = false;
    switch (action) {
    case ModuleActionOnErrorIgnore:
        //ничего не делаем
        ignore = true;
        break;
    case ModuleActionOnErrorPrint_To_Console:
        print_console = true;
        break;
    case ModuleActionOnErrorShow_Message_Box:
        print_console = true;
        show_message = true;
        break;
    case ModuleActionOnErrorStop:
        print_console = true;
        send_stop = true;
        break;
    case ModuleActioneOnErrorShow_Message_Box_and_Stop:
        print_console = true;
        show_message = true;
        send_stop = true;
        break;
    default:
        xclu_exception("Internal error: unknown action_on_error in module " + module()->name());
        break;
    }

    //запоминаем, что ошибка в интерфейсе
    set_error_values(message);

    //если не игнорируем - то, дополняем текст ошибки до полного текста
    if (!ignore) {
        message = "Runtime error in module '" + module()->name() + "':\n    " + message;
    }

    //вывод в консоль
    if (print_console) {
        xclu_console_warning(message);
    }

    //показ сообщения
    if (show_message) {
        xclu_message_box(message);
    }
    if (send_stop) {
        set_stop_out();
    }
}

//---------------------------------------------------------------------
//Проверка, изменились ли переменные
bool RtModule::was_changed(QString name) {
    //Важно, что для объектов эта функция получает доступ к объекту с помощью ObjectRead,
    //поэтому, нельзя ее вызывать, если активирован другой ObjectRead[Write] для этого объекта
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    return var->was_changed();
}

//---------------------------------------------------------------------
//int, checkbox, button, enum (rawtext), string, text
QString RtModule::get_string(QString name) {
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->supports_string(), "variable '" + name + "' doesn't supports string");
    return var->value_string();
}
//---------------------------------------------------------------------
//только out: int, checkbox, enum (rawtext), string, text
void RtModule::set_string(QString name, QString v) {
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xclu_assert(var->supports_string(), "variable '" + name + "' doesn't supports string");
    var->set_value_string(v);
}

//---------------------------------------------------------------------
void RtModule::clear_string(QString name) {
    set_string(name, "");
}

//---------------------------------------------------------------------
//дописать к строке, применимо где set_string
void RtModule::append_string(QString name, QString v, int extra_new_lines_count) {
    QString value = get_string(name);
    value.append(v);
    for (int i=0; i<1 + extra_new_lines_count; i++) {
        value.append("\n");
    }
    qDebug() << "--- " << value;
    set_string(name, value);
}

//---------------------------------------------------------------------
void RtModule::append_string(QString name, QStringList v, int extra_new_lines_count) { //дописать к строке, применимо где set_string
    append_string(name, v.join("\n"), extra_new_lines_count);
}

//---------------------------------------------------------------------
//int, checkbox, button, enum (index)
int RtModule::get_int(QString name) {
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->supports_int(), "variable '" + name + "' doesn't supports int");
    return var->value_int();
}

//---------------------------------------------------------------------
//только out: int, checkbox, enum (index)
void RtModule::set_int(QString name, int v) {
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xclu_assert(var->supports_int(), "variable '" + name + "' doesn't supports int");
    var->set_value_int(v);
}

//---------------------------------------------------------------------
//увеличение значения
void RtModule::increase_int(QString name, int increase) { //value+=increase
    set_int(name, get_int(name) + increase);
}

//---------------------------------------------------------------------
//float
float RtModule::get_float(QString name) {
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->supports_float(), "variable '" + name + "' doesn't supports float");
    return var->value_float();

}

//---------------------------------------------------------------------
//только out: float
void RtModule::set_float(QString name, float v) {
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xclu_assert(var->supports_float(), "variable '" + name + "' doesn't supports float");
    var->set_value_float(v);
}

//---------------------------------------------------------------------
//enum (title)
QString RtModule::get_title_value(QString name) {
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->supports_value_title(), "variable '" + name + "' doesn't supports title value");
    return var->value_title();

}

//---------------------------------------------------------------------
//только out: enum (title)
void RtModule::set_title_value(QString name, QString v) {
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
XcluObject *RtModule::get_object(QString name) {
    InterfaceItem *var = module()->interf()->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->supports_object(), "variable '" + name + "' doesn't supports object");
    XcluObject *object = var->get_object();
    return object;
}


//---------------------------------------------------------------------
void RtModule::reset_error_values() { //сброс того, что быда ошибка при выполнении
    set_int("was_error", 0);
    clear_string("error_text");
}

//---------------------------------------------------------------------
void RtModule::set_error_values(QString message) { //установка того, что была ошибка
    set_int("was_error", 1);
    set_string("error_text", message);
}

//---------------------------------------------------------------------
