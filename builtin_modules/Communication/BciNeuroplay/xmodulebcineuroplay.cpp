#include "xmodulebcineuroplay.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "project_props.h"
#include <Processing.NDI.Lib.h>
 

REGISTER_XMODULE(BciNeuroplay)

//---------------------------------------------------------------------
XModuleBciNeuroplay::XModuleBciNeuroplay(QString class_name)
    :XModule(class_name)
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
}


//---------------------------------------------------------------------
void XModuleBciNeuroplay::stop() {
  /*  ndi_stop();

    test_raster_.clear();
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


