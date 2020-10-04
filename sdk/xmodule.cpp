#include "xmodule.h"
#include "moduleinterface.h"
#include "module.h"
#include "incl_cpp.h"
#include "xstruct.h"

//---------------------------------------------------------------------
XModule::XModule(QString class_name) {
    class_name_ = class_name;
}

//---------------------------------------------------------------------
XModule::~XModule() {

}

//---------------------------------------------------------------------
QString XModule::class_name() {
    return class_name_;
}

//---------------------------------------------------------------------
QString XModule::name() {
    return module()->name();
}

//---------------------------------------------------------------------
void XModule::loaded_internal() {     //действия при загрузке модуля
    impl_loaded();
}

//---------------------------------------------------------------------
//выполнить update, и если нужно - start
void XModule::update_internal() {
    if (is_enabled()) {
        if (!status_.was_started) {
            impl_start();
            status_.was_started = true;
        }
        impl_update();
    }
}

//---------------------------------------------------------------------
//выполнить stop, и если нужно - start
void XModule::stop_internal() {
    if (status_.was_started) {
        status_.was_started = false;
        impl_stop();
    }
    status_.enabled__ = false;
}

//---------------------------------------------------------------------
//выполнить только один раз - в начале или конце
void XModule::one_shot_internal() {
    update_internal();
    stop_internal();
}

//---------------------------------------------------------------------
//единая функция исполнения
void XModule::execute(ModuleExecuteStage stage) {
    //отлов исключений путем обработки ошибок, и реакция соответственно настройках
    try {
        //обновление enabled__
        status_.enabled__ = geti_("enabled");

        reset_stop_out();
        reset_error_values();

        //auto mode = run_mode();
        //bool enabled = is_enabled();
        switch (stage) {
        case ModuleExecuteStageLoaded:
            loaded_internal();
            break;
        case ModuleExecuteStageStart:
            //if (enabled && mode == ModuleRunMode_Main_Loop)
            update_internal();
            break;

        case ModuleExecuteStageAfterStart:
            //Сразу после старта - TODO Executor
            //if (enabled && mode == ModuleRunMode_One_Shot_After_Start) one_shot_internal();

            break;

        case ModuleExecuteStageUpdate:
            //if (enabled && mode == ModuleRunMode_Main_Loop)
            update_internal();
            break;

        case ModuleExecuteStageBeforeStop:
             //Прямо перед остановкой - TODO Executor
            //if (enabled && mode == ModuleRunMode_One_Shot_Before_Stop) one_shot_internal();
            break;

        case ModuleExecuteStageStop:
            //останавливаем всегда
            stop_internal();
            break;

        /*case ModuleExecuteStageCallback:
            if (enabled) {
                xclu_assert(mode == ModuleRunMode_Callback, "Module is called by callback, but it's Run Mode is not Callback!");
                update_internal();
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
void XModule::button_pressed(QString button_id) {
    impl_button_pressed(button_id);
}

//---------------------------------------------------------------------
//функция вызова между модулями, вызывает impl_call
//важно, что эта функция может вызываться из других потоков - модули должны быть к этому готовы
void XModule::call(QString function, ErrorInfo &err, XStruct *input, XStruct *output) {
    try {
        if (err.is_error()) return;

        //process predefined functions
        if (function == functions_names::create_widget()) {
            create_widget_internal(input, output);
            return;
        }
        if (function == functions_names::sound_buffer_add()) {
            sound_buffer_add_internal(input, output);
            return;
        }

        //process universal function
        //if (is_enabled()) {
        impl_call(function, input, output);
        //}
    }
    catch (XCluException &e) {
        err.prepend(QString("Error during executing function '%1' in module '%2':")
                  .arg(function).arg(name()), e.err());
    }
}

//---------------------------------------------------------------------
//"create_widget" call, returns QWidget pointer
void XModule::create_widget_internal(XStruct *input, XStruct *output) {
    //call create_widget
    //Window calls GUI elements to insert them into itself.
    //string parent_id
    //out pointer widget_pointer

    //проверка, что оба объекта переданы
    xclu_assert(input, "Internal error, input object is nullptr");
    xclu_assert(output, "Internal error, output object is nullptr");

    //устанавливаем, кто использует
    QString parent_id = input->gets("parent_id");

    //проверяем, что еще не стартовали
    xclu_assert(status().was_started,
                QString("Can't create widget, because module '%1' was not started yet."
                        " You need to place it before parent '%2'.")
                .arg(module_->name())
                .arg(parent_id));

    //создаем виджет
    void* widget = impl_create_widget(parent_id);

    //ставим его в выходной объект
    output->set_pointer("widget_pointer", widget);
}

//---------------------------------------------------------------------
//"sound_buffer_add" call
void XModule::sound_buffer_add_internal(XStruct *input, XStruct * /*output*/) {
    //qDebug() << "PCM params: " << data_.image_background << data_.pcm_speed_hz;
    XStruct &sound = *input;
    int sample_rate = sound.geti("sample_rate");
    int samples = sound.geti("samples");
    int channels = sound.geti("channels");
    float *data = sound.var_array("data")->data_float();
    impl_sound_buffer_add(sample_rate, channels, samples, data);
}

//---------------------------------------------------------------------
void XModule::impl_call(QString function, XStruct * /*input*/, XStruct * /*output*/) {
    xclu_exception("Module '" + name()
                   + "' can't process function '" + function + "', because impl_call() is not implemented");
}

//---------------------------------------------------------------------
//`create_widget` call implementation, creates QWidget and returns pointer on it
void *XModule::impl_create_widget(QString /*parent_id*/) {
    xclu_exception("Module '" + name()
                   + "' can't process function 'create_widget', because impl_create_widget() is not implemented");
    return nullptr;
}

//---------------------------------------------------------------------
//`sound_buffer_add` call implementation, fills `data` buffer
//there are required to fill channels * samples values at data
void XModule::impl_sound_buffer_add(int /*sample_rate*/, int /*channels*/, int /*samples*/, float * /*data*/) {
    xclu_exception("Module '" + name()
                   + "' can't process function 'sound_buffer_add', because impl_sound_buffer_add() is not implemented");
}

//---------------------------------------------------------------------
bool XModule::is_running() {
    return status_.running;
}

//---------------------------------------------------------------------
bool XModule::is_enabled() {
    return status_.enabled__;
}

//---------------------------------------------------------------------
void XModule::reset_stop_out() {
    status_.request_stop_out = false;
}

//---------------------------------------------------------------------
void XModule::set_stop_out() {
    status_.request_stop_out = true;
}

//---------------------------------------------------------------------
bool XModule::is_stop_out() {
    return status_.request_stop_out;
}

//---------------------------------------------------------------------
//обработка ошибки в соответствие с настройками модуля
void XModule::process_error(QString message) {
    int action = geti_("action_on_error");
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
void XModule::reset_error_values() { //сброс того, что быда ошибка при выполнении
    seti_("was_error", 0);
    clear_string_("error_text");
}

//---------------------------------------------------------------------
void XModule::set_error_values(QString message) { //установка того, что была ошибка
    seti_("was_error", 1);
    sets_("error_text", message);
}

//---------------------------------------------------------------------
