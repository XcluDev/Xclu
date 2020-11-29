#ifndef INTERFACEITEMINT_H
#define INTERFACEITEMINT_H

#include "xitemscalar.h"

class ModuleInterface;

class XItemInt: public XItemScalarInt
{
public:
    //parse_range - мы будем ставить false в checkbox
    XItemInt(ModuleInterface *interf, const XItemPreDescription &pre_description, bool parse_range = true);

    //increment steps
    int get_small_step();
    int get_large_step();

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageBuilder &page_builder);

    //единицы измерения
    QString units() { return units_; }


    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------

protected:
    //int value_ = 0; //inside XItem_

    int default_value_ = 0;
    int slow_step_ = 1;
    int fast_step_ = 10;

    QString units_; //опционально - единицы измерения, которые показываются в виде метки справа от числа

    //Function for setting value using link
    virtual void set_value_from_link(XLinkResolved *linkres);

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui
};

#endif // INTERFACEITEMINT_H
