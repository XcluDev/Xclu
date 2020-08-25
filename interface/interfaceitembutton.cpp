#include "interfaceitembutton.h"
#include "interfaceguibutton.h"
#include "incl_qtcpp.h"
#include "moduleinterface.h"

//---------------------------------------------------------------------
//in button Execute execute
InterfaceItemButton::InterfaceItemButton(ModuleInterface *parent, const InterfaceItemPreDescription &pre_description)
    : InterfaceItem(parent, pre_description)
{
    //Button не может быть out
    xclu_assert(pre_description.qualifier != VarQualifierOut, "button can't have 'out' qualifier, '" + pre_description.title + "'");

    //page Main_page
    name_ = pre_description.line_to_parse;
}

//---------------------------------------------------------------------
//графический интерфейс
InterfaceGui *InterfaceItemButton::create_gui(InterfaceGuiPageCreator &input) {
    gui__ = gui_ = new InterfaceGuiButton(input, this);
    return gui_;
}

//---------------------------------------------------------------------
//вызывается из gui при нажатии кнопки
void InterfaceItemButton::callback_button_pressed() {
    //Проверка, что parent не нулевой - возможно, в конструкторе это не очень хорошо, но все же лучше проверить:)
    xclu_assert(parent(),
                "Internal error in InterfaceItemButton::callback_button_pressed, empty 'parent()' at '" + name() + "'");
    parent()->callback_button_pressed(name());
}

//---------------------------------------------------------------------
//значение - нажатие считывается один раз, затем стирается
int InterfaceItemButton::value_int() {
    int res = value_;
    value_ = 0;
    return res;
}

//---------------------------------------------------------------------
//получение значения из gui
void InterfaceItemButton::gui_to_var_internal() {
    value_ = gui_->value();
}

//---------------------------------------------------------------------
//установка значения в gui
void InterfaceItemButton::var_to_gui_internal() {
    //gui_->set_value(value());
}

//---------------------------------------------------------------------
