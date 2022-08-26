#ifndef EDITORMODULES_H
#define EDITORMODULES_H

//Редактор списка модулей в проекте
#include <QWidget>
#include "xmodule.h"

QT_BEGIN_NAMESPACE
class QAction;
class QToolBar;
class QGroupBox;
class QLabel;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QListWidget;
class QTabWidget;
class QListWidgetItem;
class QMenu;
QT_END_NAMESPACE


class EditorModules : public QWidget
{
    Q_OBJECT

public:
    EditorModules(QWidget *parent, QMenu *modulesMenu);

    //включено ли редактирование
    void set_editable(bool editable);

    //закрытие проекта
    void before_close_project();
    void after_close_project();

    //пересчитать список модулей из проекта
    void update_module_list();

    //номер выбранного модуля
    int current_index();
    int modules_count();

private:
    void emit_selection_changed();  //послать сигнал, что текущий модуль был изменен

    void set_state();

    //Список с именами модулей
    QListWidget *moduleListWidget;
    //Кнопки для управления модулями
    QToolBar *toolBar;
    QAction *addAction;
    QAction *renameAction;
    QAction *duplicateAction;
    QAction *deleteAction;
    QAction *upAction;
    QAction *downAction;
protected:
    void new_action(QAction *&action, QString title, QString icon_file, QMenu *modulesMenu);

//Нажатия на кнопки - они сами список не изменяют, а отправляют запрос в Project
private slots:
    void module_selected();
    void module_double_clicked(QListWidgetItem *item);

    void add_module_click();
    void rename_module_click();
    void duplicate_module_click();
    void delete_module_click();
    void up_module_click();
    void down_module_click();

//Внешние команды
public slots:
    //выбрать модуль и загрузить для него параметры
    void select_item(int i);

    //возвратная команда, что модуль был вставлен,
    //и осуществляется фактическая вставка в список
    void inserted_module(int i, QString name);

    //сигнал, что модуль был переименован
    void renamed_module(int i, QString name);

    //сигнал, что модуль был удален
    void deleted_module(int i);

    //сигнал, что модули были поменяны местами
    void swapped_modules(int i);

protected:
    bool editable_ = true;
    void update_buttons();


};

#endif // EDITORMODULES_H
