#ifndef INTERFACEITEMINT_H
#define INTERFACEITEMINT_H

#include "xitem.h"

class ModuleInterface;

class XItemInt: public XItem_<int>
{
public:
    //parse_range - мы будем ставить false в checkbox
    XItemInt(ModuleInterface *interf, const XItemPreDescription &pre_description, bool parse_range = true);

    bool supports_string() { return true; }
    QString value_string() { return QString::number(value_int()); }
    void set_value_string(const QString &value) { set_value_int(value.toInt()); }

    virtual bool supports_int() { return true; }
    int value_int() { return value_.data()->read().data(); }
    void set_value_int(int value) {}// value_.data()->write().data() = value; }

    int min_value() { return min_value_; }
    int max_value() { return max_value_; }
    int get_small_step() { return slow_step_; }

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageCreator &input);

    //единицы измерения
    QString units() { return units_; }

    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------

protected:
    //int value_ = 0;

    int default_value_ = 0;
    int min_value_ = 0;
    int max_value_ = 1;
    int slow_step_ = 1;
    int fast_step_ = 10;

    QString units_; //опционально - единицы измерения, которые показываются в виде метки справа от числа

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui
};

#endif // INTERFACEITEMINT_H
