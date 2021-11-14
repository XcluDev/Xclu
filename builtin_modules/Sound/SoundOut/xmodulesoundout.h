#ifndef XMODULESOUNDOUT_H
#define XMODULESOUNDOUT_H


//Реализация модуля SoundOut - вывод звукового буфера

#include <QAudioOutput>
#include <QByteArray>
#include <QIODevice>
#include <QObject>
#include <QScopedPointer>

#include "sdk_h.h"
#include "xmodule.h"
#include "xarray.h"
#include "xobjectsoundformat.h"
#include "xprotecteddata.h"

class Module;

//Данные для обмена с generator, которые защищаются с помощью mutex
struct XModuleSoundOutData: public XcluProtectedData
{
    int play_test_sound_ = 0;   //generate test sound
    int play_left_ = 1;
    int play_right_ = 1;
    float play_volume_ = 0.5;
    float play_freq_ = 440;


    float volume_left_ = 1;          //channel volume
    float volume_right_ = 1;

    //список ссылок на другие модули, которым высылать call
    QVector<Module *> modules_;

    //громкости
    QVector<float> volumes_;

    //данные об ошибке
    ErrorInfo err;

    void clear() {
        play_test_sound_ = 0;
        volume_left_ = 1;
        volume_right_ = 1;

        modules_.clear();
        volumes_.clear();
        err.clear();
    }

};


//Генератор звука
class XModuleSoundOutGenerator : public QIODevice
{
    Q_OBJECT

public:
    XModuleSoundOutGenerator(const QAudioFormat &format, XModuleSoundOutData *data);

    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
    qint64 bytesAvailable() const override;

private:
    //QByteArray m_buffer;
    QAudioFormat format_;

    XModuleSoundOutData *data_;

    //функция создания звука, во float
    //вызывает нужные модули и заполняет тестовым звуком, если требуется
    void request_sound(int samples, int channels); //создать звук в объекте sound_
    XProtectedObject sound_;  //звук

    //тестовый генератор звука
    qreal test_phase_ = 0;
};


//Модуль
class XModuleSoundOut: public XModule
{
    Q_OBJECT
public:
    XModuleSoundOut(QString class_name);
    virtual ~XModuleSoundOut();
protected:
#include "auto.h"

    //Выполнение
    virtual void on_loaded();
    virtual void start();
    virtual void update();
    virtual void stop();
    virtual void on_button_pressed(QString button_id);

    bool audio_tried_to_start_ = false;
    void start_audio();
    void stop_audio();

    void start_audio(const QAudioDeviceInfo &deviceInfo);

    //устройство вывода звука
    QScopedPointer<QAudioOutput> m_audioOutput;

    //генератор звука
    QScopedPointer<XModuleSoundOutGenerator> m_generator;

    //данные для обмена с генератором
    XModuleSoundOutData data_;

    bool audio_started_ = false;
    void set_started(bool started); //ставит audio_started_ и gui-элемент is_started

    //печать текущего формата в used_format
    void set_format(const QAudioFormat &format);
    //печать размера буфера при подключении устройства (запрашивается у устройства) в used_format
    void set_buffer_size(int buffer_size);

    int buffer_size_ = 0;

    //печать в консоль доступных устройств
    void print_devices();

    //печать в консоль поддерживаемых форматов запускаемого устройства
    void print_formats(const QAudioDeviceInfo &deviceInfo);

    //работа с громкостью
    void check_volume_change();

protected slots:
    void on_changed_audio_state(QAudio::State state);

};


#endif // XMODULESOUNDOUT_H
