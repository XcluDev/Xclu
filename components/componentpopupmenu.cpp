#include <QWidget>
#include <QMenu>
#include <QAction>
#include "incl_cpp.h"
#include "componentpopupmenu.h"
#include "xgui.h"

ComponentPopupMenu *COMPONENT_POPUP;

//---------------------------------------------------------------------
/*static*/ ComponentPopupMenu *ComponentPopupMenu::COMP_MENU() {
    if (!COMPONENT_POPUP) {
        COMPONENT_POPUP = new ComponentPopupMenu();
    }
    return COMPONENT_POPUP;
}

//---------------------------------------------------------------------
/*
    Edit Link...
    Link Enabled
    Copy Link
    Paste Link
    Reset to default value (for scalars)
    Set size... (for images and other rich elements)
*/

void ComponentPopupMenu::setup(const ComponentPopupMenuInfo &info) {
    items_.clear();
    if (info.can_use_link) {
        append("Edit Link...", ComponentPopupMenu_edit_link);
        append("Link Enabled", ComponentPopupMenu_link_enabled, true, true, true, info.link_enabled_checked);
    }
    append("Copy Link", ComponentPopupMenu_copy_link);
    if (info.can_use_link) {
        append("Paste Link", ComponentPopupMenu_paste_link);
    }
    if (info.has_default_value) {
        append("Reset to default value", ComponentPopupMenu_reset_default_value);
    }
    if (info.has_set_size) {
        append("Set size...", ComponentPopupMenu_set_size);
    }
}

//---------------------------------------------------------------------
void ComponentPopupMenu::append(QString title, int id, bool enabled, bool visible,
                                bool checkable, bool checked) {
    items_.append(ComponentPopupMenuItem(title, id, enabled, visible, checkable, checked));
}

//---------------------------------------------------------------------
//Gui should call this when switching modules, so `responder` is no valid
void ComponentPopupMenu::clear() {
    menu_.reset();
}

//---------------------------------------------------------------------
//Create and show popup menu asyncr. The clicked action will be sent to `responder` as "on_component_popup_action()
void ComponentPopupMenu::show_menu(XGui *responder, QWidget *parent, const QPoint &pos) {
    menu_.reset(new QMenu(parent));
    for (auto &item: items_) {
        QAction *a = new QAction();
        a->setText(item.title);
        a->setData(item.id_);
        menu_->addAction(a);
        connect(a, &QAction::triggered, responder, &XGui::on_component_popup_action);
    }

    menu_->popup(pos);

    //qDebug() << "popup menu for" << item__->name() << pos.x() << pos.y();
}


//---------------------------------------------------------------------





