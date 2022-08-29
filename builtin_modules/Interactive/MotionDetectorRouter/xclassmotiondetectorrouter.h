#ifndef XCLASSMOTIONDETECTOR_H
#define XCLASSMOTIONDETECTOR_H

//MotionDetectorRouter implementation

#include "sdk_h.h"
#include "xclass.h"
#include <QMediaPlayer>
#include <QScopedPointer>
#include "xraster.h"
#include "xslowbit.h"

//-------------------------------------------------------------------

class XClassMotionDetectorRouter: public XClass
{
public:
    XClassMotionDetectorRouter(QString class_name);
    virtual ~XClassMotionDetectorRouter();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();
    virtual void on_button_pressed(QString button_id);

    static const int N = 4; //max number of cameras

    XProtectedObject output_gui_[N];
    XProtectedObject template_gui_[N];

    XRaster output_[N];
    XRaster template_[N];

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

    XRaster resize_to_template_float(XProtectedObject *image);

    float normalized_correlation_float(XRaster &A_float, XRaster &B_float);
};



#endif // XCLASSMOTIONDETECTOR_H
