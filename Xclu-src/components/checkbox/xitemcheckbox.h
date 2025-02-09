#pragma once

#include "xitemscalar.h"

class XModuleInterface;

class XItemCheckbox: public XItemScalarInt
{
public:
    //parse_range - мы будем ставить false в checkbox
    XItemCheckbox(XModuleInterface *interf, const XItemPreDescription &pre_description);

    //графический интерфейс
    virtual XGuiComp *create_gui(XGuiPageBuilder &page_builder);

    //это "групповой" чекбокс, который нужно показывать слева, без label, и справа от которого идет линия
    bool is_group_checkbox() { return is_group_checkbox_; }

    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------

protected:
    //int value_ = 0; //inside XItem_
    int default_value_ = 0;

    //Function for setting value using link
    virtual void set_value_from_link(XLinkResolved *linkres);

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui

    bool is_group_checkbox_ = false;    //"групповой" чекбокс, который нужно показывать слева, без label
};
