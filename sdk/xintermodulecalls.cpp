#include "xintermodulecalls.h".h"

//---------------------------------------------------------------------
void XIntermodule::call_on_render(Module *module, const RenderCallData &data) {
    XObject input;
    data.set_to(input);
    call(module, XCallTypeRender, &input);
}

//---------------------------------------------------------------------
void XIntermodule::call(Module *module, XCallType function, XObject *input, XObject *output) {
    xc_assert(module, "XIntermodule::call failed, module is nullptr");
    module->call_function(function, input, output);
}

//---------------------------------------------------------------------
