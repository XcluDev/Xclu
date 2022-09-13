#pragma once

#include <QString>

// Типы вызовов между модулями
enum class XCallType: int {
    none = 0,
    Custom = 1,
    CreateWidget = 2,
    Draw = 3,
    SoundBufferAdd = 4,
    SoundBufferReceived = 5,
    N = 6
};
QString XCallType_to_string(XCallType type);
XCallType string_to_XCallType(QString type);

