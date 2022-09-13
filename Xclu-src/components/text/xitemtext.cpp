#include "xitemtext.h"
#include "incl_cpp.h"
#include "xguitext.h"
#include "xmodule.h"
#include "registrarxitem.h"

REGISTER_XITEM(XItemText, text)
//---------------------------------------------------------------------
//  in text Text1 text 7 20
//  //Description - описание
//  //"default text"
//  //"....."
//Многострочный редактор текста,
//7 20 - минимальное и максимальное число строк  на экране (lines count).
//Если какое-то число равно -1, это значит, что нет данного ограничения.
//Строки описания - сначала обычная, а затем идут, опционально,
//дополнительные строки - это текст для значения по умолчанию,
//в виде строк, ограниченных " " - чтобы триммер строк не съел пробелы в конце.

XItemText::XItemText(XModuleInterface *interf, const XItemPreDescription &pre_description)
    : XItemScalar_<QString>(interf, pre_description)
{

    QString line = pre_description.line_to_parse;
    QStringList query;
    split_spaced(line, name_, query);
    xc_assert(query.size()>=1, "not specified min and max visual lines count, expected '... 10 15'");
    xc_assert(query.size()>=2, "not specified max visual lines count, expected '... 10 15'");

    lines_count_min_ = xparse_int(query.at(0), "min lines count must be an integer, '... 10 15'");
    lines_count_max_ = xparse_int(query.at(1), "max lines count must be an integer, '... 10 15'");

    //устанавливаем значение в значение по умолчанию
    set_value_string(default_value());
}

//---------------------------------------------------------------------
//Function for setting value using link
void XItemText::set_value_from_link(XLinkResolved *linkres) {
    xc_assert(linkres, "set_value_from_link for `" + name() + "` - linkres is nullptr");
    XModule *mod = linkres->module_ptr();
    set_value_string(mod->gets(linkres));
}

//---------------------------------------------------------------------
//графический интерфейс
XGuiComp *XItemText::create_gui(XGuiPageBuilder &page_builder) {
    gui__ = new XGuiText(page_builder, this);
    return gui__;
}

//---------------------------------------------------------------------
//получение значения из gui
void XItemText::gui_to_var_internal() {
    if (gui__) {
        set_value_string(((XGuiText *)gui__)->value());
    }
}

//---------------------------------------------------------------------
//установка значения в gui
void XItemText::var_to_gui_internal() {
    if (gui__) {
        ((XGuiText *)gui__)->set_value(value_string());
    }
}

//---------------------------------------------------------------------
//значение по умолчанию
//это строки описания, начиная со второй. Они с кавычками - поэтому, удаляем их
QString XItemText::default_value() {
    QStringList list;
    for (int i=1; i<description_count(); i++) {
        QString line = description(i);
        if (!line.isEmpty()) {
            //удаляем кавычки
            if (line.startsWith("\"")) {
                line.remove(0,1);
            }
            if (line.endsWith("\"")) {
                line.chop(1);
            }
            list.append(line);
        }
    }
    return list.join("\n");
}

//---------------------------------------------------------------------
//C++
void XItemText::export_interface(QStringList &file) {
    export_interface_template(file, false, true, "Text ", true,
                              "QString ", "s", "gets", "sets",
                              true,
                              false, true);
}

//---------------------------------------------------------------------
