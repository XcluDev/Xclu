#include "xitemseparator.h"

#include "xguiseparator.h"

//---------------------------------------------------------------------
//separator - вертикальный отступ
//line - горизонтальная линия
XItemSeparator::XItemSeparator(ModuleInterface *parent, const XItemPreDescription &pre_description)
    : XItem(parent, pre_description)
{
    //separator
    name_ = pre_description.line_to_parse; //имя генерируется автоматически

    //это line, если описание содержит "line"
    is_line_ = pre_description.description.contains("line");
}

//---------------------------------------------------------------------
//графический интерфейс
XGui *XItemSeparator::create_gui(XGuiPageCreator &input) {
    return new XGuiSeparator(input, this);
}

//---------------------------------------------------------------------
