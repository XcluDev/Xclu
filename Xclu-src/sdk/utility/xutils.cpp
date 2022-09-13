#include "xutils.h"
#include "xhandlingerrors.h"

//---------------------------------------------------------------------
int x_string_to_int(const QString &s, bool halt_on_error) {
    bool ok;
    auto v = s.toInt(&ok);
    if (halt_on_error)
        xc_assert(ok, QString("x_string_to_int error - '%1'").arg(s));
    return v;
}

float x_string_to_float(const QString &s, bool halt_on_error) {
    bool ok;
    auto v = s.toFloat(&ok);
    if (halt_on_error)
        xc_assert(ok, QString("x_string_to_int error - '%1'").arg(s));
    return v;
}

float x_string_to_double(const QString &s, bool halt_on_error) {
    bool ok;
    auto v = s.toDouble(&ok);
    if (halt_on_error)
        xc_assert(ok, QString("x_string_to_int error - '%1'").arg(s));
    return v;
}
//---------------------------------------------------------------------
