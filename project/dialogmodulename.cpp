#include "dialogmodulename.h"
#include "ui_dialogmodulename.h"

DialogModuleName *D_MODULE_NAME = 0;

//---------------------------------------------------------------------
//Вызывайте эту функцию для работы с диалогом,
//если не nullptr - то диалог успешен и можно брать значения из него
/*static*/ DialogModuleName* DialogModuleName::call_dialog(QWidget *parent, QString name_hint) {
    //Внимание, тут parent только один раз задается
    if (!D_MODULE_NAME) {
        D_MODULE_NAME = new DialogModuleName(parent);
    }
    auto *dialog = D_MODULE_NAME;

    dialog->set_name_hint(name_hint);
    int result = dialog->exec();
    if (result == QDialog::Accepted) {
        return dialog;
    }

    return nullptr;
}

//---------------------------------------------------------------------
DialogModuleName::DialogModuleName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogModuleName)
{
    ui->setupUi(this);
}

//---------------------------------------------------------------------
DialogModuleName::~DialogModuleName()
{
    delete ui;
}

//---------------------------------------------------------------------
void DialogModuleName::set_name_hint(QString name_hint) {
    ui->lineEdit->setText(name_hint);
}

//---------------------------------------------------------------------
QString DialogModuleName::name_hint() {
    return ui->lineEdit->text();
}

//---------------------------------------------------------------------
