#ifndef INTERFACEGUITEXT_H
#define INTERFACEGUITEXT_H

#include "xgui.h"

class XItemText;
class QPlainTextEdit;

class XGuiText : public XGui
{
    Q_OBJECT
public:
    XGuiText(XGuiPageCreator &input, XItemText *item);
    ~XGuiText();

    //значение для проверки видимости детей
    QString value_string_for_visibility() { return value(); }

    QString value();
    void set_value(QString v);

protected slots:
    //Отслеживание изменений - переопределяем, чтобы скролл текста не сбрасывался при запросе toPlainText
    void on_value_changed();

protected:
    QPlainTextEdit *textEdit_ = nullptr;

    QString value_;
    bool dirty_ = false;    //если true - это значит, что пользователь изменил текст

    //установка режима read_only - для out и блокировки констант при запуске проекта
    void set_read_only(bool read_only);

    //Свойства для разных ситуаций
    virtual bool is_const_bold() { return false; }   //тут константы не делать bold


};

#endif // INTERFACEGUITEXT_H
