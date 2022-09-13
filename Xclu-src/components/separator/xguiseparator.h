#pragma once

#include "xguicomp.h"

class XItemSeparator;
class QSpacerItem;
class QFrame;

class XGuiSeparator : public XGuiComp
{
    Q_OBJECT
public:
    XGuiSeparator(XGuiPageBuilder &page_builder, XItemSeparator *item);
    virtual ~XGuiSeparator();

protected:
    QFrame *spacer_ = nullptr;

};

