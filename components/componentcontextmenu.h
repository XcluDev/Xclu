#ifndef COMPONENTCONTEXTMENU_H
#define COMPONENTCONTEXTMENU_H

//Support class for managing context menu.
//-------------------------------------------------------
//Menu items:
//    Copy Link: module3->input
//    -----
//    * Use Direct Input
//    - Use Link: webcamera1->image
//    -----
//    Edit Link...
//    Paste Link: webcamera2->image
//    -----
//    Reset to Default Value    (for scalars)
//    Set Size...     (for images and other rich elements)
//-------------------------------------------------------

#include "incl_h.h"
#include "moduledescription.h"

#include <QWidget>
class QMenu;
class XGui;


//Enumeration of menu items
enum ComponentContextMenuEnum : int {
    ComponentContextMenu_none = -1,
    ComponentContextMenu_use_input = 0,
    ComponentContextMenu_use_link = 1,
    ComponentContextMenu_edit_link = 2,
    ComponentContextMenu_paste_link = 3,
    ComponentContextMenu_copy_link = 4,
    ComponentContextMenu_reset_default_value = 5,
    ComponentContextMenu_set_size = 6,
    ComponentContextMenu_N = 7
};

//Menu item description
struct ComponentContextMenuItem {
    ComponentContextMenuItem() {}
    ComponentContextMenuItem(QString title, int id, bool enabled = true, bool visible = true,  bool checkable = false, bool checked = false) {
        this->title = title;
        separator = title.isEmpty();
        this->id_ = id;
        this->enabled = enabled;
        this->visible = visible;
        this->checkable = checkable;
        this->checked = checked;
    }

    QString title;
    bool separator = false; //separator if title == ""
    bool visible = false;
    bool enabled = false;
    bool checkable = false;
    bool checked = false;
    int id_ = ComponentContextMenu_none;    //for access after pressing
};

//Item-dependent information for creating popup menu
struct ComponentContextMenuInfo {
    ComponentContextMenuInfo() {}
    ComponentContextMenuInfo(QString get_link_to_itself, QString used_link,
                             bool can_use_link, bool use_link, bool has_default_value, bool has_set_size
                             ) {
        this->get_link_to_itself = get_link_to_itself;
        this->used_link = used_link;
        this->can_use_link = can_use_link;
        this->use_link = use_link;
        this->has_default_value = has_default_value;
        this->has_set_size = has_set_size;
    }
    QString get_link_to_itself;
    QString used_link;
    bool can_use_link = false;
    bool use_link = false;
    bool has_default_value = false;
    bool has_set_size = false;
};

//Class for generating popup menu
class ComponentContextMenu : public QWidget
{
    Q_OBJECT
public:
    //use ComponentContextMenu::COMP_MENU() to access menu
    static ComponentContextMenu *COMP_MENU();

    //prepare structure
    void setup(const ComponentContextMenuInfo &info);

    //Create and show popup menu asyncr. The clicked action will be sent to `responder` as "on_component_popup_action()
    void show_menu(XGui *responder, QWidget *parent, const QPoint &pos);

    //Gui should call this when switching modules, so `responder` is no valid
    void clear();
protected:
    QVector<ComponentContextMenuItem> items_;
    void append(QString title, int id, bool checkable = false, bool checked = false, bool enabled = true);
    void append_separator();
    bool was_added_ = false;    //for separator

    QScopedPointer<QMenu> menu_;
};


#endif // COMPONENTCONTEXTMENU_H
