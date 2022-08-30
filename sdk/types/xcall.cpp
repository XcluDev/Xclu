#include "xcall.h"
#include "xtypeutils.h"
#include "xerrorhandling.h"

//---------------------------------------------------------------------
const QString XCallTypeNames[int(XCallType::N)] =
{
    "none",
    "custom",
    "create_widget",
    "sound_buffer_add",
    "sound_buffer_received"
};


QString xcalltype_to_string(XCallType type) {
    return XTypeUtils::to_string(int(type), int(XCallType::N), XCallTypeNames);
}

//not generates exception
QString xcalltype_to_string_for_user(XCallType type) {
    if (int(type) < 0 || type >= XCallType::N) return QString("unknown:%1").arg(int(type));
    return xcalltype_to_string(type);
}

XCallType xstring_to_calltype(QString type_str) {
    return XCallType(XTypeUtils::to_type(type_str, int(XCallType::N), XCallTypeNames));
}


//---------------------------------------------------------------------
void XCall::setup(XCallType type, void *data) {
    type_ = type;
    data_ = data;
    data_const_ = nullptr;
    error_.clear();
}

//---------------------------------------------------------------------
void XCall::setup_const(XCallType type, const void *data) {
    type_ = type;
    data_ = nullptr;
    data_const_ = data;
    error_.clear();
}

//---------------------------------------------------------------------
XCallType XCall::type() const {
    return type_;
}


//---------------------------------------------------------------------
void XCall::assert_type(XCallType type) const {
    xc_assert(type_ == type, QString("XCall::assert_type - expected %1, have %2")
              .arg(xcalltype_to_string_for_user(type))
              .arg(xcalltype_to_string_for_user(type_)));
}

//---------------------------------------------------------------------
bool XCall::has_type(XCallType type) const {
    return (type_ == type);
}

//---------------------------------------------------------------------
template<> void XCall::setup<XCallCreateWidget>(XCallCreateWidget &call_data) {
    setup(XCallType::CreateWidget, &call_data);
}
template<> void XCall::setup<XCallSoundBufferAdd>(XCallSoundBufferAdd &call_data) {
    setup(XCallType::SoundBufferAdd, &call_data);
}
template<> void XCall::setup<XCallSoundBufferReceived>(XCallSoundBufferReceived &call_data) {
    setup(XCallType::SoundBufferReceived, &call_data);
}

template<> void XCall::setup_const<XCallCreateWidget>(const XCallCreateWidget &call_data) {
    setup_const(XCallType::CreateWidget, &call_data);
}
template<> void XCall::setup_const<XCallSoundBufferAdd>(const XCallSoundBufferAdd &call_data) {
    setup_const(XCallType::SoundBufferAdd, &call_data);
}
template<> void XCall::setup_const<XCallSoundBufferReceived>(const XCallSoundBufferReceived &call_data) {
    setup_const(XCallType::SoundBufferReceived, &call_data);
}


//---------------------------------------------------------------------
void* XCall::data() {
    return data_;
}

//---------------------------------------------------------------------
template<> XCallCreateWidget* XCall::data<XCallCreateWidget>() {
    if (!has_type(XCallType::CreateWidget)) return nullptr;
    return (XCallCreateWidget*) data();
}
template<> XCallSoundBufferAdd* XCall::data<XCallSoundBufferAdd>() {
    return (XCallSoundBufferAdd*) data();
}
template<> XCallSoundBufferReceived* XCall::data<XCallSoundBufferReceived>() {
    return (XCallSoundBufferReceived*) data();
}

//---------------------------------------------------------------------
template<> const XCallCreateWidget* XCall::data_const<XCallCreateWidget>() const {
    if (!has_type(XCallType::CreateWidget)) return nullptr;
    return (const XCallCreateWidget*) data_const();
}
template<> XCallSoundBufferAdd* XCall::data<XCallSoundBufferAdd>() {
    return (XCallSoundBufferAdd*) data_const();
}
template<> XCallSoundBufferReceived* XCall::data<XCallSoundBufferReceived>() {
    return (XCallSoundBufferReceived*) data_const();
}

//---------------------------------------------------------------------
XCallError& XCall::error() {
    return error_;
}

//---------------------------------------------------------------------
