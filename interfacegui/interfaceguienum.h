#ifndef INTERFACEGUISTRINGLIST_H
#define INTERFACEGUISTRINGLIST_H

#include "interfacegui.h"

class InterfaceItemStringlist;
class XcluComboBox;

class InterfaceGuiStringlist : public InterfaceGui
{
    Q_OBJECT
public:
    InterfaceGuiStringlist(InterfaceGuiPageCreator &input, InterfaceItemStringlist *item);
    ~InterfaceGuiStringlist();

    //значение для проверки видимости детей
    QString value_string_for_visibility();

    int index();
    void set_index(int v);

protected:
     XcluComboBox *combo_ = nullptr;
     QStringList names_;

     //установка режима read_only - для out и блокировки констант при запуске проекта
     void set_read_only(bool read_only);

};

#endif // INTERFACEGUISTRINGLIST_H
