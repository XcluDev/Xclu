#include "xitempage.h"
#include "xguipage.h"
#include "registrarxitem.h"

REGISTER_XITEM(XItemPage, page)
//---------------------------------------------------------------------
XItemPage::XItemPage(XModuleInterface *interf, const XItemPreDescription &pre_description)
    : XItem(interf, pre_description)
{
    //page Main_page
    name_ = pre_description.line_to_parse;
}

//---------------------------------------------------------------------
//графический интерфейс
XGui *XItemPage::create_gui(XGuiPageBuilder &page_builder) {
    gui__ = new XGuiPage(page_builder, this);
    return gui__;
}

//---------------------------------------------------------------------
//получение значения из gui
void XItemPage::gui_to_var_internal() {
    scroll_ = ((XGuiPage *)gui__)->get_vscroll();
}

//---------------------------------------------------------------------
//установка значения в gui
void XItemPage::var_to_gui_internal() {
    ((XGuiPage *)gui__)->set_vscroll(scroll_);
}

//---------------------------------------------------------------------
//C++
void XItemPage::export_interface(QStringList &file) {
    export_interface_template(file, true, true, "Page ");
}

//---------------------------------------------------------------------
