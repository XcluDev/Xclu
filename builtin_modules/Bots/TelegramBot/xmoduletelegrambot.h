#ifndef XMODULETELEGRAMBOT_H
#define XMODULETELEGRAMBOT_H

//TelegramBot implementation
//------------------------------------------------------------------
//If you get "QSslSocket::connectToHostEncrypted: TLS initialization failed" error on Windows:
//please check OpenSSL at Qt installer at Developer Tools section,
//and copy libcrypto-1_1-x64.dll, libssl-1_1-x64.dll to Xclu bin folder
//https://ru.stackoverflow.com/questions/952577/qt-network-ssl-qsslsocketconnecttohostencrypted-tls-initialization-failed
//------------------------------------------------------------------

#include "sdk_h.h"
#include "xmodule.h"

class QNetworkAccessManager;
class QNetworkReply;

class XModuleTelegramBot: public XModule
{
public:
    XModuleTelegramBot(QString class_name);
    ~XModuleTelegramBot();
#include "auto.h"

protected:
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();
    //virtual void impl_button_pressed(QString button_id);

    void send_message();

    QScopedPointer<QNetworkAccessManager> manager_;

protected slots:
    void handleNetworkData(QNetworkReply *networkReply);
    void slotError();
    void slotSslErrors();
};



#endif // XMODULETELEGRAMBOT_H
