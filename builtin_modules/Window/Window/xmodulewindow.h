#ifndef RTMODULEWINDOW_H
#define RTMODULEWINDOW_H

//Реализация модуля Window - окно на экране

#include <QObject>
#include <QMainWindow>
#include <QStack>

#include "sdk_h.h"
#include "xmodule.h"
#include "xcluprotecteddata.h"
#include "xclu_parse_tree.h"

class QLayout;
class QTabWidget;
class QWidget;
class QSpacerItem;


//Структура для создания layouts
struct XModuleWindowStructureItem {
    XModuleWindowStructureItem();
    XModuleWindowStructureItem(QWidget* widget, int stretch = 0);
    XModuleWindowStructureItem(QLayout *layout, int stretch = 0);
    XModuleWindowStructureItem(QWidget* widget, QString tab_title);
    XModuleWindowStructureItem(int stretch);

    ~XModuleWindowStructureItem();

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
class XModuleWindow: public XModule
{
    Q_OBJECT
public:
    XModuleWindow(QString class_name);
    ~XModuleWindow();
protected:
    //Выполнение
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();

    //Вызовы
    virtual void impl_call(QString function, XObject *input, XObject * /*output*/);
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
    XModuleWindowStructureItem create_layouts_internal(const XcluParseTree &tree, int index);

    //парсить число, если оно есть, иначе - выдать default_value
    int parse_int(QStringList list, int index, int default_value, QString line);

    //запрос виджета из другого модуля
    //важно, что модуль создает виджет и нам просто ссылку передает, и мы должны сами ее удалить
    //- например, путем установки его в наши layouts и виджеты
    QWidget *request_widget(QString module_name);
};


#endif // RTMODULEWINDOW_H
