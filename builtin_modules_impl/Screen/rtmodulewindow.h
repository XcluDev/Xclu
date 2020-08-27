#ifndef RTMODULEWINDOW_H
#define RTMODULEWINDOW_H

//Реализация модуля Window - окно на экране

#include <QObject>
#include <QScopedPointer>
#include <QMutex>
#include <QMainWindow>
#include <QStack>

#include "incl_h.h"
#include "rtmodule.h"
#include "xcluprotecteddata.h"
#include "xclu_parse_tree.h"

class QLayout;
class QTabWidget;
class QWidget;
class QSpacerItem;


//Структура для создания layouts
struct RtModuleWindowStructureItem {
    RtModuleWindowStructureItem();
    RtModuleWindowStructureItem(QWidget* widget, int stretch = 0);
    RtModuleWindowStructureItem(QLayout *layout, int stretch = 0);
    RtModuleWindowStructureItem(QWidget* widget, QString tab_title);
    RtModuleWindowStructureItem(int stretch);

    ~RtModuleWindowStructureItem();

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
class RtModuleWindow: public RtModule
{
    Q_OBJECT
public:
    RtModuleWindow();
    ~RtModuleWindow();

    static QString *static_class_name_ptr; //"Window", эта переменная используется для создания новых объектов
    static RtModuleWindow *new_module();

protected:
    //Выполнение
    virtual void execute_loaded_internal() {}
    virtual void execute_start_internal();
    virtual void execute_update_internal();
    virtual void execute_stop_internal();

    //Вызовы
    virtual void call_internal(QString function, XcluObject *input, XcluObject * /*output*/);
protected:
    QScopedPointer<QMainWindow> window_;

    //создание и установка начальных настроек окна
    void setup_window();

    //прочитать данные из интерфейса и использовать для управления окном
    //он использует was_changed - поэтому, при старте всегда эти значения будут использованы (при старте все переменные was_changed)
    void update_window();

    enum WindowSize : int {
        WindowSize_Default = 0,
        WindowSize_Custom = 1,
        WindowSize_640x480 = 2,
        WindowSize_800x600 = 3,
        WindowSize_1024x768 = 4,
        WindowSize_1280x720 = 5,
        WindowSize_1920x1080 = 6,
        WindowSize_1920x1200 = 7,
        WindowSize_N = 8
    };
    void set_size(int w, int h);

    enum WindowPos : int {
        WindowPos_Default = 0,
        WindowPos_Custom = 1,
        WindowPos_ScreenCenter = 2,
        WindowPos_N = 3
    };
    void set_position(int x, int y);

    //enum WindowScreen : int {
    //    WindowScreen_Default = 0,
    //    WindowScreen_Custom = 1,
    //    WindowScreen_N = 2
    //};
    //получить экран в зависимости от настроек
    QScreen *get_screen();

    enum WindowMode : int {
        WindowMode_Minimized = 0,
        WindowMode_Normal_Window = 1,
        WindowMode_Maximized = 2,
        WindowMode_Full_Screen = 3,
        WindowMode_N = 4
    };

    enum OnCloseAction : int {
        OnCloseAction_Ignore = 0,
        OnCloseAction_Stop = 1,
        OnCloseAction_N = 2
    };

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
    RtModuleWindowStructureItem create_layouts_internal(const XcluParseTree &tree, int index);

    //парсить число, если оно есть, иначе - выдать default_value
    int parse_int(QStringList list, int index, int default_value, QString line);

    //запрос виджета из другого модуля
    //важно, что модуль создает виджет и нам просто ссылку передает, и мы должны сами ее удалить
    //- например, путем установки его в наши layouts и виджеты
    QWidget *request_widget(QString module_id);
};


#endif // RTMODULEWINDOW_H
