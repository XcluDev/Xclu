#ifndef RTMODULE_H
#define RTMODULE_H

//Вычислительный модуль (run-time module)
//Базовый класс для конкретных реализаций модулей
//каждый модуль должен реализовать следующие виртуальные функции:
//execute_start_internal()
//execute_update_internal()
//execute_stop_internal()
// - они работают в основном потоке, и поэтому могут общаться с GUI
//
//execute_call_internal()  - опциональная функция, вызов из другого модуля
//Важно, что эта функция может вызываться из других потоков,
//поэтому модули должны быть к этому готовы - они должны “защищать” с помощью mutex свои данные
//и работать со своим gui только в update.

#include "incl_qt.h"
#include <QObject>

class ModuleInterface;
class InterfaceItem;
class Module;
class XcluObject;

//Переменные, описывающие состояние
class RtModuleStatus {
public:
    bool was_started = false;

    //запущен ли модуль
    bool running = false;
    bool enabled__ = false; //значение считывается на каждом update

    //модуль запрашивает остановку выполнения проекта
    bool request_stop_out = false;


};

//Описание модуля
class RtModule : public QObject
{
    Q_OBJECT
public:
    RtModule(QString class_name);
    virtual ~RtModule();

    //подклассы должны переопределить для своего имени
    //но это не виртуальная функция, так как статичная
    //static const QString static_class_name() { return ""; }

    //эта информация передается в конструкторе
    QString class_name();

    //Установка интерфейса со списком переменных - требуется делать до начала выполнения
    void set_interface(ModuleInterface *interf); //interf потом удалять не надо

    //основная функция запуска, вызывает execute_start_internal, execute_update_internal, execute_stop_internal
    void execute(ModuleExecuteStage stage);

    //функция вызова между модулями, вызывает call_internal
    //важно, что эта функция может вызываться из других потоков - модули должны быть к этому готовы
    //function - имя функции (действие, которое следует выполнить)
    //err - информация об ошибках.
    //При call-вызовах модули не должны генерировать исключения, а перехватывать их и писать в err.
    //Поэтому call перехватывает их, но реализация в call_internal может генерировать исключение
    //То, что модуль может запрашивать у других модулей, определяется свойством
    //module_send_calls=sound_buffer_add    и через запятую остальное. * - значит без ограничений
    //То, что модуль может отдавать другим модулям, определяется свойством
    //module_accept_calls=sound_buffer_add   и через запятую остальное. * - значит без ограничений

    void call(QString function, ErrorInfo &err, XcluObject *input, XcluObject *output);


    bool is_running();  //был фактический запуск

    //Если true после start/update - то нужно останавливать запуск
    //эта переменная управляется ставится изнутри, protected функциями reset_stop_out, set_stop_out
    bool is_stop_out();

    //доступ к интерфейсу модуля
    ModuleInterface *interf();

    //доступ к основному модулю - для получения информации о запуске и name
    void set_module(Module *module);
    Module *module();

    //Имя и id модуля - берется из module
    QString name();
    QString id();

    //обязательные переменные
    //модуль включен
    bool is_enabled();
    //режим работы модуля - каждый кадр, только в начале или только в конце, callback
    ModuleRunMode run_mode() { return ModuleRunMode(get_int("run_mode")); }

    //статус - например, был ли выполнен старт
    RtModuleStatus status() const { return status_; };

    void reset_error_values();                  //сброс того, что быда ошибка при выполнении
    void set_error_values(QString message);     //установка того, что была ошибка

    //Проверка, изменились ли переменные
    bool was_changed(QString name);
    //Важно, что для объектов эта функция получает доступ к объекту с помощью ObjectRead,
    //поэтому, нельзя ее вызывать, если активирован другой ObjectRead[Write] для этого объекта

    //Доступ к переменным - с учетом их квалификатора
    QString get_string(QString name);   //int, checkbox, button, stringlist (rawtext), string, text
    void set_string(QString name, QString v); //только out: int, checkbox, stringlist (rawtext), string, text
    void append_string(QString name, QString v); //дописать к строке, применимо где set_string

    int get_int(QString name);    //int, checkbox, button, stringlist (index)
    void set_int(QString name, int v); //только out: int, checkbox, stringlist (index)
    void increase_int(QString name, int increase = 1); //увеличение значения

    float get_float(QString name);  //float
    void set_float(QString name, float v);  //out: float

    QString get_title_value(QString name);  //stringlist (title)
    void set_title_value(QString name, QString v); //только out: stringlist (title)

    //доступ к объектам идет только по указателям -
    //так как объекты могут быть очень большими, и поэтому с ними работаем непосредтсвенно,
    //без копирования
    //объекты снабжены мютексами, поэтому следует начинать и завершать с ними взаимодействие
    XcluObject *get_object(QString name);


protected:
    QString class_name_;

    //Переменные, описывающие состояние выполнения
    RtModuleStatus status_;

    //start модуля вызывается при его первом update
    //если запустили - то больше не запускаем в update
    void internal_update();     //выполнить update, и если нужно - start
    void internal_stop();       //выполнить stop
    void internal_one_shot();   //start, update, stop за один раз


    //нужно ли остановить исполнение
    void reset_stop_out();
    void set_stop_out();

    ModuleInterface *interf_ = nullptr; //удалять не надо
    Module *module_ = nullptr;  //удалять не надо

    //обработка ошибки в соответствие с настройками модуля
    void process_error(QString message);

    //функции исполнения, специфичные для модулей - они должны их переопределить
    virtual void execute_start_internal() {}
    virtual void execute_update_internal() {}
    virtual void execute_stop_internal() {}

    //вызов модуля извне
    //по договоренности, модуль может писать результат прямо в input, например, добавлять в звуковой буфер
    //важно, что эта функция может вызываться из других потоков - модули должны быть к этому готовы
    //function - имя функции (действие, которое следует выполнить)
    //То, что модуль может запрашивать у других модулей, определяется свойством
    //module_send_calls=sound_buffer_add    и через запятую остальное. * - значит без ограничений
    //То, что модуль может отдавать другим модулям, определяется свойством
    //module_accept_calls=sound_buffer_add   и через запятую остальное. * - значит без ограничений

     virtual void call_internal(QString function, XcluObject *input, XcluObject *output);

    //выполнить только один раз - в начале или конце
    void execute_one_shot();

};

#endif // RTMODULE_H
