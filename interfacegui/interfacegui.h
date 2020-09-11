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
#include "incl_h.h"
#include <QScopedPointer>

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

//данные для создания визуального интерфейса
struct InterfaceGuiPageCreator {
    QWidget *parent = nullptr;
    QTabWidget *tabs = nullptr;     //сюда добавляются страницы
    QGridLayout *grid = nullptr;    //страницы создают новый, а остальные добавляются в него
    int y = 0;                      //положение в сетке
};

//Один элемент визуального интерфейса
class InterfaceGui : public QWidget
{
    Q_OBJECT
public:
    //item - не следует удалять
    InterfaceGui(InterfaceGuiPageCreator &input, XItem *item);
    virtual ~InterfaceGui();

    //Функции для блокировки и разблокировки редактирования констант при запуске проекта.
    void block_editing(); //блокирование изменения констант, вызывается перед запуском проекта
    void unblock_editing(); //разблокирование изменения констант, вызывается после остановки проекта

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

protected:
    //Ссылка на невизуальный элемент интерфейса (который и представляется данным GUI-элементом)
    XItem *item__ = nullptr;


    //Визуальные элементы
    //Динамический интерфейс - группы видимости
    QVector<VisibilityGroupGui *> vis_groups_;

    //метка - используется при регуляции visible и блокировке константы
    QLabel *label_ = nullptr;   //не надо удалять
    QColor default_label_color_;    //исходный цвет метки - используется, чтобы восстановить исходный цвет после gray

    //виджет - используется для регуляции visible
    QWidget *widget_ = nullptr; //не надо удалять
    QWidget *internal_widget_ = nullptr;    //виджет для установки фона при read_only
    QBrush default_internal_widget_brush_;  //кисть фона виджета - используется при переключении

    //Свойства для разных ситуаций
    //заблокирован ли ввод
    bool blocked() { return blocked_; }
    bool blocked_ = false;

    //константы делать bold (false для text)
    virtual bool is_const_bold() { return true; }

    //виртуальная функция, которую подклассы должны переопределить, чтобы разрешать или запрещать редактирование4
    //конкретно эта функция, реализованная по умолчанию - ставит фон в widget_
    virtual void set_read_only(bool read_only);

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
    //Члены и функции для создания страницы

    //создать label
    void insert_label(InterfaceGuiPageCreator &input);

    //вставить на страницу созданный виджет
    void insert_widget(QWidget *widget, QWidget *internal_widget, InterfaceGuiPageCreator &input,
                       int pos_x = 1, int shift_y = 0, int spanx=1, int spany=1);

    //вставить с новой строки (то есть label будет сверху, а этот widget на всю строку)
    void insert_widget_next_line(QWidget *widget, QWidget *internal_widget, InterfaceGuiPageCreator &input);

    //вставить виджет со спейсером справа, чтобы когда нет широких элементов, он не уезжал вправо
    //(int, float, checkbox, object)
    void insert_widget_with_spacer(QWidget *widget, QWidget *internal_widget, InterfaceGuiPageCreator &input,
                                   int pos_x = 1, int shift_y = 0, int spanx=1, int spany=1);
    void insert_widget_with_spacer_next_line(QWidget *widget, QWidget *internal_widget, InterfaceGuiPageCreator &input);


    //запомнить уже вставленный widget и установить оформление в зависимости от квалификаторов
    //также, вызывается из insert_widget и insert_widget_with_spacer
    void set_widget(QWidget *widget, QWidget *internal_widget);

protected slots:
    //Отслеживание изменений
    //Подклассы должны его вызывать, чтобы пометить, что проект был изменен, вот так:
    //connect(spin_, SIGNAL (valueChanged(double)), this, SLOT (on_value_changed()));
    //также, они могут переопределять их для собственных целей, но обязательно вызывать этот базовый метод
    virtual void on_value_changed();

    void customMenuRequested(QPoint pos);
protected:
    QScopedPointer<QMenu> context_menu_;
};

#endif // INTERFACEITEMGUI_H
