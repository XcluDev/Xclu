#include "dialogeditlink.h"
#include "ui_dialogeditlink.h"
#include "mainwindow.h"

DialogEditLink *D_EDIT_LINK = 0;

//---------------------------------------------------------------------
//Вызывайте эту функцию для работы с диалогом,
//если не nullptr - то диалог успешен и можно брать значения из него
/*static*/ DialogEditLink* DialogEditLink::call_dialog(const DialogEditLinkData &data) {
    auto parent = MainWindow::window();

    if (!D_EDIT_LINK) {
        D_EDIT_LINK = new DialogEditLink(parent);
    }
    auto *dialog = D_EDIT_LINK;

    dialog->set_data(data);

    //TODO now edit link dialog blocks execution, it should be done async.
    int result = dialog->exec();
    if (result == QDialog::Accepted) {
        return dialog;
    }

    return nullptr;
}

//---------------------------------------------------------------------
DialogEditLink::DialogEditLink(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditLink)
{
    ui->setupUi(this);
}

//---------------------------------------------------------------------
DialogEditLink::~DialogEditLink()
{
    delete ui;
}

//---------------------------------------------------------------------
void DialogEditLink::set_data(const DialogEditLinkData &data) {
    ui->module_name->setText(data.module_name);
    ui->component_name->setText(data.item_name);
    ui->link->setText(data.link);
    ui->link_enabled->setChecked(data.link_enabled);
}

//---------------------------------------------------------------------
bool DialogEditLink::link_enabled() {
    return ui->link_enabled->isChecked();
}

//---------------------------------------------------------------------
QString DialogEditLink::link() {
    return ui->link->text();
}

//---------------------------------------------------------------------
