#ifndef XMODULENDI_H
#define XMODULENDI_H

//NDI interface
//To check sender working - run "VB NDI Receive Example.exe" from NDI/Examples/Bin/x64/Release

#include <QImage>
#include <QtSerialPort/QSerialPort>
#include "sdk_h.h"
#include "xmodule.h"
#include "xobjectimage.h"
#include "xprotecteddata.h"
#include "sdk_h.h"

//Note: now this module writes warnings and errors to console, without interrupting the project.
//TODO: make possibility to interrupt. (Already it's set in Control module).
//It's great to do in wizard at adding the module.

class XModuleNdi: public XModule
{
public:
    XModuleNdi(QString class_name);
    ~XModuleNdi();
protected:
#include "auto.h"
    //Выполнение
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
    void ndi_send_image(XRaster_u8c4 &raster);
    void ndi_stop();

    void* pNDI_send_ = nullptr;

};



#endif // XMODULESERIAL_H
