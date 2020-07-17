#include <QtWidgets>
#include "incl_qtcpp.h"
#include "interfaceitembutton.h"
#include "interfaceguibutton.h"

//---------------------------------------------------------------------
InterfaceGuiButton::InterfaceGuiButton(InterfaceGuiPageCreator &input, InterfaceItemButton *item)
    :InterfaceGui(input, item)
{
    button_ = new QPushButton(item->title());
    button_->setMaximumWidth(xclu::BUTTON_WIDTH);
    button_->setToolTip(get_tip());

    //вставка на страницу
    insert_widget_with_spacer(button_, button_, input);

    connect(button_, SIGNAL (released()), this, SLOT (button_pressed()));

}

//---------------------------------------------------------------------
InterfaceGuiButton::~InterfaceGuiButton() {

}

//---------------------------------------------------------------------
//значение - нажатие считывается один раз, затем стирается
int InterfaceGuiButton::value() {
    int res = value_;
    value_ = 0;
    return res;
}

//---------------------------------------------------------------------
void InterfaceGuiButton::button_pressed() {
    //запоминаем, что кнопка была нажата, если не заблокирована (то есть const и запущен проект)
    if (!blocked()) {
        value_ = 1;
    }
}

//---------------------------------------------------------------------
