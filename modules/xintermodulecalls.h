#pragma once

#include <QPainter>
#include <QVector>
#include <QString>
#include "xobject.h"
#include "xmodule.h"

//Helper class for specific intermodules calls and search modules by name, type, accepted/send calls
//TODO it can be automated as XGUI!

class XIntermodule {
public:
    //----------------------------------------------------------
    //Find modules by a filter
    //----------------------------------------------------------
    // 'accept_calls_filter', 'send_calls_filter', 'type_filter' are parts of name,
    // if XCallTypeNone or if empty - it means "all" for a given filter
    static QVector<XModule *> find_modules_by_filter(XCallType accept_calls_filter = XCallTypeNone,
                                             XCallType send_calls_filter = XCallTypeNone,
                                             QString class_filter = "",
                                             bool require_enabled = true);

protected:
    // static void call(XModule *module, XCallType function, XObject *input, XObject *output = nullptr);
};
