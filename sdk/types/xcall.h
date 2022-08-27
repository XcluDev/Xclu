#pragma once

#include <QPainter>
#include <QVector>
#include <QString>
#include <xcallerror.h>

//Types of intermodules calls
enum class XCallType : int {
    None           = 0,
    Custom         = 1,
    CreateWidget   = 2,
    SoundBufferAdd = 3,
    SoundBufferReceived = 4,
    N              = 5
};

QString xcalltype_to_string(XCallType type);
QString xcalltype_to_string_for_user(XCallType type);   //not generates exception
XCallType xstring_to_calltype(QString type_str);

// Data for intermodule calls
struct XCall {
    XCallType type = XCallType::None;
    QString str_data;
    void *ptr_data = nullptr;
    XCallError error;
};

// Particular implementations of ptr_data at XCall Data
struct XCallCreateWidget {
    QString in_parent_id;
    void* out_widget = nullptr;
};

struct XCallSoundBufferAdd {
    int sample_rate = 0;
    int samples = 0;
    int channels = 0;
    float *data = nullptr;
};

struct XCallSoundBufferReceived {
    int sample_rate = 0;
    int samples = 0;
    int channels = 0;
    float *data = nullptr;
};

