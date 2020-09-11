#ifndef INTERFACEITEMCHECKBOX_H
#define INTERFACEITEMCHECKBOX_H

#include "xitem.h"

class ModuleInterface;
class XGuiCheckbox;

class XItemCheckbox: public XItem
{
public:
    //parse_range - мы будем ставить false в checkbox
    XItemCheckbox(ModuleInterface *parent, const XItemPreDescription &pre_description);

    //string
    bool supports_string() { return true; }
    QString value_string() { return QString::number(value_int()); }
    void set_value_string(const QString &value) { value_ = value.toInt(); }

    //int
    bool supports_int() { return true; }
    int value_int() { return value_; }
    void set_value_int(int value) { value_ = value; }

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageCreator &input);

    //это "групповой" чекбокс, который нужно показывать слева, без label, и справа от которого идет линия
    bool is_group_checkbox() { return is_group_checkbox_; }

protected:
    int value_ = 0;
    float default_value_ = 0;

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui
    //gui_ актуален только в случае is_gui_attached. Не следует его удалять
    XGuiCheckbox *gui_ = nullptr;

    bool is_group_checkbox_ = false;    //"групповой" чекбокс, который нужно показывать слева, без label
};


#endif // INTERFACEITEMCHECKBOX_H
