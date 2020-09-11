#ifndef INTERFACEGUIBUTTON_H
#define INTERFACEGUIBUTTON_H

#include "interfacegui.h"

class XItemButton;
class QPushButton;

class InterfaceGuiButton : public InterfaceGui
{
    Q_OBJECT
public:
    InterfaceGuiButton(InterfaceGuiPageCreator &input, XItemButton *item);
    ~InterfaceGuiButton();

    //значение - нажатие считывается один раз, затем стирается
    int value();

protected:
    QPushButton *button_ = nullptr;
    int value_ = 0;

protected slots:
    void button_pressed();
};

#endif // INTERFACEGUIBUTTON_H
