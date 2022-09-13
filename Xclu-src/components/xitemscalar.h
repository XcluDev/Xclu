#pragma once

#include "incl_h.h"
#include "xrange.h"
#include "xitem.h"

//---------------------------------------------------------------------
//XItemScalar_<T>
//Class for scalar types - int, float, enum checkbox, string, text
//It unifies processing popup menu.
//---------------------------------------------------------------------
template<typename T>
class XItemScalar_ : public XItem_<T>
{
public:
    XItemScalar_<T>(XModuleInterface *interf, const XItemPreDescription &pre_description)
        : XItem_<T>(interf, pre_description) {
    }

    //Context menu ----------------
    //Scalars have default value!
    virtual bool context_menu_has_set_default_value() { return !XItem_<T>::is_out(); }
};

//---------------------------------------------------------------------
//XItemScalarInt
//Integer scalar - used for checkbox, enum, int, with range control
//Implements "supports string, int, float"
//Note: subclasses must setup "range_" to use range control !
//---------------------------------------------------------------------
class XItemScalarInt : public XItemScalar_<int>
{
public:
    XItemScalarInt(XModuleInterface *interf, const XItemPreDescription &pre_description)
        : XItemScalar_<int>(interf, pre_description) {
    }

    //range
    const XRangeInt &range() { return range_; }

    //string
    bool supports_string() { return true; }
    QString value_string() { return QString::number(value_int()); }
    void set_value_string(const QString &value) { set_value_int(value.toInt()); }

    //int
    bool supports_int() { return true; }
    int value_int() { return value_read(); }

    //set value using range control
    void set_value_int(int value) { value_write(range_.constrain(value)); }

    //float
    bool supports_float() { return true; }
    float value_float() { return value_int(); }
    void set_value_float(float f)  { set_value_int(int(f)); }

protected:
    XRangeInt range_;
};

