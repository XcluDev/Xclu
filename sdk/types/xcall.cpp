#include "xcall.h"

#include "xerrorhandling.h"

//---------------------------------------------------------------------
void XCall::setup(XType type, void *data) {
    type_ = type;
    data_ = data;
    data_const_ = nullptr;
    error_.clear();
}

//---------------------------------------------------------------------
void XCall::setup_const(XType type, const void *data) {
    type_ = type;
    data_ = nullptr;
    data_const_ = data;
    error_.clear();
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
template<class T> void XCall::setup(T &call_data) {
    setup(cpptype_to_XType<T>(), &call_data);
}
template<class T> void XCall::setup_const(const T &call_data) {
    setup_const(cpptype_to_XType<T>(), &call_data);
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
