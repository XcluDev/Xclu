#include "soundsamplesdatabase.h"
#include "incl_cpp.h"
#include "xcore.h"
#include "xaudio_wavfile.h"
#include "xaudio_utils.h"
#include "xc_files.h"

//---------------------------------------------------------------------
void SoundSamplesDatabase::set_params(int sample_rate, int channels) {
    sample_rate_ = sample_rate;
    channels_ = channels;
}

//---------------------------------------------------------------------
void SoundSamplesDatabase::clear() {
    sample_rate_ = 0;
    channels_ = 0;

    samples_.clear();
}

//---------------------------------------------------------------------
void SoundSamplesDatabase::add(QVector<int16> sample) {
    samples_.push_back(sample);
}

//---------------------------------------------------------------------
//check all samples have equal length and there are is at least one sample
bool SoundSamplesDatabase::is_equal_length() {
    if (size() == 0) return false;
    int len = samples_[0].size();
    bool result = true;
    for (int i=1; i<size(); i++) {
        int l = samples_[i].size();
        if (l != len) {
            //qDebug() << "expected length " << len << ", but sample " <<  i << " has length " << l;
            result = false;
        }
    }
    return result;
}


//---------------------------------------------------------------------
//truncate samples to equal length
int SoundSamplesDatabase::truncate_to_equal_length() {
    if (size() == 0) return 0;
    //compute minimal length
    int len = samples_[0].length();
    for (auto &s: samples_) {
        len = qMin(len, s.size());
    }
    //truncate
    for (auto &s: samples_) {
        s.resize(len);
    }
    return len;
}

//---------------------------------------------------------------------
void SoundSamplesDatabase::save(QString database_file_bin, QString database_file_ini) {
    //Saving binary
    //we are not using xc_write_binary_file() here for speed up - because many chunks

    QFile file(database_file_bin);
    xc_assert(file.open(QIODevice::WriteOnly),
              "Can't create database binary file for writing: '" + database_file_bin + "'");
    for (int i=0; i<size(); i++) {
        auto &sample = samples_[i];
        int n = sample.size();
        int written = file.write((const char *)&sample[0], n);
        xc_assert(n == written, QString("Not all data is written to file, want to write %1, but written %2")
              .arg(n).arg(written));
    }
    file.close();

    //Saving ini
    QStringList ini;
    ini.append(QString("samples=%1").arg(size()));
    if (is_equal_length()) {
        ini.append(QString("length=%1").arg(samples_[0].size()));
    }
    ini.append(QString("sample_rate=%1").arg(sample_rate_));
    ini.append(QString("channels=%1").arg(channels_));
    xc_write_text_file(ini, database_file_ini);

}

//---------------------------------------------------------------------
//void SoundSamplesDatabase::load(QString file_name) {
//}

//---------------------------------------------------------------------
