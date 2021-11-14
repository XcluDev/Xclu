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
    virtual ~XModuleMotionDetectorRouter();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();
    virtual void on_button_pressed(QString button_id);

    static const int N = 4; //max number of cameras

    //XRaster_u8 input_[N];
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

    //number of inputs
    int n_ = 0;

    //setup route
    void make_route();
    QVector<int> route_scheme_;    //scheme of routing

    QVector<int> auto_route();

    XProtectedObject *input_image(int i);
    XProtectedObject *output_image(int i);
    XProtectedObject *template_image(int i);

    //save templates
    void save_templates();
    void load_templates();

    XRaster_float resize_to_template(XProtectedObject *image);

    float normalized_correlation(XRaster_float &A, XRaster_float &B);
};



#endif // XMODULEMOTIONDETECTOR_H
