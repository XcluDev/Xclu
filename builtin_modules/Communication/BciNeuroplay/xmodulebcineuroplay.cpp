#include "xmodulebcineuroplay.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "project_props.h"
#include <Processing.NDI.Lib.h>
 

REGISTER_XMODULE(BciNeuroplay)

//---------------------------------------------------------------------
XModuleBciNeuroplay::XModuleBciNeuroplay(QString class_name)
    :XModuleWidget(class_name)
{

}

//---------------------------------------------------------------------
XModuleBciNeuroplay::~XModuleBciNeuroplay()
{

}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::on_loaded() {
    //sets_send_status("Not started");
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::on_button_pressed(QString button_id) {
    //if (button_id == "print_devices") {

    //}

}


//---------------------------------------------------------------------
void XModuleBciNeuroplay::start() {
  /*  sets_send_status("Not started");
    ndi_inited_ = false;

    sent_frames_  = 0;

    auto mode = gete_send_mode();
    if (mode != send_mode_Off) {
        ndi_init();
    }
*/
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::update() {
  /*  auto mode = gete_send_mode();
    if (mode == send_mode_Each_Frame
            || (mode == send_mode_On_Checkbox && geti_send_new_frame())) {
        //Send frame
        send_frame();
    }
    */

    redraw();   //call to update screen
}


//---------------------------------------------------------------------
void XModuleBciNeuroplay::stop() {
  /*  ndi_stop();

    test_raster_.clear();
*/
}


//---------------------------------------------------------------------
void XModuleBciNeuroplay::draw(QPainter &painter, int outw, int outh) {

    //Antialiasing
    painter.setRenderHint(QPainter::Antialiasing);

    //Draw background
    painter.setBrush(QColor(0, 0, 0));
    painter.setPen(Qt::PenStyle::NoPen);
    painter.drawRect(0, 0, outw, outh);

  /*  //Image
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
/*void XModuleBciNeuroplay::send_frame() {
    if (!ndi_inited_) {
        return;
    }

    auto source = gete_send_image_source();
    if (source == send_image_source_Image) {
        XProtectedObject *image = getobject_send_image();
        auto read = image->read();
        if (read.data().type() == XObjectTypeImage) {
            auto info = XObjectImage::get_data(read.data());
            xc_assert(info.data_type == "u8" || info.channels == 4,
                     "XModuleBciNeuroplay::send_frame - only u8, 4 channels are supported");
            auto *array = XObjectImage::get_array(read.data());
            const unsigned char *u8 = array->data_u8();
            xc_assert(u8, "XModuleBciNeuroplay::send_frame - Empty image array 'u8'");

            ndi_send_image(u8, info.w, info.h);
        }
    }
    if (source == send_image_source_Test_Image) {
        send_test_frame(sent_frames_);
    }
}
*/
//---------------------------------------------------------------------
/*void XModuleBciNeuroplay::send_test_frame(int frame) {
    if (!ndi_inited_) {
        return;
    }
    int w = 512;
    int h = 256;

    // allocate
    if (test_raster_.is_empty()) {
        test_raster_.allocate(w, h);
    }

    // fill
    auto test_raster_data = test_raster_.data_pointer();
    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            test_raster_data[x + w*y] = rgba_u8(
                        ((x + frame) * 256 / w) % 256,
                        x * 256 / w,
                        y * 256 / h,
                        255);
        }
    }

    // send
    ndi_send_image(test_raster_.data_pointer_u8(), w, h);

}


//---------------------------------------------------------------------
void XModuleBciNeuroplay::ndi_init() {
    if (!ndi_inited_) {
        auto result = NDIlib_initialize();
        xc_assert(result, "Can't initialize NDI: Library error");
        if (!result) return;

        // We create the NDI sender
        NDIlib_send_create_t params;
        params.clock_audio = false;
        params.clock_video = false;
        params.p_groups = nullptr;
        params.p_ndi_name = gets_sender_name().toStdString().c_str();

        //TODO for unknown reason setting "p_ndi_name" not have effect when running "VB NDI Receive Example.exe"
        pNDI_send_ = NDIlib_send_create(&params);

        xc_assert(pNDI_send_, "Can't initialize NDI: error creating sender");
        if (!pNDI_send_) return;

        sets_send_status("NDI started");
        ndi_inited_ = true;
    }
}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::ndi_send_image(const unsigned char *data_rgba, int w, int h) {
    if (!ndi_inited_) {
        return;
    }
    xc_assert(data_rgba && w > 0 && h > 0, "XModuleBciNeuroplay::ndi_send_image - bad input raster");

    NDIlib_video_frame_v2_t NDI_video_frame;
    NDI_video_frame.xres = w;
    NDI_video_frame.yres = h;
    NDI_video_frame.FourCC = NDIlib_FourCC_type_RGBA;
    NDI_video_frame.p_data = (unsigned char *)data_rgba;

    //-----------------------
    //We disabled clocking "params.clock_video = false", so may be this not occur:
    //??? "Note that this call will be clocked so that we end up submitting at exactly 29.97fps."
    //-----------------------
    //Sending the frame.
    NDIlib_send_send_video_v2(pNDI_send_, &NDI_video_frame);

    // updating status
    sent_frames_++;
    sets_send_status(QString("Sending frame: %1").arg(sent_frames_));

}

//---------------------------------------------------------------------
void XModuleBciNeuroplay::ndi_stop() {
    if (ndi_inited_) {
        // Destroy the NDI sender
        NDIlib_send_destroy(pNDI_send_);
        pNDI_send_ = nullptr;

        // Not required, but nice
        NDIlib_destroy();

        ndi_inited_ = false;
        sets_send_status("NDI stopped");
    }
}
*/
//---------------------------------------------------------------------


