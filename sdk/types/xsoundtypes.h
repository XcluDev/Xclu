#pragma once

#include "xbasictypes.h"
#include <QVector>

class XSoundFormat {
public:
    int sample_rate = 0;
    int channels = 0;
    XSoundFormat();
    XSoundFormat(int sample_rate, int channels);
    void setup(int sample_rate, int channels);
    void clear();
};

class XSoundBuffer {
public:
    XSoundFormat format;
    int samples;
    QVector<float32> buffer;
    XSoundBuffer();
    XSoundBuffer(const XSoundFormat &format, int samples);
    void allocate(const XSoundFormat &format, int samples, bool set_zero = true);
    void clear();
};

