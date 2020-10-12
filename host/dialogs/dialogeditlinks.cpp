#include "dialogeditlinks.h"
#include "ui_dialogeditlinks.h"
#include "mainwindow.h"
#include "module.h"
#include "moduleinterface.h"
#include "xitem.h"
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
    xclu_assert(module, "DialogEditLinks::set_module - passed module==nullptr");
    module_ = module;
    ui->module_name->setText(module_->name());

    //Create list for edit
    QStringList list;
    list.append("##... means comment, #... means disabled link");
    auto &items = module_->interf()->items();
    QString page;
    for (auto item: items) {
        //prepare print page name if it has some links as comment
        if (item->type() == xitem_page()) {
            page = item->title();
        }
        if (!item->link().isEmpty()) {
            QString link = item->name() + " = " + item->link();
            if (!item->is_linked()) {
                link = "#" + link;
            }
            //check if there is unprinted page name
            if (!page.isEmpty()) {
                list.append(QString("##     Page %1").arg(page));
                list.append("");
                page = "";
            }
            //now append item
            list.append(link);
        }
    }
    ui->editor->setPlainText(list.join("\n"));
}

//---------------------------------------------------------------------
void DialogEditLinks::on_buttonBox_accepted()
{
    //at first, clear all links
    auto items = module_->interf()->items();
    for (auto item: items) {
        if (!item->is_link_empty()) {
            item->clear_link();
        }
    }

    //now fill user links
    QStringList list = ui->editor->toPlainText().split("\n");
    //xclu_console_append(QString("lines: %1").arg(list.size()));

    for (auto &line0: list) {
        QString line = line0.trimmed();
        if (line.isEmpty() || line.left(2) == "##") {
            continue;
        }
        //parsing:
        //var = module->var or
        //#var = module->var
        line.remove(' ');
        line.remove('\t');
        QStringList items = line.split("=");
        if (items.size() != 2) {
            xclu_console_append("Error at `" + line + "`, expected item=name");
            continue;
        }
        QString var = items.at(0);
        QString link = items.at(1);
        if (var.isEmpty()) {
            xclu_console_append("Error at `" + line + "`, empty item name");
            continue;
        }
        bool enabled = true;
        if (var.left(1) == "#") {
            enabled = false;
            var.remove(0,1);
        }
        if (!module_->interf()->has_item(var)) {
            xclu_console_append("Error at `" + line + "`, unknown item");
            continue;
        }
        XItem *item = module_->interf()->var(var);
        item->set_link_and_linked(link, enabled);
    }

}

//---------------------------------------------------------------------
