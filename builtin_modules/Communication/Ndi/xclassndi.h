#ifndef XMODULENDI_H
#define XMODULENDI_H

//NDI interface
//To check sender working - run "VB NDI Receive Example.exe" from NDI/Examples/Bin/x64/Release

#include <QImage>
#include "sdk_h.h"
#include "xclass.h"
#include "xobjectimage.h"
#include "xprotecteddata.h"
#include "sdk_h.h"

class XClassNdi: public XClass
{
public:
    XClassNdi(QString class_name);
    ~XClassNdi();
protected:
#include "auto.h"
    virtual void on_loaded();
    virtual void start();
    virtual void update();
    virtual void stop();
    virtual void on_button_pressed(QString button_id);

protected:
    void send_frame();
    void send_test_frame(int frame);
    XRaster_u8c4 test_raster_;
    int  sent_frames_ = 0;


    bool ndi_inited_ = false;
    void ndi_init();
    void ndi_send_image(const unsigned char *data_rgba, int w, int h);
    void ndi_stop();

    void* pNDI_send_ = nullptr;

};



#endif // XMODULESERIAL_H
