#pragma once

#include <QPainter>
#include <QVector>
#include <QString>
#include "xobject.h"
#include "xmodule.h"


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

//Error type for intermodule calls
struct XCallError {
    XCallError() {}
    XCallError(QString text);
    //добавить к тексту ошибки предысторию с "\n" - полезно при передаче ошибок между уровнями, дописывая подробности
    XCallError(QString prepend_text, const XCallError &err);
    void clear();
    void setup(QString text);
    void prepend(QString prepend_text, const XCallError &err);
    //извлечение информации о том, есть ли ошибка
    bool is_error() const { return is_error_; }
    QString error_text() const { return error_text_; }
    void throw_error();  //если есть ошибка - сгенерировать исключение
protected:
    bool is_error_ = false;
    QString error_text_;
};


// Data for intermodule calls
struct XCallData {
    XCallType type = XCallType::None;
    QString str_data;
    void *ptr_data = nullptr;
    XCallError error;
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

// Utility class for intermodule calls
class XCallUtils {
public:
    //----------------------------------------------------------
    //Find modules by a filter
    //----------------------------------------------------------
    // 'accept_calls_filter', 'send_calls_filter', 'type_filter' are parts of name,
    // if XCallType::None or if empty - it means "all" for a given filter
    static QVector<XModule *> find_modules_by_filter(XCallType accept_calls_filter = XCallType::None,
                                             XCallType send_calls_filter = XCallType::None,
                                             QString class_filter = "",
                                             bool require_enabled = true);

protected:
    // static void call(XModule *module, XCallType function, XObject *input, XObject *output = nullptr);
};
