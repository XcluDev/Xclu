#ifndef INTERFACEGUICHECKBOX_H
#define INTERFACEGUICHECKBOX_H

#include "xgui.h"

class XItemCheckbox;
class QCheckBox;

class XGuiCheckbox : public XGui
{
    Q_OBJECT
public:
    XGuiCheckbox(XGuiPageBuilder &page_builder, XItemCheckbox *item);
    virtual ~XGuiCheckbox();

    //значение для проверки видимости детей
    QString value_string_for_visibility() { return QString::number(value()); };

    int value();
    void set_value(int v);

protected:
    //установка режима read_only - для out и блокировки констант при запуске проекта
    void set_read_only_(bool read_only);


private:
    QCheckBox *checkbox_ = nullptr; //удалять не надо

};

#endif // INTERFACEGUICHECKBOX_H
