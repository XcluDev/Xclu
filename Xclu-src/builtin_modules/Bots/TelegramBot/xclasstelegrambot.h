#pragma once

//TelegramBot implementation
//------------------------------------------------------------------
//If you get "QSslSocket::connectToHostEncrypted: TLS initialization failed" error on Windows:
//please check OpenSSL at Qt installer at Developer Tools section,
//and copy libcrypto-1_1-x64.dll, libssl-1_1-x64.dll to Xclu bin folder
//https://ru.stackoverflow.com/questions/952577/qt-network-ssl-qsslsocketconnecttohostencrypted-tls-initialization-failed
//------------------------------------------------------------------

#include "sdk_h.h"
#include "xclass.h"

class QNetworkAccessManager;
class QNetworkReply;

class XClassTelegramBot: public XClass
{
public:
    XClassTelegramBot(QString class_name);
    virtual ~XClassTelegramBot();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();
    //virtual void on_button_pressed(QString button_id);

    void send_message();

    QScopedPointer<QNetworkAccessManager> manager_;

protected slots:
    void handleNetworkData(QNetworkReply *networkReply);
    void slotError();
    void slotSslErrors();
};


