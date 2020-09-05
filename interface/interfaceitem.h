#ifndef INTERFACEITEM_H
#define INTERFACEITEM_H

//Абстрактный элемент интерфейса (переменные и оформление GUI), невизуальная часть
//Подклассы реализуют конкретные элементы.
//Также, они порождают визуальное представление в виде InterfaceGui

#include "incl_h.h"

struct InterfaceGuiPageCreator;
class InterfaceGui;
class QJsonObject;
class InterfaceItem;
class XDict;
class ModuleInterface;

//предварительная информация для построения элемента интерфейса
struct InterfaceItemPreDescription {
    QString title;
    InterfaceItemType type = InterfaceItemTypeNone;
    VarQualifier qualifier = VarQualifierIn;
    QString qualifier_options; //опции в квалификаторе, типа out(not_save)
    QString options;        //дополнительные опции, типа choose:file, choose:folder для строк string(choose:file)
    QString line_to_parse;
    QStringList description;    //строки с описанием
};


//Элемент интерфейса
class InterfaceItem
{
public:
    static InterfaceItem *create_item(ModuleInterface *parent, const InterfaceItemPreDescription &pre_description);
    static InterfaceItem *create_item(ModuleInterface *parent, QString title_underscored, InterfaceItemType type,
                                      const QStringList &description,
                                      VarQualifier qual = VarQualifierIn, QString line_to_parse = "",
                                      QString options = "",
                                      QString qual_options = "");
    //page, group
    static InterfaceItem *create_decorate_item(ModuleInterface *parent, QString name, InterfaceItemType type, const QStringList &description);
    //separator
    static InterfaceItem *create_separator(ModuleInterface *parent, QString name, InterfaceItemType type = InterfaceItemTypeSeparator, bool is_line = false);

public:
    //создание невизуальной переменной (или описание элемента интерфейса),
    //и парсинг остатка строки line_to_parse
    InterfaceItem(ModuleInterface *parent, const InterfaceItemPreDescription &pre_description);
    virtual ~InterfaceItem();

    //доступ ко всему интерфейсу
    ModuleInterface *parent() { return parent_; }

    //Имя и тип, а также информация для создания GUI  -------------------------
    QString name();
    QString title();
    InterfaceItemType type();
    VarQualifier qualifier();
    bool is_const();
    bool is_in();
    bool is_out();
    bool is_save_to_project();    //в случае out(not_save) ставится false. Это знак, что значение переменной не нужно сохранять в проекте

    //Описание добавляется уже после создания, следующей строкой в скрипте GUI
    //может быть несколько строк - например, в string с выбором файла или папки,
    //или значение по умолчанию для текста
    //поэтому, к ним доступ через индекс. Если элемента нет - возвращается пустая строка
    QString description(int index = 0);
    int description_count();
    //void add_description(QString description); //не позволяем добавлять описание - так как его сразу передаем в конструктор

    //Проверка, что изменилось значение -------------------------
    //Важно: для объектов эти функция получает доступ к объекту, поэтому, нельзя вызывать, когда объект уже заблокирован
    bool was_changed(); //эта функция позволяет выяснить, изменялось ли значение после последнего вызова was_changed
                        //при этом, при запуске проекта это всегда ставится в true
                        //функция предназначена для обновлений объектов во время работы, а не для записи состояния проекта
                        //поэтому для const значение true только один раз после запуска проекта
    void set_changed(); //переменная была точно изменена - при следующем запросе was_changed выдастся true

    //Доступ к значениям -------------------------
    //Соответствующие типы должны переопределить эти функции
    //Здесь мы не проверяем правильность использования, и перелагаем проверку на модули
    //string
    virtual bool supports_string() { return false; }
    virtual QString value_string() { return ""; }
    virtual void set_value_string(const QString &) {}

    //int
    virtual bool supports_int() { return false; }
    virtual int value_int() { return 0; }
    virtual void set_value_int(int) {}

    //float
    virtual bool supports_float() { return false; }
    virtual float value_float() { return 0; }
    virtual void set_value_float(float) {}

    //value_title - для enum
    virtual bool supports_value_title() { return false; }
    virtual QString value_title() { return ""; }
    virtual void set_value_title(QString) {}

    //object
    virtual bool supports_object() { return false; }
    virtual XDict *get_object() { return nullptr; }

    //Запись, считывание и копирование -------------------------
    //хранит ли данные (или просто интерфейсный элемент, например, сепаратор)
    virtual bool store_data() { return true; }

    //копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
    //специальные типы, которые не поддерживают перенос через строку (object) - должны переписать copy_data_to_internal
    void copy_data_to(InterfaceItem *item);

    //Запись и считывание json
    void write_json(QJsonObject &json);
    void read_json(const QJsonObject &json);


    //Expression -------------------------
    bool expression_enabled(); //требуется ли expression (для out - нет), используется при записи на диск

    bool use_expression();  //используется ли expression для установки значения
    void set_use_expression(bool v);
    QString expression();
    void set_expression(const QString &expr);

    //GUI -------------------------
    //графический интерфейс, он тут создается, но хранится отдельно
    virtual InterfaceGui *create_gui(InterfaceGuiPageCreator &input);

    //сигнал, что GUI подключен/отключен
    void gui_attached();
    void gui_detached();
    bool is_gui_attached();

    //работа с GUI
    void gui_to_var(bool evaluate_expr); //вычисление expression и получение значения из gui
    void var_to_gui(); //установка значения в gui, также отправляет сигнал о видимости
    void block_gui_editing();       //запретить редактирование - всегда для out и после запуска для const
    void unblock_gui_editing();     //разрешить редактирование
    void propagate_visibility();    //обновить дерево видимости - используется, в частности, при тестировании интерфейса

protected:
    //доступ ко всему интерфейсу
    ModuleInterface *parent_ = nullptr;

    //основные характеристики
    QString title_;
    QString name_;
    InterfaceItemType type_;
    VarQualifier qualifier_;
    QStringList description_;   //может быть несколько строк

    bool save_to_project_ = true;  //если false, то не записывать значение в проект

    //изменялась ли переменная после последнего вызова was_changed (после старта всегда true)
    //это реализуется с помощью set_changed и may_changed
    //при этом, проверка may_changed выполняется на основе анализа того, что поддерживает объект
    //сначала int, потом float, потом string, потом object
    bool force_changed_ = false;
    int last_int_ = 0;
    float last_float_ = 0;
    QString last_string_;

    //Выражения (в данный момент не поддерживаются)
    bool use_expression_ = false;
    QString expression_;

    //парсинг q=0 0:1 100,10 -> name='q', query = '0','0:1','100,10'
    static void split_equal(const QString &line, QString &name, QStringList &query);

    //парсинг q A B -> name='q', query = 'A','B'
    static void split_spaced(const QString &line, QString &name, QStringList &query);

    //парсинг числовых значений
    static float parse_float(QString line, QString error_message);
    static int parse_int(QString line, QString error_message);

    //подключен ли GUI
    bool gui_attached_ = false;

    //работа с GUI - внутренняя реализация, без expression,
    //реализуется в конкретных классах
    //вызывается, когда is_gui_attached - поэтому, это не нужно проверять
    virtual void gui_to_var_internal() {} //получение значения из gui
    virtual void var_to_gui_internal() {} //установка значения в gui

    //копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
    //специальные типы, которые не поддерживают перенос через строку (array и image) - должны переписать copy_data_to_internal
    virtual void copy_data_to_internal(InterfaceItem *item);


    //это общее gui__ - хотя в самих представителях будут конкретные представители,
    //нам требуется общий, чтобы передавать сигналы о видимости
    //подклассы должны его устанавливать!
    InterfaceGui *gui__ = nullptr; //не нужно его удалять
};



#endif // INTERFACEITEM_H
