#include "dialogeditui.h"
#include "ui_dialogeditui.h"

DialogEditUI *D_EDITUI = nullptr;

//---------------------------------------------------------------------
/*static*/ void DialogEditUI::call_dialog(QWidget *parent) {
    //Внимание, тут parent только один раз задается
    if (!D_EDITUI) {
        D_EDITUI = new DialogEditUI(parent);
    }
    auto *dialog = D_EDITUI;
    dialog->exec();
}

//---------------------------------------------------------------------
DialogEditUI::DialogEditUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditUI)
{
    ui->setupUi(this);
}

//---------------------------------------------------------------------
DialogEditUI::~DialogEditUI()
{
    delete ui;
}

//---------------------------------------------------------------------
