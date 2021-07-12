#include "soundsamplesdatabase.h"
#include "incl_cpp.h"
#include "xcore.h"
#include "xaudio_wavfile.h"
#include "xaudio_utils.h"

//---------------------------------------------------------------------
void SoundSamplesDatabase::clear() {
    samples_.clear();
}

//---------------------------------------------------------------------
void SoundSamplesDatabase::add(QVector<int16> sample) {
    samples_.push_back(sample);
}

//---------------------------------------------------------------------
bool SoundSamplesDatabase::is_equal_length() { //check all samples have equal length and there are is at least one sample
    if (size() == 0) return false;
    int len = samples_[0].size();
    for (int i=1; i<size(); i++) {
        if (samples_[i].size() != len) return false;
    }
    return true;
}

//---------------------------------------------------------------------
void SoundSamplesDatabase::save(QString file_name) {

}

//---------------------------------------------------------------------
void SoundSamplesDatabase::load(QString file_name) {

}

//---------------------------------------------------------------------
