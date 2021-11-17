#pragma once

#include <QPainter>
#include <QVector>
#include <QString>
#include "xobject.h"
#include "module.h"

//Helper class for specific intermodules calls and search modules by name, type, accepted/send calls
//TODO it can be automated as XGUI!

class XIntermodule {
public:
    //----------------------------------------------------------
    //Find modules by a filter
    //----------------------------------------------------------
    // 'accept_calls_filter', 'send_calls_filter', 'type_filter' are parts of name,
    // if XCallTypeNone or if empty - it means "all" for a given filter
    static QVector<Module *> find_modules_by_filter(XCallType accept_calls_filter = XCallTypeNone,
                                             XCallType send_calls_filter = XCallTypeNone,
                                             QString class_filter = "");

    //----------------------------------------------------------
    //"render" call
    //----------------------------------------------------------
    struct RenderCallData {
        QPainter *painter = nullptr;
        int w = 0;
        int h = 0;
        RenderCallData() {}
        RenderCallData(QPainter *painter, int w, int h) {
            this->painter = painter;
            this->w = w;
            this->h = h;
        }
        RenderCallData(XObject *input) {
            painter = (QPainter *)input->get_pointer("painter");
            w = input->geti("w");
            h = input->geti("h");
        }
        void set_to(XObject *input) const {
            input->clear();
            input->set_type(XObjectIntermoduleCallRender);
            input->set_pointer("painter", painter);
            input->seti("w", w);
            input->seti("h", h);
        }
        void set_to(XObject &input) const {
            set_to(&input);
        }
    };
    //----------------------------------------------------------
    static void call_on_render(Module *module, const RenderCallData &data);
    //----------------------------------------------------------

protected:
    static void call(Module *module, XCallType function, XObject *input, XObject *output = nullptr);
};
