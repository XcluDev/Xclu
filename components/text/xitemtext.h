#ifndef INTERFACEITEMTEXT_H
#define INTERFACEITEMTEXT_H

#include "xitemscalar.h"

class ModuleInterface;

class XItemText: public XItemScalar_<QString>
{
public:
    XItemText(ModuleInterface *interf, const XItemPreDescription &pre_description);

    bool supports_string() { return true; }
    QString value_string() { return value_read().data(); }
    void set_value_string(const QString &value) { value_write().data() = value; }

    bool supports_int() { return true; }
    int value_int() { return value_string().toInt(); }
    void set_value_int(int v) { set_value_string(QString::number(v)); }

    bool supports_float() { return true; }
    float value_float() { return value_string().toFloat(); }
    void set_value_float(float value) { set_value_string(QString::number(value)); }

    //значение по умолчаию
    QString default_value();

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageCreator &input);
    int lines_count_min() { return lines_count_min_; }
    int lines_count_max() { return lines_count_max_; }

    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------

protected:
    //QString value_;

    int lines_count_min_ = 1;
    int lines_count_max_ = 1;

    //Function for setting value using link
    virtual void set_value_from_link(XLinkResolved *linkres);

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui

};

#endif // INTERFACEITEMTEXT_H
