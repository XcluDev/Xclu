#ifndef XCALLUTILS_H
#define XCALLUTILS_H

#include "xmodule.h"

// Utility class for intermodule calls
class XCallUtils {
public:
    //----------------------------------------------------------
    //Find modules by a filter
    //----------------------------------------------------------
    // 'accept_calls_filter', 'send_calls_filter', 'type_filter' are parts of name,
    // if XType::none or if empty - it means "all" for a given filter
    static QVector<XModule *> find_modules_by_filter(XType accept_calls_filter = XType::none,
                                             XType send_calls_filter = XType::none,
                                             QString class_filter = "",
                                             bool require_enabled = true);

protected:
    // static void call(XModule *module, XType function, XObject *input, XObject *output = nullptr);
};


#endif // XCALLUTILS_H
