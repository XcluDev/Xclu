#include "soundsamplesdatabase.h"
#include "incl_cpp.h"
#include "xcore.h"
#include "xc_audio_wavfile.h"
#include "xc_audio.h"
#include "xc_files.h"

//---------------------------------------------------------------------
void SoundSamplesDatabase::set_params(int sample_rate, int channels) {
    sample_rate_ = sample_rate;
    channels_ = channels;
}

//---------------------------------------------------------------------
void SoundSamplesDatabase::clear() {
    sounds_.clear();
    length_ = 0;
    sample_rate_ = 0;
    channels_ = 0;        
}

//---------------------------------------------------------------------
void SoundSamplesDatabase::add(QVector<int16> sound) {
    sounds_.push_back(sound);
}

//---------------------------------------------------------------------
//check all samples have equal length and there are is at least one sample
bool SoundSamplesDatabase::is_equal_length() {
    if (size() == 0) return false;
    int len = sounds_[0].size();
    bool result = true;
    for (int i=1; i<size(); i++) {
        int l = sounds_[i].size();
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
    int len = sounds_[0].length();
    for (auto &s: sounds_) {
        len = qMin(len, s.size());
    }
    //truncate
    for (auto &s: sounds_) {
        s.resize(len);
    }
    return len;
}

//---------------------------------------------------------------------
void SoundSamplesDatabase::save(QString folder) {
    QString file_bin = folder + "/database.bin";
    QString file_ini = folder + "/database.ini";

    //Saving binary
    //we are not using xc_write_binary_file() here for speed up - because many chunks

    QFile file(file_bin);
    xc_assert(file.open(QIODevice::WriteOnly),
              "Can't create database binary file for writing: '" + file_bin + "'");
    for (int i=0; i<size(); i++) {
        auto &sample = sounds_[i];
        int n = sample.size();
        int written = file.write((const char *)sample.data(), n);
        xc_assert(n == written, QString("Not all data is written to file, want to write %1, but written %2")
              .arg(n).arg(written));
    }
    file.close();

    //Saving ini
    QStringList ini;
    ini.append(QString("sounds=%1").arg(size()));
    xc_assert(is_equal_length(), "Internal error - all sounds must have equal length");
    ini.append(QString("length=%1").arg(sounds_[0].size()));
    ini.append(QString("sample_rate=%1").arg(sample_rate_));
    ini.append(QString("channels=%1").arg(channels_));
    xc_write_text_file(ini, file_ini);

}

//---------------------------------------------------------------------
void SoundSamplesDatabase::load(QString folder) {
    QString file_bin = folder + "/database.bin";
    QString file_ini = folder + "/database.ini";

    xc_assert(xc_file_exists(file_bin), QString("File '%1' doesn't exists").arg(file_bin));
    xc_assert(xc_file_exists(file_ini), QString("File '%1' doesn't exists").arg(file_ini));

    clear();

    //Ini
    auto ini = xc_read_text_file(file_ini);

    int count = 0;
    for (auto &s: ini) {
        auto item = s.split("=");
        if (item.length()==2) {
            QString name = item[0];
            int value = item[1].toInt();
            if (name == "sounds") {
                count = value;
                xc_assert(count>0, QString("Bad number of sounds specified in ini, %1").arg(count));
            }
            if (name == "length") {
                length_ = value;
                xc_assert(length_>0, QString("Bad length of sound specified in ini, %1").arg(length_));
            }
            if (name == "sample_rate") {
                sample_rate_ = value;
                xc_assert(sample_rate_>0, QString("Bad sample rate specified in ini, %1").arg(sample_rate_));
            }
            if (name == "channels") {
                channels_ = value;
                xc_assert(channels_>0, QString("Bad number of channels specified in ini, %1").arg(sample_rate_));
                //Currently we accept only mono sounds.
                xc_assert(channels_ == 1, QString("Only mono-sound databases are currently supported"));
            }
        }
    }
    //Data
    //expected size
    int file_size = count * length_ * channels_;

    //load
    //we load whole file into memory //TODO may work poor for small computers, double memory allocation - whole and for each sound
    auto data = xc_read_binary_file(file_bin);
    xc_assert(data.size() == file_size,
              QString("Bad database binary file size, expected %1 bytes, but get %2 bytes")
              .arg(file_size).arg(data.size()));

    sounds_.resize(count);
    int k = 0;
    int sound_bytes = length_ * channels_;
    for (int i=0; i<count; i++) {
        auto &sound = sounds_[i];
        sound.resize(length_);
        memcpy(&sound[0], data.data() + k, sound_bytes);
        k += sound_bytes;
    }
}

//---------------------------------------------------------------------
