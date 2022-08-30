#pragma once

#include <QPainter>
#include <QVector>
#include <QString>
#include <xcallerror.h>

//Types of intermodules calls
enum class XCallType : int {
    None           = 0,
    Custom         = 1,
    CreateWidget   = 2,
    SoundBufferAdd = 3,
    SoundBufferReceived = 4,
    N              = 5
};

QString xcalltype_to_string(XCallType type);
QString xcalltype_to_string_for_user(XCallType type);   //not generates exception
XCallType xstring_to_calltype(QString type_str);

/// Функция для конвертации типа C++ в XCallType
template<class T> XCallType cpptype_to_XCallType();

// Data for intermodule calls
struct XCall {
    XCall() {}

    void setup(XCallType type, void *data);

    /// We separating const data on compiling-level
    void setup_const(XCallType type, const void *data);

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

    XCallType type() const;
    void assert_type(XCallType type) const;
    bool has_type(XCallType type) const;

    XCallError& error();
protected:
    XCallType type_ = XCallType::None;
    void* data_ = nullptr;
    const void* data_const_ = nullptr; // Const data stores separately
    XCallError error_;
};



