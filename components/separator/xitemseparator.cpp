#include "xitemseparator.h"
#include "xguiseparator.h"
#include "registrarxitem.h"

REGISTER_XITEM(XItemSeparator, separator)
//---------------------------------------------------------------------
//separator - вертикальный отступ
//line - горизонтальная линия
XItemSeparator::XItemSeparator(ModuleInterface *interf, const XItemPreDescription &pre_description)
    : XItem(interf, pre_description)
{
    //separator
    name_ = pre_description.line_to_parse; //имя генерируется автоматически

    //это line, если описание содержит "line"
    is_line_ = pre_description.description.contains("line");
}

//---------------------------------------------------------------------
//графический интерфейс
XGui *XItemSeparator::create_gui(XGuiPageBuilder &page_builder) {
    return new XGuiSeparator(input, this);
}

//---------------------------------------------------------------------
//C++
void XItemSeparator::export_interface(QStringList &file) {
    file.append("");
}

//---------------------------------------------------------------------
