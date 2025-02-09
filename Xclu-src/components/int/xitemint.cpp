#include "xitemint.h"
#include "incl_cpp.h"
#include "xguiint.h"
#include "xmodule.h"
#include "registrarxitem.h"

REGISTER_XITEM(XItemInt, int)
//---------------------------------------------------------------------
//int A a=-1 -10:10 100,10
//      //Length of the object.    описание
//      //mm                       опционально - единица измерения, показывается справа
XItemInt::XItemInt(XModuleInterface *interf, const XItemPreDescription &pre_description, bool parse_range)
    : XItemScalarInt(interf, pre_description)
{    
    QString line = pre_description.line_to_parse;
    QStringList query;
    split_equal(line, name_, query);
    xc_assert(query.size()>=1, "no default value, expected '...q=0...'");

    //значение по умолчанию
    default_value_ = xparse_int(query.at(0), "default value must be an integer, but is '" + query.at(0) + "'");
    set_value_int(default_value_);

    //Единицы измерения - вторая строка описания после hint
    units_ = description(1);

    //Range setup
    if (parse_range) {
        xc_assert(query.size()>=3, "not enough components for range, expected '...q=0 0:1 1,10'");
        //диапазон
        auto query_range = query.at(1).split(":");
        xc_assert(query_range.size()==2, "bad range format, expected '... 0:1 ...'");

        range_.setup(query_range.at(0), query_range.at(1));

        //количество шагов слайдера
        auto query_steps = query.at(2).split(",");
        xc_assert(query_range.size()==2, "bad slider settings, expected '... 100,10'");
        slow_step_ = xparse_int(query_steps.at(0), "slow step must be an integer, expected '... 1,10'");
        fast_step_ = xparse_int(query_steps.at(1), "fast step must be an integer, expected '... 1,10'");

    }
}

//---------------------------------------------------------------------
int XItemInt::get_small_step() {
    xc_assert(slow_step_ > 0, "XItemInt `" + name() + "` - bad slow_steps value, must be greater than zero");
    return slow_step_;
}

//---------------------------------------------------------------------
int XItemInt::get_large_step() {
    xc_assert(fast_step_ > 0, "XItemInt `" + name() + "` - bad fast_step_ value, must be greater than zero");
    return fast_step_;
}

//---------------------------------------------------------------------
//Function for setting value using link
void XItemInt::set_value_from_link(XLinkResolved *linkres) {
    xc_assert(linkres, "set_value_from_link for `" + name() + "` - linkres is nullptr");
    XModule *mod = linkres->module_ptr();
    set_value_int(mod->geti(linkres));
}

//---------------------------------------------------------------------
//графический интерфейс
XGuiComp *XItemInt::create_gui(XGuiPageBuilder &page_builder) {
    gui__ = new XGuiInt(page_builder, this);
    return gui__;
}

//---------------------------------------------------------------------
//получение значения из gui
void XItemInt::gui_to_var_internal() {
    set_value_int(((XGuiInt *)gui__)->value());
}

//---------------------------------------------------------------------
//установка значения в gui
void XItemInt::var_to_gui_internal() {
    ((XGuiInt *)gui__)->set_value(value_int());
}


//---------------------------------------------------------------------
//C++
void XItemInt::export_interface(QStringList &file) {
    export_interface_template(file, false, true, "Int ", true,
                              "int ", "i", "geti", "seti",
                              true,
                              true, false);
}

//---------------------------------------------------------------------

