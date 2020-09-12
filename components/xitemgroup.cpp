#include "xitemgroup.h"

//---------------------------------------------------------------------
XItemGroup::XItemGroup(ModuleInterface *parent, const XItemPreDescription &pre_description)
    : XItem(parent, pre_description)
{
    //page Main_page
    name_ = pre_description.line_to_parse;
}

//---------------------------------------------------------------------
//C++
void XItemGroup::export_interface(QStringList & /*file*/) {

}

//---------------------------------------------------------------------
