#pragma once

#include <QPainter>
#include <QVector>
#include <QString>
#include "xobject.h"
#include "xmodule.h"

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

class XIntermodule {
public:
    //----------------------------------------------------------
    //Find modules by a filter
    //----------------------------------------------------------
    // 'accept_calls_filter', 'send_calls_filter', 'type_filter' are parts of name,
    // if XCallType::None or if empty - it means "all" for a given filter
    static QVector<XModule *> find_modules_by_filter(XCallType accept_calls_filter = XCallType::None,
                                             XCallType send_calls_filter = XCallType::None,
                                             QString class_filter = "",
                                             bool require_enabled = true);

protected:
    // static void call(XModule *module, XCallType function, XObject *input, XObject *output = nullptr);
};
