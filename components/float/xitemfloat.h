#ifndef INTERFACEITEMFLOAT_H
#define INTERFACEITEMFLOAT_H

#include "xitemscalar.h"

class ModuleInterface;

class XItemFloat: public XItemScalar_<float>
{
public:
    XItemFloat(ModuleInterface *interf, const XItemPreDescription &pre_description);

    //string
    bool supports_string() { return true; }
    QString value_string() { return QString::number(value_float()); }
    void set_value_string(const QString &value) { set_value_float(value.toFloat()); }

    bool supports_int() { return true; }
    int value_int() { return int(value_float()); }
    void set_value_int(int v) { set_value_float(v); }

    bool supports_float() { return true; }
    float value_float() { return value_read().data(); }
    void set_value_float(float value) { value_write().data() = value; }

    float min_value() { return min_value_; }
    float max_value() { return max_value_; }
    float get_small_step();

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageCreator &input);

    //единицы измерения
    QString units() { return units_; }

    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------

protected:
    //float value_ = 0; //inside XItem_

    float default_value_ = 0;
    float min_value_ = 0;
    float max_value_ = 1;
    int slow_steps_ = 100;
    int fast_steps_ = 10;

    QString units_; //опционально - единицы измерения, которые показываются в виде метки справа от числа

    //Function for setting value using link
    virtual void set_value_from_link(XLinkResolved *linkres);

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui
};

#endif // INTERFACEITEMFLOAT_H
