#ifndef INTERFACEITEMSTRING_H
#define INTERFACEITEMSTRING_H

#include "interfaceitem.h"

class InterfaceGuiString;

class InterfaceItemString: public InterfaceItem
{
public:
    InterfaceItemString(const InterfaceItemPreDescription &pre_description);

    bool supports_string() { return true; }
    QString value_string() { return value_; }
    void set_value_string(const QString &value) { value_ = value;}

    //графический интерфейс
    virtual InterfaceGui *create_gui(InterfaceGuiPageCreator &input);

    //опциональные элементы
    bool options_choose_filesystem();     //есть ли какие-нибудь опции для файловой системы (file, folder)
    bool options_choose_file();     //кнопка выбора файла
    bool options_choose_folder();   //кнопка выбора папки

protected:
    QString value_;
    QString default_value_;

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui
    //gui_ актуален только в случае is_gui_attached. Не следует его удалять
    InterfaceGuiString *gui_ = nullptr;

    //опциональные элементы
    bool options_choose_file_ = false;     //кнопка выбора файла
    bool options_choose_folder_ = false;   //кнопка выбора папки

};

#endif // INTERFACEITEMSTRING_H
