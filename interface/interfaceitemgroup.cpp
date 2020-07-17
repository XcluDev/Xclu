#include "interfaceitemgroup.h"

//---------------------------------------------------------------------
InterfaceItemGroup::InterfaceItemGroup(const InterfaceItemPreDescription &pre_description)
    : InterfaceItem(pre_description)
{
    //page Main_page
    name_ = pre_description.line_to_parse;
}

//---------------------------------------------------------------------
