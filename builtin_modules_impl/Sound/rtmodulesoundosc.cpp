#include "rtmodulesoundosc.h"
#include "incl_cpp.h"
#include <qmath.h>
#include <qendian.h>
#include "rtmoduleregistrar.h"
#include "projectruntime.h"
#include "module.h"
#include "xcluobjectimage.h"

//заполнение имени класса и регистрация класса
REGISTRAR(SoundOsc)


//---------------------------------------------------------------------
//запускать перед стартом звука, после считывания параметров из GUI
void RtModuleSoundOscData::init() {
    //установка параметров
    vol_ = volume * vol_second;
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
void RtModuleSoundOscData::update_steps(float sample_rate) {
    sample_rate_ = sample_rate;
    step_vol_ = vol_speed / (sample_rate * 0.1);
    step_freq_ = freq_speed / (sample_rate * 0.1);

    //фазы
    fm_phase_ = fmod(fm_phase_, 2 * M_PI);

    phase_ = fmod(phase_, 2 * M_PI);
}

//---------------------------------------------------------------------
//получить значение звука
float RtModuleSoundOscData::get_next_sample() {

    //обновление параметров
    float target_freq = freq;
    float target_vol = volume * vol_second;

    if (fm_enabled) {
        update_freq(fm_rate_, fm_rate);
        update_freq(fm_range_, fm_range);

        fm_phase_ += fm_rate_ * 2 * M_PI / sample_rate_;
        target_freq += qSin(fm_phase_) * fm_range_;
    }

    if (am_enabled) {
        update_freq(am_rate_, am_rate);
        update_vol(am_range_, am_range);    //внимание, тут именно vol

        am_phase_ += am_rate_ * 2 * M_PI / sample_rate_;
        target_vol *= 1 + qSin(am_phase_) * am_range_;
    }

    update_freq(freq_, target_freq);
    update_vol(vol_, target_vol);

    //генерация звука
    phase_ += freq_ * 2 * M_PI / sample_rate_;
    float v = qSin(phase_) * vol_;

    return v;
}

//---------------------------------------------------------------------
//плавная модификация параметра громкости к целевой
//со скоростью vol_speed за 0.1 сек
void RtModuleSoundOscData::update_vol(float &var, float target) {
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
void RtModuleSoundOscData::update_freq(float &var, float target) {
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
/*static*/ RtModuleSoundOsc *RtModuleSoundOsc::new_module() {
    return new RtModuleSoundOsc();
}

//---------------------------------------------------------------------
RtModuleSoundOsc::RtModuleSoundOsc()
    :RtModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
RtModuleSoundOsc::~RtModuleSoundOsc()
{

}

//---------------------------------------------------------------------
void RtModuleSoundOsc::execute_start_internal() {
    //Очистка переменных

    update_data();
    {
        DataAccess access(data_);
        data_.init();   //устанавливает первоначальные данные из GUI
    }

}

//---------------------------------------------------------------------
void RtModuleSoundOsc::execute_update_internal() {
    //считываем данные из GUI
    update_data();
}

//---------------------------------------------------------------------
void RtModuleSoundOsc::execute_stop_internal() {

}

//---------------------------------------------------------------------
void RtModuleSoundOsc::update_data() {
    DataAccess access(data_);

    data_.out_enabled = get_int("out_enabled");
    data_.volume = get_float("volume");
    data_.vol_second = 1; //get_float("vol_second");

    data_.freq = get_float("freq");

    data_.fm_enabled = get_int("fm_enabled");
    data_.fm_rate = get_float("fm_rate");
    data_.fm_range = get_float("fm_range");

    data_.am_enabled = get_int("am_enabled");
    data_.am_rate = get_float("am_rate");
    data_.am_range = get_float("am_range");

    data_.vol_speed = get_float("vol_speed");
    data_.freq_speed = get_float("freq_speed");

}

//---------------------------------------------------------------------
//генерация звука
void RtModuleSoundOsc::call_internal(QString function, XcluObject *input, XcluObject * /*output*/) {
    //"sound_buffer_add"
    if (function == call_function_name::sound_buffer_add()) {

        //получаем доступ к данным и звуковому буферу
        DataAccess access(data_);
        if (data_.out_enabled) {
            //qDebug() << "PCM params: " << data_.image_background << data_.pcm_speed_hz;
            ObjectReadWrite sound(input);

            float sample_rate = sound.get_int("sample_rate");
            int samples = sound.get_int("samples");
            int channels = sound.get_int("channels");
            float *data = sound.var_array("data")->data_float();


            data_.update_steps(sample_rate);    //обновляем приращение параметров

            int k = 0;
            for (int i=0; i<samples; i++) {
                //получить значение звука
                float v = data_.get_next_sample();
                for (int u=0; u<channels; u++) {
                    data[k++] += v;
                }
            }
        }
        return;
    }

}

//---------------------------------------------------------------------
