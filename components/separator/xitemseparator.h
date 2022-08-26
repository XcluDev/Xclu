#ifndef INTERFACEITEMSEPARATOR_H
#define INTERFACEITEMSEPARATOR_H

#include "xitem.h"

class XModuleInterface;

class XItemSeparator: public XItem
{
public:
    XItemSeparator(XModuleInterface *interf, const XItemPreDescription &pre_description);

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageBuilder &page_builder);

    virtual bool store_data() { return false; }

    //является ли линией или просто вертикальным сепаратором
    bool is_line() { return is_line_; }
    bool is_separator() { return !is_line(); }

    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------

protected:
    //копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
    //специальные типы, которые не поддерживают перенос через строку (array и image) - должны переписать copy_data_to_internal
    void copy_data_to_internal(XItem * /*item*/) {}

    bool is_line_ = false;  //является ли линией или просто вертикальным сепаратором
};
#endif // INTERFACEITEMSEPARATOR_H
