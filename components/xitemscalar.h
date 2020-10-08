#ifndef XITEMSCALAR_H
#define XITEMSCALAR_H

#include "incl_h.h"
#include "xitem.h"

//Class for scalar types - int, float, enum checkbox, string, text
//It unifies processing popup menu.

template<typename T>
class XItemScalar_ : public XItem_<T>
{
public:
    XItemScalar_<T>(ModuleInterface *interf, const XItemPreDescription &pre_description)
        : XItem_<T>(interf, pre_description) {
    }

    //Context menu ----------------
    //Each component must provide information about its menu
    virtual ComponentPopupMenuInfo component_popup_info() {
        return ComponentPopupMenuInfo(!is_out(), false, !is_out(), false);
    }
};

#endif // XITEMSCALAR_H
