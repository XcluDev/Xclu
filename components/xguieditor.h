#ifndef EDITORMODULE_H
#define EDITORMODULE_H

//Редактор параметров
//Он используется в основном окне приложения,
//а также в диалоге теста GUI модуля DialogTestModuleInterface
#include <QWidget>
#include "incl_h.h"
#include "module.h"
#include "xgui.h"

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
class QCheckBox;
class QGridLayout;
QT_END_NAMESPACE


class XGuiEditor : public QWidget
{
    Q_OBJECT

public:
    XGuiEditor(QWidget *parent);

    EditorModuleState state();
    void set_state(EditorModuleState state);

    void before_close_project();
    void after_close_project();

public slots:
    //сигнал, что модуль сменился и нужно загрузить новый модуль
    void changed_module_selection(int i);

    //сброс модуля
    void detach();

    //сигнал, что модуль был переименован
    void renamed_module();

public:
    //used module
    Module *module();

    //загрузить GUI модуля
    void load_module(Module *module);

    //создать GUI только для интерфейса - например, для отладки интерфейсов
    //force_propagate_visibility - нужно ли сделать обновление видимости.
    //для вызовов из load_module(Module *module) - это не нужно, так как там сработает module->gui_action(GuiStageAfterGuiAttached);
    //но для кастомного применения, например, тестирования интерфейса - это нужно
    void load_module(ModuleSeed *info, ModuleInterface *interf, QString module_name, bool force_propagate_visibility = false);

protected:
    void createParams();
    QGroupBox *editor_frame_;
    QLabel *editor_label_;
    QTabWidget *tabs;
    //QGroupBox *paramEditor;

    //модуль, который в данный момент показываем в редакторе
    Module *module_ = nullptr;

    QVector<XGui *> items_; //элементы GUI
    QMap<QString, XGui *> items_by_name_;   //элементы по имени, для установки связей видимости

    void reload_name(); //обновить имя и класс модуля, использует moddule_. Если его нет - скрывает Label

protected slots:
    //Отслеживание изменений, чтобы пометить, что проект был изменен
    //connect(spin_, SIGNAL (valueChanged(double)), this, SLOT (on_value_changed()));
    void on_value_changed();

protected:
    //context popup menu
    QScopedPointer<QMenu> context_menu_;
};


#endif // EDITORMODULE_H
