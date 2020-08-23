#ifndef INTERFACEGUIENUM_H
#define INTERFACEGUIENUM_H

#include "interfacegui.h"

class InterfaceItemEnum;
class XcluComboBox;

class InterfaceGuiEnum : public InterfaceGui
{
    Q_OBJECT
public:
    InterfaceGuiEnum(InterfaceGuiPageCreator &input, InterfaceItemEnum *item);
    ~InterfaceGuiEnum();

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

#endif // INTERFACEGUIENUM_H
