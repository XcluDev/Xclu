#include "xitembutton.h"
#include "xguibutton.h"
#include "incl_cpp.h"
#include "moduleinterface.h"
#include "registrarxitem.h"
#include "module.h"

REGISTER_XITEM(XItemButton, button)

//---------------------------------------------------------------------
//Button, working only runtime:
//in button Execute execute
//    //Execute command.

//Button, working always:
//in button_always Print_Devices print_devices
//    //Print Available devices.



XItemButton::XItemButton(ModuleInterface *interf, const XItemPreDescription &pre_description)
    : XItem_<int>(interf, pre_description)
{
    //Button не может быть out
    xc_assert(pre_description.qualifier != XQualifierOut, "button can't have 'out' qualifier, '" + pre_description.title + "'");

    name_ = pre_description.line_to_parse;

    QString options = pre_description.options;
    if (!options.isEmpty()) {
        is_always_enabled_ = (options == "always");
        xc_assert(is_always_enabled_, "Unknown button option, expected '... button_always...'");
    }


    //reset value, in opposite case can be "random" value
    reset_value();
}

//---------------------------------------------------------------------
//графический интерфейс
XGui *XItemButton::create_gui(XGuiPageBuilder &page_builder) {
    gui__ = new XGuiButton(page_builder, this);
    return gui__;
}

//---------------------------------------------------------------------
//called at start, stop and attached interface - used for buttons
void XItemButton::update_is_running(bool running) {
    XItem_<int>::update_is_running(running);
    if (is_gui_attached()) {
        ((XGuiButton *)gui__)->set_running(running);
    }

}

//---------------------------------------------------------------------
//вызывается из gui при нажатии кнопки
void XItemButton::callback_button_pressed() {
    //Проверка, что parent не нулевой - возможно, в конструкторе это не очень хорошо, но все же лучше проверить:)
    xc_assert(interf(),
                "Internal error in XItemButton::callback_button_pressed, empty 'interf()' at '" + name() + "'");

    //Check can we press this button not in runtime
    xc_assert(is_always_enabled() || is_running(), "Internal error - this button must be disabled during edit mode");
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
    xc_assert(linkres, "set_value_from_link for `" + name() + "` - linkres is nullptr");
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
