#include "xparser.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
float parse_float(QString line, QString error_message) {
    bool ok;
    float value = line.toFloat(&ok);
    xclu_assert(ok, error_message);
    return value;
}

//---------------------------------------------------------------------
int parse_int(QString line, QString error_message) {
    bool ok;
    float value = line.toInt(&ok);
    xclu_assert(ok, error_message);
    return value;
}

//---------------------------------------------------------------------
