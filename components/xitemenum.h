#ifndef INTERFACEITEMENUM_H
#define INTERFACEITEMENUM_H

#include "xitem.h"

class ModuleInterface;
class XGuiEnum;

class XItemEnum: public XItem
{
public:
    XItemEnum(ModuleInterface *parent, const XItemPreDescription &pre_description);

    bool supports_string() { return true; }
    QString value_string();    //rawtext, возвращает 'A_B_C'
    void set_value_string(const QString &rawstring);  //rawtext ожидается 'A_B_C'

    bool supports_int() { return true; }
    int value_int() { return index_; }    //index
    void set_value_int(int index) { index_ = index; }

    bool supports_value_title() { return true; }
    QString value_title();
    void set_value_title(QString title);  //Внимание, реализована неэффективно!

    QStringList titles();       //все заголовки
    QStringList names();       //все заголовки с подчеркиванием - для программирования

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageCreator &input);

    //единицы измерения
    QString units() { return units_; }

    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------

protected:
    int index_ = 0;

    int default_index_ = 0;
    QStringList rawtexts_;
    QMap<QString, int> map_index_;

    QString units_; //опционально - единицы измерения, которые показываются в виде метки справа от числа

    int rawtext_to_index(QString rawtext);         //возвращает -1, если не найден
    int rawtext_to_index_safe(QString rawtext);    //возвращает 0, если не найден

protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui
    //gui_ актуален только в случае is_gui_attached. Не следует его удалять
    XGuiEnum *gui_ = nullptr;

};


#endif // INTERFACEITEMENUM_H
