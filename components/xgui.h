#ifndef INTERFACEITEMGUI_H
#define INTERFACEITEMGUI_H

// A graphical interface for displaying or editing a variable.
// It creates a class that is capable of generating a GUI object on demand.
/*
Constants without expression: set from the GUI at start.
Constants with expression: are evaluated at start.
Input without expression: put from the GUI before update.
Input with expression: they are evaluated before each update and placed in the GUI.
Output: the module calculates them, and is set in the GUI after the update.
*/

#include <QWidget>
#include "sdk_h.h"

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QVBoxLayout;
class QHBoxLayout;
class QListWidget;
class QTabWidget;
class QListWidgetItem;
class QGridLayout;
class QMenu;
QT_END_NAMESPACE

class XItem;
class VisibilityGroupGui;
//class XcluClickableLabel;


//Settings for created GUI
struct XGuiSettings {
    bool show_names = false;
};

//Data for build GUI
struct XGuiPageBuilder {
    QWidget *parent = nullptr;
    QTabWidget *tabs = nullptr;     //here pages are added
    QGridLayout *grid = nullptr;    //this is main grid of each page
    int2 pos = int2(0,0);           //current insert position

    XGuiSettings settings;

    //insert new widget to grid
    //if widget is nullptr, just ignores it, but shifts x and y
    void insert(QWidget *widget, int spanx, bool new_line);
};

//GUI component
class XGui : public QWidget
{
    Q_OBJECT
public:
    //item - should not be deleted
    XGui(XGuiPageBuilder &page_builder, XItem *item);
    virtual ~XGui();

    //called at start, used for enabling buttons
    virtual void start() {}

    //called at stop, used for disabling buttons
    virtual void stop() {}

    //Functions for locking and unlocking editing of constants at project start.
    void block_editing_on_running();    //blocking changing constants, called before starting the project
    void unblock_editing_on_stopping(); //onblocking changing constants, called after stopping the project

    //Work with visibility
    //virtual function - since, for example, a separator needs to be done in a special way
    virtual void set_visible(bool visible);

    //If required, add a visibility group
    //there can be several groups, they need to be deleted in the destructor
    void add_visibility_group(VisibilityGroupGui *created_group);

    //value for checking the visibility of children
    //subclasses must implement it to participate in visibility conditions
    virtual QString value_string_for_visibility() { return ""; };

    //signal to send data on visibility change - sent after the first setting of the value in the variable
    void propagate_visibility();

    //User change link settings - should show it in GUI
    virtual void link_was_changed();

    bool is_read_only() { return current_read_only_; }

    //Change show components names
    void set_show_components_names(bool show);
protected:
    //Ссылка на невизуальный элемент интерфейса (который и представляется данным GUI-элементом)
    XItem *item__ = nullptr;

    //Settings
    XGuiSettings settings_;

    //This function controls "read only" and link properties
    //It should be called when changed read_only and link
    void on_change_link_readonly();

    //whether constants need to be done bold (false for text)
    virtual bool is_const_bold() { return true; }

    //Is running - so need to set "read only" for constants
    bool running_blocked() { return running_blocked_; }
    bool running_blocked_ = false;

    //Common function which controls setting "read only" mode.
    //It calls `set_read_only_` virtual function, thish is specific for components
    //This function is called for `out` variables, for `const` after running, for `linked` variables when set.
    //The `in` and `const` can be set to `linked` and back.
    void set_read_only(bool read_only);
    bool current_read_only_ = false;    //current state of "read only"
    bool current_is_linked_ = false;

    //Internal function, which can be reimplemented for components
    virtual void set_read_only_(bool read_only);

    //set "GuiEditorPage" for QWidget in order QSS set its background darker
    void attribute_as_GuiEditorPage(QWidget *widget);

    //tip for this control, see Tip_Style
    QString get_tip();

    //type of tip, subclasses can change get_tip_style, to set required type
    //for example, page uses only description
    enum Tip_Style: int {
        Tip_Full = 0,       //'name - description'
        Tip_Description = 1 //'decription'
    };

    virtual Tip_Style get_tip_style() { return Tip_Full; }

protected:
    //Insert to page widgets structure
    //widget_marker - is a widget which is decorated when link changes and set bold for constants,
    //it's just marker and can duplicate with widget1..5.
    //widget1..5 can be nullptr - in this case it's omitted and grid just shifted,
    //for example for button widget1 == nullptr
    //Note: each control must finish inserting with newline!
    void insert_widgets(XGuiPageBuilder &page_builder,
                        QWidget *widget_marker,
                        QWidget *widget1 = nullptr, int spanx1 = 0, int newline1 = false,
                        QWidget *widget2 = nullptr, int spanx2 = 0, int newline2 = false,
                        QWidget *widget3 = nullptr, int spanx3 = 0, int newline3 = false,
                        QWidget *widget4 = nullptr, int spanx4 = 0, int newline4 = false,
                        QWidget *widget5 = nullptr, int spanx5 = 0, int newline5 = false
                        );
    /*
    Widget structures for different controls:

    float, int:     0 label, 1 control,  2 measure unit, 3 slider,     4 link label
    checkbox:       0 label, 1 control                                 4 link label
    checkbox_group: 0--------1 control,  2---------------3 horiz.line  4 link label
    separator:      0 "control"
    button:                  1 control                                 4 link label
    string, text:   0 label                                            4 link label
                    0 -------------------------------------------------4 control
    object:         0 label                                            4 link label
                    0--------------------2 thumbnail     3-------------4 description
    */

protected slots:
    //Track changes
    //Subclasses should call it to indicate that the project has changed, like this:
    //connect (spin_, SIGNAL (valueChanged (double)), this, SLOT (on_value_changed ()));
    //also, they can override them for their own purposes, but be sure to call this base method
    virtual void on_value_changed();

protected:
    //Dynamic interface: visible groups
    QVector<VisibilityGroupGui *> vis_groups_;

    //widgets to control their visibility - includes label and label_link
    QVector<QWidget *> widgets_visibility_;

    //widget on which show read_only and link color
    QWidget *widget_marker_ = nullptr;

    //create label_ and return it for using in insert_widgets
    QWidget *new_label();
    //label is used for constant changing color
    QLabel *label_ = nullptr;
    QColor default_label_color_;    //original label color - user to restore after gray

    //create label_link_ for showing links and return it for using in insert_widgets
    QWidget *new_label_link();
    //update label link decoration when link is changed and also on "show names" command
    void update_label_link();
    QLabel *label_link_ = nullptr;  //label for link

    //attach context menu - automatically to label, and manually to button
    void attach_context_menu(QWidget *widget);

//Context menu
protected slots:
    //show popup menu
    void customMenuRequested(QPoint pos);    

    //Show "Edit link" dialog when right-clicked link
    void on_label_link_right_click(QPoint pos);

public slots:
    //signal from popup menu, action->data().toInt() is ComponentContextMenuEnum
    void on_component_popup_action();

    //Show "Edit link" dialog when clicked link
    //void on_label_link_clicked();

};

#endif // INTERFACEITEMGUI_H
