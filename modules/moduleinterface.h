#ifndef MODULEINTERFACE_H
#define MODULEINTERFACE_H

//Невизуальное описание интерфейса, строится по ModuleSeed
#include "incl_h.h"

#include "moduleseed.h"
#include "xitem.h"
#include "visibilitygroups.h"

class XGuiEditor;
class EditorModuleState;
class QJsonObject;
class Module;


//Интерфейс модуля
class ModuleInterface
{
public:
    ModuleInterface(const ModuleSeed &info);
    ~ModuleInterface();

    ModuleDescription &description();

    //доступ к родительскому модулю - для получения информации о запуске и name, а также интерфейсу
    void set_module(Module *module);
    Module *module();

    //весь интерфейс
    QVector<XItem *> &items();

    //does module contains item with given name
    bool has_item(QString name);

    //элемент по имени - кроме сепараторов
    XItem *var(QString name);

    //группы видимости - для создания дерева управления видимостью на GUI
    QVector<VisibleGroupBase> &vis_groups();

    //Compiling links and other things
    bool compile();

    //сигнал, что GUI подключен/отключен
    void gui_attached(XGuiEditor *editor);
    void gui_detached();
    bool is_gui_attached();

    //установить видимость элементов - используется при тестировании интерфейса,
    //а так, это делают сами переменные и поэтому в обычном применении модуля вызывать это не нужно
    void propagate_visibility();

    //команды для обновления внутренних значений из GUI и в GUI
    void gui_to_vars(const XQualifierMask &qual, bool evaluate_expr = false); //вычисление expression и получение значения из gui
    void vars_to_gui(const XQualifierMask &qual); //установка значения в gui
    void block_gui(const XQualifierMask &qual);         //заблокировать константы, вызывается перед запуском проекта
    void unblock_gui(const XQualifierMask &qual);       //разблокировать константы, вызывается после остановки проекта

    //пометить, что все элементы были изменены - при старте
    void set_changed_at_start();

    //update before rt-module's update
    void update();

    //запомнить/восстановить состояние GUI (страницу, промотку)
    void gui_to_state();
    void state_to_gui();

    //callback из GUI
    void callback_button_pressed(QString button_id);

    //редактор
    EditorModuleState editor_state();
    void set_editor_state(EditorModuleState editor_state);

    //дублирование данных переменных и состояние редактора, используется при дублировании модулей
    //предполагается, что оба интерфейса идентичны, то есть, принадлежат одному типу модулей
    void copy_data_to(ModuleInterface *interf);

    //Запись и считывание json
    void write_json(QJsonObject &json);
    void read_json(const QJsonObject &json);

    //----------------------------------------------
    //Variables access
    //----------------------------------------------
    //int, checkbox, button, enum (rawtext), string, text
    //index>=0: string, text separated by ' ' - no error if no such string!
    //index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
    QString gets(QString name, int index = -1, int index2 = -1);

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

    void seti(QString name, int v); //только out: int, checkbox, enum (index)
    void increase_int(QString name, int increase = 1); //увеличение значения

    //float
    //index>=0: string, text separated by ' ' - no error if no such string!
    //index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
    float getf(QString name, int index = -1, int index2 = -1);

    void setf(QString name, float v);  //out: float

    //enum (rawtext)
    QString getraw(QString name);
    void set_raw(QString name, QString text); //out: enum

    QString get_title_value(QString name);  //enum (title)
    void set_title_value(QString name, QString v); //только out: enum (title)

    //доступ к объектам идет только по указателям -
    //так как объекты могут быть очень большими, и поэтому с ними работаем непосредтсвенно,
    //без копирования
    //объекты снабжены мютексами, поэтому следует начинать и завершать с ними взаимодействие
    XProtectedStruct *get_object(QString name);

private:
    //Родительский модуль
    Module *module_ = nullptr;  //удалять не надо

    ModuleDescription description_;
    //Предполагается, что строки не содержат комментарии и не пустые, и не содержат пробелов в начале и конце
    void parse_trimmed(const QStringList &lines);

    //Общая функция добавления элемента интерфейса в список
    //а также вставка в группу визуализации
    void push_item(XItem *item);

    //Добавление конкретных элементов в интерфейс - вызывают push_item
    void new_item(const XItemPreDescription &pre_description);
    void new_item(QString title_underscored, QString type,
                     const QStringList &description,
                     XQualifier qual = XQualifierIn,
                     QString line_to_parse = "", QString options = "",
                     QString qual_options = "");
    void new_decorate_item(QString name, QString type, const QStringList &description);
    void new_separator(QString type = xitem_separator(), bool is_line = false);

    //создание имен для сепараторов, чтобы их использовать в visibility
    int separator_index_ = 0;
    QString generate_separator_name();

    //собрать описание элемента (строки, начинающиеся с "//"), и изменить счетчик i
    QStringList collect_description(const QStringList &lines, int &i);

    //Список всех элементов
    QVector<XItem *> items_;

    //Группы видимости - для динамического интерфейса
    QVector<VisibleGroupBase> vis_groups_;
    bool vis_group_opened_ = false;
    //добавить последний элемент в текущую vis_group_ если, конечно, она открыта для добавления
    //это делается автоматически во всех create_item_...
    void add_to_vis_group();

    void clear();

    //проверка того, что разные элементы имеют разные имена (у которых есть имена), и заполнение map для быстрого доступа
    void update_maps();

    //установка параметров по-умолчанию из описания модуля на страницу general
    void set_general_values();

    QMap<QString, XItem *> items_by_name_;

    //Редактор модуля - используется, чтобы запомнить его tab. Удалять не следует
    XGuiEditor *editor_ = nullptr;
    //состояние GUI-редактора (номер страницы)
    EditorModuleState editor_state_;


};

#endif // MODULEINTERFACE_H
