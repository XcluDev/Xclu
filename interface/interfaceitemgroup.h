#ifndef INTERFACEITEMGROUP_H
#define INTERFACEITEMGROUP_H

#include "interfaceitem.h"

class ModuleInterface;

class InterfaceItemGroup: public InterfaceItem
{
public:
    InterfaceItemGroup(ModuleInterface *parent, const InterfaceItemPreDescription &pre_description);

    //Внимание: ставим, что не сохранять значения
    //Когда сделаем сохранение - убрать
    bool store_data() { return false; }

protected:
    //копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
    //специальные типы, которые не поддерживают перенос через строку (array и image) - должны переписать copy_data_to_internal
    void copy_data_to_internal(InterfaceItem * /*item*/ ) {}
};

#endif // INTERFACEITEMGROUP_H
