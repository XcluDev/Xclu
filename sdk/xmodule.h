#ifndef XMODULE_H
#define XMODULE_H

//Вычислительный модуль (runtime module)
//Базовый класс для конкретных реализаций модулей
//каждый модуль должен реализовать следующие виртуальные функции:
//impl_start()
//impl_update()
//impl_stop()
// - они работают в основном потоке, и поэтому могут общаться с GUI
//
//execute_call_internal()  - опциональная функция, вызов из другого модуля
//Важно, что эта функция может вызываться из других потоков,
//поэтому модули должны быть к этому готовы - они должны “защищать” с помощью mutex свои данные
//и работать со своим gui только в update.

#include "incl_h.h"
#include <QObject>
#include "xclass.h"

class InterfaceItem;
class Module;
class XDict;

//Runtime module status
class XModuleStatus {
public:
    bool was_started = false;

    //запущен ли модуль
    bool running = false;
    bool enabled__ = false; //значение считывается на каждом update

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

    //основная функция запуска, вызывает impl_start, impl_update, impl_stop
    void execute(ModuleExecuteStage stage);

    //нажатие кнопки - это можно делать и во время остановки всего
    //внимание, обычно вызывается из основного потока как callback
    void button_pressed(QString button_id);

    //------------------------------------------------------------------------
    //функция вызова между модулями, вызывает impl_call
    //важно, что эта функция может вызываться из других потоков - модули должны быть к этому готовы
    //function - имя функции (действие, которое следует выполнить)
    //err - информация об ошибках.
    //При call-вызовах модули не должны генерировать исключения, а перехватывать их и писать в err.
    //Поэтому call перехватывает их, но реализация в impl_call может генерировать исключение
    //То, что модуль может запрашивать у других модулей, определяется свойством
    //module_send_calls=sound_buffer_add    и через запятую остальное. * - значит без ограничений
    //То, что модуль может отдавать другим модулям, определяется свойством
    //module_accept_calls=sound_buffer_add   и через запятую остальное. * - значит без ограничений

    void call(QString function, ErrorInfo &err, XDict *input, XDict *output);

    //------------------------------------------------------------------------
    bool is_running();  //был фактический запуск

    //Если true после start/update - то нужно останавливать запуск
    //эта переменная управляется ставится изнутри, protected функциями reset_stop_out, set_stop_out
    bool is_stop_out();

    //Имя модуля - берется из module
    QString name();

    //обязательные переменные
    //модуль включен
    bool is_enabled();
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
    virtual void impl_loaded() {}
    //эти функции запускаются, только если модуль включен:
    virtual void impl_start() {}
    virtual void impl_update() {}
    virtual void impl_stop() {}

    //нажатие кнопки, даже когда модуль остановлен - модуль также должен переопределить эту функцию
    //внимание, обычно вызывается из основного потока как callback
    virtual void impl_button_pressed(QString /*button_id*/) {}

    //Universal call handler
    //по договоренности, модуль может писать результат прямо в input, например, добавлять в звуковой буфер
    //важно, что эта функция может вызываться из других потоков - модули должны быть к этому готовы
    //function - имя функции (действие, которое следует выполнить)
    //То, что модуль может запрашивать у других модулей, определяется свойством
    //module_send_calls=sound_buffer_add    и через запятую остальное. * - значит без ограничений
    //То, что модуль может отдавать другим модулям, определяется свойством
    //module_accept_calls=sound_buffer_add   и через запятую остальное. * - значит без ограничений

    virtual void impl_call(QString function, XDict *input, XDict *output);

    //Concrete call handlers
    //`create_widget` call implementation, creates QWidget and returns pointer on it
    virtual void *impl_create_widget(QString parent_id);

    //`sound_buffer_add` call implementation, fills `data` buffer
    //there are required to fill channels * samples values at data
    virtual void impl_sound_buffer_add(int sample_rate, int channels, int samples, float *data);

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
    void one_shot_internal();   //start, update, stop за один раз

    //Concrete call handlers
    //"create_widget" call, returns QWidget pointer
    void create_widget_internal(XDict *input, XDict *output);
    //"sound_buffer_add" call
    void sound_buffer_add_internal(XDict *input, XDict *output);


};

#endif // XMODULE_H
