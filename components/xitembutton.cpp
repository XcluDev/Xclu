#include "xitembutton.h"
#include "xguibutton.h"
#include "incl_cpp.h"
#include "moduleinterface.h"

//---------------------------------------------------------------------
//in button Execute execute
XItemButton::XItemButton(ModuleInterface *parent, const XItemPreDescription &pre_description)
    : XItem(parent, pre_description)
{
    //Button не может быть out
    xclu_assert(pre_description.qualifier != VarQualifierOut, "button can't have 'out' qualifier, '" + pre_description.title + "'");

    //page Main_page
    name_ = pre_description.line_to_parse;
}

//---------------------------------------------------------------------
//графический интерфейс
XGui *XItemButton::create_gui(XGuiPageCreator &input) {
    gui__ = gui_ = new XGuiButton(input, this);
    return gui_;
}

//---------------------------------------------------------------------
//вызывается из gui при нажатии кнопки
void XItemButton::callback_button_pressed() {
    //Проверка, что parent не нулевой - возможно, в конструкторе это не очень хорошо, но все же лучше проверить:)
    xclu_assert(interf(),
                "Internal error in XItemButton::callback_button_pressed, empty 'interf()' at '" + name() + "'");
    interf()->callback_button_pressed(name());
}

//---------------------------------------------------------------------
//значение - нажатие считывается один раз, затем стирается
int XItemButton::value_int() {
    int res = value_;
    value_ = 0;
    return res;
}

//---------------------------------------------------------------------
//получение значения из gui
void XItemButton::gui_to_var_internal() {
    value_ = gui_->value();
}

//---------------------------------------------------------------------
//установка значения в gui
void XItemButton::var_to_gui_internal() {
    //gui_->set_value(value());
}

//---------------------------------------------------------------------
//C++
void XItemButton::export_interface(QStringList &file) {
    export_interface_template(file, false, true, "Button ", true,
                              "int", "geti", "seti");
}

//---------------------------------------------------------------------
