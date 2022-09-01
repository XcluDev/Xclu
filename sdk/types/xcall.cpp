#include "xcall.h"

#include "xerrorhandling.h"
#include "xtypeutils.h"

//---------------------------------------------------------------------
const QString XCallTypeNames[int(XCallType::N)] = {
    "none",
    "Custom",
    "CreateWidget",
    "Draw",
    "SoundBufferAdd",
    "SoundBufferReceived",
};

QString XCallType_to_string(XCallType type) {
    return XTypeUtils::to_string(int(type), int(XCallType::N), XCallTypeNames);
}

XCallType string_to_XCallType(QString type) {
    return XCallType(XTypeUtils::to_type(type, int(XCallType::N), XCallTypeNames));
}

//---------------------------------------------------------------------
void XCall::setup(XCallType call_type, XType type, void *data) {
    call_type_ = call_type;
    type_ = type;
    data_ = data;
    data_const_ = nullptr;
    error_.clear();
}

//---------------------------------------------------------------------
void XCall::setup_const(XCallType call_type, XType type, const void *data) {
    call_type_ = call_type;
    type_ = type;
    data_ = nullptr;
    data_const_ = data;
    error_.clear();
}

//---------------------------------------------------------------------
template<class T> void XCall::setup(XCallType call_type, T &call_data) {
    setup(call_type, cpptype_to_XType<T>(), &call_data);
}
template<class T> void XCall::setup_const(XCallType call_type, const T &call_data) {
    setup_const(call_type, cpptype_to_XType<T>(), &call_data);
}

//---------------------------------------------------------------------
XCallType XCall::call_type() const {
    return call_type_;
}

//---------------------------------------------------------------------
XType XCall::type() const {
    return type_;
}

//---------------------------------------------------------------------
void XCall::assert_type(XType type) const {
    xc_assert(type_ == type, QString("XCall::assert_type - expected %1, have %2")
              .arg(XType_to_string(type))
              .arg(XType_to_string(type_)));
}

//---------------------------------------------------------------------
bool XCall::has_type(XType type) const {
    return (type_ == type);
}

//---------------------------------------------------------------------
void* XCall::data() {
    return data_;
}

const void* XCall::data_const() const {
    return data_const_;
}

//---------------------------------------------------------------------
template<class T> T* XCall::data() {
    if (!has_type(cpptype_to_XType<T>())) return nullptr;
    return (T*) data();
}

template<class T> const T* XCall::data_const() const {
    if (!has_type(cpptype_to_XType<T>())) return nullptr;
    return (const T*) data_const();
}

//---------------------------------------------------------------------
XCallError& XCall::error() {
    return error_;
}

//---------------------------------------------------------------------
