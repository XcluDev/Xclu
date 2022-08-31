#pragma once

#include "xitemscalar.h"

class XModuleInterface;

class XItemEnum: public XItemScalarInt
{
public:
    XItemEnum(XModuleInterface *interf, const XItemPreDescription &pre_description);

    //string to write/read json (for enum is custom)
    virtual QString value_string_json() { return value_raw(); }
    virtual void set_value_string_json(const QString &v) { set_value_raw(v); }

    //raw title value
    bool supports_value_raw() { return true; }
    QString value_raw();
    void set_value_raw(QString rawstring);

    //processed title value, with "_" replaced by " "
    bool supports_value_title() { return true; }
    QString value_title();
    void set_value_title(QString title);  //Внимание, реализована неэффективно!

    QStringList titles();       //все заголовки
    QStringList names();       //все заголовки с подчеркиванием - для программирования

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageBuilder &page_builder);

    //единицы измерения
    QString units() { return units_; }

    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------

protected:
    //int index_ = 0; //inside XItem_

    int default_index_ = 0;

    QStringList rawtexts_;
    QMap<QString, int> map_index_;

    QString units_; //опционально - единицы измерения, которые показываются в виде метки справа от числа

    //Function for setting value using link
    virtual void set_value_from_link(XLinkResolved *linkres);

    int rawtext_to_index(QString rawtext);         //возвращает -1, если не найден
    int rawtext_to_index_safe(QString rawtext);    //возвращает 0, если не найден

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui
};

