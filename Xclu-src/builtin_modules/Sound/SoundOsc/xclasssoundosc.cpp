#include "xclasssoundosc.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"
#include "xobjectvis.h"

//registering module implementation
REGISTER_XCLASS(SoundOsc)


//---------------------------------------------------------------------
//запускать перед стартом звука, после считывания параметров из GUI
void XClassSoundOscData::init() {
    //установка параметров
    vol_ = volume * vol_mod;
    freq_ = freq;

    fm_rate_ = fm_rate;
    fm_range_ = fm_range;
    fm_phase_ = 0;

    am_rate_ = am_rate;
    am_range_ = am_range;
    am_phase_ = 0;

    //сброс генерации звука
    phase_ = 0;

}

//---------------------------------------------------------------------
//обновить размер шагов - вызывается для одного вызова заполнения буфера
//также, делает warping фаз
void XClassSoundOscData::update_steps(float sample_rate) {
    sample_rate_ = sample_rate;
    step_vol_ = vol_speed / (sample_rate * 0.1);
    step_freq_ = freq_speed / (sample_rate * 0.1);

    //фазы
    fm_phase_ = fmod(fm_phase_, 2 * M_PI);

    phase_ = fmod(phase_, 2 * M_PI);
}

//---------------------------------------------------------------------
//получить значение звука
float XClassSoundOscData::get_next_sample() {

    //обновление параметров
    float target_freq = freq;
    float target_vol = volume * vol_mod;
    update_freq(freq_, target_freq);
    update_vol(vol_, target_vol);

    //modulation
    float freq = freq_;
    float vol = vol_;
    if (fm_enabled) {
        update_freq(fm_rate_, fm_rate);
        update_freq(fm_range_, fm_range);

        fm_phase_ += fm_rate_ * 2 * M_PI / sample_rate_;
        freq += qSin(fm_phase_) * fm_range_;
    }

    if (am_enabled) {
        update_freq(am_rate_, am_rate);
        update_vol(am_range_, am_range);    //внимание, тут именно vol

        am_phase_ += am_rate_ * 2 * M_PI / sample_rate_;
        vol *= 1 + qSin(am_phase_) * am_range_;
    }



    //генерация звука
    phase_ += freq * 2 * M_PI / sample_rate_;
    float v = qSin(phase_) * vol;

    return v;
}

//---------------------------------------------------------------------
//плавная модификация параметра громкости к целевой
//со скоростью vol_speed за 0.1 сек
void XClassSoundOscData::update_vol(float &var, float target) {
    if (var < target) {
        var = qMin(var + step_vol_, target);
    }
    else {
        var = qMax(var - step_vol_, target);
    }
}

//---------------------------------------------------------------------
//плавная модификация параметра громкости к целевой
//со скоростью freq_speed за 0.1 сек
void XClassSoundOscData::update_freq(float &var, float target) {
    if (var < target) {
        var = qMin(var + step_freq_, target);
    }
    else {
        var = qMax(var - step_freq_, target);
    }
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
XClassSoundOsc::XClassSoundOsc(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassSoundOsc::~XClassSoundOsc()
{

}

//---------------------------------------------------------------------
void XClassSoundOsc::start() {
    //Очистка переменных

    update_data();
    data_.write().data().init();   //устанавливает первоначальные данные из GUI

}

//---------------------------------------------------------------------
void XClassSoundOsc::update() {
    //считываем данные из GUI
    update_data();
}

//---------------------------------------------------------------------
void XClassSoundOsc::stop() {

}

//---------------------------------------------------------------------
void XClassSoundOsc::update_data() {
    auto write = data_.write();
    auto &data = write.data();

    data.out_enabled = geti_out_enabled();

    //volume
    data.volume = getf_volume();
    data.vol_mod = getf_volume_mod();

    //freq
    data.freq = getf_freq();

    //fm, am
    data.fm_enabled = geti_fm_enabled();
    data.fm_rate = getf_fm_rate();
    data.fm_range = getf_fm_range();

    data.am_enabled = geti_am_enabled();
    data.am_rate = getf_am_rate();
    data.am_range = getf_am_range();

    //speed
    data.vol_speed = getf_vol_speed();
    data.freq_speed = getf_freq_speed();
}

//---------------------------------------------------------------------
//sound generation
//"sound_buffer_add" call, fills `data` buffer
//there are required to fill channels * samples values at data
void XClassSoundOsc::on_sound_buffer_add(int sample_rate, int channels, int samples, float *data) {
    //получаем доступ к данным и звуковому буферу
    auto write = data_.write();
    auto &dat = write.data();
    if (dat.out_enabled) {
        dat.update_steps(sample_rate);    //обновляем приращение параметров
        int k = 0;
        for (int i=0; i<samples; i++) {
            //получить значение звука
            float v = dat.get_next_sample();
            for (int u=0; u<channels; u++) {
                data[k++] += v;
            }
        }
    }
}

//---------------------------------------------------------------------
