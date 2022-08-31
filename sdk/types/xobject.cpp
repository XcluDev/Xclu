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
template<class T> void XObject::link(T &data) {
    auto type = cpptype_to_XType<T>();
    xc_assert(type != XType::none, "XObject::link - can't typed link void *")
    link(&data, type);
}

//---------------------------------------------------------------------
template<class T> T* XObject::data() {
    if (!data_ || !has_type(cpptype_to_XType<T>())) return nullptr;
    return (T *)data_;
}

template<class T> const T* XObject::data() const {
    if (!data_ || !has_type(cpptype_to_XType<T>())) return nullptr;
    return (T *)data_;
}

//---------------------------------------------------------------------
/// Cast to the type with copying - useful to copy values from XProtectedObject<XObject>
template <class T> bool XObject::cast_copy_to(T &data) {
    auto *d = data();
    if (d) {
        data = *d;
        return true;
    }
    return false;
}

template <class T> bool XObject::cast_copy_to(const T &data) const {
    auto *d = data();
    if (d) {
        data = *d;
        return true;
    }
    return false;
}

//---------------------------------------------------------------------
XType XObject::type() const { //тип - image, array, strings, используется для того, чтобы можно было фильтровать и управлять визуализацией
    return type_;
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
