#pragma once

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

