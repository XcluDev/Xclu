#ifndef MODULEINTERFACE_H
#define MODULEINTERFACE_H

//Невизуальное описание интерфейса, строится по ModuleInfo
#include "incl_h.h"

#include "moduleinfo.h"
#include "interfaceitem.h"
#include "visibilitygroups.h"

class EditorModule;
class EditorModuleState;
class QJsonObject;
class Module;

//Интерфейс модуля
class ModuleInterface
{
public:
    ModuleInterface(const ModuleInfo &info);
    ~ModuleInterface();

    ModuleDescription &description();

    //доступ к родительскому модулю - для получения информации о запуске и name, а также интерфейсу
    void set_module(Module *module);
    Module *module();

    //весь интерфейс
    QVector<InterfaceItem *> &items();

    //элемент по имени - кроме сепараторов
    InterfaceItem *var(QString name);

    //список по типу использования - const, in, out
    QVector<InterfaceItem *> &vars_qual(VarQualifier qual);

    //группы видимости - для создания дерева управления видимостью на GUI
    QVector<VisibleGroupBase> &vis_groups();

    //сигнал, что GUI подключен/отключен
    void gui_attached(EditorModule *editor);
    void gui_detached();
    bool is_gui_attached();

    //установить видимость элементов - используется при тестировании интерфейса,
    //а так, это делают сами переменные и поэтому в обычном применении модуля вызывать это не нужно
    void propagate_visibility();

    //команды для обновления внутренних значений из GUI и в GUI
    void gui_to_vars(VarQualifier qual, bool evaluate_expr = false); //вычисление expression и получение значения из gui
    void vars_to_gui(VarQualifier qual); //установка значения в gui
    void block_gui_constants();         //заблокировать константы, вызывается перед запуском проекта
    void unblock_gui_constants();       //раззаблокировать константы, вызывается после остановки проекта

    //пометить, что все элементы были изменены - при старте
    void set_changed_at_start();

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

private:
    //Родительский модуль
    Module *module_ = nullptr;  //удалять не надо

    ModuleDescription description_;
    //Предполагается, что строки не содержат комментарии и не пустые, и не содержат пробелов в начале и конце
    void parse_trimmed(const QStringList &lines);

    //Общая функция добавления элемента интерфейса в список
    //а также вставка в группу визуализации
    void push_item(InterfaceItem *item);

    //Добавление конкретных элементов в интерфейс - вызывают push_item
    void create_item(const InterfaceItemPreDescription &pre_description);
    void create_item(QString title_underscored, InterfaceItemType type,
                     const QStringList &description,
                     VarQualifier qual = VarQualifierIn,
                     QString line_to_parse = "", QString options = "",
                     QString qual_options = "");
    void create_decorate_item(QString name, InterfaceItemType type, const QStringList &description);
    void create_separator(InterfaceItemType type = InterfaceItemTypeSeparator, bool is_line = false);

    //создание имен для сепараторов, чтобы их использовать в visibility
    int separator_index_ = 0;
    QString generate_separator_name();

    //собрать описание элемента (строки, начинающиеся с "//"), и изменить счетчик i
    QStringList collect_description(const QStringList &lines, int &i);

    //Список всех элементов
    QVector<InterfaceItem *> items_;

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

    QMap<QString, InterfaceItem *> items_by_name_;

    QVector<QVector<InterfaceItem *>> vars_qual_;

    //Редактор модуля - используется, чтобы запомнить его tab. Удалять не следует
    EditorModule *editor_ = nullptr;
    //состояние GUI-редактора (номер страницы)
    EditorModuleState editor_state_;


};

#endif // MODULEINTERFACE_H
