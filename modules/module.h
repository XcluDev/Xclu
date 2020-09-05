#ifndef MODULEINSTANCE_H
#define MODULEINSTANCE_H

//Модуль, содержащий невизуальный интерфейс (ModuleInterface) и исполнительную часть (RtModule)

#include "incl_h.h"
#include "moduleinfo.h"
#include "moduleinterface.h"
#include "rtmodule.h"

class EditorModule;
class QJsonObject;
class XDict;

class Module
{
public:
    //ModuleInfo парсится и преврашается в ModuleInterface, но указатель на него также запоминается для help
    Module(ModuleInfo *info_external, RtModule *rtmodule_new);
    ~Module();

    //Описание типа модуля
    ModuleDescription &description();
    ModuleInfo *info() { return info_external_; } //хранится не тут, а в ModulesFactory - нужен для Help

    //Имя и name
    QString name();
    void set_name(QString name);
    //QString name();
    //void set_id(QString name);

    //Дублирование модуля, без имени
    Module *duplicate(QString new_nameid);

    //Невизуальный интерфейс
    ModuleInterface *interf();

    //Исполняемый модуль
    RtModule *rtmodule();

    //Выполнение
    void execute(ModuleExecuteStage stage);
    bool is_stop_out();
    bool is_running();
    void button_pressed(QString button_id);   //нажатие кнопки, даже при редактировании

    //access_call - Запуск функции из других модулей
    //важно, что эта функция может вызываться из других потоков - модули должны быть к этому готовы
    //function - имя функции (действие, которое следует выполнить)
    //err - информация об ошибках.
    //При call-вызовах модули не должны генерировать исключения, а перехватывать их и писать в err.
    //
    //То, что модуль может запрашивать у других модулей, определяется свойством
    //module_send_calls=sound_buffer_add    и через запятую остальное. * - значит без ограничений
    //То, что модуль может отдавать другим модулям, определяется свойством
    //module_accept_calls=sound_buffer_add   и через запятую остальное. * - значит без ограничений
    //
    //Популярные call-имена для function в классе call_function_name:
    //call_function_name::sound_buffer_add()

    //в случае исключения - оно выдастся
    void access_call(QString function, XDict *input = nullptr, XDict *output = nullptr);

    //исключение "записывается" в err
    void access_call_no_exception(QString function, ErrorInfo &err, XDict *input = nullptr, XDict *output = nullptr);


    //Доступ к переменным и запуску из других модулей

    //int, checkbox, button, enum (rawtext), string, text
    //index>=0: string, text separated by ' ' - no error if no such string!
    //index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
    QString gets(QString name, int index = -1, int index2 = -1);

    //splits text using "\n"
    QStringList get_strings(QString name);

    void sets(QString name, QString v); //только out: int, checkbox, enum (rawtext), string, text

    //int, checkbox, button, enum (index)
    //index>=0: string, text separated by ' ' - no error if no such string!
    //index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
    int geti(QString name, int index = -1, int index2 = -1);

    void seti(QString name, int v); //только out: int, checkbox, enum (index)

    //float
    //index>=0: string, text separated by ' ' - no error if no such string!
    //index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
    float getf(QString name, int index = -1, int index2 = -1);

    void setf(QString name, float v);  //out: float

    QString get_title_value(QString name);  //enum (title)
    void set_title_value(QString name, QString v); //только out: enum (title)
    //доступ к объектам идет только по указателям
    XDict *get_object(QString name);

    //сигнал, что GUI подключен/отключен
    void gui_attached(EditorModule *editor);
    void gui_detached();
    bool is_gui_attached();

    //Вычисление expressions и работа с GUI, см. определение GuiStage
    //Предполагается, что извне приходят только действия с проектом: GuiStageProjectLoaded и GuiStageProjectBeforeSaving
    //Побочное действие - также ставит и выключает is_running
    void gui_action(GuiStage stage, bool affect_is_running = true);

    //Запись и считывание json
    void write_json(QJsonObject &json);
    void read_json(const QJsonObject &json);

private:
    QString name_;
    QString module_type_title_;   //тип

    //Информация
    ModuleInfo *info_external_ = nullptr;    //хранится в ModulesFactory

    //Невизуальный интерфейс
    ModuleInterface *interf_ = nullptr;

    //Исполняемый модуль
    RtModule *rtmodule_ = nullptr;

    //Сигнал, что был запуск - вне зависимости от того, запустился ли реально rtmodule_
    bool running_ = false;
    void set_running(bool v);

};

#endif // MODULEINSTANCE_H
