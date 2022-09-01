#pragma once

#include <QPainter>
#include <QVector>
#include <QString>
#include <xcallerror.h>
#include "xtype.h"
#include "xcalltype.h"
#include "xtypeconvertor.h"


// XCall - описание функции для вызова между модулями,
// хранит тип вызова call_type и данные data (либо data_const)
// Структура класса проектировалась с расчетом на простую передачу между DLL.

struct XCall {
    XCall() {}

    void setup(XCallType call_type, XType type, void *data);

    /// We separating const data on compiling-level
    void setup_const(XCallType call_type, XType type, const void *data);

    /// Typed implementations for data and const data
    /// Example of usage:
    /// XCallDataCreateWidget call_data = {...};
    /// XCall call;
    /// call.setup<XCallDataCreateWidget>(XCallType::CreateWidget, call_data);
    template<class T> void setup(XCallType call_type, T &call_data);
    template<class T> void setup_const(XCallType call_type, const T &call_data);

    XCallType call_type() const;

    XType type() const;
    void assert_type(XType type) const;
    bool has_type(XType type) const;

    void* data();
    const void* data_const() const;
    /// Typed implementations
    /// Example usage: auto* call_data = call.data<XCallDataCreateWidget>();
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

//---------------------------------------------------------------------
template<class T> void XCall::setup(XCallType call_type, T &call_data) {
    setup(call_type, cpptype_to_XType<T>(), &call_data);
}
template<class T> void XCall::setup_const(XCallType call_type, const T &call_data) {
    setup_const(call_type, cpptype_to_XType<T>(), &call_data);
}

//---------------------------------------------------------------------
template<class T> T* XCall::data() {
    if (!has_type(cpptype_to_XType<T>())) return nullptr;
    return (T*) data();
}

template<class T> const T* XCall::data_const() const {
    if (!has_type(cpptype_to_XType<T>())) return nullptr;
    return (const T*) data_const();
}

//---------------------------------------------------------------------

