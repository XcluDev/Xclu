#pragma once

// Типы для XCall
#includ <QString>


struct XCallCreateWidget {
    QString in_parent_id;
    void* out_widget = nullptr;
};

struct XCallSoundBufferAdd {
    int sample_rate = 0;
    int samples = 0;
    int channels = 0;
    float *data = nullptr;
};

struct XCallSoundBufferReceived {
    int sample_rate = 0;
    int samples = 0;
    int channels = 0;
    float *data = nullptr;
};

