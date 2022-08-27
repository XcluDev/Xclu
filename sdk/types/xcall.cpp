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
    error_.clear();
}

//---------------------------------------------------------------------
void XCall::assert_type(XCallType type) {
    xc_assert(type_ == type, QString("XCall::assert_type - expected %1, have %2")
              .arg(xcalltype_to_string_for_user(type))
              .arg(xcalltype_to_string_for_user(type_)));
}

//---------------------------------------------------------------------
XCallType XCall::type() {
    return type_;
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

//---------------------------------------------------------------------
void* XCall::data() {
    return data_;
}

//---------------------------------------------------------------------
template<> XCallCreateWidget* XCall::data<XCallCreateWidget>() {
    return (XCallCreateWidget*) data();
}
template<> XCallSoundBufferAdd* XCall::data<XCallSoundBufferAdd>() {
    return (XCallSoundBufferAdd*) data();
}
template<> XCallSoundBufferReceived* XCall::data<XCallSoundBufferReceived>() {
    return (XCallSoundBufferReceived*) data();
}

//---------------------------------------------------------------------
XCallError& XCall::error() {
    return error_;
}

//---------------------------------------------------------------------
