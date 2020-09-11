#ifndef INTERFACEGUIINT_H
#define INTERFACEGUIINT_H

#include "interfacegui.h"

class XItemInt;
class XcluSpinBox;

class InterfaceGuiInt : public InterfaceGui
{
    Q_OBJECT
public:
    InterfaceGuiInt(InterfaceGuiPageCreator &input, XItemInt *item);
    ~InterfaceGuiInt();

    //значение для проверки видимости детей
    QString value_string_for_visibility() { return QString::number(value()); };

    int value();
    void set_value(int v);

private:
    XcluSpinBox *spin_ = nullptr; //удалять не надо

    //установка режима read_only - для out и блокировки констант при запуске проекта
    void set_read_only(bool read_only);

};

#endif // INTERFACEGUIINT_H
