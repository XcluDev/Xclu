#pragma once

#include <QPainter>
#include <QVector>
#include <QString>
#include <xcallerror.h>
#include "xtype.h"


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


// Data for intermodule calls
struct XCall {
    XCall() {}

    void setup(XCallType call_type, XType type, void *data);

    /// We separating const data on compiling-level
    void setup_const(XCallType call_type, XType type, const void *data);

    /// Typed implementations for data and const data
    /// Example of usage:
    /// XCallCreateWidget call_data = {...};
    /// XCall call;
    /// call.setup<XCallCreateWidget>(XCallType::CreateWidget, call_data);
    template<class T> void setup(XCallType call_type, T &call_data);
    template<class T> void setup_const(XCallType call_type, const T &call_data);

    XCallType call_type() const;

    XType type() const;
    void assert_type(XType type) const;
    bool has_type(XType type) const;

    void* data();
    const void* data_const() const;
    /// Typed implementations
    /// Example usage: auto* call_data = call.data<XCallCreateWidget>();
    template<class T> T* data();
    template<class T> const T* data_const() const;

    XCallError& error();
protected:
    XCallType call_type_ = XCallType::none;
    XType type_ = XType::none;
    void* data_ = nullptr;
    const void* data_const_ = nullptr; // Const data stores separately
    XCallError error_;
};



