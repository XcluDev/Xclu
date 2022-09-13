#pragma once

//Визуальное представление проекта, и управление списком модулей и редактором

#include <QWidget>
#include "xguieditor.h"
#include "editormodules.h"

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
class QMenu;
QT_END_NAMESPACE

class ProjectGui : public QWidget
{
    Q_OBJECT

public:
    ProjectGui(QWidget *parent, QMenu *modulesMenu);

    //включено ли редактирование
    void set_editable(bool editable);

    //закрытие проекта
    void before_close_project();
    void after_close_project();

    //открытие проекта - выбор модуля
    void after_load_project();
    //пересчитать список модулей из проекта
    void update_module_list();

    //перед сохранением проекта
    void before_save_project();

    //user changed "Show Components Names" checkbox menu item
    void on_changed_show_components_names(bool show);

    //show Links Editor dialog
    void show_links_editor();

protected:
    EditorModules *editor_modules; //Редактор списка модулей проекта
    XGuiEditor *editor_module;  //Редактор параметров

    void properties_from_gui();
    void properties_to_gui();

//Прием сигналов от редакторов, посылает их в Project и затем обратно в редакторы
public slots:
    //сигнал от списка модулей, что изменился выбранный модуль
    //после этого следует загрузить новый модуль в редактор параметров
    void changed_module_selection(int i);

    //сигнал от списка модулей, что выбранный модуль изменился
    //после этого следует обновить этот модуль в редактор параметров
    void selected_module_updated();

    //сигнал от списка модулей, что добавился новый модуль
    void new_module(int i, QString class_name, QString name_hint);

    //сигнал, что модуль переименован
    void rename_module(int i, QString new_name);

    //сигнал, что модуль нужно удалить
    void delete_module(int i);

    //сигнал, что модуль нужно сдублировать
    void duplicate_module(int i);

    //сигнал, что модули нужно поменять местами
    void swap_modules(int i);   //i<->i+1

};

extern ProjectGui *PROJ_GUI;

