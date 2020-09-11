#ifndef INTERFACEGUICHECKBOX_H
#define INTERFACEGUICHECKBOX_H

#include "interfacegui.h"

class XItemCheckbox;
class QCheckBox;

class InterfaceGuiCheckbox : public InterfaceGui
{
    Q_OBJECT
public:
    InterfaceGuiCheckbox(InterfaceGuiPageCreator &input, XItemCheckbox *item);
    ~InterfaceGuiCheckbox();

    //значение для проверки видимости детей
    QString value_string_for_visibility() { return QString::number(value()); };

    int value();
    void set_value(int v);

protected:
    //установка режима read_only - для out и блокировки констант при запуске проекта
    void set_read_only(bool read_only);


private:
    QCheckBox *checkbox_ = nullptr; //удалять не надо

};

#endif // INTERFACEGUICHECKBOX_H
