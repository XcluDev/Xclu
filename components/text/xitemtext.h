#ifndef INTERFACEITEMTEXT_H
#define INTERFACEITEMTEXT_H

#include "xitem.h"

class ModuleInterface;

class XItemText: public XItem
{
public:
    XItemText(ModuleInterface *interf, const XItemPreDescription &pre_description);

    bool supports_string() { return true; }
    QString value_string() { return value_; }
    void set_value_string(const QString &value) { value_ = value; }


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
    QString value_;

    int lines_count_min_ = 1;
    int lines_count_max_ = 1;

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui

};

#endif // INTERFACEITEMTEXT_H