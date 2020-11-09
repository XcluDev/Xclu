#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xguiint.h"
#include "xitemint.h"
#include "xcluspinbox.h"

//---------------------------------------------------------------------
XGuiInt::XGuiInt(XGuiPageCreator &input, XItemInt *item)
    :XGui(input, item)
{    
    insert_label(input);

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
    }

    //вставка на страницу
    //если есть единицы измерения - создаем блок с Label
    QString units = item->units();

    if (!units.isEmpty()) {
        //qDebug() << "units" << units;
        insert_widget_with_spacer(xclu::hwidget(0,
                                                spin_,0,
                                                new QLabel(units), 0,
                                                slider_, 0),
                                  spin_, input);
    }
    else {
        insert_widget_with_spacer(xclu::hwidget(0,
                                                spin_, 0,
                                                slider_, 0),
                                  spin_, input);
    }

    //отслеживание изменений
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
    XGui::on_value_changed();
}

//---------------------------------------------------------------------
void XGuiInt::on_slider_changed(int v) {
    if (!during_changing_) {    //for `int` - that is here - is not required, but nevertheless
        //xclu_console_append("slider " + QString::number(v));
        set_value(v);
    }
}

//---------------------------------------------------------------------
