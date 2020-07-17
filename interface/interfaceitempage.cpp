#include "interfaceitempage.h"
#include "interfaceguipage.h"

//---------------------------------------------------------------------
InterfaceItemPage::InterfaceItemPage(const InterfaceItemPreDescription &pre_description)
    : InterfaceItem(pre_description)
{
    //page Main_page
    name_ = pre_description.line_to_parse;
}

//---------------------------------------------------------------------
//графический интерфейс
InterfaceGui *InterfaceItemPage::create_gui(InterfaceGuiPageCreator &input) {
    gui__ = gui_ = new InterfaceGuiPage(input, this);
    return gui_;
}

//---------------------------------------------------------------------
//получение значения из gui
void InterfaceItemPage::gui_to_var_internal() {
    scroll_ = gui_->get_vscroll();
}

//---------------------------------------------------------------------
//установка значения в gui
void InterfaceItemPage::var_to_gui_internal() {
    gui_->set_vscroll(scroll_);
}

//---------------------------------------------------------------------
