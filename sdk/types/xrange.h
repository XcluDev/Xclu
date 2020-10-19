#ifndef XRANGE_H
#define XRANGE_H

#include "incl_h.h"
#include "xparser.h"

//---------------------------------------------------------------------
//Classed for range control of int and float values
//XRange<T, int=0,1>  (0 - int, 1 - float)
//XRangeInt
//XRangeFloat
//---------------------------------------------------------------------
template<typename T, int IntFloat>
class XRange {
public:
    XRange() {}
    XRange(bool low_enabled0, T low0, bool high_enabled0, T high0) {
        setup(low_enabled0, low0, high_enabled0, high0);
    }
    //low, high can be "*" or number. "*" means no limit
    XRange(QString low0, QString high0) {
        setup(low0, high0);
    }
    void setup(bool low_enabled0, T low0, bool high_enabled0, T high0) {
        low_enabled = low_enabled0;
        low = low0;
        high_enabled = high_enabled0;
        high = high0;
    }

    //low, high can be "*" or number. "*" means no limit
    void setup(QString low0, QString high0) {
        if (low0 != "*") {
            low_enabled = true;
            if (IntFloat == 0) low = parse_int(low0, error_message("min value must be int", low0, high0));
            else low = parse_float(low0, error_message("max value must be an int", low0, high0));
        }
        if (high0 != "*") {
            high_enabled = true;
            if (IntFloat == 0) high = parse_int(high0, error_message("min value must be float", low0, high0));
            else high = parse_float(high0, error_message("max value must be float", low0, high0));
        }
    }

    //passing value through range control
    T constrain(T value) const {
        if (low_enabled) value = qMax(value, low);
        if (high_enabled) value = qMin(value, high);
        return value;
    }

    bool low_enabled = false;
    bool high_enabled = false;
    T low = 0;
    T high = 0;

protected:
    QString error_message(QString begin, QString low0, QString high0) {
        return begin + " value or '*', but is `" + low0 + ":" + high0;
    }

};

typedef XRange<int, 0> XRangeInt;
typedef XRange<float, 1> XRangeFloat;


#endif // XRANGE_H
