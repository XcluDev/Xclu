#include "neuroplayprodevice.h"


NeuroplayDevice::NeuroplayDevice(const QJsonObject &json) :
    m_id(-1),
    m_isConnected(false),
    m_isStarted(false),
    m_grabFilteredData(false), m_grabRawData(false), m_grabRhythms(false), m_grabMeditation(false), m_grabConcentration(false),
    m_meditation(0), m_concentration(0)
{
    m_name = json["name"].toString();
    m_model = json["model"].toString();
    m_serialNumber = json["serialNumber"].toString();
    m_maxChannels = json["maxChannels"].toInt();
    m_preferredChannelCount = json["preferredChannelCount"].toInt();
    QJsonArray arr = json["channelModes"].toArray();
    for (QJsonValueRef value: arr)
    {
        QJsonObject o = value.toObject();
        int channels = o["channels"].toInt();
        int frequency = o["frequency"].toInt();
        m_channelModes << QPair<int, int>(channels, frequency);
    }
    m_grabTimer = new QTimer(this);
    connect(m_grabTimer, &QTimer::timeout, this, &NeuroplayDevice::grabRequest);

    connect(this, &QObject::destroyed, this, &NeuroplayDevice::stop);
}

QStringList NeuroplayDevice::channelModes() const
{
    QStringList list;
    for (auto mode: m_channelModes)
        list << QString("%1ch@%2Hz").arg(mode.first).arg(mode.second);
    return list;
}

void NeuroplayDevice::makeFavorite()
{
    request({{"command", "makefavorite"}, {"value", m_name}});
    request("getfavoritedevicename");
}

void NeuroplayDevice::grabFilteredData(bool enable)
{
    m_grabFilteredData = enable;
    switchGrabMode();
}

void NeuroplayDevice::grabRawData(bool enable)
{
    m_grabRawData = enable;
    switchGrabMode();
}

void NeuroplayDevice::grabRhythmsHistory(bool enable)
{
    m_grabRhythms = enable;
    switchGrabMode();
}

void NeuroplayDevice::grabMeditationHistory(bool enable)
{
    m_grabMeditation = enable;
    switchGrabMode();
}

void NeuroplayDevice::grabConcentrationHistory(bool enable)
{
    m_grabConcentration = enable;
    switchGrabMode();
}

NeuroplayDevice::ChannelsData NeuroplayDevice::readFilteredDataHistory()
{
    ChannelsData result;
    while (!m_filteredDataBuffer.isEmpty())
    {
        QVector<double> entry = m_filteredDataBuffer.dequeue();
        int chnum = entry.size();
        if (result.size() < chnum)
            result.resize(chnum);
        for (int i=0; i<chnum; i++)
            result[i] << entry[i];
    }
    return result;
}

NeuroplayDevice::ChannelsData NeuroplayDevice::readRawDataHistory()
{
    ChannelsData result;
    while (!m_rawDataBuffer.isEmpty())
    {
        QVector<double> entry = m_rawDataBuffer.dequeue();
        int chnum = entry.size();
        if (result.size() < chnum)
            result.resize(chnum);
        for (int i=0; i<chnum; i++)
            result[i] << entry[i];
    }
    return result;
}

QVector<NeuroplayDevice::ChannelsRhythms> NeuroplayDevice::readRhythmsHistory()
{
    QVector<ChannelsRhythms> result;
    while (!m_rhythmsBuffer.isEmpty())
    {
        result << m_rhythmsBuffer.dequeue();
    }
    return result;
}

QVector<NeuroplayDevice::TimedValue> NeuroplayDevice::readMeditationHistory()
{
    QVector<TimedValue> result;
    while (!m_meditationBuffer.isEmpty())
    {
        result << m_meditationBuffer.dequeue();
    }
    return result;
}

QVector<NeuroplayDevice::TimedValue> NeuroplayDevice::readConcentrationHistory()
{
    QVector<TimedValue> result;
    while (!m_concentrationBuffer.isEmpty())
    {
        result << m_concentrationBuffer.dequeue();
    }
    return result;
}

void NeuroplayDevice::setGrabInterval(int value_ms)
{
    m_grabIntervalMs = value_ms;
    m_grabTimer->setInterval(m_grabIntervalMs);
}

void NeuroplayDevice::start()
{
    m_isStarted = false;
    request({{"command", "startdevice"}, {"sn", m_serialNumber}});
}

void NeuroplayDevice::start(int channelNumber)
{
    m_isStarted = false;
    request({{"command", "startdevice"}, {"sn", m_serialNumber}, {"channels", channelNumber}});
}

void NeuroplayDevice::stop()
{
    m_isStarted = false;
    m_grabFilteredData = false;
    m_grabRawData = false;
    m_grabRhythms = false;
    m_grabMeditation = false;
    m_grabConcentration = false;
    switchGrabMode();
    request("stopdevice");
}

void NeuroplayDevice::setStarted(bool started)
{
    bool need_emit = !m_isStarted && started;
    m_isStarted = started;
    //if (started)
    //    request("spectrumfrequencies");   // TODO require
    if (need_emit)
        emit ready();
}

void NeuroplayDevice::request(QString text)
{
    emit doRequest(text);
}

void NeuroplayDevice::request(QJsonObject json)
{
    request(QJsonDocument(json).toJson());
}

void NeuroplayDevice::requestGrab(QString text)
{
    enableGrabMode();
    request(text);
}


void NeuroplayDevice::onResponse(QJsonObject resp)
{
    QString cmd = resp["command"].toString();
    //qDebug() << "received " << cmd;

    if (resp["error"].isString()) {
        emit error(resp["error"].toString());
        return;
    }

    if (cmd == "lastspectrum")
    {
        m_spectrum.clear();
        QJsonArray arr = resp["spectrum"].toArray();
        for (QJsonValueRef ch: arr)
        {
            QVector<double> array;
            for (QJsonValueRef val: ch.toArray())
                array << val.toDouble();
            m_spectrum << array;
        }
        emit spectrumReady();
    }
    else if (cmd == "spectrumfrequencies")
    {
        m_spectrumFrequencies.clear();
        for (QJsonValueRef val: resp["spectrum"].toArray())
            m_spectrumFrequencies << val.toDouble();
    }
    else if (cmd == "rhythms")
    {
        m_rhythms.clear();
        QJsonArray arr = resp["rhythms"].toArray();
        for (QJsonValueRef ch: arr)
        {
            QJsonObject o = ch.toObject();
            Rhythms r;
            r.data.resize(RhythmN);
            r.data[RhythmDelta] = o["delta"].toDouble();
            r.data[RhythmTheta] = o["theta"].toDouble();
            r.data[RhythmAlpha] = o["alpha"].toDouble();
            r.data[RhythmBeta] = o["beta"].toDouble();
            r.data[RhythmGamma] = o["gamma"].toDouble();
            r.timestamp = o["t"].toInt();
            m_rhythms << r;
        }
        emit rhythmsReady();
    }
    else if (cmd == "meditation")
    {
        m_meditation = resp["meditation"].toDouble();
        emit meditationReady();
    }
    else if (cmd == "concentration")
    {
        m_concentration = resp["concentration"].toDouble();
        emit concentrationReady();
    }
    else if (cmd == "bci")
    {
        m_meditation = resp["meditation"].toDouble();
        m_concentration = resp["concentration"].toDouble();
        emit bciReady();
    }
    else if (cmd == "enabledatagrabmode")
    {
        m_grabTimer->start(m_grabIntervalMs);
    }
    else if (cmd == "disabledatagrabmode")
    {
        m_grabTimer->stop();
    }
    else if (cmd == "filtereddata")
    {
        ChannelsData data;
        QJsonArray arr = resp["data"].toArray();
        for (QJsonValueRef ch: arr)
        {
            QVector<double> array;
            for (QJsonValueRef val: ch.toArray())
                array << val.toDouble();
            data << array;
        }
        emit filteredDataReceived(data);
    }
    else if (cmd == "rawdata")
    {
        ChannelsData data;
        QJsonArray arr = resp["data"].toArray();
        for (QJsonValueRef ch: arr)
        {
            QVector<double> array;
            for (QJsonValueRef val: ch.toArray())
                array << val.toDouble();
            data << array;
        }
        emit rawDataReceived(data);
    }
    else if (cmd == "grabfiltereddata")
    {
        QJsonArray arr = resp["data"].toArray();
        int chnum = arr.size();
        int count = arr[0].toArray().size();
        for (int i=0; i<count; i++)
        {
            QVector<double> entry;
            for (int j=0; j<chnum; j++)
            {
                entry << arr[j].toArray()[i].toDouble();
            }
            m_filteredDataBuffer.enqueue(entry);
        }
    }
    else if (cmd == "grabrawdata")
    {
        QJsonArray arr = resp["data"].toArray();
        int chnum = arr.size();
        int count = arr[0].toArray().size();
        for (int i=0; i<count; i++)
        {
            QVector<double> entry;
            for (int j=0; j<chnum; j++)
            {
                entry << arr[j].toArray()[i].toDouble();
            }
            m_rawDataBuffer.enqueue(entry);
        }
    }
    else if (cmd == "rhythmshistory")
    {
        QJsonArray history = resp["history"].toArray();
        for (QJsonValueRef entry: history)
        {
            ChannelsRhythms chr;
            QJsonArray arr = entry.toArray();
            for (QJsonValueRef ch: arr)
            {
                QJsonObject o = ch.toObject();
                Rhythms r;
                r.data.resize(RhythmN);
                r.data[RhythmDelta] = o["delta"].toDouble();
                r.data[RhythmTheta] = o["theta"].toDouble();
                r.data[RhythmAlpha] = o["alpha"].toDouble();
                r.data[RhythmBeta] = o["beta"].toDouble();
                r.data[RhythmGamma] = o["gamma"].toDouble();
                r.timestamp = o["t"].toInt();
                chr << r;
            }
            m_rhythms = chr;
            m_rhythmsBuffer.enqueue(chr);
        }
    }
    else if (cmd == "meditationhistory")
    {
        QJsonArray history = resp["history"].toArray();
        for (QJsonValueRef entry: history)
        {
            QJsonObject o = entry.toObject();
            TimedValue tv;
            tv.value = o["v"].toDouble();
            tv.timestamp = o["t"].toInt();
            m_meditation = tv.value;
            m_meditationBuffer.enqueue(tv);
        }
    }
    else if (cmd == "concentrationhistory")
    {
        QJsonArray history = resp["history"].toArray();
        for (QJsonValueRef entry: history)
        {
            QJsonObject o = entry.toObject();
            TimedValue tv;
            tv.value = o["v"].toDouble();
            tv.timestamp = o["t"].toInt();
            m_concentration = tv.value;
            m_concentrationBuffer.enqueue(tv);
        }
    }
    else if (cmd == "stoprecord" && resp["result"].toBool())
    {
        QByteArray edf, npd;
        QJsonArray files = resp["files"].toArray();
        for (QJsonValueRef file: files)
        {
            QJsonObject o = file.toObject();
            if (o["type"] == "edf")
                edf = QByteArray::fromBase64(o["data"].toString().toLocal8Bit());
            if (o["type"] == "npd")
                npd = QByteArray::fromBase64(o["data"].toString().toLocal8Bit());
        }
        emit recordedData(edf, npd);
    }
}

void NeuroplayDevice::switchGrabMode()
{
    bool enable = false;
    if (m_grabFilteredData || m_grabRawData || m_grabRhythms || m_grabMeditation || m_grabConcentration)
        enable = true;

    if (enable && !m_grabTimer->isActive())
        request("enabledatagrabmode");
    else if (!enable)
    {
        request("disabledatagrabmode");
        m_grabTimer->stop();
    }
}

void NeuroplayDevice::enableGrabMode()
{
    if (!grab_mode_enabled)
    {
        grab_mode_enabled = true;
        request("enableDataGrabMode");
    }
}

void NeuroplayDevice::disableGrabMode()
{
    if (grab_mode_enabled)
    {
        grab_mode_enabled = false;
        request("disabledatagrabmode");
    }
}


void NeuroplayDevice::grabRequest()
{
    if (m_grabFilteredData)
        request("grabrawdata");
    if (m_grabRawData)
        request("graboriginaldata");
    if (m_grabRhythms)
        request("rhythmsHistory");
    if (m_grabMeditation)
        request("meditationHistory");
    if (m_grabConcentration)
        request("concentrationHistory");
}

