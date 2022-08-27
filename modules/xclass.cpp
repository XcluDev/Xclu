#include "xclass.h"
#include "xmoduleinterface.h"
#include "xmodule.h"
#include "incl_cpp.h"
#include "xobject.h"
#include "xcall.h"

//---------------------------------------------------------------------
XClass::XClass(QString class_name) {
    class_name_ = class_name;
}

//---------------------------------------------------------------------
XClass::~XClass() {

}

//---------------------------------------------------------------------
QString XClass::class_name() {
    return class_name_;
}

//---------------------------------------------------------------------
QString XClass::name() {
    return module()->name();
}

//---------------------------------------------------------------------
void XClass::loaded_internal() {     //действия при загрузке модуля
    on_loaded();
}

//---------------------------------------------------------------------
//выполнить update, и если нужно - start
void XClass::update_internal() {
    if (is_auto_update()) {
        bang_internal();
    }
}

//---------------------------------------------------------------------
//bang: (start) and update if enabled
void XClass::bang_internal() {
    if (is_enabled()) {
        if (!status_.was_started) {
            start();
            status_.was_started = true;
        }
        process_events();   //mouse/keyboard events in XClassWidget
        update();
    }
}

//---------------------------------------------------------------------
//выполнить stop, и если нужно - start
void XClass::stop_internal() {
    if (status_.was_started) {
        status_.was_started = false;
        stop();
    }
    //status_.enabled__ = false;
}

//---------------------------------------------------------------------
//единая функция исполнения
void XClass::execute(ModuleExecuteStage stage) {
    //отлов исключений путем обработки ошибок, и реакция соответственно настройках
    try {
        //обновление enabled__
        //status_.enabled__ = _is_enabled_();

        //Clear stop values
        reset_stop_out();

        //auto mode = run_mode();
        //bool enabled = is_enabled();
        switch (stage) {
        case ModuleExecuteStageLoaded:
            loaded_internal();
            break;
        case ModuleExecuteStageStart:
            //Clear errors
            reset_error_values();

            status_.running = true;
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
            status_.running = false;
            //останавливаем всегда
            stop_internal();
            break;

        /*case ModuleExecuteStageCallback:
            if (enabled) {
                xc_assert(mode == ModuleRunMode_Callback, "XModule is called by callback, but it's Run Mode is not Callback!");
                update_internal();
            }
            break;*/

        default:
            xc_exception(QString("Unknown execute stage %1").arg(stage));
        }
    }
    catch(XException& e) {
        //отлов исключений путем обработки ошибок, и реакция соответственно настройках
        process_error(e.whatQt());
    }
}

//---------------------------------------------------------------------
//нажатие кнопки - это можно делать и во время остановки всего
//внимание, обычно вызывается из основного потока как callback
void XClass::button_pressed(QString button_id) {
    if (button_id == module_bang_button_name()) {
        if (is_running()) {
            bang_internal();
        }
        else {
            xc_message_box("Can't bang - please run the project before.");
        }
        return;
    }

    //send as pressed event
    on_button_pressed(button_id);
}

//---------------------------------------------------------------------
// Subclasses must reimplement this for drawing
void XClass::draw(QPainter & /*painter*/, int /*w*/, int /*h*/) {
    xc_exception("draw() is not yet implemented for class `" + class_name() + "`");
}

//---------------------------------------------------------------------
//функция вызова между модулями, вызывает on_call
//важно, что эта функция может вызываться из других потоков - модули должны быть к этому готовы
void XClass::call(XCall& call) {
    try {
        if (call.error().is_error()) return;

        //process predefined functions
        switch (call.type()) {
        case XCallType::None: xc_exception("XClass::call type is XCallType::None");
            break;
        //process universal function
        case XCallType::Custom: on_custom_call(call);
            break;
        case XCallType::CreateWidget: on_create_widget_internal(call);
            break;
        case XCallType::SoundBufferAdd: {
            auto *call_data = call.data<XCallSoundBufferAdd>();
            on_sound_buffer_add(call_data->sample_rate, call_data->channels, call_data->samples, call_data->data);
        }
            break;

        case XCallType::SoundBufferReceived: {
            auto *call_data = call.data<XCallSoundBufferReceived>();
            on_sound_buffer_received(call_data->sample_rate, call_data->channels, call_data->samples, call_data->data);
        }
            break;
        default:
            xc_exception("Unknnown function type");
        }

    }
    catch (XException &e) {
        call.error().prepend(QString("Error during executing function '%1' in module '%2':")
                  .arg(xcalltype_to_string_for_user(call.type())).arg(name()), e.err());
    }
}

//---------------------------------------------------------------------
//"create_widget" call, returns QWidget pointer
//if parent_id == "", it means need to reset widget pointer (at stop)
void XClass::on_create_widget_internal(XCall& call) {
    auto *call_data = call.data<XCallCreateWidget>();

    QString parent_id = call_data->in_parent_id;
    // if parent_id is empty - it means that we need to delete widget
    if (parent_id.isEmpty()) {
        on_reset_widget();
    }
    else {
        // Check we are not started
        xc_assert(status().was_started,
                    QString("Can't create widget, because module '%1' was not started yet."
                            " You need to place it before parent '%2'.")
                    .arg(module_->name())
                    .arg(parent_id));
        call_data->out_widget = on_create_widget(parent_id);
    }
}

//---------------------------------------------------------------------
void XClass::on_custom_call(XCall& call) {
    xc_exception("XModule '" + name()
                   + "' can't process custom call, because on_custom_call() is not implemented");
}

//---------------------------------------------------------------------
//`create_widget` call implementation, creates QWidget and returns pointer on it
void *XClass::on_create_widget(QString /*parent_id*/) {
    xc_exception("XModule '" + name()
                   + "' can't process function 'create_widget', because on_create_widget() is not implemented");
    return nullptr;
}

//---------------------------------------------------------------------
//resetting created widget (`create_widget` called with empty parent_id)
void XClass::on_reset_widget() {
    xc_exception("XModule '" + name()
                   + "' can't process function 'create_widget', because on_reset_widget() is not implemented");
}

//---------------------------------------------------------------------
//`render` call implementation
void XClass::on_render(QPainter &/*painter*/, int /*w*/, int /*h*/) {
    xc_exception("XModule '" + name()
                   + "' can't process Paint call, because on_paint() is not implemented");
}

//---------------------------------------------------------------------
//`sound_buffer_add` call implementation, fills `data` buffer
//there are required to fill channels * samples values at data
void XClass::on_sound_buffer_add(int /*sample_rate*/, int /*channels*/, int /*samples*/, float * /*data*/) {
    xc_exception("XModule '" + name()
                   + "' can't process function 'sound_buffer_add', because on_sound_buffer_add() is not implemented");
}

//---------------------------------------------------------------------
//`sound_buffer_received` call implementation, processes input `data` buffer
//there are channels * samples values at `data`
void XClass::on_sound_buffer_received(int /*sample_rate*/, int /*channels*/, int /*samples*/, float * /*data*/) {
    xc_exception("XModule '" + name()
                   + "' can't process function 'sound_buffer_received', because on_sound_buffer_received() is not implemented");
}

//---------------------------------------------------------------------
bool XClass::is_running() {
    return status_.running;
}

//---------------------------------------------------------------------
//bool XClass::is_enabled() {
//    return status_.enabled__;
//}

//---------------------------------------------------------------------
void XClass::reset_stop_out() {
    status_.request_stop_out = false;
}

//---------------------------------------------------------------------
void XClass::set_stop_out() {
    status_.request_stop_out = true;
}

//---------------------------------------------------------------------
bool XClass::is_stop_out() {
    return status_.request_stop_out;
}

//---------------------------------------------------------------------
//обработка ошибки в соответствие с настройками модуля
void XClass::process_error(QString message) {
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
        xc_exception("Internal error: unknown action_on_error in module " + module()->name());
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
        xc_console_warning(message);
    }

    //показ сообщения
    if (show_message) {
        xc_message_box(message);
    }
    if (send_stop) {
        set_stop_out();
    }
}

//---------------------------------------------------------------------
void XClass::reset_error_values() { //сброс того, что быда ошибка при выполнении
    seti_("was_error", 0);
    clear_string_("error_text");
}

//---------------------------------------------------------------------
void XClass::set_error_values(QString message) { //установка того, что была ошибка
    seti_("was_error", 1);
    sets_("error_text", message);
}

//---------------------------------------------------------------------
