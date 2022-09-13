#include "xcall.h"
#include "xhandlingerrors.h"

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
XCallError& XCall::error() {
    return error_;
}

//---------------------------------------------------------------------
