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

// Data for intermodule calls
struct XCall {
    XCall() {}

    void setup(XCallType type, void *data);
    /// Typed implementations for XCallCreateWidget, XCallSoundBufferAdd and others
    /// Example of usage:
    /// XCallCreateWidget call_data = {...};
    /// XCall call;
    /// call.setup<XCallCreateWidget>(call_data);
    template<class T> void setup(T &call_data);

    void* data();
    /// Typed implementations
    /// Example usage: auto* call_data = call.data<XCallCreateWidget>();
    template<class T> T* data();

    XCallType type();
    void assert_type(XCallType type);

    XCallError& error();
protected:
    XCallType type_ = XCallType::None;
    void* data_ = nullptr;
    XCallError error_;


};

// Particular implementations of ptr_data at XCall Data
struct XCallCreateWidget {
    QString in_parent_id;
    void* out_widget = nullptr;
};

struct XCallSoundBufferAdd {
    int sample_rate = 0;
    int samples = 0;
    int channels = 0;
    float *data = nullptr;
};

struct XCallSoundBufferReceived {
    int sample_rate = 0;
    int samples = 0;
    int channels = 0;
    float *data = nullptr;
};

