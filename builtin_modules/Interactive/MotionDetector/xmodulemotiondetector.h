#ifndef XMODULEMOTIONDETECTOR_H
#define XMODULEMOTIONDETECTOR_H

//MotionDetector implementation

#include "sdk_h.h"
#include "xmodule.h"
#include <QMediaPlayer>
#include <QScopedPointer>

class XModuleMotionDetector: public XModule
{
public:
    XModuleMotionDetector(QString class_name);
    ~XModuleMotionDetector();
#include "auto.h"

protected:
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();
    //virtual void impl_button_pressed(QString button_id);

    XProtectedObject out_image_;
    XProtectedObject out_background_;

};



#endif // XMODULEMOTIONDETECTOR_H
