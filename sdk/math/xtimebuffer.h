#ifndef XTIMEBUFFER_H
#define XTIMEBUFFER_H

// XTimeBuffer - buffer for storing any data and time.
// Allows to push a data with time, and then clear data in a given interval.
// Used in XClassBciNeuroplay for buffering async data for eye blinking removal.

#include "incl_h.h"

template<typename Data>
class XTimeBuffer
{
public:
    void push(const Data &data, float time) {
        data_.push_back({data, time});
    }

    bool has_earlier(float time) {
        for (auto &v: data_) {
            if (v.time < time) {
                return true;
            }
        }
        return false;
    }

    Data pop() {
        xc_assert(!data_.empty(), "XTimeBuffer is empty, can't 'pop' from it");
        Data v = data_[0].data;
        data_.pop_back();
        return v;
    }

    void clear() {
        data_.clear();
    }

    void clear_range(float time_from, float time_to) {
        for (int i=0; i<data_.size();) {
            if (xinrangef(data_[i].time, time_from, time_to)) {
                data_.remove(i);
            }
            else {
                i++;
            }
        }
    }
protected:
    struct DataTime { // for constructing object, use {data, time}
        Data data;
        float time = 0;
    };
    QVector<DataTime> data_;
};

#endif // XTIMEBUFFER_H
