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

    spin_ = new XcluDoubleSpinBox();
    spin_->setMinimumWidth(xclu::SPIN_WIDTH);
    spin_->setMaximumWidth(xclu::SPIN_WIDTH);

    spin_->setMinimum(item->min_value());
    spin_->setMaximum(item->max_value());


    spin_->setSingleStep(item->get_small_step());

    //точность - число цифр после запятой
    spin_->setDecimals(3);

    //установка десятичной точки
    spin_->setLocale(QLocale::C);

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
    connect(spin_, SIGNAL (valueChanged(double)), this, SLOT (on_value_changed()));
}

//---------------------------------------------------------------------
XGuiFloat::~XGuiFloat() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void XGuiFloat::set_read_only(bool read_only) {
    //цвет фона
    XGui::set_read_only(read_only);

    spin_->setReadOnly(read_only);
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
       spin_->setValue(v);
    }
}

//---------------------------------------------------------------------
