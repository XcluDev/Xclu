#include "xitemgroup.h"
#include "registrarxitem.h"

REGISTER_XITEM(Group, group)
//---------------------------------------------------------------------
XItemGroup::XItemGroup(ModuleInterface *interf, const XItemPreDescription &pre_description)
    : XItem(interf, pre_description)
{
    //page Main_page
    name_ = pre_description.line_to_parse;
}

//---------------------------------------------------------------------
//C++
void XItemGroup::export_interface(QStringList & /*file*/) {

}

//---------------------------------------------------------------------
