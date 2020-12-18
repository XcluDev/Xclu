#ifndef XMODULEMOTIONDETECTOR_H
#define XMODULEMOTIONDETECTOR_H

//MotionDetectorRouter implementation

#include "sdk_h.h"
#include "xmodule.h"
#include <QMediaPlayer>
#include <QScopedPointer>
#include "xraster.h"
#include "xslowbit.h"

//-------------------------------------------------------------------

class XModuleMotionDetectorRouter: public XModule
{
public:
    XModuleMotionDetectorRouter(QString class_name);
    ~XModuleMotionDetectorRouter();
#include "auto.h"

protected:
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();
    virtual void impl_button_pressed(QString button_id);

    static const int N = 4; //max number of cameras

    XRaster_u8 input_[N];
    XRaster_u8 template_[N];
    XRaster_u8 output_[N];

    XProtectedObject output_gui_[N];
    XProtectedObject template_gui_[N];

  //  resize_shrink
   // void decimate_input(XRaster_u8 &input, XRaster_u8 &result);

    //how much ignore frames before start
    int ignore_frames_ = 0;
    //are we started?
    int started_ = 0;




};



#endif // XMODULEMOTIONDETECTOR_H
