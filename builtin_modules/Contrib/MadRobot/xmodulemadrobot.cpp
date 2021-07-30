#include "qt_widgets.h"
#include "xmodulemadrobot.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xcore.h"
#include "module.h"
#include "xobjectimage.h"


//registering module implementation
REGISTER_XMODULE(MadRobot)

//---------------------------------------------------------------------
XModuleMadRobot::XModuleMadRobot(QString class_name)
    :XModuleVisual(class_name)
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

    received_state_ = ReceivedStateStarted;

}

//---------------------------------------------------------------------
void XModuleMadRobot::update() {
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

    //parse python string
    parse_python();

    refresh();   //call to update screen
}

//---------------------------------------------------------------------
void XModuleMadRobot::parse_python() {
    //face 1 90 127 114 114 emotions 0.10962291 0.0005123505 0.13974306 0.070729405 0.051511575 0.11338797 0.51449275
    QString python_string = gets_python_string();

    if (python_string.isEmpty()) {
        if (received_state_ != ReceivedStateWaiting) {
            xc_console_append("Waiting Python answer...");
            received_state_ = ReceivedStateWaiting;
        }
        return;
    }

    /*QStringList list = python_string.split(" ");
    is_face_ = 0;
    if (list.size() == 2 + 5 + n_) {
        int k = 0;
        //"face"
        k++;
        //is face
        is_face_ = list[k++].toInt();
        //face position
        float w = geti_image_face_w();
        float h = geti_image_face_h();

        face_rect_u_.setLeft(list[k++].toInt()/w); //it's important to fill field by field, for correct k increasing
        face_rect_u_.setTop(list[k++].toInt()/h);
        face_rect_u_.setWidth(list[k++].toInt()/w);
        face_rect_u_.setHeight(list[k++].toInt()/h);

        //emotions
        k++;

        //emotions vector
        for (int i=0; i<n_; i++) {
            emovec_[i] = list[k++].toFloat();
        }
        //if not face - discard readed values
        if (!is_face_) {
            for (int i=0; i<n_; i++) {
                emovec_[i] = 0;
            }
        }

        xc_assert(k == list.size(), "Internal error at parse_python: not all string is parsed" + python_string);

        if (received_state_ != ReceivedStateParsed) {
            xc_console_append("Python data received and parsed");
            received_state_ = ReceivedStateParsed;
        }
    }
    else {
        xc_console_append("Bad python string, not consistent with number of emotions: " + python_string);
    }
    */

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

    XRaster::draw(&painter, webcam_, QRectF(0,0,320,320));

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

