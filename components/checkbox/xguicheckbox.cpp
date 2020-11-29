#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xitemcheckbox.h"
#include "xguicheckbox.h"

//---------------------------------------------------------------------
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

//---------------------------------------------------------------------
XGuiCheckbox::XGuiCheckbox(XGuiPageBuilder &page_builder, XItemCheckbox *item)
    :XGui(page_builder, item)
{
    checkbox_ = new QCheckBox("");

    if (!item->is_group_checkbox()) { //normal checkbox
        //insert to page
        insert_widgets(page_builder,
                       checkbox_,
                       new_label(), 1, false,
                       checkbox_, 1, false,
                       nullptr, 2, false,
                       new_label_link(), 1, true);
    }
    else {
        //group checkbox - show at left and with horizontl line
        checkbox_->setText(item->title());
        checkbox_->setToolTip(get_tip());

        //horizontal line - now commented
        //QFrame *line_ = new QFrame();
        //line_->setFrameShape(QFrame::HLine);
        //line_->setFrameShadow(QFrame::Sunken);

        //insert to page
        insert_widgets(page_builder,
                       checkbox_,
                       checkbox_, 4, false,
                       new_label_link(), 1, true);
    }

    //квалификаторы
    if (item->is_out()) {
        set_read_only(true);
    }

    //track changes
    connect(checkbox_, SIGNAL (stateChanged(int)), this, SLOT (on_value_changed()));
}

//---------------------------------------------------------------------
XGuiCheckbox::~XGuiCheckbox() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void XGuiCheckbox::set_read_only_(bool read_only) {
    //тут цвета фона ставить не нужно!
    checkbox_->setEnabled(!read_only);
}

//---------------------------------------------------------------------
int XGuiCheckbox::value() {
    return (checkbox_->checkState() == Qt::Checked) ? 1 : 0;
}

//---------------------------------------------------------------------
void XGuiCheckbox::set_value(int v) {
    Qt::CheckState state = (v == 1) ? Qt::Checked : Qt::Unchecked;
    //проверяем, что значение не изменилось
    //(в противном случае, проект будет помечен как измененный, хотя это не так)
    if (value() != v) {
        checkbox_->setCheckState(state);
    }
}

//---------------------------------------------------------------------
