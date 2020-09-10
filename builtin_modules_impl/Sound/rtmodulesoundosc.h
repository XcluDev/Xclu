#ifndef RTMODULESOUNDOSC_H
#define RTMODULESOUNDOSC_H

//Реализация модуля SoundOsc - осциллятор с FM и AM модуляциями

#include <QObject>
#include <QScopedPointer>
#include <QMutex>

#include "incl_h.h"
#include "rtmodule.h"
#include "xcluarray.h"
#include "xcluobjectsoundformat.h"
#include "xcluprotecteddata.h"

//Данные для генерации
struct RtModuleSoundOscData: public XcluProtectedData
{
    void init();    //запускать перед стартом звука, после считывания параметров из GUI

    //обновить размер шагов - вызывается для одного вызова заполнения буфера
    //также, делает warping фаз
    void update_steps(float sample_rate);

    //получить значение звука
    float get_next_sample();

    //---------------------------------
    //внутренние параметры
    float sample_rate_ = 44100; //обновляется при вызове get_next_sample
    float step_vol_ = 0;    //шаги для плавного изменения параметров
    float step_freq_ = 0;

    float vol_ = 0;
    float freq_ = 0;

    float fm_rate_ = 0;
    float fm_range_ = 0;
    float fm_phase_ = 0;

    float am_rate_ = 0;
    float am_range_ = 0;
    float am_phase_ = 0;

    float phase_ = 0;


    //---------------------------------
    //плавная модификация параметра громкости к целевой со скоростью vol_speed за 0.1 сек
    void update_vol(float &var, float target);
    //плавная модификация параметра громкости к целевой со скоростью freq_speed за 0.1 сек
    void update_freq(float &var, float target);

    //внешние параметры
    int out_enabled = 0;       //Generate output sound.
    int mod_enabled = 1;        //Is modulatio enabled
    float volume = 0.5f;        //Main volume.
    float vol_mod=1;            //External modulation

    float freq=440;     //Oscillator basic frequency.

    int fm_enabled=0;   //Is FM enabled.
    float fm_rate=5;    //FM frequency.
    float fm_range=10;  //FM range (instead of index), Hz


    int am_enabled=0;   //Is AM enabled.
    float am_rate=5;    //AM rate.
    float am_range=0.1f;  //AM range.

    //испльзуются в update_steps()
    float vol_speed=1;  //Speed of changing volume. 1/(0.1 sec)
    float freq_speed=1; //Speed of changing frequency. Hz/(0.1 sec)
};

//Модуль
class RtModuleSoundOsc: public RtModule
{
    Q_OBJECT
public:
    RtModuleSoundOsc();
    ~RtModuleSoundOsc();

    static QString *static_class_name_ptr;
    static RtModuleSoundOsc *new_module();

protected:
    //Выполнение
    virtual void loaded_impl() {}
    virtual void start_impl();
    virtual void update_impl();
    virtual void stop_impl();

    //генерация звука
    virtual void call_impl(QString function, XDict *input, XDict * /*output*/);

    //данные - они обновляются из GUI в основном потоке
    //и используются при генерации звука
    RtModuleSoundOscData data_;
    void update_data();

};

#endif // RTMODULESOUNDOSC_H
