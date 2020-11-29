#ifndef INTERFACEGUIFLOAT_H
#define INTERFACEGUIFLOAT_H

#include "xgui.h"
#include "xrange.h"

class XItemFloat;
class XcluDoubleSpinBox;
class QSlider;

class XGuiFloat : public XGui
{
    Q_OBJECT
public:
    XGuiFloat(XGuiPageBuilder &page_builder, XItemFloat *item);
    ~XGuiFloat();

    //значение для проверки видимости детей
    QString value_string_for_visibility() { return QString::number(value()); };

    float value();
    void set_value(float v);
protected:
    XcluDoubleSpinBox *spin_ = nullptr;
    QSlider *slider_ = nullptr;
    XRangeFloat range_;

    //number of ticks for slider, without zero tick, so really there are ticks_ + 1
    int ticks_ = 0;

    //установка режима read_only - для out и блокировки констант при запуске проекта
    void set_read_only_(bool read_only);

    //own implementation of value change event to change slider
    virtual void on_value_changed();

protected slots:
    void on_slider_changed(int v);
protected:
    bool during_changing_ = false;

};

#endif // INTERFACEGUIFLOAT_H
