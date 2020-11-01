#include "xparser.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
float xparse_float(QString line, QString error_message) {
    bool ok;
    float value = line.toFloat(&ok);
    xclu_assert(ok, error_message);
    return value;
}

//---------------------------------------------------------------------
int xparse_int(QString line, QString error_message) {
    bool ok;
    float value = line.toInt(&ok);
    xclu_assert(ok, error_message);
    return value;
}

//---------------------------------------------------------------------
//seconds -> HMS, that is 00:00:00:0
QString xparse_seconds_to_hms(double seconds) {
    if (seconds < 0) { return "---"; }
    int s = int(seconds);
    float frac = int((seconds - s)*10);
    int h = s / 3600;
    s %= 3600;
    int m = s / 60;
    s %= 60;
    return QString("%1:%2:%3:%4").arg(h, 2, 10, QLatin1Char('0'))
            .arg(m, 2, 10, QLatin1Char('0'))
            .arg(s, 2, 10, QLatin1Char('0'))
            .arg(frac);
}

//---------------------------------------------------------------------
