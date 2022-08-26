#ifndef INTERFACEITEMBUTTON_H
#define INTERFACEITEMBUTTON_H

#include "xitem.h"

class XModuleInterface;

//Button item
//It's not regular int-valued class, so derived from XItem_, not XItemScalarInt
class XItemButton: public XItem_<int>
{
public:
    XItemButton(XModuleInterface *interf, const XItemPreDescription &pre_description);

    //string
    bool supports_string() { return true; }
    QString value_string() { return QString::number(value_int()); }
    void set_value_string(const QString &) {}

    //int
    bool supports_int() { return true; }
    int value_int();    //значение - нажатие считывается один раз, затем стирается
    void set_value_int(int) {}

    void hit_value();  //set that button was pressed
    void reset_value();    //reset that button was pressed

    //float
    bool supports_float() { return true; }
    float value_float() { return value_int(); }
    void set_value_float(float f)  { set_value_int(int(f)); }

    virtual bool store_data() { return false; }

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageBuilder &page_builder);

    //flag that button works always - at edit mode and runtime, not only runtime
    bool is_always_enabled() { return is_always_enabled_; }

    //вызывается из gui при нажатии кнопки
    void callback_button_pressed();

    //called at start, stop and attached interface - used for buttons
    virtual void update_is_running(bool running);

    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------

protected:
    //int value_ = 0; //inside XItem_

    bool is_always_enabled_ = false;   //flag that button works always - at edit mode and runtime, not only runtime

    //Function for setting value using link
    virtual void set_value_from_link(XLinkResolved *linkres);

    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui

    //копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
    //специальные типы, которые не поддерживают перенос через строку (array и image) - должны переписать copy_data_to_internal
    void copy_data_to_internal(XItem * /*item*/ ) {}
};

#endif // INTERFACEITEMBUTTON_H
