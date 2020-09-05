#include "qt_widgets.h"
#include "incl_cpp.h"
#include "interfaceguiint.h"
#include "interfaceitemint.h"
#include "xcluspinbox.h"

//---------------------------------------------------------------------
InterfaceGuiInt::InterfaceGuiInt(InterfaceGuiPageCreator &input, InterfaceItemInt *item)
    :InterfaceGui(input, item)
{
    insert_label(input);

    spin_ = new XcluSpinBox();
    spin_->setMinimumWidth(xclu::SPIN_WIDTH);
    spin_->setMaximumWidth(xclu::SPIN_WIDTH);

    spin_->setMinimum(item->min_value());
    spin_->setMaximum(item->max_value());

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
InterfaceGuiInt::~InterfaceGuiInt() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void InterfaceGuiInt::set_read_only(bool read_only) {
    //цвет фона
    InterfaceGui::set_read_only(read_only);

    spin_->setReadOnly(read_only);
}

//---------------------------------------------------------------------
int InterfaceGuiInt::value() {
    return spin_->value();
}

//---------------------------------------------------------------------
void InterfaceGuiInt::set_value(int v) {
    //проверяем, что значение не изменилось
    //(в противном случае, out-значение невозможно скопировать во время выполнения)
    if (value() != v) {
        spin_->setValue(v);
    }
}

//---------------------------------------------------------------------
