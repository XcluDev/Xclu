#ifndef INTERFACEITEMCHECKBOX_H
#define INTERFACEITEMCHECKBOX_H

#include "xitemscalar.h"

class ModuleInterface;

class XItemCheckbox: public XItemScalar_<int>
{
public:
    //parse_range - мы будем ставить false в checkbox
    XItemCheckbox(ModuleInterface *interf, const XItemPreDescription &pre_description);

    //string
    bool supports_string() { return true; }
    QString value_string() { return QString::number(value_int()); }
    void set_value_string(const QString &value) { set_value_int(value.toInt()); }

    //int
    bool supports_int() { return true; }
    int value_int() { return value_read().data(); }
    void set_value_int(int value) { value_write().data() = value; }

    //float
    bool supports_float() { return true; }
    float value_float() { return value_int(); }
    void set_value_float(float f)  { set_value_int(int(f)); }

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageCreator &input);

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


#endif // INTERFACEITEMCHECKBOX_H
