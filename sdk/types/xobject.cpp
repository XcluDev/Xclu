#include "xobject.h"
#include "incl_cpp.h"
#include <QPainter>

//---------------------------------------------------------------------
XObject::XObject(XObjectType type)
{
    type_ = type;
}

//---------------------------------------------------------------------
XObject::~XObject() {

}

//---------------------------------------------------------------------
XObjectType XObject::type() const { //тип - image, array, strings, используется для того, чтобы можно было фильтровать и управлять визуализацией
    return type_;
}

//---------------------------------------------------------------------
bool XObject::has_type(XObjectType expected_type) const {
    return (type() == expected_type);
}

//---------------------------------------------------------------------
//проверить, что объект имеет конкретный тип, если нет - то выдаст expeption
void XObject::assert_type(XObjectType expected_type) const {
    xc_assert(type() == expected_type,
            QString("Expected object of type '%1', but get %2")
                .arg(object_type_to_string(expected_type))
                .arg(object_type_to_string(type()))
            );
}

//---------------------------------------------------------------------
