#ifndef INTERFACEITEMBUTTON_H
#define INTERFACEITEMBUTTON_H

#include "xitem.h"

class ModuleInterface;
class InterfaceGuiButton;

class XItemButton: public XItem
{
public:
    XItemButton(ModuleInterface *parent, const XItemPreDescription &pre_description);

    //string
    bool supports_string() { return true; }
    QString value_string() { return QString::number(value_int()); }
    void set_value_string(const QString &) {}

    //int
    bool supports_int() { return true; }
    int value_int();    //значение - нажатие считывается один раз, затем стирается
    void set_value_int(int) {}

    virtual bool store_data() { return false; }

    //графический интерфейс
    virtual InterfaceGui *create_gui(InterfaceGuiPageCreator &input);

    //вызывается из gui при нажатии кнопки
    void callback_button_pressed();

protected:
    int value_ = 0;

    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui
    //gui_ актуален только в случае is_gui_attached. Не следует его удалять
    InterfaceGuiButton *gui_ = nullptr;

    //копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
    //специальные типы, которые не поддерживают перенос через строку (array и image) - должны переписать copy_data_to_internal
    void copy_data_to_internal(XItem * /*item*/ ) {}
};

#endif // INTERFACEITEMBUTTON_H
