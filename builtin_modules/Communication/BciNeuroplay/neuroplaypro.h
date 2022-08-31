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

#include "neuroplayprodevice.h"

class NeuroplayPro : public QObject
{
    Q_OBJECT
public:
    enum State {Disconnected, Connected, Searching, Ready};

    explicit NeuroplayPro(QObject *parent = nullptr);
    virtual ~NeuroplayPro();
    State state() const {return m_state;}
    bool isConnected() const {return m_state >= Connected;}
    bool isDataGrabMode() const {return m_isDataGrab;}
    int deviceCount() const {return m_deviceList.size();}
    NeuroplayDevice *device(int id) {return (id >= 0 && id < deviceCount())? m_deviceList[id]: nullptr;}
    NeuroplayDevice *device(QString sn) {return m_deviceMap.contains(sn)? m_deviceMap[sn]: nullptr;}
    NeuroplayDevice *currentDevice() {return m_currentDevice;}
    QString favoriteDeviceName() const {return m_favoriteDeviceName;}
    QString version() {return m_version;}

    double LPF() const {return m_LPF;}
    void setLPF(double value);
    double HPF() const {return m_HPF;}
    void setHPF(double value);
    double BSF() const {return m_BSF;}
    void setBSF(double value);
    void setFilters(double LPF, double HPF, double BSF);
    void setDefaultFilters();

    int dataStorageTime() const {return m_dataStorageTime;}
    void setDataStorageTime(int seconds);

public slots:
    void open();
    void close();
    void enableDataGrabMode();
    void disableDataGrabMode();
    void setDataGrabMode(bool enabled);

signals:
    void connected();
    void disconnected();
    void error(QString text);
    void deviceConnected(NeuroplayDevice *device);
    void deviceReady(NeuroplayDevice *device);

protected slots:
public slots:
    void send(QString cmd);

private:
    QWebSocket *socket;
    State m_state;
    bool m_isDataGrab;
    QMap<QString, QString> m_commands;
    QVector<NeuroplayDevice*> m_deviceList;
    QMap<QString, NeuroplayDevice*> m_deviceMap;
    QTimer *m_searchTimer;
    QTimer *m_devStartTimer;
    NeuroplayDevice *m_currentDevice;
    QString m_favoriteDeviceName;
    double m_LPF, m_HPF, m_BSF;
    int m_dataStorageTime;
    QString m_version;

    void send(QJsonObject obj);
    friend class NeuroplayDevice;

    NeuroplayDevice *createDevice(const QJsonObject &o, const QJsonObject &resp);

private slots:
    void onSocketResponse(const QString &text);

signals:
    void responseJson(QJsonObject json);

};

