#ifndef INTERFACEGUIFLOAT_H
#define INTERFACEGUIFLOAT_H

#include "xgui.h"

class XItemFloat;
class XcluDoubleSpinBox;

class XGuiFloat : public XGui
{
    Q_OBJECT
public:
    XGuiFloat(XGuiPageCreator &input, XItemFloat *item);
    ~XGuiFloat();

    //значение для проверки видимости детей
    QString value_string_for_visibility() { return QString::number(value()); };

    float value();
    void set_value(float v);
protected:
    XcluDoubleSpinBox *spin_ = nullptr;

    //установка режима read_only - для out и блокировки констант при запуске проекта
    void set_read_only_(bool read_only);

};

#endif // INTERFACEGUIFLOAT_H
