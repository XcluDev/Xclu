#include "registrarxitem.h"

#include "incl_cpp.h"
#include "xitem.h"
#include "moduleinterface.h"

//---------------------------------------------------------------------
QMap<QString, XItemCreateFunction> *xitem_registered_classes_ = nullptr;

//---------------------------------------------------------------------
//Registering item class by name
/*static*/ void RegistrarXItem::register_xitem(QString class_name, XItemCreateFunction creator_function) {
    if (!xitem_registered_classes_) {
        xitem_registered_classes_ = new QMap<QString, XItemCreateFunction>;
    }
    //qDebug() << "Registered module implementation " << class_name;
    (*xitem_registered_classes_)[class_name] = creator_function;
}

//---------------------------------------------------------------------
//Check if item class registered
/*static*/ bool RegistrarXItem::is_xitem_registered(QString class_name) {
    if (!xitem_registered_classes_) return false;
    return xitem_registered_classes_->contains(class_name);
}

//---------------------------------------------------------------------
//Create item object
/*static*/ XItem *RegistrarXItem::create_xitem(ModuleInterface *interf, const XItemPreDescription *pre_description) {
    xc_assert(xitem_registered_classes_, "No modules classes were added at startup");

    QString class_name = pre_description->type;

    //check the item class is registered
    xc_assert(is_xitem_registered(class_name), "Unknown item type " + class_name);

    XItemCreateFunction creator_fun = (*xitem_registered_classes_)[class_name];

    return creator_fun(interf, pre_description);
}

//---------------------------------------------------------------------
