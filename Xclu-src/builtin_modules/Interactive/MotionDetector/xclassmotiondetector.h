#pragma once

//MotionDetector implementation

#include "sdk_h.h"
#include "xclass.h"
#include <QMediaPlayer>
#include <QScopedPointer>
#include "xraster.h"
#include "xslowbit.h"

struct XClassMotionDetectorBlockParams {
    float thresh_in=0.2f; //Threshold for block detection, 0..1

    float thresh_out=0.1f;   //Threshold for block undetection after detection, 0..1

    float block_event_sec=0.1f; //How much time block event must be to detect it, sec
};

//-------------------------------------------------------------------
class XClassMotionDetectorBlock {
public:
    void setup(int x, int y, int w, int h) {
        x_ = x;
        y_ = y;
        w_ = w;
        h_ = h;
    }
    int x_ = 0;
    int y_ = 0;
    int w_ = 0;
    int h_ = 0;

    void update(XRaster &input_u8, XRaster &background_u8, const XClassMotionDetectorBlockParams &params,
                bool enabled, float dt) {
        input_u8.assert_type(XType::uint8);
        background_u8.assert_type(XType::uint8);
        enabled_ = enabled;
        if (enabled) {
            //Compute distance
            //TODO now only brightness correction, but can use correlation
            int mean1 = 0;
            int mean2 = 0;
            int area = w_ * h_;
            /* mean now is commented:
            for (int y=y_; y<y_+h_; y++) {
                for (int x=x_; x<x_+w_; x++) {
                    mean1 += input.pixel_unsafe(x, y);
                    mean2 += background.pixel_unsafe(x, y);
                }
            }
            mean1 /= area;
            mean2 /= area;
            */
            int diff = 0;
            for (int y=y_; y<y_+h_; y++) {
                for (int x=x_; x<x_+w_; x++) {
                    diff += abs(int(input_u8.pixel_unsafe<uint8>(x, y))-mean1 - (int(background_u8.pixel_unsafe<uint8>(x, y)) - mean2));
                }
            }
            dist_ = float(diff)/(area*255);

            //Update fire            
            int fire = fires_;
            if (!fires_) {
                if (dist_ > params.thresh_in) fire = 1;
            }
            else {
                if (dist_ < params.thresh_out) fire = 0;
            }
            bit_.update_times(params.block_event_sec);
            bit_.update(dt, fire);
            fires_ = bit_.state(); //dist_ > params.thresh_in;
        }
        else {
            dist_  = 0;
            fires_ = 0;
        }

    }

    int fires() { return fires_ && enabled_; }
    int enabled() { return enabled_; }
protected:
    int enabled_ = false;

    int fires_ = 0;

    float dist_ = 0;

    float fire_time_ = 0;   //last time of fire

    XSlowbit bit_;
};


//-------------------------------------------------------------------

class XClassMotionDetector: public XClass
{
public:
    XClassMotionDetector(QString class_name);
    virtual ~XClassMotionDetector();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();
    //virtual void on_button_pressed(QString button_id);

    XRaster out_image_holder_;
    XRaster out_background_holder_;

    XRaster input0_u8_, input_u8_;
    XRaster background_u8_;
    XRaster output_u8c3_;

    //decimate inout
    void decimate_input(XRaster &input_u8, XRaster &result_u8);


    //detection blocks
    QVector<XClassMotionDetectorBlock> blocks_; //

    //state
    int state_ = 0;
    float time_ = -10000;

    //how much ignore frames
    int ignore_frames_ = 0;

    void bang_on();
    void bang_off();

    //vector of blocks fires
    //while not changed - increase timer for background update
    QVector<int> fires_;
    float static_time_ = 1000000;   //time when started static behavior of blocks fires


};


