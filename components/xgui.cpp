#include "qt_widgets.h"
#include "xgui.h"
#include "incl_cpp.h"
#include "xitem.h"
#include "visibilitygroups.h"
#include "componentcontextmenu.h"
//#include "xcluclickablelabel.h"

//---------------------------------------------------------------------
//XGuiPageBuilder
//---------------------------------------------------------------------
//insert new widget to grid
//if widget is nullptr, just ignores it, but shifts x and y
void XGuiPageBuilder::insert(QWidget *widget, int spanx, bool new_line) {
    if (widget) {
        grid->addWidget(widget, pos.y, pos.x, 1, spanx);
    }
    pos.x += spanx;
    if (new_line) {
        pos.y++;
    }
}

//---------------------------------------------------------------------
//XGui
//---------------------------------------------------------------------
XGui::XGui(XGuiPageBuilder &input, XItem * item)
    :QWidget(input.parent)
{
    item__ = item;
    settings_ = input.settings;
}

//---------------------------------------------------------------------
XGui::~XGui() {
    for (int i=0; i<vis_groups_.size(); i++) {
        delete vis_groups_[i];
    }
}

//---------------------------------------------------------------------
//строка-подсказка, может быть разных типов - см. Tip_Style
QString XGui::get_tip() {
    QString tip;
    switch (get_tip_style()) {
    case Tip_Full: {
        tip = item__->name();
        if (!item__->description().isEmpty()) {
            tip.append(" - ");
            tip.append(item__->description());
        }
        break;
    }
    case Tip_Description: {
        tip = item__->description();
        break;
    }
    default:
        xclu_exception("Bad tip style of '" + item__->name() + "'");
    }
    return tip;
}

//---------------------------------------------------------------------
//create label_ and return it for using in insert_widgets
QWidget *XGui::new_label() {
    label_ = new QLabel(item__->title());
    label_->setMinimumWidth(xclu::LABEL_WIDTH_MIN);
    //label_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    label_->setAlignment(Qt::AlignVCenter);

    //hint
    label_->setToolTip(get_tip());

    //decorate label using qualifier
    //out
    if (item__->is_out()) {
        auto font = label_->font();
        font.setUnderline(true);
        //font.setBold(true);
        label_->setFont(font);
    }

    //const
    if (item__->is_const()) {
        auto font = label_->font();
        //font.setItalic(true);
        font.setBold(true);
        label_->setFont(font);
    }


    //context menu
    attach_context_menu(label_);

    //insert on page
    //input.grid->addWidget(label_, input.y, 0);
    return label_;
}

//---------------------------------------------------------------------
//attach context menu - automatically to label, and manually to button
void XGui::attach_context_menu(QWidget *widget) {
    //context menu
    //https://forum.qt.io/topic/31233/how-to-create-a-custom-context-menu-for-qtableview/3
    widget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(label_, SIGNAL(customContextMenuRequested(QPoint)),
                SLOT(customMenuRequested(QPoint)));
}

//---------------------------------------------------------------------
//show popup menu
void XGui::customMenuRequested(QPoint pos){
    xclu_assert(label_, "XGui::customMenuRequested - empty label_, can't compute menu position");
    //Get information about menu
    ComponentContextMenu::COMP_MENU()->setup(item__->context_menu_info());
    //Start menu async.
    ComponentContextMenu::COMP_MENU()->show_menu(this, label_, label_->mapToGlobal(pos));
}

//---------------------------------------------------------------------
//signal from popup menu, action->data().toInt() is ComponentContextMenuEnum
void XGui::on_component_popup_action() {
    if (const QAction *action = qobject_cast<const QAction *>(sender())) {
        ComponentContextMenuEnum id = (ComponentContextMenuEnum)action->data().toInt();
        item__->context_menu_on_action(id, action->text());
    }
    else {
      xclu_exception("Error casting action at XGui::on_component_popup_action");
    }
}

//---------------------------------------------------------------------
//Show "Edit link" dialog when right-clicked link
void XGui::on_label_link_right_click(QPoint /*pos*/) {
    if (!item__->link().link.isEmpty()) {
        item__->context_menu_on_action(ComponentContextMenu_edit_link, "Label link is clicked");
    }
}

//---------------------------------------------------------------------
//Insert to page widgets structure
//widget_marker - is a widget which is decorated when link changes and set bold for constants,
//it's just marker and can duplicate with widget1..5.
//widget1..5 can be nullptr - in this case it's omitted and grid just shifted,
//for example for button widget1 == nullptr
void XGui::insert_widgets(XGuiPageBuilder &page_builder,
                          QWidget *widget_marker,
                          QWidget *widget1, int spanx1, int newline1,
                          QWidget *widget2, int spanx2, int newline2,
                          QWidget *widget3, int spanx3, int newline3,
                          QWidget *widget4, int spanx4, int newline4,
                          QWidget *widget5, int spanx5, int newline5
                          ) {

    //insert to page
    page_builder.insert(widget1, spanx1, newline1);
    page_builder.insert(widget2, spanx2, newline2);
    page_builder.insert(widget3, spanx3, newline3);
    page_builder.insert(widget4, spanx4, newline4);
    page_builder.insert(widget5, spanx5, newline5);

    //register visibility
    if (widget1) widgets_visibility_.push_back(widget1);
    if (widget2) widgets_visibility_.push_back(widget2);
    if (widget3) widgets_visibility_.push_back(widget3);
    if (widget4) widgets_visibility_.push_back(widget4);
    if (widget5) widgets_visibility_.push_back(widget5);


    //store widget to control its background color and decorate by qualifier,
    //for example, "bolds" on constants and green on linked state
    widget_marker_ = internal_widget;

    //change font type
    /*if (internal_widget) {
        auto font = internal_widget->font();
        font.setFamily(xclu::font_family_values());
        internal_widget->setFont(font);
    }*/

    //const make bold, if widget accepts this by is_const_bold() = true
    if (item__->is_const() && is_const_bold()) {
        if (widget_marker_) {
            auto font = widget_marker_->font();
            font.setBold(true);
            widget_marker_->setFont(font);
        }
    }

    //out and links - set "read only"
    on_change_link_readonly();
}

//---------------------------------------------------------------------
//вставить на страницу созданный виджет
void XGui::insert_widget(QWidget *widget, QWidget *internal_widget, XGuiPageBuilder &input,
                                 int pos_x, int shift_y, int spanx, int spany) {

    //insert widget
    input.grid->addWidget(widget, input.y + shift_y, pos_x, spany, spanx);

    input.y += shift_y + spany;

    //collect "widgets_visibility_" - widgets to control their visibility
    if (label_) {
        widgets_visibility_.push_back(label_);
    }
    widgets_visibility_.push_back(label_link_);
    widgets_visibility_.push_back(widget);

    //store widget to control its background color and decorate by qualifier,
    //for example, "bolds" on constants and green on linked state
    widget_marker_ = internal_widget;

    //change font type
    /*if (internal_widget) {
        auto font = internal_widget->font();
        font.setFamily(xclu::font_family_values());
        internal_widget->setFont(font);
    }*/

    //const make bold, if widget accepts this by is_const_bold() = true
    if (item__->is_const() && is_const_bold()) {
        if (widget_marker_) {
            auto font = widget_marker_->font();
            font.setBold(true);
            widget_marker_->setFont(font);
        }
    }

    //out and links - set "read only"
    on_change_link_readonly();
}

//---------------------------------------------------------------------
//вставить с новой строки (то есть label будет сверху, а этот widget на всю строку)
void XGui::insert_widget_next_line(QWidget *widget, QWidget *internal_widget, XGuiPageBuilder &input) {
    insert_widget(widget, internal_widget, input, 0, 1, 4, 1);
}

//---------------------------------------------------------------------
//вставить виджет со спейсером справа, чтобы когда нет широких элементов, он не уезжал вправо
//(int, float, checkbox, object)
void XGui::insert_widget_with_spacer(QWidget *widget, QWidget *internal_widget, XGuiPageBuilder &input,
                                             int pos_x, int shift_y, int spanx, int spany) {
    /*QSpacerItem *spacer = new QSpacerItem(1,1);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(widget);
    layout->addItem(spacer);
    layout->setStretch(0,0);
    layout->setStretch(1,1);
    QWidget *holder= new QWidget;
    attribute_as_GuiEditorPage(holder);  //set background as a whole page

    holder->setLayout(layout);
    insert_widget(holder, internal_widget, input, pos_x, shift_y, spanx, spany);
*/
    insert_widget(widget, internal_widget, input, pos_x, shift_y, spanx, spany);

}

//---------------------------------------------------------------------
void XGui::insert_widget_with_spacer_next_line(QWidget *widget, QWidget *internal_widget, XGuiPageBuilder &input) {
     insert_widget_with_spacer(widget, internal_widget, input, 0, 1, 4, 1);
}

//---------------------------------------------------------------------
//set "GuiEditorPage" for QWidget in order QSS set its background darker
void XGui::attribute_as_GuiEditorPage(QWidget *widget) {
    widget->setObjectName("GuiEditorPage");
}

//---------------------------------------------------------------------
void XGui::set_read_only(bool read_only) {
    //decide if required to do something
    if (current_read_only_ == read_only) return;
    current_read_only_ = read_only;

    set_read_only_(read_only);
}

//---------------------------------------------------------------------
//Internal function, which should be reimplemented for components
void XGui::set_read_only_(bool read_only) {

}

//---------------------------------------------------------------------
//Отслеживание изменений
//Подклассы должны его вызывать, чтобы пометить, что проект был изменен, вот так:
//connect(spin_, SIGNAL (valueChanged(double)), this, SLOT (on_value_changed()));
void XGui::on_value_changed() {
    xclu_document_modified();

    QString value_string_vis = value_string_for_visibility();
    for (int i=0; i<vis_groups_.size(); i++) {
        vis_groups_[i]->value_changed(value_string_vis);
    }
}

//---------------------------------------------------------------------
void XGui::block_editing_on_running() { //блокирование изменения констант, вызывается перед запуском проекта
    if (label_) {
        default_label_color_ = xclu::set_font_color_gray(label_);
    }
    running_blocked_ = true;
    set_read_only(true);
}

//---------------------------------------------------------------------
void XGui::unblock_editing_on_stopping() { //разблокирование изменения констант, вызывается после остановки проекта
    if (label_) {
        xclu::reset_font_color(label_, default_label_color_);
    }
    running_blocked_ = false;
    set_read_only(false);
}

//---------------------------------------------------------------------
void XGui::set_visible(bool visible) {
    for (auto *widget: widgets_visibility_) {
        widget->setVisible(visible);
    }
    for (int i=0; i<vis_groups_.size(); i++) {
        vis_groups_[i]->visibility_changed(visible);
    }

}

//---------------------------------------------------------------------
//Если требуется - добавить группу видимости
//групп может быть несколько, их нужно в деструкторе удалить
void XGui::add_visibility_group(VisibilityGroupGui *created_group) {
    vis_groups_.push_back(created_group);
    //vis_group_->value_visibility_setup(true)
}

//---------------------------------------------------------------------
//сигнал послать данные об изменении видимости - высылается после первой установки значения в переменную
void XGui::propagate_visibility() {
    for (int i=0; i<vis_groups_.size(); i++) {
        vis_groups_[i]->propagate_visibility(value_string_for_visibility());
    }
}

//---------------------------------------------------------------------
//User change link settings - should show it in GUI
void XGui::link_was_changed() {
    on_change_link_readonly();
}

//---------------------------------------------------------------------
//Controls "read only" and link properties
//Should be called when changed read_only and link
void XGui::on_change_link_readonly() {
    bool read_only = item__->is_out() || item__->is_linked() || (item__->is_const() && running_blocked());
    set_read_only(read_only);

    //update "is_linked" property in widget, to set its background
    if (widget_marker_) {
        if (current_is_linked_ != item__->is_linked()) {
            current_is_linked_ = item__->is_linked();
            widget_marker_->setProperty("is_link", current_is_linked_);
            xclu::widget_update_css(widget_marker_);
        }
    }

    update_label_link();

}

//---------------------------------------------------------------------
//create label_link_ for showing links and return it for using in insert_widgets
QWidget *XGui::new_label_link() {
    label_link_ = new QLabel("");
    //input.grid->addWidget(label_link_, input.y, xclu::gui_page_link_column);
    update_label_link();

    //Attach context menu with "Edit link" dialog, when right-clicked link
    label_link_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(label_link_, SIGNAL(customContextMenuRequested(QPoint)),
                SLOT(on_label_link_right_click(QPoint)));

    //connect(label_link_, SIGNAL(clicked()), SLOT(on_label_link_clicked()));
}

//---------------------------------------------------------------------
//update label link decoration when link is changed and also on "show names" command
void XGui::update_label_link() {
    if (label_link_) {
        QString name_text;
        if (settings_.show_names) {
            name_text = item__->name();
        }
        QString link_text = item__->link().link;
        if (!link_text.isEmpty()) {
            if (!item__->is_linked()) {
                link_text = QString("(%1)").arg(link_text);
            }
        }
        QString text = name_text;
        if (!link_text.isEmpty()) {
            if (!text.isEmpty()) {
                text.append(": ");
            }
            text.append(link_text);
        }
        label_link_->setText(text);
    }
}

//---------------------------------------------------------------------
//Change show components names
void XGui::set_show_components_names(bool show) {
    if (settings_.show_names != show) {
        settings_.show_names = show;
        update_label_link();
    }
 }

//---------------------------------------------------------------------





