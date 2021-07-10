#ifndef INTERFACEGUIBUTTON_H
#define INTERFACEGUIBUTTON_H

#include "xgui.h"

class XItemButton;
class QPushButton;

class XGuiButton : public XGui
{
    Q_OBJECT
public:
    XGuiButton(XGuiPageBuilder &page_builder, XItemButton *item);
    ~XGuiButton();

    //value - pressing is read once and cleared
    int value();

    void set_running(bool running);  //switch enabled at start, disabled at stop
protected:
    QPushButton *button_ = nullptr;
    int value_ = 0;

protected slots:
    void button_pressed();
};

#endif // INTERFACEGUIBUTTON_H
