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

    void connect_();
    void disconnect_();

    void on_deviceConnected(NeuroplayDevice *device);

};



#endif // XMODULEBCINEUROPLAY_H
