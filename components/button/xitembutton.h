#ifndef INTERFACEITEMBUTTON_H
#define INTERFACEITEMBUTTON_H

#include "xitem.h"

class ModuleInterface;

class XItemButton: public XItem_<int>
{
public:
    XItemButton(ModuleInterface *interf, const XItemPreDescription &pre_description);

    //string
    bool supports_string() { return true; }
    QString value_string() { return QString::number(value_int()); }
    void set_value_string(const QString &) {}

    //int
    bool supports_int() { return true; }
    int value_int();    //значение - нажатие считывается один раз, затем стирается
    void set_value_int(int) {}

    //float
    bool supports_float() { return true; }
    float value_float() { return value_int(); }
    void set_value_float(float f)  { set_value_int(int(f)); }

    virtual bool store_data() { return false; }

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageCreator &input);

    //вызывается из gui при нажатии кнопки
    void callback_button_pressed();

    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------

protected:
    //int value_ = 0; //inside XItem_

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
