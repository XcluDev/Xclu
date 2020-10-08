#ifndef COMPONENTPOPUPMENU_H
#define COMPONENTPOPUPMENU_H

//Support class for managing popup menu.
//-------------------------------------------------------
//Menu items:
//    Edit Link...
//    Link Enabled
//    Copy Link
//    Paste Link
//    Reset to default value (for scalars)
//    Set size... (for images and other rich elements)
//-------------------------------------------------------

#include "incl_h.h"
#include "moduledescription.h"

#include <QWidget>
class QMenu;
class XGui;


//Enumeration of menu items
enum ComponentPopupMenuEnum : int {
    ComponentPopupMenu_none = -1,
    ComponentPopupMenu_edit_link = 0,
    ComponentPopupMenu_link_enabled = 1,
    ComponentPopupMenu_copy_link = 2,
    ComponentPopupMenu_paste_link = 3,
    ComponentPopupMenu_reset_default_value = 4,
    ComponentPopupMenu_set_size = 5,
    ComponentPopupMenu_N = 6
};

//Menu item description
struct ComponentPopupMenuItem {
    ComponentPopupMenuItem() {}
    ComponentPopupMenuItem(QString title, int id, bool enabled = true, bool visible = true,  bool checkable = false, bool checked = false) {
        this->title = title;
        this->id_ = id;
        this->enabled = enabled;
        this->visible = visible;
        this->checkable = checkable;
        this->checked = checked;
    }

    QString title;
    bool visible = false;
    bool enabled = false;
    bool checkable = false;
    bool checked = false;
    int id_ = ComponentPopupMenu_none;    //for access after pressing

};

//Class for generating popup menu
class ComponentPopupMenu : public QWidget
{
    Q_OBJECT
public:
    //use ComponentPopupMenu::COMP_MENU() to access menu
    static ComponentPopupMenu *COMP_MENU();

    //prepare structure
    void setup(bool can_use_link, bool link_enabled_checked, bool has_default_value, bool has_set_size);

    //Create and show popup menu asyncr. The clicked action will be sent to `responder` as "on_component_popup_menu()
    void show_menu(XGui *responder, QWidget *parent, const QPoint &pos);

    //Gui should call this when switching modules, so `responder` is no valid
    void clear();
protected:
    QVector<ComponentPopupMenuItem> items_;
    void append(QString title, int id, bool enabled = true, bool visible = true,  bool checkable = false, bool checked = false);

    QScopedPointer<QMenu> menu_;
};


#endif // COMPONENTPOPUPMENU_H
