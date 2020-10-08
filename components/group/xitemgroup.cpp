#include "xitemgroup.h"
#include "registrarxitem.h"

REGISTER_XITEM(XItemGroup, group)
//---------------------------------------------------------------------
XItemGroup::XItemGroup(ModuleInterface *interf, const XItemPreDescription &pre_description)
    : XItem(interf, pre_description)
{
    //page Main_page
    name_ = pre_description.line_to_parse;
}

//---------------------------------------------------------------------
//Context menu
//Each component must provide information about its menu
ComponentPopupMenuInfo XItemGroup::component_popup_info() {
    return ComponentPopupMenuInfo(false, false, false, false);
}

//---------------------------------------------------------------------
//C++
void XItemGroup::export_interface(QStringList & /*file*/) {

}

//---------------------------------------------------------------------
