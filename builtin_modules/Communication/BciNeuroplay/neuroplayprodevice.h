#ifndef NEUROPLAYPRODEVICE_H
#define NEUROPLAYPRODEVICE_H

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

class NeuroplayDevice : public QObject
{
    Q_OBJECT
public:
    int id() const {return m_id;}
    const QString &name() const {return m_name;}
    const QString &model() const {return m_model;}
    const QString &serialNumber() const {return m_serialNumber;}
    int maxChannels() const {return m_maxChannels;}
    int preferredChannelCount() const {return m_preferredChannelCount;}
    const QVector< QPair<int, int> > &channelModesValues() const {return m_channelModes;}
    QStringList channelModes() const;

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
    void requestSpectrum()      {
        enableGrabMode();
        request("lastSpectrum");
    }

    void requestRhythms()       {request("rhythms");}
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
    int m_id;
    QString m_name;
    QString m_model;
    QString m_serialNumber;
    int m_maxChannels;
    int m_preferredChannelCount;
    QVector< QPair<int, int> > m_channelModes;
    friend class NeuroplayPro;
    NeuroplayDevice(const QJsonObject &json);

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

    void switchGrabMode();



signals: // private
    void doRequest(QString text);

private slots:
    void onResponse(QJsonObject resp);
    void grabRequest();
};

#endif // NEUROPLAYPRODEVICE_H
