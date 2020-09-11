#include "xitemint.h"
#include "incl_cpp.h"
#include "interfaceguiint.h"

//---------------------------------------------------------------------
//int A a=-1 -10:10 100,10
//      //Length of the object.    описание
//      //mm                       опционально - единица измерения, показывается справа
XItemInt::XItemInt(ModuleInterface *parent, const XItemPreDescription &pre_description, bool parse_range)
    : XItem(parent, pre_description)
{
    QString line = pre_description.line_to_parse;
    QStringList query;
    split_equal(line, name_, query);
    xclu_assert(query.size()>=1, "no default value, expected '...q=0...'");

    //значение по умолчанию
    default_value_ = parse_int(query.at(0), "default value must be an integer, but is '" + query.at(0) + "'");
    value_ = default_value_;

    //Единицы измерения - вторая строка описания после hint
    units_ = description(1);

    //Диапазон
    if (parse_range) {
        xclu_assert(query.size()>=3, "not enough components for range, expected '...q=0 0:1 1,10'");
        //диапазон
        auto query_range = query.at(1).split(":");
        xclu_assert(query_range.size()==2, "bad range format, expected '... 0:1 ...'");
        min_value_ = parse_int(query_range.at(0), "min value must be an integer, expected '... 0:1 ...'");
        max_value_ = parse_int(query_range.at(1), "max value must be an integer, expected '... 0:1 ...'");

        //количество шагов слайдера
        auto query_steps = query.at(2).split(",");
        xclu_assert(query_range.size()==2, "bad slider settings, expected '... 100,10'");
        slow_step_ = parse_int(query_steps.at(0), "slow step must be an integer, expected '... 1,10'");
        fast_step_ = parse_int(query_steps.at(1), "fast step must be an integer, expected '... 1,10'");

    }
}

//---------------------------------------------------------------------
//графический интерфейс
InterfaceGui *XItemInt::create_gui(InterfaceGuiPageCreator &input) {
    gui__ = gui_ = new InterfaceGuiInt(input, this);
    return gui_;
}

//---------------------------------------------------------------------
//получение значения из gui
void XItemInt::gui_to_var_internal() {
    set_value_int(gui_->value());
}

//---------------------------------------------------------------------
//установка значения в gui
void XItemInt::var_to_gui_internal() {
    gui_->set_value(value_int());
}

//---------------------------------------------------------------------

