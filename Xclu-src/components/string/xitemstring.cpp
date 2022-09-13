#include "xitemstring.h"
#include "incl_cpp.h"
#include "xguistring.h"
#include "xmodule.h"
#include "registrarxitem.h"

REGISTER_XITEM(XItemString, string)
//---------------------------------------------------------------------
//Строка
//in string Name name="aa bb"
//   This is object name   - описание
//
//значение по умолчанию может содержать пробелы и кавычки - просто убираются первая и последняя.
//
//Строка с кнопкой для выбора файла
// in string_file Name name="aa"
//   //File to load - обычное описание
//   //Choose a file - заголовок окна
//   //All files (*.*);;Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml) - фильтр

//Строка с кнопкой для выбора папки
//  in string_folder Choose_Folder choose_Folder="aa"
//  //Folder to scan - обычное описание
//  //Choose a file - заголовок окна

//(не реализовано) Выбор переменной из другого модуля
//... string_int
//... string_object
//...string_image
//Например: in string_int Int_Link int_link="module1->value"



XItemString::XItemString(XModuleInterface *interf, const XItemPreDescription &pre_description)
    : XItemScalar_<QString>(interf, pre_description)
{

    QString line = pre_description.line_to_parse;
    QStringList query;
    split_equal(line, name_, query);
    xc_assert(query.size()>=1, "not enough components for string, expected '...q=\"abc\"'");

    //значение по умолчанию
    default_value_ = query.at(0);
    //проверяем, что начало и конец - двойные кавычки
    xc_assert(!default_value_.isEmpty(), "default value is not filled, but must start and end with '\"', '...\"\"'");
    xc_assert(default_value_.startsWith("\"") && default_value_.endsWith("\""), "default value must start and end with '\"', '...\"\"',"
                                                                                  "but is `" + default_value_ + "'");
    //удаляем кавычки в начале и конце
    default_value_ = default_value_.mid(1);
    default_value_.chop(1);

    set_value_string(default_value_);

    //опции
    QString options = pre_description.options;
    if (!options.isEmpty()) {
        //опции выбора файла и папки нельзя применять в случае, если переменная 'out'
        xc_assert(!is_out(), "Can't apply options for 'out'");

        options_choose_file_ = (options == "file");
        options_choose_folder_ = (options == "folder");
        //какая-то из опций должна быть включена, если переданы не пустые
        //xc_assert(options_, "Unknown option, expected 'in string(choose:file)...' or 'in string(choose:folder)...', or not use options: 'in string ...'");
    }
}

//---------------------------------------------------------------------
//Function for setting value using link
void XItemString::set_value_from_link(XLinkResolved *linkres) {
    xc_assert(linkres, "set_value_from_link for `" + name() + "` - linkres is nullptr");
    XModule *mod = linkres->module_ptr();
    set_value_string(mod->gets(linkres));
}

//---------------------------------------------------------------------
//графический интерфейс
XGuiComp *XItemString::create_gui(XGuiPageBuilder &page_builder) {
    gui__ = new XGuiString(page_builder, this);
    return gui__;
}

//---------------------------------------------------------------------
//получение значения из gui
void XItemString::gui_to_var_internal() {
    set_value_string(((XGuiString *)gui__)->value());
}

//---------------------------------------------------------------------
//установка значения в gui
void XItemString::var_to_gui_internal() {
    ((XGuiString *)gui__)->set_value(value_string());
}

//---------------------------------------------------------------------
//опциональные элементы
bool XItemString::options_choose_filesystem() {                 //есть ли какие-нибудь опции
    return options_choose_file() || options_choose_folder();
}

//---------------------------------------------------------------------
bool XItemString::options_choose_file() {     //кнопка выбора файла
    return options_choose_file_;
}

//---------------------------------------------------------------------
bool XItemString::options_choose_folder() {   //кнопка выбора папки
    return options_choose_folder_;
}

//---------------------------------------------------------------------
//C++
void XItemString::export_interface(QStringList &file) {
    export_interface_template(file, false, true, "String ", true,
                              "QString ", "s", "gets", "sets",
                              true,
                              false, true);
}

//---------------------------------------------------------------------
