#include "neuroplaypro.h"

NeuroplayPro::NeuroplayPro(QObject *parent) : QObject(parent),
    m_state(Disconnected),
    m_isDataGrab(false),
    m_currentDevice(nullptr),
    m_LPF(0), m_HPF(0), m_BSF(0),
    m_dataStorageTime(0)
{
    socket = new QWebSocket();
    connect(socket, &QWebSocket::connected, [=]()
    {
        m_state = Connected;
        send("help");
    });
    connect(socket, &QWebSocket::disconnected, [=]()
    {
        m_state = Disconnected;
        emit disconnected();
    });
    connect(socket, &QWebSocket::textMessageReceived, this, &NeuroplayPro::onSocketResponse);

    m_searchTimer = new QTimer(this);
    m_searchTimer->setInterval(200);
    connect(m_searchTimer, &QTimer::timeout, [=]()
    {
        send("listdevices");
    });

    m_devStartTimer = new QTimer(this);
    m_devStartTimer->setInterval(200);
    connect(m_devStartTimer, &QTimer::timeout, [=]()
    {
        send("currentdeviceinfo");
    });
}

NeuroplayPro::~NeuroplayPro()
{
    close();
}

void NeuroplayPro::open()
{
    socket->open(QUrl("ws://localhost:1336"));
}

void NeuroplayPro::close()
{
    for (NeuroplayDevice *dev: m_deviceList)
        dev->deleteLater();
    m_deviceMap.clear();
    m_deviceList.clear();
    socket->close();
}

void NeuroplayPro::send(QString cmd)
{
// qDebug() << "> " + cmd;
    socket->sendTextMessage(cmd);
//    emit response("> " + cmd);
}

void NeuroplayPro::send(QJsonObject obj)
{
    send(QJsonDocument(obj).toJson());
}

NeuroplayDevice *NeuroplayPro::createDevice(const QJsonObject &o, const QJsonObject &resp)
{
    NeuroplayDevice *dev = new NeuroplayDevice(o, resp);
    dev->set_id(m_deviceList.size());
    NeuroplayDeviceInfo info = dev->info();
    qDebug() << "device created" << info.name;
    QObject::connect(dev, SIGNAL(doRequest(QString)), this, SLOT(send(QString)));//, Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(responseJson(QJsonObject)), dev, SLOT(onResponse(QJsonObject)));//, Qt::QueuedConnection);
    m_deviceMap[info.name] = dev;
    m_deviceList << dev;
    emit deviceConnected(dev);
    return dev;
}

void NeuroplayPro::onSocketResponse(const QString &text)
{
    QJsonDocument json = QJsonDocument::fromJson(text.toUtf8());
    QJsonObject resp = json.object();
    QString cmd = resp["command"].toString();
    bool result = resp["result"].toBool();

    emit responseJson(resp);

    if (resp.contains("error") && m_state == Ready)
    {
        emit error(resp["error"].toString());
        return;
    }

    if (cmd == "help")
    {
        QString help;
        QJsonArray arr = resp["commands"].toArray();
        for (QJsonValueRef value: arr)
        {
            QJsonObject o = value.toObject();
            QString c = o["command"].toString();
            QString d = o["description"].toString();
            m_commands[c] = d;
            if (d.isEmpty())
                help += c + "\n";
            else
                help += c + " \t - " + m_commands[c] + "\n";
        }

        // aqcuire current settings:
        send("version");
        send("getfavoritedevicename");
        send("getfilters");
        send("getdatastoragetime");

        // aqcuire current connected device.
        // the search will started later if device is not connected
        send("currentdeviceinfo");

        bool need_emit = (m_state < Searching);
        m_state = Searching;
        if (need_emit)
        {
            emit connected();
            return;
        }

//        emit response(help);
        return;
    }
    else if (cmd == "version" && result)
    {
        m_version = resp["version"].toString();
    }
    else if (cmd == "getfavoritedevicename")
    {
        m_favoriteDeviceName = resp["device"].toString();
    }
    else if (cmd == "getfilters" || cmd == "setdefaultfilters")
    {
        m_LPF = resp["LPF"].toDouble(0);
        m_HPF = resp["HPF"].toDouble(0);
        m_BSF = resp["BSF"].toDouble(0);
    }
    else if (cmd == "getdatastoragetime")
    {
        m_dataStorageTime = resp["storagetime"].toInt();
    }
    else if (cmd == "startsearch")
    {
        for (NeuroplayDevice *dev: m_deviceList)
            dev->m_isConnected = false;
        m_searchTimer->start();
        QTimer::singleShot(6000, [=]()
        {
            m_searchTimer->stop();
            m_state = Ready;
        });
    }
    else if (cmd == "listdevices")
    {
        QJsonArray arr = resp["devices"].toArray();
        for (QJsonValueRef devjson: arr)
        {
            QJsonObject o = devjson.toObject();
            QString name = o["name"].toString();
            NeuroplayDevice *dev = nullptr;
            if (!m_deviceMap.contains(name))
            {
                dev = createDevice(o, resp);
            }
            else
            {
                dev  = m_deviceMap[name];
            }
            dev->m_isConnected = true;
        }
    }
    else if (cmd == "startdevice")
    {
        m_searchTimer->stop();
        m_devStartTimer->start();
        QTimer::singleShot(6000, [=](){m_devStartTimer->stop();});
    }
    else if (cmd == "currentdeviceinfo")
    {
        if (resp["result"].toBool())
        {
            m_devStartTimer->stop();
            QJsonObject o = resp["device"].toObject();
            QString name = o["name"].toString();
            if (!m_deviceMap.contains(name))
            {
                createDevice(o, resp);
            }
            m_currentDevice = m_deviceMap[name];
            m_currentDevice->setStarted();
            emit deviceReady(m_currentDevice);
        }
        else if (m_state < Ready)
        {
            send("startsearch");
        }
    }
    else if (cmd == "enabledatagrabmode")
    {
        m_isDataGrab = true;
    }
    else if (cmd == "disabledatagrabmode")
    {
        m_isDataGrab = false;
    }

//    emit response(text);
}

void NeuroplayPro::setLPF(double value)
{
    m_LPF = value;
    send({{"command", "setLPF"}, {"value", m_LPF}});
}

void NeuroplayPro::setHPF(double value)
{
    m_HPF = value;
    send({{"command", "setHPF"}, {"value", m_HPF}});
}

void NeuroplayPro::setBSF(double value)
{
    m_BSF = value;
    send({{"command", "setBSF"}, {"value", m_BSF}});
}

void NeuroplayPro::setFilters(double LPF, double HPF, double BSF)
{
    setLPF(LPF);
    setHPF(HPF);
    setBSF(BSF);
}

void NeuroplayPro::setDefaultFilters()
{
    send("setdefaultfilters");
}

void NeuroplayPro::setDataStorageTime(int seconds)
{
    //! @bug "value" value expected as string instead of number!
    send({{"command", "setdatastoragetime"}, {"value", QString::number(seconds)}});
}

void NeuroplayPro::enableDataGrabMode()
{
    send("enabledatagrabmode");
}

void NeuroplayPro::disableDataGrabMode()
{
    send("disabledatagrabmode");
}

void NeuroplayPro::setDataGrabMode(bool enabled)
{
    if (enabled)
        enableDataGrabMode();
    else
        disableDataGrabMode();
}
