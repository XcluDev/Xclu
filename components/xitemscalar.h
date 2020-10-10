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
    //Scalars have default value!
    virtual bool context_menu_has_set_default_value() { return !is_out(); }
};

#endif // XITEMSCALAR_H
