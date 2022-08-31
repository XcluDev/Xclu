#pragma once

#include <QString>

class XTypeUtils
{
public:
    // Universal converter for types enums
    static QString to_string(int i, int N, const QString array[]);
    static int to_type(const QString &str, int N, const QString array[]);
};

