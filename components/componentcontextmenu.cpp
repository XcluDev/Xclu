#include <QWidget>
#include <QMenu>
#include <QAction>
#include "incl_cpp.h"
#include "componentcontextmenu.h"
#include "xgui.h"

ComponentContextMenu *COMPONENT_POPUP;

//---------------------------------------------------------------------
/*static*/ ComponentContextMenu *ComponentContextMenu::COMP_MENU() {
    if (!COMPONENT_POPUP) {
        COMPONENT_POPUP = new ComponentContextMenu();
    }
    return COMPONENT_POPUP;
}

//---------------------------------------------------------------------
//Menu items:
//    Copy Link: module3->input
//    Edit Link...
//    Paste Link: module->var
//    -----
//    Reset to Default Value    (for scalars)
//    Set Size...     (for images and other rich elements)
//    -----
//    * Use Direct Input
//    - Use Link: webcamera1->image
//
//ComponentContextMenu_use_input
//ComponentContextMenu_use_link
//ComponentContextMenu_edit_link
//ComponentContextMenu_paste_link
//ComponentContextMenu_copy_link
//ComponentContextMenu_reset_default_value
//ComponentContextMenu_set_size

void ComponentContextMenu::setup(const ComponentContextMenuInfo &info) {
    items_.clear();
    want_separator_ = false;
    append(QString("Copy Link: '%1'").arg(XLink::shorten_link(info.get_link_to_itself)), ComponentContextMenu_copy_link);
    if (info.can_use_link) {
        append("Edit Link...", ComponentContextMenu_edit_link);
        QString paste_link = XLink::shorten_link(XLink::get_link_from_clipboard());
        if (!paste_link.isEmpty()) {
            append(QString("Paste Link: '%1'").arg(paste_link), ComponentContextMenu_paste_link);
        }
    }
    append_separator();
    if (info.has_default_value && !info.use_link) {
        append("Reset to Default Value", ComponentContextMenu_reset_default_value);
    }
    if (info.has_set_size) {
        append("Set Size...", ComponentContextMenu_set_size);
    }
    if (info.can_use_link) {
        append_separator();
        //if link is empty - not show choosing options
        if (!info.used_link.isEmpty() || info.use_link) {
            append("Use Direct Input", ComponentContextMenu_use_input, true, !info.use_link);
            append(QString("Use Link: '%1'").arg(XLink::shorten_link(info.used_link)), ComponentContextMenu_use_link, true, info.use_link);
            append_separator();
        }
    }
}

//---------------------------------------------------------------------
void ComponentContextMenu::append(QString title, int id,
                                bool checkable, bool checked, bool enabled) {
    if (want_separator_) {
        items_.append(ComponentContextMenuItem("", ComponentContextMenu_none));
        want_separator_ = false;
    }
    items_.append(ComponentContextMenuItem(title, id, enabled, true, checkable, checked));
}

//---------------------------------------------------------------------
void ComponentContextMenu::append_separator() {
    want_separator_ = true;
}

//---------------------------------------------------------------------
//Gui should call this when switching modules, so `responder` is no valid
void ComponentContextMenu::clear() {
    menu_.reset();
}

//---------------------------------------------------------------------
//Create and show popup menu asyncr. The clicked action will be sent to `responder` as "on_component_popup_action()
void ComponentContextMenu::show_menu(XGui *responder, QWidget *parent, const QPoint &pos) {
    menu_.reset(new QMenu(parent));
    for (auto &item: items_) {
        if (item.separator) {
            menu_->addSeparator();
            continue;
        }
        QAction *a = new QAction();
        a->setText(item.title);
        a->setData(item.id_);
        if (item.checkable) {
            a->setCheckable(true);
            if (item.checked) {
                a->setChecked(true);
            }
        }
        menu_->addAction(a);
        connect(a, &QAction::triggered, responder, &XGui::on_component_popup_action);
    }

    menu_->popup(pos);

    //qDebug() << "popup menu for" << item__->name() << pos.x() << pos.y();
}


//---------------------------------------------------------------------





