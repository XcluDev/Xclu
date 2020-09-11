#ifndef INTERFACEITEMPAGE_H
#define INTERFACEITEMPAGE_H

#include "xitem.h"

class ModuleInterface;
class XGuiPage;

class XItemPage: public XItem
{
public:
    XItemPage(ModuleInterface *parent, const XItemPreDescription &pre_description);

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageCreator &input);

    bool supports_string() { return true; }
    QString value_string() { return QString().setNum(scroll_); }
    void set_from_string(const QString &value) { scroll_ = value.toInt(); }

    //не делаем поддержку int, так как это чисто интерфейсный элемент

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui

    //gui_ актуален только в случае is_gui_attached. Не следует его удалять
    XGuiPage *gui_ = nullptr;

    //значение scroll
    int scroll_ = 0;

    //копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
    //специальные типы, которые не поддерживают перенос через строку (array и image) - должны переписать copy_data_to_internal
    void copy_data_to_internal(XItem * /*item*/) {}
};

#endif // INTERFACEITEMPAGE_H
