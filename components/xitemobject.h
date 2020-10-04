#ifndef INTERFACEITEMOBJECT_H
#define INTERFACEITEMOBJECT_H

//Объект

#include "xitem.h"
#include "xstruct.h"
#include <QScopedPointer>

class ModuleInterface;

class XItemObject: public XItem_<XStruct>
{
public:
    //parse_range - мы будем ставить false в checkbox
    XItemObject(ModuleInterface *interf, const XItemPreDescription &pre_description);
    //~XItemObject();

    //не поддерживаем скаляры, но будем записывать настройки в строку
    bool supports_string() { return true; }
    QString value_string() { return ""; }
    void set_value_string(const QString & /*value*/) {}

    bool supports_int() { return false; }

    //доступ к объекту
    virtual bool supports_object() { return true; }
    virtual XProtectedStruct *get_object() { return value_.data(); }

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageCreator &input);

    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------

protected:
    //QScopedPointer<XStruct> object_; //inside XItem_

    QStringList types_; //список типов, которыми может быть этот объект, например, image, array

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui

    //копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
    //специальные типы, которые не поддерживают перенос через строку (array и image) - должны переписать copy_data_to_internal
    virtual void copy_data_to_internal(XItem *item);
};


#endif // INTERFACEITEMOBJECT_H
