#include "xitemfloat.h"
#include "incl_cpp.h"
#include "xguifloat.h"
#include "registrarxitem.h"

REGISTER_XITEM(XItemFloat, float)
//---------------------------------------------------------------------
//float Q Q qq=0 0:1 100,10
//      //Length of the object.    описание
//      //mm                       опционально - единица измерения, показывается справа
XItemFloat::XItemFloat(ModuleInterface *interf, const XItemPreDescription &pre_description)
    : XItem(interf, pre_description)
{

    QString line = pre_description.line_to_parse;
    QStringList query;
    split_equal(line, name_, query);
    xclu_assert(query.size()>=3, "not enough components for float, expected '...q=0 0:1 100,10'");

    //значение по умолчанию
    default_value_ = parse_float(query.at(0), "default value must be a number");
    value_ = default_value_;

    //Единицы измерения - вторая строка описания после hint
    units_ = description(1);

    //диапазон
    auto query_range = query.at(1).split(":");
    xclu_assert(query_range.size()==2, "bad range format, expected '... 0:1 ...'");
    min_value_ = parse_float(query_range.at(0), "min value must be a number, expected '... 0:1 ...'");
    max_value_ = parse_float(query_range.at(1), "max value must be a number, expected '... 0:1 ...'");

    //количество шагов слайдера
    auto query_steps = query.at(2).split(",");
    xclu_assert(query_range.size()==2, "bad slider settings, expected '... 100,10'");
    slow_steps_ = parse_int(query_steps.at(0), "number of slow steps must be an integer, expected '... 100,10'");
    fast_steps_ = parse_int(query_steps.at(1), "number of fast steps must be an integer, expected '... 100,10'");

}

//---------------------------------------------------------------------
float XItemFloat::get_small_step() {
    xclu_assert(slow_steps_ > 0, "XItemFloat - bad slow_steps value, must be greater thatn zero");
    return (max_value_ - min_value_) / slow_steps_;

}

//---------------------------------------------------------------------
//графический интерфейс
XGui *XItemFloat::create_gui(XGuiPageCreator &input) {
    gui__ = gui_ = new XGuiFloat(input, this);
    return gui_;
}

//---------------------------------------------------------------------
//получение значения из gui
void XItemFloat::gui_to_var_internal() {
    set_value_float(gui_->value());
}

//---------------------------------------------------------------------
//установка значения в gui
void XItemFloat::var_to_gui_internal() {
    gui_->set_value(value_float());
}

//---------------------------------------------------------------------
//C++
void XItemFloat::export_interface(QStringList &file) {
    export_interface_template(file, false, true, "Float ", true,
                              "float ", "f", "getf", "setf");

}

//---------------------------------------------------------------------
