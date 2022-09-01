#include "xobject.h"
#include "incl_cpp.h"
#include <QPainter>

//---------------------------------------------------------------------
XObject::XObject()
{
}

//---------------------------------------------------------------------
XObject::~XObject() {

}

//---------------------------------------------------------------------
void XObject::clear() {
    type_ = XType::none;
    subtype_.clear();
    data_ = nullptr;
}

//---------------------------------------------------------------------
/// Link object to given data and type. Object not own the data.
void XObject::link(void *data, XType type, QString subtype) {
    data_ = data;
    type_ = type;
    subtype_ = subtype;
}

//---------------------------------------------------------------------
XType XObject::type() const { //тип - image, array, strings, используется для того, чтобы можно было фильтровать и управлять визуализацией
    return type_;
}

//---------------------------------------------------------------------
QString XObject::subtype() const {   // Name of the subtype, used for differenciating objects of "Custom" type
    return subtype_;
}

//---------------------------------------------------------------------
bool XObject::has_type(XType expected_type) const {
    return (type() == expected_type);
}

//---------------------------------------------------------------------
//проверить, что объект имеет конкретный тип, если нет - то выдаст expeption
void XObject::assert_type(XType expected_type) const {
    xc_assert(type() == expected_type,
            QString("Expected object of type '%1', but get %2")
                .arg(XType_to_string(expected_type))
                .arg(XType_to_string(type()))
            );
}

//---------------------------------------------------------------------
