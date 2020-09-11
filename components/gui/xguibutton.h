#ifndef INTERFACEGUIBUTTON_H
#define INTERFACEGUIBUTTON_H

#include "xgui.h"

class XItemButton;
class QPushButton;

class XGuiButton : public XGui
{
    Q_OBJECT
public:
    XGuiButton(XGuiPageCreator &input, XItemButton *item);
    ~XGuiButton();

    //значение - нажатие считывается один раз, затем стирается
    int value();

protected:
    QPushButton *button_ = nullptr;
    int value_ = 0;

protected slots:
    void button_pressed();
};

#endif // INTERFACEGUIBUTTON_H
