#include "interfaceitemcheckbox.h"
#include "interfaceguicheckbox.h"
#include "incl_qtcpp.h"

//---------------------------------------------------------------------
//in checkbox Active active=0
//      //Length of the object.    описание

//in checkbox(group) Details show_details=0
//- показ чеббокса слева, для обозначения группы элементов GUI, и еще справа строка

InterfaceItemCheckbox::InterfaceItemCheckbox(const InterfaceItemPreDescription &pre_description)
    : InterfaceItem(pre_description)
{
    QString line = pre_description.line_to_parse;
    QStringList query;
    split_equal(line, name_, query);
    xclu_assert(query.size()>=1, "no default value, expected '...q=0...'");

    //опции - "групповой" чекбокс
    QString options = pre_description.options;
    if (!options.isEmpty()) {
        //является ли "групповым"
        is_group_checkbox_ = (options == "group");
        //какая-то из опций должна быть включена, если переданы не пустые
        xclu_assert(is_group_checkbox_, "Unknown option, expected '... checkbox(group)...'");
    }

    //значение по умолчанию
    default_value_ = parse_int(query.at(0), "default value must be an integer, but is '" + query.at(0) + "'");
    value_ = default_value_;

}

//---------------------------------------------------------------------
//графический интерфейс
InterfaceGui *InterfaceItemCheckbox::create_gui(InterfaceGuiPageCreator &input) {
    gui__ = gui_ = new InterfaceGuiCheckbox(input, this);
    return gui_;
}

//---------------------------------------------------------------------
//получение значения из gui
void InterfaceItemCheckbox::gui_to_var_internal() {
    set_value_int(gui_->value());
}

//---------------------------------------------------------------------
//установка значения в gui
void InterfaceItemCheckbox::var_to_gui_internal() {
    gui_->set_value(value_int());
}

//---------------------------------------------------------------------
