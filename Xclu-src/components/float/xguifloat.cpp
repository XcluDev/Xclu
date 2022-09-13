#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xguifloat.h"
#include "xitemfloat.h"
#include "xcludoublespinbox.h"

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
XGuiFloat::XGuiFloat(XGuiPageBuilder &page_builder, XItemFloat *item)
    :XGuiComp(page_builder, item)
{
    //Spin setup
    spin_ = new XcluDoubleSpinBox();
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

    spin_->setSingleStep(item->get_small_step());

    //точность - число цифр после запятой
    spin_->setDecimals(3);

    //установка десятичной точки
    spin_->setLocale(QLocale::C);

    //Slider setup
    //ticks > 0 means slider can be created
    ticks_ = range_.ticks(item->get_small_step());
    if (ticks_ > 0) {
        slider_ = new QSlider();
        slider_->setMinimum(0);
        slider_->setMaximum(ticks_);
        slider_->setTickInterval(1);
        float step0 = item->get_small_step();
        float step1 = item->get_large_step();
        if (step0>0) {
            slider_->setPageStep(int(step1/step0));
        }
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
    connect(spin_, SIGNAL (valueChanged(double)), this, SLOT (on_value_changed()));

    if (slider_) {
        connect(slider_, SIGNAL (valueChanged(int)), this, SLOT (on_slider_changed(int)));
    }
}

//---------------------------------------------------------------------
XGuiFloat::~XGuiFloat() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void XGuiFloat::set_read_only_(bool read_only) {
    spin_->setReadOnly(read_only);
    if (slider_) slider_->setDisabled(read_only);
    xclu::widget_update_css(spin_);
}

//---------------------------------------------------------------------
float XGuiFloat::value() {
    return spin_->value();
}

//---------------------------------------------------------------------
void XGuiFloat::set_value(float v) {
    //проверяем, что значение не изменилось
    //(в противном случае, out-значение невозможно скопировать во время выполнения)
    if (value() != v) {
        during_changing_ = true;
       spin_->setValue(v);
       if (slider_) {
           slider_->setValue(range_.value_to_ticks(spin_->value(), ticks_));
       }
       during_changing_ = false;
    }
}

//---------------------------------------------------------------------
//own implementation of value change event to change slider
void XGuiFloat::on_value_changed() {
    if (slider_) {
        slider_->setValue(range_.value_to_ticks(spin_->value(), ticks_));
    }
    XGuiComp::on_value_changed();
}

//---------------------------------------------------------------------
void XGuiFloat::on_slider_changed(int v) {
    if (!during_changing_) {
        //xc_console_append("slider float " + QString::number(v));
        set_value(range_.tick_to_value(v, ticks_));
    }
}

//---------------------------------------------------------------------
