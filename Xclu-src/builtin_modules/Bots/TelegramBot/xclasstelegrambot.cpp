#include "xclasstelegrambot.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkReply>

//registering module implementation
REGISTER_XCLASS(TelegramBot)

//---------------------------------------------------------------------
XClassTelegramBot::XClassTelegramBot(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassTelegramBot::~XClassTelegramBot()
{

}

//---------------------------------------------------------------------
void XClassTelegramBot::start() {

}

//---------------------------------------------------------------------
void XClassTelegramBot::update() {
    if (geti_button_send()) {
        send_message();
    }

}

//---------------------------------------------------------------------
void XClassTelegramBot::stop() {
    manager_.reset();
}

//---------------------------------------------------------------------
//void XClassTelegramBot::on_button_pressed(QString button_id) {
//}

//---------------------------------------------------------------------
void XClassTelegramBot::send_message() {
    QString token = gets_bot_token().trimmed();
    QString chat_id = gets_chat_id().trimmed();
    QString message = gets_message_send();
    xc_assert(!token.isEmpty(), "Bot token is empty");
    xc_assert(!chat_id.isEmpty(), "Chat id is empty");
    xc_assert(!message.isEmpty(), "Message is empty");


    //https://stackoverflow.com/questions/13302236/qt-simple-post-request

    if (!manager_.data()) {
        manager_.reset(new QNetworkAccessManager(this));

        connect(manager_.data(), SIGNAL(finished(QNetworkReply *)), this, SLOT(handleNetworkData(QNetworkReply *)));

    }

    QUrl url(QString("https://api.telegram.org/bot%1/sendMessage").arg(token));
    QNetworkRequest request(url);

    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("chat_id", chat_id);
    params.addQueryItem("text", message);



    QNetworkReply *reply = manager_->post(request, params.query().toUtf8());

    //connect(reply, &QIODevice::readyRead, this, &MyClass::slotReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &XClassTelegramBot::slotError);
    connect(reply, &QNetworkReply::sslErrors,
            this, &XClassTelegramBot::slotSslErrors);

}

//---------------------------------------------------------------------
void XClassTelegramBot::handleNetworkData(QNetworkReply *networkReply) {
    //https://ru.stackoverflow.com/questions/952577/qt-network-ssl-qsslsocketconnecttohostencrypted-tls-initialization-failed

    if(networkReply->error() == QNetworkReply::NoError){
        //QByteArray json_data = networkReply->readAll();
        //ui->textEdit->setPlainText(json_data)

        //QByteArray response(networkReply->readAll());
        //QXmlStreamReader xml(response);

        //while (!xml.atEnd()) {
        //    xml.readNext();
        //    if (xml.tokenType() == QXmlStreamReader::StartElement)
        //        if (xml.name() == "suggestion") {
        //            QStringRef str = xml.attributes().value("data");
        //            choices << str.toString();
        //        }
        //}
    }
    else {
        xc_exception(QString("Network error: %1").arg(networkReply->error()));
    }

    //Why?
    networkReply->deleteLater();

}

//---------------------------------------------------------------------
void XClassTelegramBot::slotError() {
    //Can't do exception here, so just put to console
    xc_console_append(QString("XClassTelegramBot - network error"));
    //xc_exception(QString("XClassTelegramBot - network error"));
}

//---------------------------------------------------------------------
void XClassTelegramBot::slotSslErrors() {
    //Can't do exception here, so just put to console
    xc_console_append(QString("XClassTelegramBot - network SSL error"));
    //xc_exception(QString("XClassTelegramBot - network SSL error"));

}

//---------------------------------------------------------------------
