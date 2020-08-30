#include "interfaceitemstring.h"
#include "incl_cpp.h"
#include "interfaceguistring.h"

//---------------------------------------------------------------------
//Строка
//in string Name name="aa"
//
//Строка с кнопкой для выбора файла
// in string(choose:file) Name name="aa"
//   //File to load - обычное описание
//   //Choose a file - заголовок окна
//   //All files (*.*);;Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml) - фильтр

//Строка с кнопкой для выбора папки
//  in string(choose:folder) Choose_Folder choose_Folder="aa"
//  //Folder to scan - обычное описание
//  //Choose a file - заголовок окна

//Выбор переменной из другого модуля
//... string(choose:int)
//... string(choose:object)
//...string(choose:object:image)
//Например: in string(choose:int) Int_Link int_link="module1->value"



InterfaceItemString::InterfaceItemString(ModuleInterface *parent, const InterfaceItemPreDescription &pre_description)
    : InterfaceItem(parent, pre_description)
{

    QString line = pre_description.line_to_parse;
    QStringList query;
    split_equal(line, name_, query);
    xclu_assert(query.size()>=1, "not enough components for string, expected '...q=\"abc\"'");

    //значение по умолчанию
    default_value_ = query.at(0);
    //проверяем, что начало и конец - двойные кавычки
    xclu_assert(!default_value_.isEmpty(), "default value is not filled, but must start and end with '\"', '...\"\"'");
    xclu_assert(default_value_.startsWith("\"") && default_value_.endsWith("\""), "default value must start and end with '\"', '...\"\"',"
                                                                                  "but is `" + default_value_ + "'");
    //удаляем кавычки в начале и конце
    default_value_ = default_value_.mid(1);
    default_value_.chop(1);

    value_ = default_value_;

    //опции
    QString options = pre_description.options;
    if (!options.isEmpty()) {
        //опции выбора файла и папки нельзя применять в случае, если переменная 'out'
        xclu_assert(!is_out(), "Can't apply options for 'out'");

        options_choose_file_ = (options == "choose:file");
        options_choose_folder_ = (options == "choose:folder");
        //какая-то из опций должна быть включена, если переданы не пустые
        //xclu_assert(options_, "Unknown option, expected 'in string(choose:file)...' or 'in string(choose:folder)...', or not use options: 'in string ...'");
    }
}

//---------------------------------------------------------------------
//графический интерфейс
InterfaceGui *InterfaceItemString::create_gui(InterfaceGuiPageCreator &input) {
    gui__ = gui_ = new InterfaceGuiString(input, this);
    return gui_;
}

//---------------------------------------------------------------------
//получение значения из gui
void InterfaceItemString::gui_to_var_internal() {
    set_value_string(gui_->value());
}

//---------------------------------------------------------------------
//установка значения в gui
void InterfaceItemString::var_to_gui_internal() {
    gui_->set_value(value_string());
}

//---------------------------------------------------------------------
//опциональные элементы
bool InterfaceItemString::options_choose_filesystem() {                 //есть ли какие-нибудь опции
    return options_choose_file() || options_choose_folder();
}

//---------------------------------------------------------------------
bool InterfaceItemString::options_choose_file() {     //кнопка выбора файла
    return options_choose_file_;
}

//---------------------------------------------------------------------
bool InterfaceItemString::options_choose_folder() {   //кнопка выбора папки
    return options_choose_folder_;
}

//---------------------------------------------------------------------
