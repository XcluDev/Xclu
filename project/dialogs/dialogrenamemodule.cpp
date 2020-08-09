#include <QtWidgets>

#include "dialogrenamemodule.h"
#include "project.h"

DialogRenameModule *D_RENAME_MODULE;

//---------------------------------------------------------------------
//делает все операции и изменяет name, если success
/*static*/ bool DialogRenameModule::call_dialog(QString &name, QWidget *parent) {
    //Внимание, тут parent только один раз задается
    if (!D_RENAME_MODULE) {
        D_RENAME_MODULE = new DialogRenameModule(parent);
    }
    auto *dialog = D_RENAME_MODULE;
    dialog->set_name(name);
    int result = dialog->exec();
    if (result == QDialog::Accepted) {
        name = dialog->get_name();
        return true;
    }
    return false;
}

//---------------------------------------------------------------------
DialogRenameModule::DialogRenameModule(QWidget *parent)
    : QDialog(parent)
{
    QLabel *label = new QLabel(tr("Module Name:"));

    lineEdit = new QLineEdit("");
    lineEdit->setMinimumWidth(250);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                  | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &DialogRenameModule::pressed_ok);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    //сборка диалога
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(label, 0, 0);
    mainLayout->addWidget(lineEdit, 0, 1);
    mainLayout->addWidget(buttonBox, 2, 0, 1, 2);
    setLayout(mainLayout);

    //Заголовок
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("Rename Module"));

    lineEdit->setFocus();
}

//---------------------------------------------------------------------
void DialogRenameModule::set_name(QString name) {
    lineEdit->setText(name);
    name_ = name;
}

//---------------------------------------------------------------------
QString DialogRenameModule::get_name() {
    return lineEdit->text();
}

//---------------------------------------------------------------------
void DialogRenameModule::pressed_ok() {
    //закрываем диалог, если PROJ разрешает такое переименование
    if (PROJ.can_rename_module(name_,get_name())) {
        emit accept();
    }
}

//---------------------------------------------------------------------
