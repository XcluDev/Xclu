#pragma once

#include "xguicomp.h"

class XItemString;
class QLineEdit;

class XGuiString : public XGuiComp
{
    Q_OBJECT
public:
    XGuiString(XGuiPageBuilder &page_builder, XItemString *item);
    virtual ~XGuiString();

    //значение для проверки видимости детей
    QString value_string_for_visibility() { return value(); }

    QString value();
    void set_value(QString v);

protected:
    QLineEdit *lineEdit_ = nullptr;
    QString dialog_title_;
    QString file_filter_;

    //установка режима read_only - для out и блокировки констант при запуске проекта
    void set_read_only_(bool read_only);

protected slots:
    void choose_file();
    void choose_folder();
};

