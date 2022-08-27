#pragma once

#include "xarray.h"

class XSoundFormat {
public:
    int sample_rate = 0;
    int channels = 0;
};

class XSoundBuffer {
public:
    XSoundFormat format;
    XArray buffer;
};

