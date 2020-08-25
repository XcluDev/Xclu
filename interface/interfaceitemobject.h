#ifndef INTERFACEITEMOBJECT_H
#define INTERFACEITEMOBJECT_H

//Объект

#include "interfaceitem.h"
#include "xcluobject.h"
#include <QScopedPointer>

class ModuleInterface;
class InterfaceGuiObject;

class InterfaceItemObject: public InterfaceItem
{
public:
    //parse_range - мы будем ставить false в checkbox
    InterfaceItemObject(ModuleInterface *parent, const InterfaceItemPreDescription &pre_description);
    //~InterfaceItemObject();

    //не поддерживаем скаляры, но будем записывать настройки в строку
    bool supports_string() { return true; }
    QString value_string() { return ""; }
    void set_value_string(const QString & /*value*/) {}

    bool supports_int() { return false; }

    //доступ к объекту
    virtual bool supports_object() { return true; }
    virtual XcluObject *get_object() { return object_.data(); }

    //графический интерфейс
    virtual InterfaceGui *create_gui(InterfaceGuiPageCreator &input);

protected:
    QScopedPointer<XcluObject> object_;

    QStringList types_; //список типов, которыми может быть этот объект, например, image, array

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui
    //gui_ актуален только в случае is_gui_attached. Не следует его удалять
    InterfaceGuiObject *gui_ = nullptr;

    //копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
    //специальные типы, которые не поддерживают перенос через строку (array и image) - должны переписать copy_data_to_internal
    virtual void copy_data_to_internal(InterfaceItem *item);
};


#endif // INTERFACEITEMOBJECT_H
