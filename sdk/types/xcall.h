#pragma once

#include <QPainter>
#include <QVector>
#include <QString>
#include <xcallerror.h>
#include "xtype.h"

// Data for intermodule calls
struct XCall {
    XCall() {}

    void setup(XType type, void *data);

    /// We separating const data on compiling-level
    void setup_const(XType type, const void *data);

    /// Typed implementations for XCallCreateWidget, XCallSoundBufferAdd and others
    /// Example of usage:
    /// XCallCreateWidget call_data = {...};
    /// XCall call;
    /// call.setup<XCallCreateWidget>(call_data);
    template<class T> void setup(T &call_data);
    template<class T> void setup_const(const T &call_data);

    void* data();
    const void* data_const();
    /// Typed implementations
    /// Example usage: auto* call_data = call.data<XCallCreateWidget>();
    template<class T> T* data();
    template<class T> const T* data_const() const;

    XType type() const;
    void assert_type(XType type) const;
    bool has_type(XType type) const;

    XCallError& error();
protected:
    XType type_ = XType::None;
    void* data_ = nullptr;
    const void* data_const_ = nullptr; // Const data stores separately
    XCallError error_;
};



