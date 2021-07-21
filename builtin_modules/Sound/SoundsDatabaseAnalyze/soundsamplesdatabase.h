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
    void add(QVector<int16> sound);
    void save(QString folder);
    void load(QString folder);

    //sounds
    QVector<QVector<int16>> &sounds() { return sounds_; }

    //number of sounds
    int size() { return sounds_.size(); }; //number of sounds

    //length of the each sound
    int length() { return length_; }
    int sample_rate() { return sample_rate_; }
    int channels() { return channels_; }

    //utilities for truncating different-sized sounds
    bool is_equal_length(); //check if all sounds have equal length and there are is at least one sound
    int truncate_to_equal_length(); //truncate sounds to equal length

protected:
    QVector<QVector<int16>> sounds_;
    int length_ = 0;
    int sample_rate_ = 0;
    int channels_ = 0;

};


#endif // SOUNDSAMPLESDATABASE_H
