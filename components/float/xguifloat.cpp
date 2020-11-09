#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xguifloat.h"
#include "xitemfloat.h"
#include "xcludoublespinbox.h"

//---------------------------------------------------------------------
XGuiFloat::XGuiFloat(XGuiPageCreator &input, XItemFloat *item)
    :XGui(input, item)
{
    insert_label(input);

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
    }

    //вставка на страницу
    //если есть единицы измерения - создаем блок с Label
    QString units = item->units();
    if (!units.isEmpty()) {
        //qDebug() << "units" << units;
        insert_widget_with_spacer(xclu::hwidget(0,
                                                spin_,0,
                                                new QLabel(units), 0,
                                                slider_, 0
                                                ),
                                  spin_, input);
    }
    else {
        insert_widget_with_spacer(xclu::hwidget(0,
                                                spin_,0,
                                                slider_, 0),
                                  spin_, input);
    }

    //отслеживание изменений
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
    XGui::on_value_changed();
}

//---------------------------------------------------------------------
void XGuiFloat::on_slider_changed(int v) {
    if (!during_changing_) {
        //xclu_console_append("slider float " + QString::number(v));
        set_value(range_.tick_to_value(v, ticks_));
    }
}

//---------------------------------------------------------------------
