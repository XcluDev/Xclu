#include "xcall.h"
#include "xtypeutils.h"

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
