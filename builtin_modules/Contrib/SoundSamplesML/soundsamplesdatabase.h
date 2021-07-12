#ifndef SOUNDSAMPLESDATABASE_H
#define SOUNDSAMPLESDATABASE_H

/*
Sound database
*/


#include "sdk_h.h"

class SoundSamplesDatabase
{
public:
    void clear();
    void add(QVector<int16> sample);
    void save(QString file_name);
    void load(QString file_name);

    QVector<QVector<int16>> &samples() { return samples_; }
    int size() { return samples_.size(); }; //number of sampler
    bool is_equal_length(); //check all samples have equal length and there are is at least one sample
protected:
    QVector<QVector<int16>> samples_;
};


#endif // SOUNDSAMPLESDATABASE_H
