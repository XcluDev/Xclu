#include "xitempage.h"
#include "xguipage.h"
#include "registrarxitem.h"

REGISTER_XITEM(XItemPage, page)
//---------------------------------------------------------------------
XItemPage::XItemPage(ModuleInterface *interf, const XItemPreDescription &pre_description)
    : XItem(interf, pre_description)
{
    //page Main_page
    name_ = pre_description.line_to_parse;
}

//---------------------------------------------------------------------
//графический интерфейс
XGui *XItemPage::create_gui(XGuiPageCreator &input) {
    gui__ = gui_ = new XGuiPage(input, this);
    return gui_;
}

//---------------------------------------------------------------------
//получение значения из gui
void XItemPage::gui_to_var_internal() {
    scroll_ = gui_->get_vscroll();
}

//---------------------------------------------------------------------
//установка значения в gui
void XItemPage::var_to_gui_internal() {
    gui_->set_vscroll(scroll_);
}

//---------------------------------------------------------------------
//C++
void XItemPage::export_interface(QStringList &file) {
    export_interface_template(file, true, true, "Page ");
}

//---------------------------------------------------------------------
