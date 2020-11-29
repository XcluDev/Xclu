#include "xitemfloat.h"
#include "incl_cpp.h"
#include "xguifloat.h"
#include "module.h"
#include "registrarxitem.h"

REGISTER_XITEM(XItemFloat, float)
//---------------------------------------------------------------------
//float Q Q qq=0 0:1 100,10
//      //Length of the object.    описание
//      //mm                       опционально - единица измерения, показывается справа
XItemFloat::XItemFloat(ModuleInterface *interf, const XItemPreDescription &pre_description)
    : XItemScalar_<float>(interf, pre_description)
{

    QString line = pre_description.line_to_parse;
    QStringList query;
    split_equal(line, name_, query);
    xclu_assert(query.size()>=3, "not enough components for float, expected '...q=0 0:1 100,10'");

    //значение по умолчанию
    default_value_ = xparse_float(query.at(0), "default value must be a number");
    set_value_float(default_value_);

    //Единицы измерения - вторая строка описания после hint
    units_ = description(1);

    //диапазон
    auto query_range = query.at(1).split(":");
    xclu_assert(query_range.size()==2, "bad range format, expected '... 0:1 ...'");

    range_.setup(query_range.at(0), query_range.at(1));    

    //количество шагов слайдера
    auto query_steps = query.at(2).split(",");
    xclu_assert(query_steps.size()==2, "bad slider settings, expected '... 100,10'");
    slow_step_ = xparse_float(query_steps.at(0), "number of slow steps must be an integer, expected '... 100,10'");
    fast_step_ = xparse_float(query_steps.at(1), "number of fast steps must be an integer, expected '... 100,10'");

}

//---------------------------------------------------------------------
float XItemFloat::get_small_step() {
    xclu_assert(slow_step_ > 0, "XItemFloat `" + name() + "` - bad slow_steps value, must be greater than zero");
    return slow_step_;
}

//---------------------------------------------------------------------
float XItemFloat::get_large_step() {
    xclu_assert(fast_step_ > 0, "XItemFloat `" + name() + "` - bad fast_step_ value, must be greater than zero");
    return fast_step_;
}

//---------------------------------------------------------------------
//Function for setting value using link
void XItemFloat::set_value_from_link(XLinkResolved *linkres) {
    xclu_assert(linkres, "set_value_from_link for `" + name() + "` - linkres is nullptr");
    Module *mod = linkres->module_ptr();
    set_value_float(mod->getf(linkres));
}

//---------------------------------------------------------------------
//графический интерфейс
XGui *XItemFloat::create_gui(XGuiPageBuilder &page_builder) {
    gui__ = new XGuiFloat(input, this);
    return gui__;
}

//---------------------------------------------------------------------
//получение значения из gui
void XItemFloat::gui_to_var_internal() {
    set_value_float(((XGuiFloat *)gui__)->value());
}

//---------------------------------------------------------------------
//установка значения в gui
void XItemFloat::var_to_gui_internal() {
    ((XGuiFloat *)gui__)->set_value(value_float());
}

//---------------------------------------------------------------------
//C++
void XItemFloat::export_interface(QStringList &file) {
    export_interface_template(file, false, true, "Float ", true,
                              "float ", "f", "getf", "setf");

}

//---------------------------------------------------------------------
