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

    auto range = item->range();
    if (range.low_enabled) {
        spin_->setMinimum(range.low);
    }
    if (range.high_enabled) {
        spin_->setMaximum(range.high);
    }

    //шаг
    spin_->setSingleStep(item->get_small_step());

    //вставка на страницу
    //если есть единицы измерения - создаем блок с Label
    QString units = item->units();

    if (!units.isEmpty()) {
        //qDebug() << "units" << units;
        insert_widget_with_spacer(xclu::hwidget(0,
                                                spin_,0,
                                                new QLabel(units), 0),
                                  spin_, input);
    }
    else {
        insert_widget_with_spacer(spin_, spin_, input);
    }

    //отслеживание изменений
    connect(spin_, SIGNAL (valueChanged(int)), this, SLOT (on_value_changed()));
}

//---------------------------------------------------------------------
XGuiInt::~XGuiInt() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void XGuiInt::set_read_only_(bool read_only) {
    spin_->setReadOnly(read_only);
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
        spin_->setValue(v);
    }
}

//---------------------------------------------------------------------
