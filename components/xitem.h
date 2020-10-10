#ifndef INTERFACEITEM_H
#define INTERFACEITEM_H

//Абстрактный элемент интерфейса (переменные и оформление GUI), невизуальная часть
//Подклассы реализуют конкретные элементы.
//Также, они порождают визуальное представление в виде XGui

#include "incl_h.h"
#include "xref.h"
#include "xstruct.h"
#include "xlink.h"
#include "componentcontextmenu.h"

struct XGuiPageCreator;
class XGui;
class QJsonObject;
class XItem;
class ModuleInterface;

//---------------------------------------------------------------------
//Preliminary information for constructing interface element
class XItemPreDescription {
public:
    QString title;
    QString type = "";
    VarQualifier qualifier = VarQualifierIn;
    QString qualifier_options; //опции в квалификаторе, типа out(not_save)
    QString options;        //дополнительные опции, типа choose:file, choose:folder для строк string(choose:file)
    QString line_to_parse;
    QStringList description;    //строки с описанием
};


//---------------------------------------------------------------------
//Hepler - Element creator class
class XItemCreator {
public:
    static XItem *new_item(ModuleInterface *interf, const XItemPreDescription &pre_description);
    static XItem *new_item(ModuleInterface *interf, QString title_underscored, QString type,
                                  const QStringList &description,
                                  VarQualifier qual = VarQualifierIn, QString line_to_parse = "",
                                  QString options = "",
                                  QString qual_options = "");
    //page, group
    static XItem *new_decorate_item(ModuleInterface *interf, QString name, QString type, const QStringList &description);
    //separator
    static XItem *new_separator(ModuleInterface *interf, QString name, QString type = xitem_separator(), bool is_line = false);
};

//---------------------------------------------------------------------
//Module interface component
class XItem {
public:
    //создание невизуальной переменной (или описание элемента интерфейса),
    //и парсинг остатка строки line_to_parse
    XItem(ModuleInterface *interf, const XItemPreDescription &pre_description);
    virtual ~XItem();

    //доступ ко всему интерфейсу
    ModuleInterface *interf() { return interf_; }

    //Имя и тип, а также информация для создания GUI  -------------------------
    QString name();
    QString title();
    QString type();
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
    virtual XProtectedStruct *get_object() { return nullptr; }

    //Запись, считывание и копирование -------------------------
    //хранит ли данные (или просто интерфейсный элемент, например, сепаратор)
    virtual bool store_data() { return true; }

    //копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
    //специальные типы, которые не поддерживают перенос через строку (object) - должны переписать copy_data_to_internal
    void copy_data_to(XItem *item);

    //Запись и считывание json
    void write_json(QJsonObject &json);
    void read_json(const QJsonObject &json);

    //Link -------------------------
    //link to itself
    XLink link_to_itself();

    bool is_link_can_be_used(); //can be link used (for out - no), used for project saving
    bool is_use_link();     //use link
    void set_use_link(bool v);
    QString link();
    void set_link(const QString &link);

    //Expression -------------------------
    bool is_expression_can_be_used(); //требуется ли expression (для out - нет), используется при записи на диск
    bool is_use_expression();  //используется ли expression для установки значения
    void set_use_expression(bool v);
    QString expression();
    void set_expression(const QString &expr);

    //GUI -------------------------
    //графический интерфейс, он тут создается, но хранится отдельно
    virtual XGui *create_gui(XGuiPageCreator &input);

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

    //Belonging to general page, common for all modules
    void set_belongs_general_page(bool v);
    bool belongs_general_page();

    //Context menu ----------------
    //Common setting up of context menu
    //It's filled using custom implementations of context_menu_has_set_default_value() and context_menu_has_set_size()
    ComponentContextMenuInfo context_menu_info();

    //Each component can provide information menu details
    virtual bool context_menu_has_set_default_value() { return false; }
    virtual bool context_menu_has_set_size() { return false; }

    //Processing of context menu actions
    //Subclasses must implement non-common actions and call parent method
    virtual void context_menu_on_action(ComponentContextMenuEnum id, QString action_text);

    //C++ -------------------------
    //function `export_interface` generates function or functions definitions
    //for using inside C++ class module definition
    //----------------------------------------------------
    virtual void export_interface(QStringList &file);
    //Subclasses must reimplement it, in opposite case the exception will arise.
    //export_interface_template() - useful helper for this
    //Note: only items which are not belong to general page, that is belongs_general_page() == false
    //are exported by default


protected:
    //доступ ко всему интерфейсу
    ModuleInterface *interf_ = nullptr;

    //основные характеристики
    QString title_;
    QString name_;
    QString type_;
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

    //Link info
    bool use_link_ = false;
    QString link_;

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
    virtual void copy_data_to_internal(XItem *item);


    //это общее gui__ - хотя в самих представителях будут конкретные представители,
    //нам требуется общий, чтобы передавать сигналы о видимости
    //подклассы должны его устанавливать!
    XGui *gui__ = nullptr; //не нужно его удалять

    //General page marker
    bool belongs_general_page_ = false;

    //Helper for export_interface
    void export_interface_template(QStringList &file,
                                   bool horiz_line,
                                   bool comment_description,
                                   QString custom_comment_begin,

                                   bool getter_setter = false,
                                   QString cpp_type = "",
                                   QString fun_prefix = "",
                                   QString cpp_getter = "",
                                   QString cpp_setter = "",
                                   bool final_blank = true,
                                   bool is_int = false,
                                   bool is_string = false
            );
};

//---------------------------------------------------------------------
//Interface element with value
//allows to use links and protection for multithread access
template<typename T>
class XItem_: public XItem {
public:
    XItem_<T>(ModuleInterface *interf, const XItemPreDescription &pre_description)
        : XItem(interf, pre_description) {
        //by default, set value_ as owner
        value_.own(new XProtectedData_<T>(new T()));

    }

    //Access for read and write value
    //for one-time access of scalars,
    //can use `value_read().data()`, `value_.data()->write().data() = value`
    XProtectedRead_<T> value_read() { return value_.data()->read(); }
    XProtectedWrite_<T> value_write() { return value_.data()->write(); }

protected:
     XRef<XProtectedData_<T>> value_;

};



#endif // INTERFACEITEM_H
