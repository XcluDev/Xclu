#include "xitembutton.h"
#include "xguibutton.h"
#include "incl_cpp.h"
#include "moduleinterface.h"
#include "registrarxitem.h"

REGISTER_XITEM(XItemButton, button)

//---------------------------------------------------------------------
//in button Execute execute
XItemButton::XItemButton(ModuleInterface *interf, const XItemPreDescription &pre_description)
    : XItem_<int>(interf, pre_description)
{
    //Button не может быть out
    xclu_assert(pre_description.qualifier != XQualifierOut, "button can't have 'out' qualifier, '" + pre_description.title + "'");

    //page Main_page
    name_ = pre_description.line_to_parse;
}

//---------------------------------------------------------------------
//графический интерфейс
XGui *XItemButton::create_gui(XGuiPageCreator &input) {
    gui__ = new XGuiButton(input, this);
    return gui__;
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
    auto v_write = value_write();
    int res = v_write.data();
    v_write.data() = 0;
    return res;
}

//---------------------------------------------------------------------
//получение значения из gui
void XItemButton::gui_to_var_internal() {
    value_write().data() = ((XGuiButton *)gui__)->value();
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
                              "int ", "i", "geti", "seti", false, false, false);
    //export button name
    file.append(QString("QString button_%1() { return \"%1\"; }").arg(name()));
    file.append("");

}

//---------------------------------------------------------------------
