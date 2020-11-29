#ifndef INTERFACEITEMSTRING_H
#define INTERFACEITEMSTRING_H

#include "xitemscalar.h"

class ModuleInterface;

class XItemString: public XItemScalar_<QString>
{
public:
    XItemString(ModuleInterface *interf, const XItemPreDescription &pre_description);

    bool supports_string() { return true; }
    QString value_string() { return value_read().data(); }
    void set_value_string(const QString &value) { value_write().data() = value; }

    bool supports_int() { return true; }
    int value_int() { return value_string().toInt(); }
    void set_value_int(int v) { set_value_string(QString::number(v)); }

    bool supports_float() { return true; }
    float value_float() { return value_string().toFloat(); }
    void set_value_float(float value) { set_value_string(QString::number(value)); }

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageBuilder &page_builder);

    //опциональные элементы
    bool options_choose_filesystem();     //есть ли какие-нибудь опции для файловой системы (file, folder)
    bool options_choose_file();     //кнопка выбора файла
    bool options_choose_folder();   //кнопка выбора папки

    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------

protected:
    QString default_value_;

    //Function for setting value using link
    virtual void set_value_from_link(XLinkResolved *linkres);

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui

    //опциональные элементы
    bool options_choose_file_ = false;     //кнопка выбора файла
    bool options_choose_folder_ = false;   //кнопка выбора папки

};

#endif // INTERFACEITEMSTRING_H
