#include "interfaceitemgroup.h"

//---------------------------------------------------------------------
InterfaceItemGroup::InterfaceItemGroup(ModuleInterface *parent, const InterfaceItemPreDescription &pre_description)
    : InterfaceItem(parent, pre_description)
{
    //page Main_page
    name_ = pre_description.line_to_parse;
}

//---------------------------------------------------------------------
