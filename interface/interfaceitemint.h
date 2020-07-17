#ifndef INTERFACEITEMINT_H
#define INTERFACEITEMINT_H

#include "interfaceitem.h"

class InterfaceGuiInt;

class InterfaceItemInt: public InterfaceItem
{
public:
    //parse_range - мы будем ставить false в checkbox
    InterfaceItemInt(const InterfaceItemPreDescription &pre_description, bool parse_range = true);

    bool supports_string() { return true; }
    QString value_string() { return QString::number(value_int()); }
    void set_value_string(const QString &value) { value_ = value.toInt(); }

    virtual bool supports_int() { return true; }
    int value_int() { return value_; }
    void set_value_int(int value) { value_ = value; }

    int min_value() { return min_value_; }
    int max_value() { return max_value_; }

    //графический интерфейс
    virtual InterfaceGui *create_gui(InterfaceGuiPageCreator &input);

    //единицы измерения
    QString units() { return units_; }

protected:
    int value_ = 0;

    float default_value_ = 0;
    float min_value_ = 0;
    float max_value_ = 1;
    int slow_step_ = 1;
    int fast_step_ = 10;

    QString units_; //опционально - единицы измерения, которые показываются в виде метки справа от числа

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui
    //gui_ актуален только в случае is_gui_attached. Не следует его удалять
    InterfaceGuiInt *gui_ = nullptr;

};

#endif // INTERFACEITEMINT_H
