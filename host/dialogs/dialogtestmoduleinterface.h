#ifndef DIALOGTESTMODULEINTERFACE_H
#define DIALOGTESTMODULEINTERFACE_H

//Диалог тестирования XGUI создаваемых модулей
#include <QDialog>
#include <QScopedPointer>
QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QPlainTextEdit;
class QTabWidget;
class QTableWidget;
class QListWidget;
QT_END_NAMESPACE
#include "moduleseed.h"
#include "moduleinterface.h"

class EditorModule;


class DialogTestModuleInterface : public QDialog
{
    Q_OBJECT

public:
    //Вызывайте эту функцию для работы с диалогом,
    //если не nullptr - то диалог успешен и можно брать значения из него
    static void call_dialog(QWidget *parent);

    DialogTestModuleInterface(QWidget *parent);

private slots:
    void pressed_load();
    void pressed_reload();
    void pressed_export_h();

private:
    QPlainTextEdit *folder_edit_;

    EditorModule *editor_;
    QString folder_;


    void load_module(QString folder, int tab_index = 0);
    void reload(int tab_index);


    QScopedPointer<ModuleSeed> module_seed_;
    QScopedPointer<ModuleInterface> interf_;

    void clear();

};



#endif // DIALOGTESTMODULEINTERFACE_H
