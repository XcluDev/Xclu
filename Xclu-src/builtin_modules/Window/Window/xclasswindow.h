#pragma once

//Реализация модуля Window - окно на экране

#include <QObject>
#include <QMainWindow>
#include <QStack>

#include "sdk_h.h"
#include "xclass.h"
#include "xprotecteddata.h"
#include "xparse_tree.h"

class QLayout;
class QTabWidget;
class QWidget;
class QSpacerItem;


//Структура для создания layouts
struct XClassWindowStructureItem {
    XClassWindowStructureItem();
    XClassWindowStructureItem(QWidget* widget, int stretch = 0);
    XClassWindowStructureItem(QLayout *layout, int stretch = 0);
    XClassWindowStructureItem(QWidget* widget, QString tab_title);
    XClassWindowStructureItem(int stretch);

    virtual ~XClassWindowStructureItem();

    QWidget *take_widget();         //забрать указатель и тут его выставит в nullptr - чтобы деструктор не удалил widget

    void add_to_layout(QLayout *layout);    //вставить в layout
    void add_to_tabs(QTabWidget *tabs);     //вставить в Tabs - должно быть имя страницы

    QWidget *widget = nullptr;
    int stretch = 0;

    bool is_stretch = false;    //тип Stretch
    bool is_tab = false;        //тип Tab
    QString tab_title;          //имя страницы для Tab

};


//Модуль
class XClassWindow: public XClass
{
    Q_OBJECT
public:
    XClassWindow(QString class_name);
    virtual ~XClassWindow();
protected:
    //Выполнение
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    //Вызовы
    //virtual void on_custom_call(QString function, XObject *input, XObject * /*output*/);
protected:
#include "auto.h"

    QScopedPointer<QMainWindow> window_;

    //создание и установка начальных настроек окна
    void setup_window();

    //прочитать данные из интерфейса и использовать для управления окном
    //он использует was_changed - поэтому, при старте всегда эти значения будут использованы (при старте все переменные was_changed)
    void update_window();

    void set_size(int w, int h);

    void set_position(int x, int y);

    //получить экран в зависимости от настроек
    QScreen *get_screen();

protected slots:

    //сигнал на изменение состояния окна
    void on_windowStateChanged(Qt::WindowState windowState);
    void on_visibleChanged(bool arg);

protected:
    bool notify_visible_change_ = false;    //нотификация, что изменилось visibility окна
                                            //TODO по-хорошему, надо сделать с mutex, но делаем просто так )
    bool need_apply_initial_state_ = false;

    void create_layouts();  //создать структуру окна - при этом, запрашиваются виджеты из соответствующих модулей

    //типы узлов дерева структуры
    enum StructureItemType : int {
        TypeNone = 0,
        TypeLayout = 1,
        TypeTabs = 2,
        TypeTab = 3,
        TypeWidget = 4
    };

    //Рекурсивное создание структуры окна
    //При реализации я старался сделать здесь безопасным при exceptions и исключить утечки памяти
    //для этого старался использовать QScopedPointer и забирать его указатели с помощью take в безопасные моменты
    XClassWindowStructureItem create_layouts_internal(const XcluParseTree &tree, int index);

    //парсить число, если оно есть, иначе - выдать default_value
    int xparse_int(QStringList list, int index, int default_value, QString line);

    //modules list which are involved in widgets creation
    //it's collected by request_widget and cleared at stop
    QStringList used_modules_;

    //запрос виджета из другого модуля
    //важно, что модуль создает виджет и нам просто ссылку передает, и мы должны сами ее удалить
    //- например, путем установки его в наши layouts и виджеты
    QWidget *request_widget(QString module_name);

    //remove all requested widgets stored at used_modules_
    void reset_widgets();

    //remove requested widget from another module - called at stopping
    void reset_widget(QString module_name);

protected:
    //Capture window
    void capture_window();
    XRaster capture_holder_;
};

