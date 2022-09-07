#pragma once

// Conversion of numbers to and from QString.
// Idea is taken from openFrameworks's x_to_string(), x_string_to_float(), ofToInt().

#include <QString>

template <class T>
QString x_to_string(const T& value){
    return QString::number(value);
}

template <class T>
QString x_to_string_precision(const T &value, int precision = 6, char fill = 'g'){
    return QString::number(value, fill, precision);
}

int x_string_to_int(const QString &s, bool halt_on_error = true);
float x_string_to_float(const QString &s, bool halt_on_error = true);
float x_string_to_double(const QString &s, bool halt_on_error = true);
