#include "xobject.h"
#include "incl_cpp.h"
#include <QPainter>
#include "xtypeutils.h"

//---------------------------------------------------------------------
const QString ObjectTypeNames[int(XObjectType::N)] =
{
    "Empty",
    "Custom",
    "Array",
    "Image",
    "SoundFormat",
    "SoundBuffer"
};

//---------------------------------------------------------------------
QString XObjectType_to_string(XObjectType type) {
    return XTypeUtils::to_string(int(type), int(XObjectType::N), ObjectTypeNames);
}

XObjectType string_to_XObjectType(QString type_str) {
    return XObjectType(XTypeUtils::to_type(type_str, int(XObjectType::N), ObjectTypeNames));
}

template<> XObjectType cpptype_to_XObjectType<void *>() { return XObjectType::Empty; }
template<> XObjectType cpptype_to_XObjectType<XArray>() { return XObjectType::Array; }
template<> XObjectType cpptype_to_XObjectType<XRaster>() { return XObjectType::Image; }
template<> XObjectType cpptype_to_XObjectType<XSoundFormat>() { return XObjectType::SoundFormat; }
template<> XObjectType cpptype_to_XObjectType<XSoundBuffer>() { return XObjectType::SoundBuffer; }

//---------------------------------------------------------------------
XObject::XObject()
{
}

//---------------------------------------------------------------------
XObject::~XObject() {

}

//---------------------------------------------------------------------
void XObject::clear() {
    type_ = XObjectType::Empty;
    subtype_.clear();
    data_ = nullptr;
}

//---------------------------------------------------------------------
/// Link object to given data and type. Object not own the data.
void XObject::link(void *data, XObjectType type, QString subtype) {
    data_ = data;
    type_ = type;
    subtype_ = subtype;
}

//---------------------------------------------------------------------
template<class T> void XObject::link(T &data) {
    auto type = cpptype_to_XObjectType<T>();
    xc_assert(type != XObjectType::Empty, "XObject::link - can't typed link void *")
    link(&data, type);
}

//---------------------------------------------------------------------
template<class T> T* XObject::data() {
    if (!data_ || !has_type(cpptype_to_XObjectType<T>())) return nullptr;
    return (T *)data_;
}

template<class T> const T* XObject::data() const {
    if (!data_ || !has_type(cpptype_to_XObjectType<T>())) return nullptr;
    return (T *)data_;
}

//---------------------------------------------------------------------
/// Cast to the type with copying - useful to copy values from XProtectedObject<XObject>
template <class T> bool XObject::cast_copy(T &data) {
    auto *d = data();
    if (d) {
        data = *d;
        return true;
    }
    return false;
}

template <class T> bool XObject::cast_copy(const T &data) const {
    auto *d = data();
    if (d) {
        data = *d;
        return true;
    }
    return false;
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
                .arg(XObjectType_to_string(expected_type))
                .arg(XObjectType_to_string(type()))
            );
}

//---------------------------------------------------------------------
