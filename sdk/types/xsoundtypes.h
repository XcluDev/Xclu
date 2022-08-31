#pragma once

#include "xbasictypes.h"
#include "xarray.h"

class XSoundFormat {
public:
    int sample_rate = 0;
    int channels = 0;
    XSoundFormat();
    XSoundFormat(int sample_rate, int channels);
};

class XSoundBuffer {
public:
    XSoundFormat format;
    int samples;
    XArray buffer;
    XSoundBuffer();
    XSoundBuffer(const XSoundFormat &format, int samples);
    void allocate(const XSoundFormat &format, int samples);
};

