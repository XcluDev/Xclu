#include "interfaceitemseparator.h"

#include "interfaceguiseparator.h"

//---------------------------------------------------------------------
//separator - вертикальный отступ
//line - горизонтальная линия
InterfaceItemSeparator::InterfaceItemSeparator(const InterfaceItemPreDescription &pre_description)
    : InterfaceItem(pre_description)
{
    //separator
    name_ = pre_description.line_to_parse; //имя генерируется автоматически

    //это line, если описание содержит "line"
    is_line_ = pre_description.description.contains("line");
}

//---------------------------------------------------------------------
//графический интерфейс
InterfaceGui *InterfaceItemSeparator::create_gui(InterfaceGuiPageCreator &input) {
    return new InterfaceGuiSeparator(input, this);
}

//---------------------------------------------------------------------
