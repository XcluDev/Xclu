#include "incl_cpp.h"
#include "visibilitygroups.h"
#include "interfacegui.h"

//---------------------------------------------------------------------
//группа для сбора дерева зависимости
VisibleGroupBase::VisibleGroupBase(QString item_name, QStringList variants) {
    item_name_ = item_name;
    for (int i=0; i<variants.size(); i++) {
        if (!variants_.contains(variants[i])) {
            variants_[variants[i]] = 1;
        }
    }
}

//---------------------------------------------------------------------
void VisibleGroupBase::add_affected_item(QString name) {
    affected_items_.append(name);
}

//---------------------------------------------------------------------
QString VisibleGroupBase::item_name() {
    return item_name_;
}

//---------------------------------------------------------------------
QStringList VisibleGroupBase::affected_items() {
    return affected_items_;
}


//---------------------------------------------------------------------
//создает группу для визуального применения, наполнив ее только variants
VisibilityGroupGui *VisibleGroupBase::create_group_gui() {
    return new VisibilityGroupGui(variants_);
}

//---------------------------------------------------------------------
//группа для применения в родительском GUI-элементе
//создается в ModuleInterface при подключении GUI
//когда в этот объект приходят сигналы value_visibility_setup, value_changed или visibility_changed,
//он при необходимости высылает сигналы детям.
VisibilityGroupGui::VisibilityGroupGui(const QMap<QString, int> &variants) {
    variants_ = variants;
}

//---------------------------------------------------------------------
void VisibilityGroupGui::add_affected_item(InterfaceGui *item) {
    affected_items_.push_back(item);
}

//---------------------------------------------------------------------
//отправить сигналы о видимости, этот сигнал отправляется после установки значения переменной
void VisibilityGroupGui::propagate_visibility(QString new_value) {
    group_visibility_ = variants_.contains(new_value);
    propagate_if_changed();
}

//---------------------------------------------------------------------
void VisibilityGroupGui::value_changed(QString new_value) {  //изменился параметр
    group_visibility_ = variants_.contains(new_value);
    propagate_if_changed();
}

//---------------------------------------------------------------------
void VisibilityGroupGui::visibility_changed(bool visibility) {   //видимость самого элемента
    self_visibility_ = visibility;
    propagate_if_changed();
}

//---------------------------------------------------------------------
//распространить сигнал об изменении видимости группы
//вызывается при изменении self_visibility_, group_visibility_
void VisibilityGroupGui::propagate_if_changed() {
    bool vis = self_visibility_ && group_visibility_;
    if (int(vis) != last_propagated_) {
        propagate();
    }
}

//---------------------------------------------------------------------
//распространить сигнал об изменении видимости группы
void VisibilityGroupGui::propagate() {
    bool vis = self_visibility_ && group_visibility_;
    last_propagated_ = vis;
    for (int i=0; i<affected_items_.size(); i++) {
        affected_items_[i]->set_visible(vis);
    }
}

//---------------------------------------------------------------------
