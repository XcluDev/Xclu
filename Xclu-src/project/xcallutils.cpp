#include "xcallutils.h"
#include "project.h"

//---------------------------------------------------------------------
QVector<XModule *> XCallUtils::find_modules_by_filter(XCallType accept_calls_filter,
                                         XCallType send_calls_filter,
                                         QString class_filter,
                                         bool require_enabled) {
    return PROJECT.find_modules_by_filter(accept_calls_filter, send_calls_filter, class_filter, require_enabled);
}

//---------------------------------------------------------------------
// void XCallUtils::call(XModule *module, XType function, XObject *input, XObject *output) {
//    xc_assert(module, "XCallUtils::call failed, module is nullptr");
//    module->call(function, input, output);
// }

//---------------------------------------------------------------------
