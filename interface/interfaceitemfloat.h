#ifndef INTERFACEITEMFLOAT_H
#define INTERFACEITEMFLOAT_H

#include "interfaceitem.h"

class ModuleInterface;
class InterfaceGuiFloat;

class InterfaceItemFloat: public InterfaceItem
{
public:
    InterfaceItemFloat(ModuleInterface *parent, const InterfaceItemPreDescription &pre_description);

    //string
    bool supports_string() { return true; }
    QString value_string() { return QString::number(value_float()); }
    void set_value_string(const QString &value) { value_ = value.toFloat(); }

    virtual bool supports_float() { return true; }
    float value_float() { return value_; }
    void set_value_float(float value) { value_ = value; }

    float min_value() { return min_value_; }
    float max_value() { return max_value_; }
    float get_small_step();

    //графический интерфейс
    virtual InterfaceGui *create_gui(InterfaceGuiPageCreator &input);

    //единицы измерения
    QString units() { return units_; }
protected:
    float value_ = 0;

    float default_value_ = 0;
    float min_value_ = 0;
    float max_value_ = 1;
    int slow_steps_ = 100;
    int fast_steps_ = 10;

    QString units_; //опционально - единицы измерения, которые показываются в виде метки справа от числа

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui
    //gui_ актуален только в случае is_gui_attached. Не следует его удалять
    InterfaceGuiFloat *gui_ = nullptr;

};

#endif // INTERFACEITEMFLOAT_H
