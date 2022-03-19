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

};



#endif // XMODULEBCINEUROPLAY_H
