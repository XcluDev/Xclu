#include "dialogeditlinks.h"
#include "ui_dialogeditlinks.h"
#include "mainwindow.h"
#include "module.h"
#include "moduleinterface.h"
#include "incl_cpp.h"

DialogEditLinks *D_EDIT_LINKS = 0;

//---------------------------------------------------------------------
//Call this function for working with dialog
//if returns not nullptr - then success and you can use dialog's value
/*static*/ void DialogEditLinks::call_dialog(Module *module) {
    auto parent = MainWindow::window();

    if (!D_EDIT_LINKS) {
        D_EDIT_LINKS = new DialogEditLinks(parent);
    }
    auto *dialog = D_EDIT_LINKS;

    dialog->set_module(module);

    dialog->open();
}

//---------------------------------------------------------------------
DialogEditLinks::DialogEditLinks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditLinks)
{
    ui->setupUi(this);
}

//---------------------------------------------------------------------
DialogEditLinks::~DialogEditLinks()
{
    delete ui;
}

//---------------------------------------------------------------------
void DialogEditLinks::set_module(Module *module) {
    module_ = module;
}

//---------------------------------------------------------------------
void DialogEditLinks::on_buttonBox_accepted()
{
    xclu_console_append("Accepted");
}

//---------------------------------------------------------------------
