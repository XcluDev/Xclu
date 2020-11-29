#ifndef INTERFACEGUISEPARATOR_H
#define INTERFACEGUISEPARATOR_H

#include "xgui.h"

class XItemSeparator;
class QSpacerItem;
class QFrame;

class XGuiSeparator : public XGui
{
    Q_OBJECT
public:
    XGuiSeparator(XGuiPageBuilder &page_builder, XItemSeparator *item);
    ~XGuiSeparator();

    //здесь нам нужно кастомно менять размер сепаратора, так как у него нет метода setVisible
    virtual void set_visible(bool visible);
protected:
    //мы пока не стали создавать два класса - для сепаратора и линии... :)
    bool is_line_ = false;
    bool is_separator_ = false;

    //сепаратор
    QSpacerItem *spacer_ = nullptr;
    int visible_size_ = 0;

    //линия
    QFrame *line_ = nullptr;
};

#endif // INTERFACEGUISEPARATOR_H
