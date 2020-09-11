#ifndef VISIBILITYGROUPS_H
#define VISIBILITYGROUPS_H

//Структуры для динамического GUI - отслеживание, кто должен включиться/выключиться
//причем, это работает только в GUI - а сами элементы (XItem) не меняют своего значения, пока не придет сигнал

#include "incl_h.h"

class XGui;
class VisibilityGroupGui;

//группа для сбора дерева зависимости
class VisibleGroupBase {
public:
    VisibleGroupBase() {}
    VisibleGroupBase(QString item_name, QStringList variants);
    void add_affected_item(QString name);

    QString item_name();
    QStringList affected_items();

    //создает группу для визуального применения, наполнив ее только variants
    VisibilityGroupGui *create_group_gui();

protected:
    QString item_name_;
    QMap<QString, int> variants_;
    QStringList affected_items_;
};


//группа для применения в родительском GUI-элементе
//создается в ModuleInterface при подключении GUI
//когда в этот объект приходят сигналы value_visibility_setup, value_changed или visibility_changed,
//он при необходимости высылает сигналы детям.
class VisibilityGroupGui
{
public:
    VisibilityGroupGui(const QMap<QString, int> &variants);
    void add_affected_item(XGui *item);

    //сигналы
    void propagate_visibility(QString new_value);   //отправить сигналы о видимости, этот сигнал отправляется после установки значения переменной
    void value_changed(QString new_value);   //изменился параметр
    void visibility_changed(bool visibility);   //видимость самого элемента
protected:
    QMap<QString, int> variants_;
    QVector<XGui *> affected_items_;

    bool self_visibility_ = true;
    bool group_visibility_ = true;

    //распространить сигнал об изменении видимости группы
    //вызывается при изменении self_visibility_, group_visibility_
    void propagate_if_changed();
    int last_propagated_ = -1;  //чтобы первый раз точно отправил

    //распространить сигнал об изменении видимости группы
    void propagate();
};

#endif // VISIBILITYGROUPS_H
