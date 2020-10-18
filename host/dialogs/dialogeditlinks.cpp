#include "dialogeditlinks.h"
#include "ui_dialogeditlinks.h"
#include "mainwindow.h"
#include "module.h"
#include "moduleinterface.h"
#include "xitem.h"
#include "incl_cpp.h"
#include "consoleview.h"

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
        auto &item_link = item->link();
        if (!item_link.link.isEmpty()) {
            QString link = item->name() + " = " + item_link.link;
            if (!item_link.enabled) {
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
DialogEditLinks::Links DialogEditLinks::get_list() {
    Links result;
    result.ok = true;

    QStringList list = ui->editor->toPlainText().split("\n");

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
            result.ok = false;
            continue;
        }
        QString var = items.at(0);
        QString link = items.at(1);
        if (var.isEmpty()) {
            xclu_console_append("Error at `" + line + "`, empty item name");
            result.ok = false;
            continue;
        }
        bool enabled = true;
        if (var.left(1) == "#") {
            enabled = false;
            var.remove(0,1);
        }
        if (!module_->interf()->has_item(var)) {
            xclu_console_append("Error at `" + line + "`, unknown item");
            result.ok = false;
            continue;
        }
        result.links.append(XLink(enabled, link));
        result.vars.append(var);
        //XItem *item = module_->interf()->var(var);
        //item->set_link(enabled, link);
    }

    return result;
}


//---------------------------------------------------------------------
void DialogEditLinks::on_button_check_links_clicked()
{
    Links links = DialogEditLinks::get_list();
    if (!links.ok) {
        xclu_message_box("There are error(s) in links format");
    }
    else {
        //check resolving links
        bool ok = true;
        for (int i=0; i<links.links.size(); i++) {
            auto &link = links.links[i];
            if (link.enabled) {
                XLinkResolved::CheckLinkResult checking = XLinkResolved::check_link(link.link);
                if (!checking.ok) {
                    xclu_console_append(QString("Error at link `%1`: %2")
                                        .arg(links.vars[i])
                                        .arg(checking.error));
                    ok = false;
                }
            }
        }
        if (ok) {
            xclu_console_append("Links are correct");
            xclu_message_box("Links are correct");
        }
        else {
            xclu_console_append("There are error(s) in links");
            xclu_message_box("There are error(s) in links, see Console");
        }
    }
}

//---------------------------------------------------------------------
void DialogEditLinks::on_button_ok_clicked()
{
    Links links = DialogEditLinks::get_list();
    if (!links.ok) {
        xclu_message_box("There are error(s) in links format");
        return;
    }

    //at first, clear all links
    auto items = module_->interf()->items();
    for (auto item: items) {
        if (!item->link().is_empty()) {
            item->clear_link();
        }
    }

    for (int i=0; i<links.links.size(); i++) {
        auto &var = links.vars[i];
        auto &link = links.links[i];
        XItem *item = module_->interf()->var(var);
        item->set_link(link);
    }

    accept();
}

//---------------------------------------------------------------------
void DialogEditLinks::on_button_cancel_clicked()
{
    reject();
}

//---------------------------------------------------------------------
