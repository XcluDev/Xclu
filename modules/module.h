#ifndef MODULEINSTANCE_H
#define MODULEINSTANCE_H

//Модуль, содержащий невизуальный интерфейс (ModuleInterface) и исполнительную часть (XModule)

#include "incl_h.h"
#include "moduleseed.h"
#include "moduleinterface.h"
#include "xmodule.h"
#include "xintermodulecalls.h"

class XGuiEditor;
class QJsonObject;
class XObject;

class Module
{
public:
    //ModuleSeed парсится и преврашается в ModuleInterface, но указатель на него также запоминается для help
    Module(ModuleSeed *info_external, XModule *rtmodule_new);
    ~Module();

    //Описание типа модуля
    ModuleDescription &description();
    ModuleSeed *info() { return info_external_; } //хранится не тут, а в ModulesFactory - нужен для Help

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
    XModule *xmodule();

    //Compiling links and other things
    bool compile();

    //Выполнение
    void execute(ModuleExecuteStage stage);
    bool is_stop_out();
    bool is_running();
    void button_pressed(QString button_id);   //нажатие кнопки, даже при редактировании
    void bang();        //Bang button

    //call_function - Запуск функции из других модулей
    //важно, что эта функция может вызываться из других потоков - модули должны быть к этому готовы
    //function - имя функции (действие, которое следует выполнить)
    //err - информация об ошибках.
    //При call-вызовах модули не должны генерировать исключения, а перехватывать их и писать в err.
    //
    //То, что модуль может запрашивать у других модулей, определяется свойством
    //module_send_calls=sound_buffer_add    и через запятую остальное. * - значит без ограничений
    //То, что модуль может отдавать другим модулям, определяется свойством
    //module_accept_calls=sound_buffer_add   и через запятую остальное. * - значит без ограничений

    //Note: Use XIntermoduleCalls helper class for specific calls (render, create_widget, etc)


    //в случае исключения - оно выдастся
    void call_function(XCallType function, XObject *input = nullptr, XObject *output = nullptr);

    //исключение "записывается" в err
    void call_function_no_exception(XCallType function, ErrorInfo &err, XObject *input = nullptr, XObject *output = nullptr);


    //Доступ к переменным и запуску из других модулей

    //int, checkbox, button, enum (rawtext), string, text
    //index>=0: string, text separated by ' ' - no error if no such string!
    //index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
    QString gets(QString name, int index = -1, int index2 = -1);
    QString gets(XLinkParsed *link);

    //splits text using "\n"
    QStringList get_strings(QString name);

    void sets(QString name, QString v); //только out: int, checkbox, enum (rawtext), string, text
    void clear_string(QString name);
    void append_string(QString name, QString v, int extra_new_lines_count = 0); //дописать к строке, применимо где sets
    void append_string(QString name, QStringList v, int extra_new_lines_count = 0); //дописать к строке, применимо где sets

    //int, checkbox, button, enum (index)
    //index>=0: string, text separated by ' ' - no error if no such string!
    //index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
    int geti(QString name, int index = -1, int index2 = -1);
    int geti(XLinkParsed *link);

    void seti(QString name, int v); //только out: int, checkbox, enum (index)
    void increase_int(QString name, int increase = 1); //увеличение значения

    //float
    //index>=0: string, text separated by ' ' - no error if no such string!
    //index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
    float getf(QString name, int index = -1, int index2 = -1);
    float getf(XLinkParsed *link);


    void setf(QString name, float v);  //out: float

    QString getraw(QString name);  //enum (rawtext)
    void set_raw(QString name, QString v); //только out: enum (rawtext)


    QString get_title_value(QString name);  //enum (title)
    void set_title_value(QString name, QString v); //только out: enum (title)

    //Access to objects is only by pointers - because we are required not to copy data, it can be large
    XProtectedObject *get_object(QString name);

    //Set pointer to object
    //Note: object must be live, because only pointer to it is stored
    void set_object(QString name, XProtectedObject *object);

    //сигнал, что GUI подключен/отключен
    void gui_attached(XGuiEditor *editor);
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
    ModuleSeed *info_external_ = nullptr;    //хранится в ModulesFactory

    //Невизуальный интерфейс
    ModuleInterface *interf_ = nullptr;

    //Исполняемый модуль
    XModule *xmodule_ = nullptr;

    //Сигнал, что был запуск - вне зависимости от того, запустился ли реально xmodule_
    bool running_ = false;
    void set_running(bool v);

};

#endif // MODULEINSTANCE_H
