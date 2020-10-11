#ifndef INTERFACEGUIINT_H
#define INTERFACEGUIINT_H

#include "xgui.h"

class XItemInt;
class XcluSpinBox;

class XGuiInt : public XGui
{
    Q_OBJECT
public:
    XGuiInt(XGuiPageCreator &input, XItemInt *item);
    ~XGuiInt();

    //значение для проверки видимости детей
    QString value_string_for_visibility() { return QString::number(value()); };

    int value();
    void set_value(int v);

private:
    XcluSpinBox *spin_ = nullptr; //удалять не надо

    //установка режима read_only - для out и блокировки констант при запуске проекта
    void set_read_only_(bool read_only);

};

#endif // INTERFACEGUIINT_H
