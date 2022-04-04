#ifndef XMODULEBCINEUROPLAY_H
#define XMODULEBCINEUROPLAY_H

//BCI Neuroplay, https://neuroplay.ru

#include <QImage>
#include "sdk_h.h"
#include "xmodulewidget.h"
#include "xobjectimage.h"
#include "xprotecteddata.h"
#include "sdk_h.h"
#include "neuroplaypro.h"
#include "qosc.h"

class XModuleBciNeuroplay: public XModuleWidget
{
public:
    XModuleBciNeuroplay(QString class_name);
    ~XModuleBciNeuroplay();
protected:
#include "auto.h"
    virtual void on_loaded();
    virtual void start();
    virtual void update();
    virtual void stop();
    virtual void on_button_pressed(QString button_id);

    virtual void draw(QPainter &painter, int w, int h);

protected:
    QScopedPointer<NeuroplayPro> neuroplay_;
    NeuroplayDevice *device_ = nullptr;

    void connect_();
    void disconnect_();

    void on_deviceConnected(NeuroplayDevice *device);

    void reset_stat();
    void update_stat();
    void inc_requests();
    void inc_received();
    int num_requests_ = 0;
    int num_received_ = 0;

    void set_rhythms(const NeuroplayDevice::ChannelsRhythms &rhythms);

    QString exception_; // Not empty in case of errors from BCI device

    void rec_start();
    void rec_stop();
    void rec_clear();
    void rec_update();
    void rec_update_status(QString status);
    void rec_data(QVector<float> values);
    bool recording_ = false;
    float rec_time_start_ = 0;
    QString rec_file_;

    QStringList rec_data_;

//OSC TODO move to SDK
private:
    void osc_send(QString net_address, QString osc_address, const QOscValue &value); //example of net_address: 127.0.0.1:12345
//public slots:
    //void onOscMessage(const QOscMessage& msg);  // Can't use "on_osc_message" - because Qt treats two "_" specially

};



#endif // XMODULEBCINEUROPLAY_H
