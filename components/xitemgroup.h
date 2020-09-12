#ifndef INTERFACEITEMGROUP_H
#define INTERFACEITEMGROUP_H

#include "xitem.h"

class ModuleInterface;

class XItemGroup: public XItem
{
public:
    XItemGroup(ModuleInterface *parent, const XItemPreDescription &pre_description);

    //Внимание: ставим, что не сохранять значения
    //Когда сделаем сохранение - убрать
    bool store_data() { return false; }

    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------


protected:
    //копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
    //специальные типы, которые не поддерживают перенос через строку (array и image) - должны переписать copy_data_to_internal
    void copy_data_to_internal(XItem * /*item*/ ) {}
};

#endif // INTERFACEITEMGROUP_H
