#include "xmodulemotiondetector.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xcore.h"
#include "xcluobjectimage.h"

//registering module implementation
REGISTER_XMODULE(MotionDetector)

//---------------------------------------------------------------------
XModuleMotionDetector::XModuleMotionDetector(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleMotionDetector::~XModuleMotionDetector()
{

}

//---------------------------------------------------------------------
void XModuleMotionDetector::impl_start() {
    //link images with internal objects
    setobject_output_image(&out_image_);
    setobject_background_image(&out_background_);

    //Human presence detection
    //Algorithm works using correlation inside smaller pixel blocks of fixed size.
    //If correlation in some block exceeds threshold, the object is detected.
    //If no changes of "block image" for a minute - then update background.

    out_image_.write().data().clear();
    out_background_.write().data().clear();

    blocks_.clear();
    input_.clear();
    background_.clear();
    output_.clear();

    state_ = 0;
    time_ = -10000;

    static_time_ = 1000000;
    fires_.clear();
    setf_restore_timer(0);

    //send "off" at start
    bang_off();

    ignore_frames_ = geti_ignore_start_frames();

}

//---------------------------------------------------------------------
void XModuleMotionDetector::impl_update() {

    //Read image
    auto reader = getobject_input_image()->read();

    //no image yet
    if (reader.data().type() != XObjectTypeImage) return;

    //ignore frames at start
    ignore_frames_--;
    if (ignore_frames_ > 0) return;

    //read image
    XObjectImage::to_raster(reader.data(), input_);

    if (input_.w == 0) return;  //no frames yet

    int w = input_.w;
    int h = input_.h;
    int size = geti_block_size();
    int W = w / size;
    int H = h / size;
    //create blocks
    //TODO assuming that image size will not change
    if (blocks_.size() != W*H) {
        blocks_.resize(W*H);
        fires_.resize(W*H);
        for (int y=0; y<H; y++) {
            for (int x=0; x<W; x++) {
                blocks_[x+W*y].setup(x*size, y*size, size, size);
            }
        }

        //initial setting background
        background_ = input_;
    }

    //background update
    if (geti_restore_now()) {   //reset by button
        background_ = input_;
    }

    //area
    int X0 = getf_x0() * w;
    int Y0 = getf_y0() * h;
    int X1 = getf_x1() * w;
    int Y1 = getf_y1() * h;

    //update blocks
    XModuleMotionDetectorBlockParams params;
    params.thresh_in = getf_thresh_in();
    //params.thresh_out = getf_thresh_out();
    params.block_event_sec = getf_block_event_sec();


    float dt = xcore_dt();
    float time = xcore_elapsed_time_sec();
    int nfires = 0;
    int N = 0;
    for (int y=0; y<H; y++) {
        for (int x=0; x<W; x++) {
            auto &block = blocks_[x+W*y];
            bool enabled = (block.x_ >= X0 && block.y_ >= Y0
                            && block.x_ + block.w_ <= X1 && block.y_ + block.h_ <= Y1);
            block.update(input_, background_, params, enabled, dt);
            N++;
            if (block.fires()) {
                nfires++;
            }
        }
    }

    seti_blocks_on(nfires);

    //check fires to vector
    bool fires_changed = false;
    for (int i=0; i<W*H; i++) {
        int f = blocks_[i].fires();
        if (f != fires_[i]) {
            fires_changed = true;
        }
        fires_[i] = f;
    }
    //if changed - then reset timer for background update
    if (fires_changed) {
        static_time_ = time;
    }
    //update background
    float restore_sec = getf_background_restore_sec();
    if (time - static_time_ >= restore_sec) {
        background_ = input_;
        static_time_ = time;
    }
    if (restore_sec>0) {
        setf_restore_timer((time - static_time_) / restore_sec);
    }
    else {
        setf_restore_timer(0);
    }




    //detection result
    int fire = (nfires >= geti_blocks_threshold());
    if (!state_) {
        if (fire && time > time_ + getf_keep_off_sec()) {
            state_ = 1;
            time_ = time;
            //Bang on
            bang_on();
        }
    }
    else {
        if (fire) {     //update time on fire
            time_ = time;
        }
        if (!fire && time > time_ + getf_keep_off_sec()) {
            state_ = 0;
            time_ = time;
            //Bang off
            bang_off();
        }
    }

    seti_event(state_);

    //make output
    XRaster::convert(input_, output_);
    for (int Y=0; Y<H; Y++) {
        for (int X=0; X<W; X++) {
            auto &block = blocks_[X+W*Y];
            if (block.enabled()) {
                if (block.fires()) {
                    for (int y=block.y_; y<block.y_+block.h_; y++) {
                        for (int x=block.x_; x<block.x_+block.w_; x++) {
                            //colorize fires
                            output_.pixel_unsafe(x,y).v[0] = 255;   //red
                        }
                    }
                }
            }
            else {
                for (int y=block.y_; y<block.y_+block.h_; y++) {
                    for (int x=block.x_; x<block.x_+block.w_; x++) {
                        output_.pixel_unsafe(x,y).v[0] /= 3;    //fade brightness
                        output_.pixel_unsafe(x,y).v[1] /= 3;
                        output_.pixel_unsafe(x,y).v[2] /= 3;
                    }
                }
            }
        }
    }
    //border
    int border_w = 10;
    rgb_u8 border_color(0,0,0);
    if (state_) {
        border_color = rgb_u8(255,0,0);
        if (fire) {
            border_color = rgb_u8(255,255,0);
        }
    }
    else {
        if (fire) {
            border_color = rgb_u8(0,0,255);
        }

    }
    for (int y=0; y<h; y++) {
        for (int x=0; x<border_w; x++) {
            output_.pixel_unsafe(x,y) = border_color;
            output_.pixel_unsafe(w-1-x,y) = border_color;
        }
    }



    //set to images
    XObjectImage::create_from_raster(out_image_.write().data(), output_);
    XObjectImage::create_from_raster(out_background_.write().data(), background_);
}

//---------------------------------------------------------------------
void XModuleMotionDetector::bang_on() {
    XCORE.bang(get_strings_bang_on());
}

//---------------------------------------------------------------------
void XModuleMotionDetector::bang_off() {
    XCORE.bang(get_strings_bang_off());
}

//---------------------------------------------------------------------
void XModuleMotionDetector::impl_stop() {
    //send "off" at stop
    bang_off();

}

//---------------------------------------------------------------------
//void XModuleTimerm::impl_button_pressed(QString button_id) {
//}

//---------------------------------------------------------------------
