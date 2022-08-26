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
#include "xmoduleprototype.h"
#include "xmoduleinterface.h"

class XGuiEditor;


class DialogTestModuleInterface : public QDialog
{
    Q_OBJECT

public:
    //Call this function for working with dialog
    //if returns not nullptr - then success and you can use dialog's value
    static void call_dialog(QWidget *parent);

    DialogTestModuleInterface(QWidget *parent);

private slots:
    void pressed_load();
    void pressed_reload();
    void pressed_export_h();

private:
    QPlainTextEdit *folder_edit_;

    XGuiEditor *editor_;
    QString folder_;


    void load_module(QString folder, int tab_index = 0);
    void reload(int tab_index);


    QScopedPointer<XModulePrototype> module_seed_;
    QScopedPointer<XModuleInterface> interf_;

    void clear();

};



#endif // DIALOGTESTMODULEINTERFACE_H
