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

//---------------------------------------------------------------------
XObject::XObject()
{
}

//---------------------------------------------------------------------
XObject::~XObject() {

}

//---------------------------------------------------------------------
/// Link object to given data and type. Object not own the data.
void XObject::link(void *data, XObjectType type, QString subtype) {
    data_ = data;
    type_ = type;
    subtype_ = subtype;
}

//---------------------------------------------------------------------
template<> void XObject::link<XArray>(XArray &data) {
    link(&data, XObjectType::Array);
}
template<> void XObject::link<XRaster>(XRaster &data) {
    link(&data, XObjectType::Image);
}
template<> void XObject::link<XSoundFormat>(XSoundFormat &data) {
    link(&data, XObjectType::SoundFormat);
}
template<> void XObject::link<XSoundBuffer>(XSoundBuffer &data) {
    link(&data, XObjectType::SoundBuffer);
}

//---------------------------------------------------------------------
template<> XArray* XObject::data<XArray>() {
    if (!data()) return nullptr;
    assert_type(XObjectType::Array);
    return (XArray *)data();
}
template<> XRaster* XObject::data<XRaster>() {
    if (!data()) return nullptr;
    assert_type(XObjectType::Image);
    return (XRaster *)data();
}
template<> XSoundFormat* XObject::data<XSoundFormat>() {
    if (!data()) return nullptr;
    assert_type(XObjectType::SoundFormat);
    return (XSoundFormat *)data();
}
template<> XSoundBuffer* XObject::data<XSoundBuffer>() {
    if (!data()) return nullptr;
    assert_type(XObjectType::SoundBuffer);
    return (XSoundBuffer *)data();
}

//---------------------------------------------------------------------
template<> const XArray* XObject::data<XArray>() const {
    if (!data()) return nullptr;
    assert_type(XObjectType::Array);
    return (XArray *)data();
}
template<> const XRaster* XObject::data<XRaster>() const {
    if (!data()) return nullptr;
    assert_type(XObjectType::Image);
    return (XRaster *)data();
}
template<> const XSoundFormat* XObject::data<XSoundFormat>() const {
    if (!data()) return nullptr;
    assert_type(XObjectType::SoundFormat);
    return (XSoundFormat *)data();
}
template<> const XSoundBuffer* XObject::data<XSoundBuffer>() const {
    if (!data()) return nullptr;
    assert_type(XObjectType::SoundBuffer);
    return (XSoundBuffer *)data();
}
//---------------------------------------------------------------------
void* XObject::data() {
    return data_;
}

//---------------------------------------------------------------------
const void* XObject::data() const {
    return data_;
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
