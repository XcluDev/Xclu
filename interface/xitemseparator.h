#ifndef INTERFACEITEMSEPARATOR_H
#define INTERFACEITEMSEPARATOR_H

#include "xitem.h"

class ModuleInterface;

class XItemSeparator: public XItem
{
public:
    XItemSeparator(ModuleInterface *parent, const XItemPreDescription &pre_description);

    //графический интерфейс
    virtual InterfaceGui *create_gui(InterfaceGuiPageCreator &input);

    virtual bool store_data() { return false; }

    //является ли линией или просто вертикальным сепаратором
    bool is_line() { return is_line_; }
    bool is_separator() { return !is_line(); }
protected:
    //копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
    //специальные типы, которые не поддерживают перенос через строку (array и image) - должны переписать copy_data_to_internal
    void copy_data_to_internal(XItem * /*item*/) {}

    bool is_line_ = false;  //является ли линией или просто вертикальным сепаратором
};
#endif // INTERFACEITEMSEPARATOR_H
