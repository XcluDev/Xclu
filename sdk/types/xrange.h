#ifndef XRANGE_H
#define XRANGE_H

#include "incl_h.h"
#include "xparser.h"
#include "math_utils.h"
#include "console.h"

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
            if (IntFloat == 0) low = xparse_int(low0, error_message("min value must be int", low0, high0));
            else low = xparse_float(low0, error_message("max value must be an int", low0, high0));
        }
        if (high0 != "*") {
            high_enabled = true;
            if (IntFloat == 0) high = xparse_int(high0, error_message("min value must be float", low0, high0));
            else high = xparse_float(high0, error_message("max value must be float", low0, high0));
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

    //number of ticks for float slider, wihtout counting zero, so really there are ticks+1
    //0 means that there are no need in slider
    int ticks(float step) const {
        xclu_assert(IntFloat == 1, "XRange: ticks() is only float");
        if (low_enabled && high_enabled && low < high && step>0) {
            return qMax(int((high - low)/step),2);
        }
        return 0;
    }
    //tick to value
    float tick_to_value(int tick, int ticks) const {
        xclu_assert(IntFloat == 1, "XRange: tick_to_value() is only for float");
        if (low_enabled && high_enabled && ticks > 0) {
            return xmapf_clamped(tick, 0, ticks, low, high);
        }
        return 0;
    }
    int value_to_ticks(float value, int ticks) const {
        xclu_assert(IntFloat == 1, "XRange: value_to_ticks() is only for float");
        if (low_enabled && high_enabled && ticks > 0 && low < high) {
            return xmapf_clamped(value, low, high, 0, ticks);
        }
        return 0;
    }
protected:
    QString error_message(QString begin, QString low0, QString high0) {
        return begin + " value or '*', but is `" + low0 + ":" + high0;
    }

};

typedef XRange<int, 0> XRangeInt;
typedef XRange<float, 1> XRangeFloat;


#endif // XRANGE_H
