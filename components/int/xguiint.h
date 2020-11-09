#ifndef INTERFACEGUIINT_H
#define INTERFACEGUIINT_H

#include "xgui.h"
#include "xrange.h"

class XItemInt;
class XcluSpinBox;
class QSlider;

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
    XcluSpinBox *spin_ = nullptr;
    QSlider *slider_ = nullptr;
    XRangeInt range_;

    //установка режима read_only - для out и блокировки констант при запуске проекта
    void set_read_only_(bool read_only);

    //own implementation of value change event to change slider
    virtual void on_value_changed();

protected slots:
    void on_slider_changed(int v);
protected:
    bool during_changing_ = false;

};

#endif // INTERFACEGUIINT_H
