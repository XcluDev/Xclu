#pragma once

#include "xguicomp.h"

class XItemEnum;
class XcluComboBox;

class XGuiEnum : public XGuiComp
{
    Q_OBJECT
public:
    XGuiEnum(XGuiPageBuilder &page_builder, XItemEnum *item);
    virtual ~XGuiEnum();

    //значение для проверки видимости детей
    QString value_string_for_visibility();

    int index();
    void set_index(int v);

protected:
     XcluComboBox *combo_ = nullptr;
     QStringList names_;

     //установка режима read_only - для out и блокировки констант при запуске проекта
     void set_read_only_(bool read_only);

};

