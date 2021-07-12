#ifndef SOUNDSAMPLESDATABASE_H
#define SOUNDSAMPLESDATABASE_H

/*
Sound database
*/


#include "sdk_h.h"

class SoundSamplesDatabase
{
public:
    void set_params(int sample_rate, int channels);
    void clear();
    void add(QVector<int16> sample);
    void save(QString database_file_bin, QString database_file_ini);
    //void load(QString file_name);

    QVector<QVector<int16>> &samples() { return samples_; }
    int size() { return samples_.size(); }; //number of sampler
    bool is_equal_length(); //check all samples have equal length and there are is at least one sample
    int truncate_to_equal_length(); //truncate samples to equal length

protected:
    QVector<QVector<int16>> samples_;
    int sample_rate_ = 0;
    int channels_ = 0;

};


#endif // SOUNDSAMPLESDATABASE_H
