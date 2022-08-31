#pragma once

// Code from https://github.com/perevalovds/NeuroplayPro-QtSDK,
// forked from example by neuroplay.ru

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include <QVector>
#include <QQueue>

struct NeuroplayDeviceInfo {
    void clear() {
        *this = NeuroplayDeviceInfo();
    }
    int id = -1;
    QString name;
    QString model;
    QString serial_number;

    int channels_count = 0;
    QStringList channels_names;

    // Find channel by name, returns -1 if not found
    int find_channel_by_name(QString name) const {
        return channels_names.indexOf(name);
    }

    int frequency = 0;

    float BSF = 0;
    float HPF = 0;
    float LPF = 0;

    int max_channels = 0;
    int preferred_channel_count = 0;

    QVector< QPair<int, int> > channel_modes_values;
    QStringList channel_modes() const {
        QStringList list;
        for (auto mode: channel_modes_values)
            list << QString("%1ch@%2Hz").arg(mode.first).arg(mode.second);
        return list;
    }

};

class NeuroplayDevice : public QObject
{
    Q_OBJECT
public:
    const NeuroplayDeviceInfo& info() { return info_; }

    void set_id(int id) { info_.id = id; }

    void makeFavorite();

    enum RhythmsEnum: int {
        RhythmDelta = 0,
        RhythmTheta = 1,
        RhythmAlpha = 2,
        RhythmBeta = 3,
        RhythmGamma = 4,
        RhythmN = 5
    };

    typedef struct
    {
        QVector<double> data;   // See RhythmsEnum
        int timestamp;
    } Rhythms;
    typedef struct
    {
        double value;
        int timestamp;
    } TimedValue;
    typedef QVector< QVector<double> > ChannelsData;
    typedef QVector<Rhythms> ChannelsRhythms;

    const ChannelsData &spectrum() const {return m_spectrum;}
    const QVector<double> &spectrumFrequencies() const {return m_spectrumFrequencies;}
    const ChannelsRhythms &rhythms() const {return m_rhythms;}
    double meditation() const {return m_meditation;}
    double concentration() const {return m_concentration;}

    bool isConnected() const {return m_isConnected;}
    bool isStarted() const {return m_isStarted;}

    void grabFilteredData(bool enable = true);
    void grabRawData(bool enable = true);
    void grabRhythmsHistory(bool enable = true);
    void grabMeditationHistory(bool enable = true);
    void grabConcentrationHistory(bool enable = true);

    void enableGrabMode();
    void disableGrabMode();

    ChannelsData readFilteredDataHistory();
    ChannelsData readRawDataHistory();
    QVector<ChannelsRhythms> readRhythmsHistory();
    QVector<TimedValue> readMeditationHistory();
    QVector<TimedValue> readConcentrationHistory();

    void setGrabInterval(int value_ms);
    int grabInterval() const {return m_grabIntervalMs;}

public slots:
    void start();
    void start(int channelNumber);
    void stop();

    void startRecord() {request("startrecord");}
    void stopRecord() {request("stoprecord");}

    void requestFilteredData()  {request("filtereddata");}
    void requestRawData()       {request("rawdata");}
    void requestSpectrum()      {requestGrab("lastSpectrum");}
    void requestRhythms()       {requestGrab("rhythms");}
    void requestMeditation()    {request("meditation");}
    void requestConcentration() {request("concentration");}
    void requestBCI()           {request("BCI");}

signals:    
    void ready();

    void filteredDataReceived(ChannelsData data);
    void rawDataReceived(ChannelsData data);
    void spectrumReady();
    void rhythmsReady();
    void meditationReady();
    void concentrationReady();
    void bciReady();

    void recordedData(QByteArray edf, QByteArray npd);

    void error(QString message);

private:
    NeuroplayDeviceInfo info_;

    friend class NeuroplayPro;

    // resp is all response, and json is resp["device"]
    NeuroplayDevice(const QJsonObject &json, const QJsonObject &resp);

    bool m_isConnected;
    bool m_isStarted;

    bool m_grabFilteredData;
    bool m_grabRawData;
    bool m_grabRhythms;
    bool m_grabMeditation;
    bool m_grabConcentration;

    bool grab_mode_enabled = false;

    QVector<double> m_spectrumFrequencies;
    ChannelsData m_spectrum;
    ChannelsRhythms m_rhythms;
    double m_meditation;
    double m_concentration;

    QQueue< QVector<double> > m_filteredDataBuffer;
    QQueue< QVector<double> > m_rawDataBuffer;
    QQueue<ChannelsRhythms> m_rhythmsBuffer;
    QQueue<TimedValue> m_meditationBuffer;
    QQueue<TimedValue> m_concentrationBuffer;
    QTimer *m_grabTimer;
    int m_grabIntervalMs = 50;

    void setStarted(bool started = true);

    void request(QString text);
    void request(QJsonObject json);
    void requestGrab(QString text);

    void switchGrabMode();


signals: // private
    void doRequest(QString text);

private slots:
    void onResponse(QJsonObject resp);
    void grabRequest();
};
