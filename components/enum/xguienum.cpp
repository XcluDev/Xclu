#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xguienum.h"
#include "xitemenum.h"
#include "xclucombobox.h"

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
XGuiEnum::XGuiEnum(XGuiPageBuilder &page_builder, XItemEnum *item)
    :XGui(page_builder, item)
{
    combo_ = new XcluComboBox();
    combo_->addItems(item->titles());
    names_ = item->names();     //remember the original names to return them when checking visibility groups

    combo_->setMinimumWidth(xclu::COMBO_WIDTH_MIN);
    combo_->setMaximumWidth(xclu::COMBO_WIDTH_MAX);

    //disable possibility for accidentally change from the mouse wheel
    //https://stackoverflow.com/questions/5821802/qspinbox-inside-a-qscrollarea-how-to-prevent-spin-box-from-stealing-focus-when
    combo_->setFocusPolicy(Qt::StrongFocus);

    //create units label if required
    QString units = item->units();
    QLabel *units_label = nullptr;
    if (!units.isEmpty()) {
        units_label = new QLabel(units);
    }

    //insert to page
    insert_widgets(page_builder,
                   combo_,
                   new_label(), 1, false,
                   combo_, 1, false,
                   units_label, 1, false,
                   nullptr, 1, false,
                   new_label_link(), 1, true);

    //track changes
    connect(combo_, SIGNAL (currentIndexChanged(int)), this, SLOT (on_value_changed()));
}

//---------------------------------------------------------------------
XGuiEnum::~XGuiEnum() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void XGuiEnum::set_read_only_(bool read_only) {
    combo_->setEnabled(!read_only);
    xclu::widget_update_css(combo_);
}

//---------------------------------------------------------------------
int XGuiEnum::index() {
    return combo_->currentIndex();
}

//---------------------------------------------------------------------
void XGuiEnum::set_index(int v) {
    if (v < 0 || v >= combo_->count()) v = 0;
    //проверяем, что значение не изменилось
    //(в противном случае, out-значение невозможно скопировать во время выполнения)
    if (combo_->count() > 0 && combo_->currentIndex() != v) {
        combo_->setCurrentIndex(v);
    }
}

//---------------------------------------------------------------------
//значение для проверки видимости детей
QString XGuiEnum::value_string_for_visibility() {
    int i = index();
    if (i >= 0 && i < names_.size()) {
        return names_[i];
    }
    return "";
};

//---------------------------------------------------------------------
