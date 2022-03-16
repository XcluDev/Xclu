#ifndef XMODULEBCINEUROPLAY_H
#define XMODULEBCINEUROPLAY_H

//BCI Neuroplay, https://neuroplay.ru

#include <QImage>
#include "sdk_h.h"
#include "xmodulewidget.h"
#include "xobjectimage.h"
#include "xprotecteddata.h"
#include "sdk_h.h"

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
  /*  void send_frame();
    void send_test_frame(int frame);
    XRaster_u8c4 test_raster_;
    int  sent_frames_ = 0;


    bool ndi_inited_ = false;
    void ndi_init();
    void ndi_send_image(const unsigned char *data_rgba, int w, int h);
    void ndi_stop();

    void* pNDI_send_ = nullptr;
*/
};



#endif // XMODULEBCINEUROPLAY_H
