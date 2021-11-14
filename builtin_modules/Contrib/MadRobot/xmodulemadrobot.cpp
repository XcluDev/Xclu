#include "qt_widgets.h"
#include "xmodulemadrobot.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "project_props.h"
#include "module.h"
#include "xobjectimage.h"


//registering module implementation
REGISTER_XMODULE(MadRobot)

//---------------------------------------------------------------------
XModuleMadRobot::XModuleMadRobot(QString class_name)
    :XModuleWidget(class_name)
{

}

//---------------------------------------------------------------------
XModuleMadRobot::~XModuleMadRobot()
{

}


//---------------------------------------------------------------------
void XModuleMadRobot::start() {
    webcam_.clear();

    //link yolo image to GUI
    image_gui_.clear();
    setobject_yolo_image(&image_gui_);

    set_state("---");

    //auto start mind
    if (geti_auto_start()) {
        mind_start();
    }

}

//---------------------------------------------------------------------
void XModuleMadRobot::set_state(QString state) {
    state_ = state;
    xc_console_append(state_);
}

//---------------------------------------------------------------------
void XModuleMadRobot::update() {
    //Buttons
    if (geti_btn_mind_start()) mind_start();
    if (geti_btn_mind_stop()) mind_stop();
    if (geti_btn_pick_up()) move_pickup();
    if (geti_btn_forw()) move_forward();
    //if (geti_btn_back()) move_backward();
    if (geti_btn_left()) move_left();
    if (geti_btn_right()) move_right();
    if (geti_btn_stop()) move_stop();

    //Read image
    XObjectImage::to_raster(getobject_input_image(), webcam_);
    if (webcam_.w == 0) return;

    //transform
    int w = webcam_.w;
    int h = webcam_.h;
    int x0 = geti_crop_x0() * w / 100;
    int y0 = geti_crop_y0() * h / 100;
    int x1 = geti_crop_x1() * w / 100;
    int y1 = geti_crop_y1() * h / 100;

    auto cropped = webcam_.crop(x0, y0, x1-x0, y1-y0);
    XRaster::resize_nearest(cropped, image_,geti_resize_x(), geti_resize_y());
    XObjectImage::create_from_raster(image_gui_, image_);

    //write to yolo
    XRaster::save(image_, gets_yolo_write_image(), "JPG");

    //parse yolo
    parse_yolo();

    //robot
    mind_update();

    repaint();   //call to update screen
}



//---------------------------------------------------------------------
void XModuleMadRobot::move_pickup() {
    set_state("pick up");
    xc_bang(gets_ard_pick_up());
}

//---------------------------------------------------------------------
void XModuleMadRobot::move_forward() {
    set_state("forward");
    xc_bang(gets_ard_forw());
}

//---------------------------------------------------------------------
void XModuleMadRobot::move_backward() {
    set_state("backward");
    xc_bang(gets_ard_back());
}

//---------------------------------------------------------------------
void XModuleMadRobot::move_left() {
    set_state("left");
    xc_bang(gets_ard_left());
}

//---------------------------------------------------------------------
void XModuleMadRobot::move_right() {
    set_state("right");
    xc_bang(gets_ard_right());
}

//---------------------------------------------------------------------
void XModuleMadRobot::move_stop() {
    set_state("stop");
    xc_bang(gets_ard_stop());
}

//---------------------------------------------------------------------
void XModuleMadRobot::parse_yolo() {

    /*
    0 0.2100 0.3200 0.0895 0.0971
    0 0.5285 0.3169 0.1411 0.1377
    0 0.2900 0.2750 0.0286 0.0533
    */
    QString yolo_file = gets_yolo_read_TXT();

    //we need to delete this file because YOLO waits while we delete it
    QFile(yolo_file).remove();

    //wait while this file will be created
    int max_wait = 1000;    //milliseconds
    int one_wait = 20;
    int final_wait = 10;
    int waited = 0;
    bool found = false;
    while (waited < max_wait) {
        QThread::msleep(one_wait);
        waited += one_wait;
        if (xc_file_exists(yolo_file)) {
            //wait a while to finish writing file
            QThread::msleep(final_wait);
                found = true;
                break;
        }
    }
    if (!found) {
        xc_console_append("YOLO timeout...");
        return;
    }

    //reading and parsing
    auto file = xc_read_text_file(yolo_file);
    sets_yolo_data(file.join("\n"));

    int n = file.size();
    pnt_.resize(n);
    size_.resize(n);
    for (int i=0; i<n; i++) {
        QStringList list = file[i].split(" ");
        if (list.size() == 5) {
            pnt_[i].x = list[1].toFloat();
            pnt_[i].y = list[2].toFloat();
            size_[i].x = list[3].toFloat();
            size_[i].y = list[4].toFloat();
        }
    }

}

//---------------------------------------------------------------------
void XModuleMadRobot::mind_start() {
    xc_console_append("mind_start");
    mind_on_ = true;

    target_ = glm::vec2(xrandomf(-0.3f,0.3f), xrandomf(-0.3f,0.3f));//glm::vec2(0,1000);
    target_size_ = glm::vec2(0,0);

    last_pickup = 0;

    queue_.clear();

    no_targets_ = 0;
    walking_ = false;
}

//---------------------------------------------------------------------
void XModuleMadRobot::mind_stop() {
    xc_console_append("mind_stop");
    mind_on_ = false;
}


//---------------------------------------------------------------------
void XModuleMadRobot::mind_update() {
    if (!mind_on_) return;

    //search target
    bool is_target = false;

    float dist = 100000;
    int k = -1;
    target_ = glm::vec2(0,1000);
    target_size_ = glm::vec2(0,0);

    glm::vec2 cross = glm::vec2(getf_cross_x(), getf_cross_y());
    for (int i=0; i<pnt_.size(); i++) {
        float d = glm::distance(pnt_[i], cross);
        if (d < dist) {
            dist = d;
            k = i;
        }
    }
    if (k >= 0) {
        target_ = pnt_[k] - cross;
        target_size_ = size_[k];
        no_targets_=0;
        is_target = true;
    }
    else {
        no_targets_++;
        xc_console_append(QString("Waiting targets %1...").arg(no_targets_));
    }

    //if we are walking - then stop walk and move to target
    if (walking_ && is_target) {
        walking_ = false;
        queue_.clear();
        xc_console_append("Found target, stop walking");
    }

    float time = xc_elapsed_time_sec();
    //qDebug() << time << queue_.size();
    //apply queue
    bool is_queue = false;
    while (!queue_.isEmpty()) {
        is_queue = true;
        auto &a = queue_[0];
        //qDebug() << "action " << a.action << " time " << time;
        if (time < a.end_time) return;  //waiting...

        //time is over, delete and perform next
        queue_.erase(queue_.begin());
        if (!queue_.isEmpty()) {
            auto &a = queue_[0];
            //perform
            int act = a.action;
            if (act == Pickup) move_pickup();
            if (act == Forward) move_forward();
            if (act == Backward) move_backward();
            if (act == Left) move_left();
            if (act == Right) move_right();
            if (act == Stop) move_stop();
        }
    }
    if (is_queue) return; //nothing to do now!!!




    //if no targets for long time - run random walk for a while
    int max_no_targets = 12;    //PARAM
    if (no_targets_>=max_no_targets) {
        no_targets_ = 0;
        walking_ = true;
        //random walk
        float t = xc_elapsed_time_sec();
        for (int i=0; i<2; i++) {
            t+= 2;
            put_action(Action(Forward,t));
             if (xrandomf(-1,1)>0) {
                 for (int i=0; i<8; i++) {
                     t += 0.3f;
                     put_action(Action(Right,t));
                 }
             }
             else {
                 for (int i=0; i<8; i++) {
                 t += 0.3f;
                 put_action(Action(Left,t));
                 }
             }
        }
        return; //nothing to  do now, we are pickuping!
    }

    //pickup
    float w = getf_cross_w();
    float h = getf_cross_h();
    float x0 = qMax(target_.x-target_size_.x/2,-w/2);
    float x1 = qMin(target_.x+target_size_.x/2,w/2);
    float y0 = qMax(target_.y-target_size_.y/2,-h/2);
    float y1 = qMin(target_.y+target_size_.y/2,h/2);

//    bool inside = (fabs(target_.x) <= getf_cross_w()/2 && fabs(target_.y) <= getf_cross_h()/2);

    //qDebug() << "area " << x1-x0 << " " << y1-y0 << " " << (x1-x0)*(y1-y0) << " >? " << w*h/4;
    float cover = w*h*geti_cross_cover()/100.f; //how much need to cover for pickup

    bool inside = (x1-x0 >0 && y1-y0>0 && (x1-x0)*(y1-y0) > cover); //area is big enough

    if (inside) {
        xc_console_append("--- Pick up ---");
        float t = xc_elapsed_time_sec();

        //target_ = glm::vec2(xrandomf(-0.3,0.3), xrandomf(-0.3,0.3));
        //target_size_ = glm::vec2(0,0);

        t+= 0.5;
        put_action(Action(Stop,t));

        t+=13;
        put_action(Action(Pickup,t));

        if (xrandomf(-1,1)>0) {
            for (int i=0; i<15; i++) {
            t += 0.3f;
            put_action(Action(Right,t));
            }
        }
        else {
            for (int i=0; i<15; i++) {
            t += 0.3f;
            put_action(Action(Left,t));
            }
        }
        t+= 4;
        put_action(Action(Forward,t));

        return; //nothing to  do now, we are pickuping!
    }

    //move to target
    //below or rotated - then rotate, else move forward
    float perspective_correction = 1; //0.7; //TODO PARAM

    if (!no_targets_) {
        if (target_.y > 0 || fabs(target_.x) > fabs(target_.y)*perspective_correction) {
            if (target_.x > 0) move_right();
            else move_left();
            return;
        }
        move_forward();
    }

}


//---------------------------------------------------------------------
void XModuleMadRobot::stop() {
}

//---------------------------------------------------------------------
void XModuleMadRobot::draw(QPainter &painter, int outw, int outh) {

    //Antialiasing
    painter.setRenderHint(QPainter::Antialiasing);

    //Draw background
    painter.setBrush(QColor(0, 0, 0));
    painter.setPen(Qt::PenStyle::NoPen);
    painter.drawRect(0, 0, outw, outh);

    //Image
    XRaster::draw(&painter, image_, QRectF(0,0,outw,outh));

    //YOLO
    for (int i=0; i<pnt_.size(); i++) {
        QPen pen(QColor(255,255,0));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.setBrush(Qt::BrushStyle::NoBrush);
        painter.drawRect((pnt_[i].x-size_[i].x/2)*outw, (pnt_[i].y-size_[i].y/2)*outh,
                         size_[i].x*outw, size_[i].y*outh);
    }

    //Cross
    bool pickup  = !queue_.isEmpty();

    QPen pen(QColor(0,255,255));
    if (pickup) pen.setColor(QColor(255,0,0));
    if (walking_) pen.setColor(QColor(0,0,255));

    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::BrushStyle::NoBrush);
    glm::vec2 cross = glm::vec2(getf_cross_x(),getf_cross_y());
    glm::vec2 size = glm::vec2(getf_cross_w(),getf_cross_h());
    painter.drawRect((cross.x-size.x/2)*outw, (cross.y-size.y/2)*outh,
                     size.x*outw, size.y*outh);
    painter.drawLine((cross.x-size.x/4)*outw, (cross.y)*outh,
                     (cross.x+size.x/4)*outw, (cross.y)*outh);
    painter.drawLine((cross.x)*outw, (cross.y-size.y/4)*outh,
                     (cross.x)*outw, (cross.y+size.y/4)*outh);

    //Target
    if (!pickup) {
        QPen pen(QColor(0,0,255));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawLine((cross.x)*outw, (cross.y)*outh,
                         (cross.x+target_.x)*outw, (cross.y+target_.y)*outh);
    }
/*    //Compute translate and scale
    //Note: we use scaling to have independence of lines width from screen resolution
    int spacing = geti_spacing();

    float w = 300;  //base size
    float h = 300;
    float wsp = w + spacing;

    float scrw = 3*w + 2*spacing;
    float scrh = h;

    float scl = qMin(outw/scrw, outh/scrh);
    float outw1 = scrw*scl;
    float outh1 = scrh*scl;

    int x0 = (outw-outw1)/2;
    int y0 = (outh-outh1)/2;

    painter.save();
    painter.translate(x0, y0);
    painter.scale(scl, scl);

    //------------------------
    //Actual drawing

    //Face
    face_draw(painter, w, h);

    //Vector field - attractors
    painter.save();
    painter.translate(wsp, 0);
    //painter.setPen(QColor(255,255,255));
    //painter.setBrush(Qt::BrushStyle::NoBrush);
    //painter.drawRect(0,0,w,h);
    attr_draw(painter, w, h);

    painter.restore();

    //Morph
    painter.save();    
    painter.translate(2*wsp, 0);    
    morph_draw(painter, w, h);
    painter.restore();

    //border
    painter.setPen(get_col(getf_border_color()));
    painter.setBrush(Qt::BrushStyle::NoBrush);
    painter.drawRect(0,0,scrw,scrh);
    painter.drawLine(w,0,w,h);
    painter.drawLine(scrw-w,0,scrw-w,h);


    //------------------------
    painter.restore();
    */
}



//---------------------------------------------------------------------

