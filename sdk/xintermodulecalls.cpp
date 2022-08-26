#include "xintermodulecalls.h"
#include "project.h"

//---------------------------------------------------------------------
QVector<Module *> XIntermodule::find_modules_by_filter(XCallType accept_calls_filter,
                                         XCallType send_calls_filter,
                                         QString class_filter,
                                         bool require_enabled) {
    return PROJECT.find_modules_by_filter(accept_calls_filter, send_calls_filter, class_filter, require_enabled);
}

//---------------------------------------------------------------------
// void XIntermodule::call(Module *module, XCallType function, XObject *input, XObject *output) {
//    xc_assert(module, "XIntermodule::call failed, module is nullptr");
//    module->call(function, input, output);
// }

//---------------------------------------------------------------------
