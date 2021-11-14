#ifndef XMODULE_H
#define XMODULE_H

//Вычислительный модуль (runtime module)
//Базовый класс для конкретных реализаций модулей
//каждый модуль должен реализовать следующие виртуальные функции:
//start()
//update()
//stop()
// - они работают в основном потоке, и поэтому могут общаться с GUI
//
//execute_call_internal()  - опциональная функция, вызов из другого модуля
//Важно, что эта функция может вызываться из других потоков,
//поэтому модули должны быть к этому готовы - они должны “защищать” с помощью mutex свои данные
//и работать со своим gui только в update.

#include "sdk_h.h"
#include <QObject>
#include <QPainter>
#include "xclass.h"

class InterfaceItem;
class Module;
class XObject;

//Runtime module status
class XModuleStatus {
public:
    bool was_started = false;

    //запущен ли модуль
    bool running = false;
    //bool enabled__ = false; //значение считывается на каждом update

    //модуль запрашивает остановку выполнения проекта
    bool request_stop_out = false;

};

//Runtime module class, base for most modules implementations
class XModule : public QObject, public XClass
{
    Q_OBJECT
public:
    //--------------------------------------------------------------
    //Public interface
    //--------------------------------------------------------------
    XModule(QString class_name);
    virtual ~XModule();

    //Module access, variables access and runtime values are inherited from XClass.


    //подклассы должны переопределить для своего имени
    //но это не виртуальная функция, так как статичная
    //static const QString static_class_name() { return ""; }

    //эта информация передается в конструкторе
    QString class_name();

    //основная функция запуска, вызывает start, update, stop
    void execute(ModuleExecuteStage stage);

    //нажатие кнопки - это можно делать и во время остановки всего
    //внимание, обычно вызывается из основного потока как callback
    void button_pressed(QString button_id);

    //------------------------------------------------------------------------
    //функция вызова между модулями, вызывает on_call
    //важно, что эта функция может вызываться из других потоков - модули должны быть к этому готовы
    //function - имя функции (действие, которое следует выполнить)
    //err - информация об ошибках.
    //При call-вызовах модули не должны генерировать исключения, а перехватывать их и писать в err.
    //Поэтому call перехватывает их, но реализация в on_call может генерировать исключение
    //То, что модуль может запрашивать у других модулей, определяется свойством
    //module_send_calls=sound_buffer_add    и через запятую остальное. * - значит без ограничений
    //То, что модуль может отдавать другим модулям, определяется свойством
    //module_accept_calls=sound_buffer_add   и через запятую остальное. * - значит без ограничений

    void call_function(XCallType function, ErrorInfo &err, XObject *input, XObject *output);

    //------------------------------------------------------------------------
    //General (Control) page
    bool general_is_enabled() { return geti_("general_enabled_"); }
    bool general_is_auto_update() { return geti_("general_auto_update_"); }
    QString general_bang_button_name() { return "general_bang_"; }
    //call "bang" of the module
    void general_bang() { button_pressed(general_bang_button_name()); }


    bool is_running();  //был фактический запуск

    //Если true после start/update - то нужно останавливать запуск
    //эта переменная управляется ставится изнутри, protected функциями reset_stop_out, set_stop_out
    bool is_stop_out();

    //Имя модуля - берется из module
    QString name();

    //обязательные переменные
    //модуль включен
    //bool is_enabled();
    //режим работы модуля - каждый кадр, только в начале или только в конце, callback
    //ModuleRunMode run_mode() { return ModuleRunMode(geti("run_mode")); }

    //статус - например, был ли выполнен старт
    XModuleStatus status() const { return status_; }

    void reset_error_values();                  //сброс того, что быда ошибка при выполнении
    void set_error_values(QString message);     //установка того, что была ошибка

protected:
    //--------------------------------------------------------------
    //Protected interface for subclasses
    //--------------------------------------------------------------

    //нужно ли остановить исполнение
    void reset_stop_out();
    void set_stop_out();

    //обработка ошибки в соответствие с настройками модуля
    void process_error(QString message);

    //функции исполнения, специфичные для модулей - они должны их переопределить
    //внимание, эта функция запускается всегда, без контроля enabled - для проверки используйте is_enabled()
    virtual void on_loaded() {}
    //эти функции запускаются, только если модуль включен:
    virtual void start() {}
    virtual void process_events() {}   //used for processing mouse/keyboard events in at XModuleVisual
    virtual void update() {}
    virtual void stop() {}

    //If module want to process button presses while stopped mode,
    //it should reimplement this function.
    //Note: if module don't need to process buttons - it may not implement this,
    //and instead use geti_... function, such as geti_button_start() to check button pressing inside update().
    virtual void on_button_pressed(QString /*button_id*/) {}

    //Universal call handler
    //По договоренности, можно задавать имя или номер функции в input
    //По договоренности, модуль может писать результат прямо в input, например, добавлять в звуковой буфер
    //важно, что эта функция может вызываться из других потоков - модули должны быть к этому готовы
    //function - имя функции (действие, которое следует выполнить)
    //То, что модуль может запрашивать у других модулей, определяется свойством
    //module_send_calls=sound_buffer_add    и через запятую остальное. * - значит без ограничений
    //То, что модуль может отдавать другим модулям, определяется свойством
    //module_accept_calls=sound_buffer_add   и через запятую остальное. * - значит без ограничений

    virtual void on_custom_call(XObject *input, XObject *output);

    //Specific call handlers
    //`create_widget` call implementation, creates QWidget and returns pointer on it
    virtual void *on_create_widget(QString parent_id);
    //resetting created widget (`create_widget` called with empty parent_id)
    virtual void on_reset_widget();

    //`render` call implementation
    virtual void on_render(QPainter &painter, int w, int h);

    //`sound_buffer_add` call implementation, fills `data` buffer
    //there are required to fill channels * samples values at data
    virtual void on_sound_buffer_add(int sample_rate, int channels, int samples, float *data);


    //`sound_buffer_received` call implementation, processes input `data` buffer
    //there are channels * samples values at `data`
    virtual void on_sound_buffer_received(int sample_rate, int channels, int samples, float *data);

private:
    //--------------------------------------------------------------
    //Private members
    //--------------------------------------------------------------
    QString class_name_;

    //Переменные, описывающие состояние выполнения
    XModuleStatus status_;

    //start модуля вызывается при его первом update
    //если запустили - то больше не запускаем в update
    void loaded_internal();     //действия при загрузке модуля
    void update_internal();     //выполнить update, и если нужно - start
    void stop_internal();       //выполнить stop

    //Main caller for start(), update()
    void bang_internal();       //bang: (start) and update if enabled, also calls process_events

    // Concrete call handlers
    // "create_widget" call, returns QWidget pointer
    void on_create_widget_internal(XObject *input, XObject *output);
    // "sound_buffer_add" call
    void on_sound_buffer_add_internal(XObject *input, XObject *output);
    // "sound_buffer_received" call
    void on_sound_buffer_received_internal(XObject *input, XObject *output);


};

#endif // XMODULE_H
