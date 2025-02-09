#pragma once

//Sound buffer input

#include <QAudioInput>
#include <QByteArray>
#include <QIODevice>
#include <QObject>
#include <QScopedPointer>

#include "sdk_h.h"
#include "xclass.h"
#include "xarray.h"
#include "xsoundtypes.h"
#include "xprotecteddata.h"

class XModule;

//Data exchange
struct XClassSoundInData {
    //list of modules for sending callbacks
    QVector<XModule *> modules_;

    XCallError err;

    void clear() {
        modules_.clear();
        err.clear();
    }

};


class XClassSoundInGenerator : public QIODevice
{
    Q_OBJECT

public:
    XClassSoundInGenerator(const QAudioFormat &format, XProtectedData_<XClassSoundInData> *data);

    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
    qint64 bytesAvailable() const override;

private:
    //QByteArray m_buffer;
    QAudioFormat format_;

    XProtectedData_<XClassSoundInData> *data_;

    //send sound callbacks with sound as float to other modules
    void send_sound_in();
    XProtectedObject sound_;
    XSoundBuffer buffer_holder_;       // linked to sound_, not use directly!

};


//XClass
class XClassSoundIn: public XClass
{
    Q_OBJECT
public:
    XClassSoundIn(QString class_name);
    virtual ~XClassSoundIn();
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

    QScopedPointer<QAudioInput> m_audioInput;
    QScopedPointer<XClassSoundInGenerator> m_generator;

    XSoundFormat format_holder_;

    //данные для обмена с генератором
    XProtectedData_<XClassSoundInData> data_;

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

