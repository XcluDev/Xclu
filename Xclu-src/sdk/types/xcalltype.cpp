#include "xcalltype.h"
#include "xtypeutils.h"

//---------------------------------------------------------------------
const QString XCallTypeNames[int(XCallType::N)] = {
    "none",
    "Custom",
    "CreateWidget",
    "Draw",         // Note: modules receiving Draw event must have render_area value
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
