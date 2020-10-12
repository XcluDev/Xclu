#ifndef INTERFACEITEMGUI_H
#define INTERFACEITEMGUI_H

//Графический интерфейс для показа или редактирования переменной.
//Он создает класс, который способен генерировать GUI объект по запросу.
/*
Константы без expression: ставятся из GUI при start.
Константы с expression: вычисляются при start.
Входные без expression: ставятся из GUI перед update.
Входные с expression: они вычисляются перед каждым update и ставятся в GUI.
Выходные: модуль их вычисляет, и ставятся в GUI после update.
*/

#include <QWidget>
#include "sdk_h.h"

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QVBoxLayout;
class QHBoxLayout;
class QListWidget;
class QTabWidget;
class QListWidgetItem;
class QGridLayout;
class QMenu;
QT_END_NAMESPACE

class XItem;
class VisibilityGroupGui;
//class XcluClickableLabel;

//Settings for created GUI
struct XGuiSettings {
    bool show_names = false;
};

//данные для создания визуального интерфейса
struct XGuiPageCreator {
    QWidget *parent = nullptr;
    QTabWidget *tabs = nullptr;     //сюда добавляются страницы
    QGridLayout *grid = nullptr;    //страницы создают новый, а остальные добавляются в него
    int y = 0;                      //положение в сетке

    XGuiSettings settings;
};

//Один элемент визуального интерфейса
class XGui : public QWidget
{
    Q_OBJECT
public:
    //item - не следует удалять
    XGui(XGuiPageCreator &input, XItem *item);
    virtual ~XGui();

    //Функции для блокировки и разблокировки редактирования констант при запуске проекта.
    void block_editing_on_running(); //блокирование изменения констант, вызывается перед запуском проекта
    void unblock_editing_on_stopping(); //разблокирование изменения констант, вызывается после остановки проекта

    //Работа с видимостью
    //функция виртуальная - так как, например, у сепаратора нужно делать специальным образом
    virtual void set_visible(bool visible);
    //Если требуется - добавить группу видимости
    //групп может быть несколько, их нужно в деструкторе удалить
    void add_visibility_group(VisibilityGroupGui *created_group);

    //значение для проверки видимости детей
    //подклассы должны реализовать ее для участия в условиях видимости
    virtual QString value_string_for_visibility() { return ""; };

    //сигнал послать данные об изменении видимости - высылается после первой установки значения в переменную
    void propagate_visibility();

    //User change link settings - should show it in GUI
    virtual void link_was_changed();

    bool is_read_only() { return current_read_only_; }

    //Change show components names
    void set_show_components_names(bool show);
protected:
    //Ссылка на невизуальный элемент интерфейса (который и представляется данным GUI-элементом)
    XItem *item__ = nullptr;

    //Settings
    XGuiSettings settings_;

    //This function controls "read only" and link properties
    //It should be called when changed read_only and link
    void update_view();

    //нужно ли константы делать bold (false для text)
    virtual bool is_const_bold() { return true; }

    //Is running - so need to set "read only" for constants
    bool running_blocked() { return running_blocked_; }
    bool running_blocked_ = false;

    //Common function which controls setting "read only" mode.
    //It calls `set_read_only_` virtual function, thish is specific for components
    //This function is called for `out` variables, for `const` after running, for `linked` variables when set.
    //The `in` and `const` can be set to `linked` and back.
    void set_read_only(bool read_only);
    bool current_read_only_ = false;    //current state of "read only"
    bool current_is_linked_ = false;

    //Internal function, which can be reimplemented for components
    virtual void set_read_only_(bool read_only);

protected:
    //Tip control

    //строка-подсказка, может быть разных типов - см. Tip_Style
    QString get_tip();

    //тип подсказки - подклассы могут менять get_tip_style, чтобы установить свой тип
    //например, page использует только описание
    enum Tip_Style: int {
        Tip_Full = 0,       //'name - description'
        Tip_Description = 1 //'decription'
    };

    virtual Tip_Style get_tip_style() { return Tip_Full; }

protected:
    //Визуальные элементы
    //Динамический интерфейс - группы видимости
    QVector<VisibilityGroupGui *> vis_groups_;

    //метка - используется при регуляции visible и блокировке константы
    QLabel *label_ = nullptr;       //не надо удалять
    QColor default_label_color_;    //исходный цвет метки - используется, чтобы восстановить исходный цвет после gray

    void update_label_link();       //set label link
    QLabel *label_link_ = nullptr;  //label for link

    //виджет - используется для регуляции visible
    QWidget *widget_ = nullptr; //не надо удалять
    QWidget *internal_widget_ = nullptr;    //виджет для установки read_only

    //создать label
    void insert_label(XGuiPageCreator &input);

    //вставить на страницу созданный виджет
    void insert_widget(QWidget *widget, QWidget *internal_widget, XGuiPageCreator &input,
                       int pos_x = 1, int shift_y = 0, int spanx=1, int spany=1);

    //вставить с новой строки (то есть label будет сверху, а этот widget на всю строку)
    void insert_widget_next_line(QWidget *widget, QWidget *internal_widget, XGuiPageCreator &input);

    //вставить виджет со спейсером справа, чтобы когда нет широких элементов, он не уезжал вправо
    //(int, float, checkbox, object)
    void insert_widget_with_spacer(QWidget *widget, QWidget *internal_widget, XGuiPageCreator &input,
                                   int pos_x = 1, int shift_y = 0, int spanx=1, int spany=1);
    void insert_widget_with_spacer_next_line(QWidget *widget, QWidget *internal_widget, XGuiPageCreator &input);


    //запомнить уже вставленный widget и установить оформление в зависимости от квалификаторов
    //также, вызывается из insert_widget и insert_widget_with_spacer
    void set_widget(QWidget *widget, QWidget *internal_widget);

    //set "GuiEditorPage" for QWidget in order QSS set its background darker
    void atribute_as_GuiEditorPage(QWidget *widget);

protected slots:
    //Отслеживание изменений
    //Подклассы должны его вызывать, чтобы пометить, что проект был изменен, вот так:
    //connect(spin_, SIGNAL (valueChanged(double)), this, SLOT (on_value_changed()));
    //также, они могут переопределять их для собственных целей, но обязательно вызывать этот базовый метод
    virtual void on_value_changed();

//Context menu
protected slots:
    //show popup menu
    void customMenuRequested(QPoint pos);    

    //Show "Edit link" dialog when right-clicked link
    void on_label_link_right_click(QPoint pos);

public slots:
    //signal from popup menu, action->data().toInt() is ComponentContextMenuEnum
    void on_component_popup_action();

    //Show "Edit link" dialog when clicked link
    //void on_label_link_clicked();

};

#endif // INTERFACEITEMGUI_H
