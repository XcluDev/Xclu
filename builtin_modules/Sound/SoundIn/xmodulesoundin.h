#ifndef XMODULESOUNDIN_H
#define XMODULESOUNDIN_H


//Sound buffer input

#include <QAudioInput>
#include <QByteArray>
#include <QIODevice>
#include <QObject>
#include <QScopedPointer>

#include "sdk_h.h"
#include "xclass.h"
#include "xarray.h"
#include "xobjectsoundformat.h"
#include "xprotecteddata.h"

class Module;

//Data exchange
struct XModuleSoundInData {
    //list of modules for sending callbacks
    QVector<Module *> modules_;

    ErrorInfo err;

    void clear() {
        modules_.clear();
        err.clear();
    }

};


class XModuleSoundInGenerator : public QIODevice
{
    Q_OBJECT

public:
    XModuleSoundInGenerator(const QAudioFormat &format, XProtectedData_<XModuleSoundInData> *data);

    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
    qint64 bytesAvailable() const override;

private:
    //QByteArray m_buffer;
    QAudioFormat format_;

    XProtectedData_<XModuleSoundInData> *data_;

    //send sound callbacks with sound as float to other modules
    void send_sound_in();
    XProtectedObject sound_;

};


//Module
class XModuleSoundIn: public XClass
{
    Q_OBJECT
public:
    XModuleSoundIn(QString class_name);
    virtual ~XModuleSoundIn();
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
    QScopedPointer<XModuleSoundInGenerator> m_generator;

    //данные для обмена с генератором
    XProtectedData_<XModuleSoundInData> data_;

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


#endif // XMODULESOUNDIN_H
