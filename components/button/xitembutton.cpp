#include "xitembutton.h"
#include "xguibutton.h"
#include "incl_cpp.h"
#include "moduleinterface.h"
#include "registrarxitem.h"
#include "module.h"

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

    //hit_value() will be called from there
    interf()->callback_button_pressed(name());

}

//---------------------------------------------------------------------
//значение - нажатие считывается один раз, затем стирается
int XItemButton::value_int() {
    int res = value_read().data();
    reset_value();
    return res;
}

//---------------------------------------------------------------------
//Function for setting value using link
void XItemButton::set_value_from_link(XLinkResolved *linkres) {
    xclu_assert(linkres, "set_value_from_link for `" + name() + "` - linkres is nullptr");
    Module *mod = linkres->module_ptr();
    set_value_int(mod->geti(linkres));
}


//---------------------------------------------------------------------
void XItemButton::hit_value() {  //set that button was pressed
    if (value_read().data() == 0) {
        value_write().data() = 1;
    }
}

//---------------------------------------------------------------------
void XItemButton::reset_value() {    //reset that button was pressed
    if (value_read().data() != 0) {
        value_write().data() = 0;
    }
}

//---------------------------------------------------------------------
//получение значения из gui
void XItemButton::gui_to_var_internal() {
    if (((XGuiButton *)gui__)->value()) {
        hit_value();
    }
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
