#ifndef INTERFACEITEMOBJECT_H
#define INTERFACEITEMOBJECT_H

//Object
//Note, it doesn't store object's value, but only pointer

#include "xitem.h"
#include "xobject.h"
#include <QScopedPointer>
#include "xpointer.h"

class ModuleInterface;

class XItemObject: public XItem
{
public:
    //parse_range - мы будем ставить false в checkbox
    XItemObject(ModuleInterface *interf, const XItemPreDescription &pre_description);
    //virtual ~XItemObject();

    //не поддерживаем скаляры, но будем записывать настройки в строку
    bool supports_string() { return true; }
    QString value_string() { return ""; }
    void set_value_string(const QString & /*value*/) {}

    bool supports_int() { return false; }

    virtual bool supports_object() { return true; }
    virtual XProtectedObject *get_object() { return value_.pointer(); }
    virtual void set_object(XProtectedObject *object) { value_.set_pointer(object); }

    //changes control
    virtual bool was_changed(XWasChangedChecker &checker);

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageBuilder &page_builder);

    //Context menu ----------------
    //Objects have size in GUI editor!
    virtual bool context_menu_has_set_size() { return true; }

    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------


protected:
    XPointer<XObject> value_;
    XProtectedObject default_;

    //Function for setting value using link
    virtual void set_value_from_link(XLinkResolved *linkres);

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui

    //копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
    //специальные типы, которые не поддерживают перенос через строку (array и image) - должны переписать copy_data_to_internal
    virtual void copy_data_to_internal(XItem *item);
};


#endif // INTERFACEITEMOBJECT_H
