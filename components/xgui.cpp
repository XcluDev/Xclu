#include "qt_widgets.h"
#include "xgui.h"
#include "incl_cpp.h"
#include "xitem.h"
#include "visibilitygroups.h"

//---------------------------------------------------------------------
XGui::XGui(XGuiPageCreator &input, XItem * item)
    :QWidget(input.parent)
{
    item__ = item;
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
//создать и вставить label
void XGui::insert_label(XGuiPageCreator &input) {
    //запоминаем label_, чтобы управлять ее видимостью
    label_ = new QLabel(item__->title());
    label_->setMinimumWidth(xclu::LABEL_WIDTH_MIN);
    //label_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    label_->setAlignment(Qt::AlignVCenter);

    //Подсказка
    label_->setToolTip(get_tip());

    //оформить label в зависимости от квалификатора
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
    //https://forum.qt.io/topic/31233/how-to-create-a-custom-context-menu-for-qtableview/3
    label_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(label_, SIGNAL(customContextMenuRequested(QPoint)),
                SLOT(customMenuRequested(QPoint)));


    //insert on page
    input.grid->addWidget(label_, input.y, 0);
}

//---------------------------------------------------------------------
void XGui::customMenuRequested(QPoint pos){
    //QModelIndex index=table->indexAt(pos);

  /*  QStringList arr;
    arr.append("Edit Link...");
    arr.append("Disable Link");
    arr.append("Edit Expression...");
    arr.append("Disable expression");
    arr.append("Copy Link");
    arr.append("Paste Link");
    arr.append("Promote Link...");
    arr.append("Reset to default value (for scalars)");
    arr.append("Set size... (for images and other rich elements)");

    context_menu_.reset(new QMenu(this));
    for (auto &s: arr) {
        context_menu_->addAction(new QAction(s, this));
    }
    context_menu_->popup(label_->mapToGlobal(pos));

    //qDebug() << "popup menu for" << item__->name() << pos.x() << pos.y();*/

}

//---------------------------------------------------------------------
//вставить на страницу созданный виджет
void XGui::insert_widget(QWidget *widget, QWidget *internal_widget, XGuiPageCreator &input,
                                 int pos_x, int shift_y, int spanx, int spany) {

    input.grid->addWidget(widget, input.y + shift_y, pos_x, spany, spanx);
    input.y += shift_y + spany;

    //запоминаем widget, чтобы управлять его видимостью и цветом фона
    set_widget(widget, internal_widget);
}

//---------------------------------------------------------------------
//вставить с новой строки (то есть label будет сверху, а этот widget на всю строку)
void XGui::insert_widget_next_line(QWidget *widget, QWidget *internal_widget, XGuiPageCreator &input) {
    insert_widget(widget, internal_widget, input, 0, 1, 2, 1);
}

//---------------------------------------------------------------------
//вставить виджет со спейсером справа, чтобы когда нет широких элементов, он не уезжал вправо
//(int, float, checkbox, object)
void XGui::insert_widget_with_spacer(QWidget *widget, QWidget *internal_widget, XGuiPageCreator &input,
                                             int pos_x, int shift_y, int spanx, int spany) {
    QSpacerItem *spacer = new QSpacerItem(1,1);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(widget);
    layout->addItem(spacer);
    layout->setStretch(0,0);
    layout->setStretch(1,1);
    QWidget *holder= new QWidget;
    holder->setLayout(layout);

    insert_widget(holder, internal_widget, input, pos_x, shift_y, spanx, spany);
}

//---------------------------------------------------------------------
void XGui::insert_widget_with_spacer_next_line(QWidget *widget, QWidget *internal_widget, XGuiPageCreator &input) {
     insert_widget_with_spacer(widget, internal_widget, input, 0, 1, 2, 1);
}

//---------------------------------------------------------------------
//запомнить уже вставленный widget и установить оформление в зависимости от квалификаторов
//также, вызывается из insert_widget и insert_widget_with_spacer
void XGui::set_widget(QWidget *widget, QWidget *internal_widget) {
    widget_ = widget;
    internal_widget_ = internal_widget;

    //out
    if (item__->is_out()) {
        set_read_only(true);    //выключаем редактирование
    }

    //Установка типа шрифта
    /*if (internal_widget) {
        auto font = internal_widget->font();
        font.setFamily(xclu::font_family_values());
        internal_widget->setFont(font);
    }*/

    //const - ставим жирным, если виджет не просит этого не делать, установив is_const_bold() = false
    if (item__->is_const() && is_const_bold()) {
        if (internal_widget) {
            auto font = internal_widget_->font();
            font.setBold(true);
            internal_widget_->setFont(font);
        }
    }
}

//---------------------------------------------------------------------
void XGui::set_read_only(bool read_only) {
    //установка фона
    if (internal_widget_) {
        QPalette pal = internal_widget_->palette();
        QBrush brush;
        if (read_only) {
            //запоминаем старую кисть
            default_internal_widget_brush_ = pal.brush(QPalette::Base);
            brush = pal.brush(QPalette::Midlight);
        }
        else {
            brush = default_internal_widget_brush_;
        }
        pal.setBrush(QPalette::Base, brush);
        internal_widget_->setPalette(pal);
    }
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
void XGui::block_editing() { //блокирование изменения констант, вызывается перед запуском проекта
    if (label_) {
        default_label_color_ = xclu::set_font_color_gray(label_);
    }
    blocked_ = true;
    set_read_only(true);
}

//---------------------------------------------------------------------
void XGui::unblock_editing() { //разблокирование изменения констант, вызывается после остановки проекта
    if (label_) {
        xclu::reset_font_color(label_, default_label_color_);
    }
    blocked_ = false;
    set_read_only(false);
}

//---------------------------------------------------------------------
void XGui::set_visible(bool visible) {
    if (label_) {
        label_->setVisible(visible);
    }
    if (widget_) {
        widget_->setVisible(visible);
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
