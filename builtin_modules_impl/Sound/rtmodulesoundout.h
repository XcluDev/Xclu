#ifndef RTMODULESOUNDOUT_H
#define RTMODULESOUNDOUT_H


//Реализация модуля SoundOut - вывод звукового буфера

#include <QAudioOutput>
#include <QByteArray>
#include <QIODevice>
#include <QObject>
#include <QScopedPointer>

#include "incl_h.h"
#include "rtmodule.h"
#include "xcluarray.h"
#include "xcluobjectsoundformat.h"
#include "xcluprotecteddata.h"

class Module;

//Данные для обмена с generator, которые защищаются с помощью mutex
struct RtModuleSoundOutData: public XcluProtectedData
{
    int play_test_sound_ = 0;   //воспроизводить ли тестовый звук

    //список ссылок на другие модули, которым высылать call
    QVector<Module *> modules_;

    //громкости
    QVector<float> volumes_;

    //данные об ошибке
    ErrorInfo err;

    void clear() {
        play_test_sound_ = 0;
        modules_.clear();
        volumes_.clear();
        err.clear();
    }

};


//Генератор звука
class RtModuleSoundOutGenerator : public QIODevice
{
    Q_OBJECT

public:
    RtModuleSoundOutGenerator(const QAudioFormat &format, RtModuleSoundOutData *data);

    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
    qint64 bytesAvailable() const override;

private:
    //QByteArray m_buffer;
    QAudioFormat format_;

    RtModuleSoundOutData *data_;

    //функция создания звука, во float
    //вызывает нужные модули и заполняет тестовым звуком, если требуется
    void request_sound(int samples, int channels); //создать звук в объекте sound_
    XcluObject sound_;  //звук

    //тестовый генератор звука
    qreal test_phase_ = 0;
};


//Модуль
class RtModuleSoundOut: public RtModule
{
    Q_OBJECT
public:
    RtModuleSoundOut();
    ~RtModuleSoundOut();

    static QString *static_class_name_ptr; //"SoundOut", эта переменная используется для создания новых объектов
    static RtModuleSoundOut *new_module();

protected:
    //Выполнение
    virtual void execute_start_internal();
    virtual void execute_update_internal();
    virtual void execute_stop_internal();

    //режим выбора аудиоустройства
    enum SelectDevice: int {
        SelectDeviceDefault = 0,
        SelectDeviceByIndex = 1,
        SelectDeviceByName = 2,
        SelectDeviceByN = 3
    };

    bool audio_tried_to_start_ = false;
    void start_audio();
    void stop_audio();

    void start_audio(const QAudioDeviceInfo &deviceInfo);

    //устройство вывода звука
    QScopedPointer<QAudioOutput> m_audioOutput;

    //генератор звука
    QScopedPointer<RtModuleSoundOutGenerator> m_generator;

    //данные для обмена с генератором
    RtModuleSoundOutData data_;

    bool audio_started_ = false;
    void set_started(bool started); //ставит audio_started_ и gui-элемент is_started

    //печать текущего формата в used_format
    void set_format(const QAudioFormat &format);
    //печать размера буфера при подключении устройства (запрашивается у устройства) в used_format
    void set_buffer_size(int buffer_size);

    int buffer_size_ = 0;

    //печать в консоль доступных устройств
    void print_devices();
    bool print_devices_worked_ = false;

    //печать в консоль поддерживаемых форматов запускаемого устройства
    void print_formats(const QAudioDeviceInfo &deviceInfo);
    bool print_formats_worked_ = false;

    //работа с громкостью
    void check_volume_change();

protected slots:
    void on_changed_audio_state(QAudio::State state);

};


#endif // RTMODULESOUNDOUT_H
