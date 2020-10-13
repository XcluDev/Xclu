#include "dialogeditlink.h"
#include "ui_dialogeditlink.h"
#include "mainwindow.h"
#include "xitem.h"

DialogEditLink *D_EDIT_LINK = 0;

//---------------------------------------------------------------------
//Call this function for working with dialog
//if returns not nullptr - then success and you can use dialog's value
/*static*/ void DialogEditLink::call_dialog(const DialogEditLinkData &data) {
    auto parent = MainWindow::window();

    if (!D_EDIT_LINK) {
        D_EDIT_LINK = new DialogEditLink(parent);
    }
    auto *dialog = D_EDIT_LINK;

    dialog->set_data(data);

    dialog->open();
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
    item_ = data.item;
    ui->module_name->setText(data.module_name);
    ui->component_name->setText(item_->name());
    ui->link->setText(item_->link().link);
    ui->link_enabled->setChecked(item_->link().enabled);
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
void DialogEditLink::on_buttonBox_accepted()
{
    item_->set_link(ui->link_enabled->isChecked(), ui->link->text());
}

//---------------------------------------------------------------------
