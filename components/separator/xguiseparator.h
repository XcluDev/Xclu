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
    virtual ~XGuiSeparator();

protected:
    QFrame *spacer_ = nullptr;

};

#endif // INTERFACEGUISEPARATOR_H
