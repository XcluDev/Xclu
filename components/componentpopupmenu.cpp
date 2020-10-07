#include "componentpopupmenu.h"

#include "incl_cpp.h"

ComponentPopupMenu COMPONENT_POPUP;


/*
    context_menu_.reset(new QMenu(this));
    for (auto &s: arr) {
        context_menu_->addAction(new QAction(s, this));
    }
    context_menu_->popup(label_->mapToGlobal(pos));

    //qDebug() << "popup menu for" << item__->name() << pos.x() << pos.y();

    ComponentPopupMenu_none = -1,
    ComponentPopupMenu_edit_link = 0,
    ComponentPopupMenu_link_enabled = 1,
    ComponentPopupMenu_copy_link = 2,
    ComponentPopupMenu_paste_link = 3,
    ComponentPopupMenu_reset_default_value = 4,
    ComponentPopupMenu_set_size = 5,
    ComponentPopupMenu_N = 6

*/


//---------------------------------------------------------------------
/*
    Edit Link...
    Link Enabled
    Copy Link
    Paste Link
    Reset to default value (for scalars)
    Set size... (for images and other rich elements)
*/

void ComponentPopupMenu::setup(bool can_use_link, bool link_enabled_checked, bool has_default_value, bool has_set_size) {
    items_.clear();
    if (can_use_link) {
        append("Edit Link...", ComponentPopupMenu_edit_link);
        append("Link Enabled", ComponentPopupMenu_link_enabled, true, true, true, link_enabled_checked);
    }
    append("Copy Link", ComponentPopupMenu_copy_link);
    if (can_use_link) {
        append("Paste Link", ComponentPopupMenu_paste_link);
    }
    if (has_default_value) {
        append("Reset to default value", ComponentPopupMenu_reset_default_value);
    }
    if (has_set_size) {
        append("Set size...", ComponentPopupMenu_set_size);
    }
}

//---------------------------------------------------------------------
void ComponentPopupMenu::append(QString title, int id, bool enabled, bool visible,
                                bool checkable, bool checked) {
    items_.append(ComponentPopupMenuItem(title, id, enabled, visible, checkable, checked));
}

//---------------------------------------------------------------------





