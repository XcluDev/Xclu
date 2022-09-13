#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xguiint.h"
#include "xitemint.h"
#include "xcluspinbox.h"

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
XGuiInt::XGuiInt(XGuiPageBuilder &page_builder, XItemInt *item)
    :XGuiComp(page_builder, item)
{    
    spin_ = new XcluSpinBox();
    spin_->setMinimumWidth(xclu::SPIN_WIDTH);
    spin_->setMaximumWidth(xclu::SPIN_WIDTH);

    range_ = item->range();
    if (range_.low_enabled) {
        spin_->setMinimum(range_.low);
    }
    else {
        spin_->setMinimum(-1000000000);
    }
    if (range_.high_enabled) {
        spin_->setMaximum(range_.high);
    }
    else {
        spin_->setMaximum(1000000000);
    }

    //шаг
    spin_->setSingleStep(item->get_small_step());

    //Slider setup
    if (range_.low_enabled && range_.high_enabled && range_.low < range_.high) {
        slider_ = new QSlider();
        slider_->setMinimum(range_.low);
        slider_->setMaximum(range_.high);
        slider_->setTickInterval(item->get_small_step());
        slider_->setPageStep(item->get_large_step());

        slider_->setOrientation(Qt::Horizontal);
        slider_->setTickPosition(QSlider::TicksBelow);
        slider_->setMinimumWidth(xclu::SLIDER_WIDTH);

        //disable possibility for accidentally change from the mouse wheel
        //https://stackoverflow.com/questions/5821802/qspinbox-inside-a-qscrollarea-how-to-prevent-spin-box-from-stealing-focus-when
        slider_->setFocusPolicy(Qt::StrongFocus);
    }

    //create units label if required
    QString units = item->units();
    QLabel *units_label = nullptr;
    if (!units.isEmpty()) {
        units_label = new QLabel(units);
    }

    //insert to page
    insert_widgets(page_builder,
                   spin_,
                   new_label(), 1, false,
                   spin_, 1, false,
                   units_label, 1, false,
                   slider_, 1, false,
                   new_label_link(), 1, true);

    //track changes
    connect(spin_, SIGNAL (valueChanged(int)), this, SLOT (on_value_changed()));

    if (slider_) {
        connect(slider_, SIGNAL (valueChanged(int)), this, SLOT (on_slider_changed(int)));
    }
}

//---------------------------------------------------------------------
XGuiInt::~XGuiInt() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void XGuiInt::set_read_only_(bool read_only) {
    spin_->setReadOnly(read_only);
    if (slider_) slider_->setDisabled(read_only);
    xclu::widget_update_css(spin_);
}

//---------------------------------------------------------------------
int XGuiInt::value() {
    return spin_->value();
}

//---------------------------------------------------------------------
void XGuiInt::set_value(int v) {
    //проверяем, что значение не изменилось
    //(в противном случае, out-значение невозможно скопировать во время выполнения)
    if (value() != v) {
        during_changing_ = true;
        spin_->setValue(v);
        if (slider_) {
            slider_->setValue(spin_->value());
        }
        during_changing_ = false;
    }
}

//---------------------------------------------------------------------
//own implementation of value change event to change slider
void XGuiInt::on_value_changed() {
    if (slider_) {
        slider_->setValue(spin_->value());
    }
    XGuiComp::on_value_changed();
}

//---------------------------------------------------------------------
void XGuiInt::on_slider_changed(int v) {
    if (!during_changing_) {    //for `int` - that is here - is not required, but nevertheless
        //xc_console_append("slider " + QString::number(v));
        set_value(v);
    }
}

//---------------------------------------------------------------------
