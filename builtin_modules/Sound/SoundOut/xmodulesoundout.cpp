#include "xmodulesoundout.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "projectruntime.h"
#include "module.h"

//registering module implementation
REGISTER_XMODULE(SoundOut)

//---------------------------------------------------------------------
XModuleSoundOutGenerator::XModuleSoundOutGenerator(const QAudioFormat &format,
                                                     XModuleSoundOutData *data)
{
    xclu_assert(format.isValid(), "Not valid sound format");
    format_ = format;
    data_ = data;
}

//---------------------------------------------------------------------
void XModuleSoundOutGenerator::start()
{
    open(QIODevice::ReadOnly);
}

//---------------------------------------------------------------------
void XModuleSoundOutGenerator::stop()
{
    close();
}

//---------------------------------------------------------------------
void XModuleSoundOutGenerator::request_sound(int samples, int channels) { //создать звук в объекте sound_
    try {
        DataAccess access(data_);
        {
            auto write = sound_.write();
            XObject &sound = write.data();
            sound.clear();
            //создаем массив
            sound.seti("samples", samples);
            sound.seti("channels", channels);
            sound.seti("sample_rate", format_.sampleRate());
            XArray *arr = sound.var_array("data", true);
            arr->allocate(samples*channels, XTypeId_float);
        }

        //заполнение массива

        //тестовый звук или остальные модули
        int play_test_sound = data_->play_test_sound_;
        if (play_test_sound) {
            auto write = sound_.write();
            XObject &sound = write.data();
            float *data = sound.var_array("data")->data_float();
            float freq_Hz = 600;
            float sample_rate = format_.sampleRate();
            int k = 0;

            qreal phase_add = 2 * M_PI * freq_Hz / sample_rate;
            test_phase_ = fmod(test_phase_, 2*M_PI);
            for (int i=0; i<samples; i++) {
                float v = qSin(test_phase_);
                test_phase_+=phase_add;
                for (int u=0; u<channels; u++) {
                    data[k++] = v;
                }
            }
        }
        else {
            //вызов генерации звуков у остальных модулей
            auto sound_write = sound_.write();

            for (int i=0; i<data_->modules_.size(); i++) {
                //если модуль выдаст ошибку - оно перехватится и запишется в data_->err - см. ниже
                data_->modules_[i]->access_call(functions_names::sound_buffer_add(), sound_write.pointer());
            }
        }

        //применение громкости
        {
            auto sound_write = sound_.write();
            float *data = sound_write.data().var_array("data")->data_float();
            float volume = data_->volume_;
            for (int i=0; i<samples * channels; i++) {
                data[i] *= volume;
            }
        }
    }
    catch (XException &e) {
        qDebug() << "XException exception at request_sound: " << e.whatQt();
        DataAccess access(data_);
        data_->err = e.err();
    }
    catch(std::exception& e) {
        qDebug() << QString("Exception at request_sound: ") + e.what();
        throw e;
    }
    catch(...) {
        qDebug() << QString("Unhandled exception at request_sound");
    }
}


//---------------------------------------------------------------------
qint64 XModuleSoundOutGenerator::readData(char *data, qint64 len)
{
    qint64 total = 0;
    try {
        const int channels = format_.channelCount();
        const int audioSampleBit = format_.sampleSize();
        const int channelBytes = audioSampleBit / 8;
        const int sampleBytes = channels * channelBytes;
        //qint64 length = (format_.sampleRate() * format_.channelCount() * (format_.sampleSize() / 8))
        //                    * durationUs / 1000000;

        //m_buffer.resize(length);

        //создаем звук
        int samples = len / sampleBytes;
        request_sound(samples, channels);

        //считываем звук
        auto sound_read = sound_.read();
        XArray const *arr = sound_read.data().get_array("data");
        float const *data_float = arr->data_float();

        //записываем его в буфер звуковой карты
        unsigned char *ptr = reinterpret_cast<unsigned char *>(data);

        if (audioSampleBit == 16) {
            for (int i=0; i<samples*channels; i++) {
                if (format_.sampleType() == QAudioFormat::UnSignedInt) {
                    quint16 value = quint16((1.0 + data_float[i]) / 2 * 65535);
                    if (format_.byteOrder() == QAudioFormat::LittleEndian) {
                        qToLittleEndian<quint16>(value, ptr);
                    }
                    else {
                        qToBigEndian<quint16>(value, ptr);
                    }
                }
                if (format_.sampleType() == QAudioFormat::SignedInt) {
                    qint16 value = static_cast<qint16>(data_float[i] * 32767);
                    if (format_.byteOrder() == QAudioFormat::LittleEndian) {
                        qToLittleEndian<qint16>(value, ptr);
                    }
                    else {
                        qToBigEndian<qint16>(value, ptr);
                    }
                }
                ptr += channelBytes;
                total += channelBytes;
            }
        }
        else {
            xclu_exception(QString("SoundUnsupported sound output with bits %1").arg(audioSampleBit));
        }
    }
    catch (XException &e) {
        DataAccess access(data_);
        data_->err = e.err();
    }

    return total;
}

//---------------------------------------------------------------------
qint64 XModuleSoundOutGenerator::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

//---------------------------------------------------------------------
qint64 XModuleSoundOutGenerator::bytesAvailable() const
{
    return /*m_buffer.size() + */QIODevice::bytesAvailable();
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
XModuleSoundOut::XModuleSoundOut(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleSoundOut::~XModuleSoundOut()
{

}

//---------------------------------------------------------------------
//Звук в Qt - https://doc.qt.io/qt-5/audiooverview.html
//Вывод низкоуровневого звука - https://doc.qt.io/qt-5/qaudiooutput.html
//Пример Qt - Audio Output Example

void XModuleSoundOut::impl_start() {
    //Очистка переменных
    audio_tried_to_start_ = false;
    print_devices_worked_ = false;
    print_formats_worked_ = false;

    //данные surface
    {
        DataAccess access(data_);
        data_.clear();
    }
    buffer_size_= 0;
    seti_buffer_size(0);
    getstruct_sound_format()->write().data().clear();

    set_started(false); //также ставит gui-элемент is_started
    clear_string_connected_device_name();

    clear_string_local_console();

    //если требуется, печать подключенных устройств
    print_devices();

}

//---------------------------------------------------------------------
void XModuleSoundOut::impl_update() {
    //запустить устройство, если еще это не делали
    start_audio();

    //изменение громкости
    check_volume_change();

    //если требуется, печать подключенных устройств
    print_devices();

    //поставить информацию о том, воспроизводить ли тестовый звук
    //а также, список модулей
    //также проверить - если есть ошибка, то остановиться
    {
        DataAccess access(data_);
        data_.play_test_sound_ = geti_gen_test();
        data_.volume_ = getf_volume();
        data_.modules_ = RUNTIME.get_modules(gets_modules_list());

        //если ошибка - обработать ошибку
        data_.err.throw_error();
    }
    //показ размера буфера
    seti_buffer_size(buffer_size_);

    //Callback:
    //вызывать только если размер буфера уже ненулевой
    //RUNTIME.execute_callbacks(gets_callback_modules"));
}


//---------------------------------------------------------------------
void XModuleSoundOut::check_volume_change() {
    if (audio_started_) {
        if (was_changed_device_volume()) {
            float volume = getf_device_volume();
            qreal linearVolume = QAudio::convertVolume(volume, QAudio::LogarithmicVolumeScale, QAudio::LinearVolumeScale);
            m_audioOutput->setVolume(linearVolume);
        }
    }
}

//---------------------------------------------------------------------
void XModuleSoundOut::impl_stop() {
    stop_audio();

}


//---------------------------------------------------------------------
void XModuleSoundOut::on_changed_audio_state(QAudio::State state) {
    try {
        switch (state) {
        case QAudio::ActiveState:
            set_started(true);
            //запрос и выдача размера буфера - до запуска он неактуален
            set_buffer_size(m_audioOutput->bufferSize());
            break;
        case QAudio::SuspendedState:
        case QAudio::StoppedState:
            set_started(false);
            break;
        case QAudio::IdleState:
            //default used for handling Qt 5.13:
            //case QAudio::InterruptedState:
        default:
            QAudio::Error error = m_audioOutput->error();
            switch (error) {
            case QAudio::NoError:                
                break;
            case QAudio::IOError:
                set_started(false);
                xclu_exception("QAudio::IOError");
                break;
            case QAudio::OpenError:
                set_started(false);
                xclu_exception("QAudio::OpenError");
                break;
            case QAudio::UnderrunError:
                //TODO some text to console!
                //xclu_exception("QAudio::UnderrunError");
                break;
            case QAudio::FatalError:
                set_started(false);
                xclu_exception("QAudio::FatalError");
                break;
            }
        }
    }
    catch (XException &e) {
        DataAccess access(data_);
        data_.err = e.err();
    }
}


//---------------------------------------------------------------------
void XModuleSoundOut::stop_audio() {
    if (m_audioOutput.data()) {
        //m_audioOutput.stop - возможно, не полная остановка
        m_audioOutput.reset();
    }
}

//---------------------------------------------------------------------
void XModuleSoundOut::start_audio() {
    //запустить устройство, если еще это не делали
    if (!audio_tried_to_start_) {
        //пытаемся стартовать устройство
        audio_tried_to_start_ = true;

        //выбор устройства
        const QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
        xclu_assert(!devices.empty(), "No connected devices");

        auto method = gete_select_device();
        switch (method) {
        case select_device_Default: {
            start_audio(QAudioDeviceInfo::defaultOutputDevice());
            break;
        }
        case select_device_By_Index: {
                int name = geti_device_index();
                xclu_assert(name >= 0 && name < devices.size(), "Bad device index " + QString::number(name));
                start_audio(devices[name]);
                break;
        }
        case select_device_By_Name: {
            QString name = gets_device_name();
            for (int i=0; i<devices.size(); i++) {
                auto &info = devices.at(i);
                if (info.deviceName().contains(name)) {
                    start_audio(info);
                    break;
                }
            }
            break;
        }
        default:
            //мы здесь не должны быть, так как все методы запуска рассмотренли,
            //поэтому выдаем ошибку
            xclu_exception(QString("Bad select_device specifier '%1'").arg(method));
        }
    }

}

//---------------------------------------------------------------------
void XModuleSoundOut::start_audio(const QAudioDeviceInfo &deviceInfo) {
    //сбор значений параметров
    QAudioFormat format;

    //sample rate
    QString srate_string = getraw_sample_rate();
    int sample_rate = 44100;
    if (srate_string == "Default") {
        sample_rate = deviceInfo.preferredFormat().sampleRate();
    }
    else {
        if (srate_string == "Custom") {
            sample_rate = geti_custom_sample_rate();
        }
        else {
            bool ok;
            sample_rate = srate_string.toInt(&ok);
            xclu_assert(ok, "Bad sample rate");
        }
    }
    format.setSampleRate(sample_rate);

    //channels
    format.setChannelCount(geti_channels());

    //sample format
    format.setCodec("audio/pcm");

    //TODO сейчас поддерживаем только int16
    format.setSampleSize(16);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    if (!deviceInfo.isFormatSupported(format)) {
        xclu_message_box(QString("Sound output module '%1': format not supported, trying to use nearest")
                         .arg(name()));
        format = deviceInfo.nearestFormat(format);
    }


    //выдача информации о устройстве
    QString device_name = deviceInfo.deviceName();

    sets_connected_device_name(device_name);
    append_string_local_console("Starting: " + device_name, 2);


    //печатаем формат в used_format, пока без размера буфера - его допечатаем, когда устройство стартует
    set_format(format);

    //-------------------------------------------

    //создание объектов для генерации и вывода звука
    m_generator.reset(new XModuleSoundOutGenerator(format, &data_));
    m_audioOutput.reset(new QAudioOutput(deviceInfo, format));

    connect(m_audioOutput.data(), SIGNAL(stateChanged(QAudio::State)), this, SLOT(on_changed_audio_state(QAudio::State)));

    //вычисление и установка размера буфера
    QString buffer_size_str = getraw_buffer_size_desired();
    if (buffer_size_str != "Default") {
        int buffer_size = buffer_size_str.toInt();
        xclu_assert(buffer_size > 0, QString("Bad buffer size %1").arg(buffer_size));
        m_audioOutput->setBufferSize(buffer_size);
    }


    //ставим громкость
    check_volume_change();

    //если требуется, вывести в консоль поддерживаемые разрешения и частоты кадров
    //делаем тут это до старта камеры, и в функции делаем "camera_->load()",
    //чтобы в случае ее падения увидеть поддерживаемые разрешения
    print_formats(deviceInfo);

    m_generator->start();
    m_audioOutput->start(m_generator.data());
}


//---------------------------------------------------------------------
void XModuleSoundOut::set_started(bool started) { //ставит camera_started_ и gui-элемент is_started
    audio_started_ = started;
    seti_is_started(started);
}

//---------------------------------------------------------------------
 //печать текущего формата в used_format
void XModuleSoundOut::set_format(const QAudioFormat &format) {
    auto format_ = XObjectSoundFormatData(format.sampleRate(), format.channelCount());
    auto write = getstruct_sound_format()->write();
    XObjectSoundFormat::set_to_object(write.data(), format_);

}

//---------------------------------------------------------------------
//печать размера буфера при подключении устройства (запрашивается у устройства) в used_format
void XModuleSoundOut::set_buffer_size(int buffer_size) {
    buffer_size_ = buffer_size;
    //DataAccess access(data_);
    //data_.buffer_size = buffer_size;
    //это может быть вызвано из другого потока,
    //поэтому мы не можем тут ставить в GUI - надо дождаться основного потока update
    //append_string_used_format",QString("Buffer size: %1").arg(buffer_size));
}

//---------------------------------------------------------------------
//печать в консоль доступных устройств аудиовывода
void XModuleSoundOut::print_devices() {
    int print = geti_print_devices();
    if (!print) {
        print_devices_worked_ = false;
    }
    else {
        if (!print_devices_worked_) {
            print_devices_worked_ = true;
            QStringList list;
            list.append("Connected Output Audio devices:");
            //xclu_console_append("Connected Output Audiodevices:");

            const QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
            for (int i=0; i<devices.size(); i++) {
                auto &info = devices.at(i);
                QString device = QString::number(i) + ": " + info.deviceName();
                list.append(device);
                //xclu_console_append(device);
            }
            append_string_local_console(list, 1);
        }
    }
}

//---------------------------------------------------------------------
//печать в консоль поддерживаемых аудиоформатов запускаемого устройства
//внимание, эта функция запускает camera_->load()
void XModuleSoundOut::print_formats(const QAudioDeviceInfo &deviceInfo) {
    if (audio_tried_to_start_
            && !print_formats_worked_
            && geti_print_formats()) {
        print_formats_worked_ = true;

        QString device_name = deviceInfo.deviceName();

        QStringList list;
        list.append("Supported Formats for '" + device_name + "'");
        //xclu_console_append("Supported Formats for '" + device_name + "'");

        //Sample rates
        QString sample_rates_str = "  Sample rates: ";
        auto sample_rates = deviceInfo.supportedSampleRates();
        for (int i=0; i<sample_rates.size(); i++) {
            if (i > 0) {
                sample_rates_str.append(", ");
            }
            sample_rates_str.append(QString::number(sample_rates.at(i)));
        }
        list.append(sample_rates_str);
        //xclu_console_append(sample_rates_str);

        //Channels
        QString channels_str = "  Channels: ";
        auto channels = deviceInfo.supportedChannelCounts();
        for (int i=0; i<channels.size(); i++) {
            if (i > 0) {
                channels_str.append(", ");
            }
            channels_str.append(QString::number(channels.at(i)));
        }
        list.append(channels_str);
        //xclu_console_append(channels_str);

        //Печать
        append_string_local_console(list, 1);
    }
}

//---------------------------------------------------------------------
