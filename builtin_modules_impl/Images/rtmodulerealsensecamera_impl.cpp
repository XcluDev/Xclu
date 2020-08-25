#include "rtmodulerealsensecamera_impl.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
/*static*/ QString RealsenseCamera::get_sdk_version() {
    return (QString("Realsense SDK %1").arg(RS2_API_VERSION_STR));
}

//---------------------------------------------------------------------
/*static*/ int RealsenseCamera::get_number_of_connected_devices() {
    rs2::context ctx;
    return ctx.query_devices().size();
}

//---------------------------------------------------------------------
/*static*/ QVector<RealsenseCameraInfo> RealsenseCamera::get_connected_devices_info() {
    QVector<RealsenseCameraInfo> list;
    rs2::context ctx;
    int i = 0;
    for (auto&& dev : ctx.query_devices()) {
        i++;
        QString id = dev.get_info(RS2_CAMERA_INFO_NAME);

        QString firmware = dev.get_info(RS2_CAMERA_INFO_FIRMWARE_VERSION);
        QString usb = dev.get_info(RS2_CAMERA_INFO_USB_TYPE_DESCRIPTOR);

        QString serial = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);

        RealsenseCameraInfo info;
        info.descr_full = QString("Device %1: %2, serial %3, firmware %4, connected to USB %5")
                    .arg(i).arg(id, serial, firmware, usb);
        info.descr_short = QString("Device %1: %2, serial %3")
                    .arg(i).arg(id, serial);
        info.serial = serial;
        list.push_back(info);
    }
    return list;

}

//---------------------------------------------------------------------
/*static*/ QStringList RealsenseCamera::get_connected_devices_list() {
    QStringList list;
    QVector<RealsenseCameraInfo> list1 = get_connected_devices_info();
    for (auto &info: list1) {
        list.append(info.descr_full);
    }
    return list;
}

//---------------------------------------------------------------------
RealsenseCamera::RealsenseCamera() {

}

//---------------------------------------------------------------------
RealsenseCamera::~RealsenseCamera() {
    close();
}

//---------------------------------------------------------------------
void RealsenseCamera::setup(rs2::device &dev, const RealsenseSettings &settings) {
    qDebug() << "RealSense device starting";

    settings_ = settings;
    auto &S = settings_;
    //auto &ctx = Realsense_ctx;
    rs2::config cfg;

    std::string serial = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);
    device_.connected = false;	//setting it true later only if success

    //Start using settings
    QString stage = "---";
    try {

        //Aligning - must to create before start camera
        //https://github.com/IntelRealSense/librealsense/blob/master/examples/align/rs-align.cpp
        // Define two align objects. One will be used to align
        // to depth viewport and the other to color.
        // Creating align object is an expensive operation
        // that should not be performed in the main loop

        //TODO !!!!!!!! control deleting when camera stop
        if (S.align_to_depth && S.use_depth) {
            device_.align_to_depth.reset(new rs2::align(RS2_STREAM_DEPTH));
        }

        stage = "Disable all streams";
        cfg.disable_all_streams();
        stage = "Enable depth stream";

        //See about formats:
        //https://github.com/IntelRealSense/librealsense/issues/1140

        if (S.use_depth) {
            cfg.enable_stream(RS2_STREAM_DEPTH, S.depth_w, S.depth_h, RS2_FORMAT_Z16, S.depth_fps);
        }
        stage = "Enable color stream";
        if (S.use_rgb) {
            cfg.enable_stream(RS2_STREAM_COLOR, S.rgb_w, S.rgb_h, RS2_FORMAT_ANY, S.rgb_fps);
        }
        stage = "Enable IR stream";
        if (S.use_ir) {
            int ir_id = 1;  //TODO can choose 1 or 2
            cfg.enable_stream(RS2_STREAM_INFRARED, ir_id, S.depth_w, S.depth_h, RS2_FORMAT_Y8, S.depth_fps);
        }
        //__log__("resolution " + ofToString(w) + " " + ofToString(h) + " " + ofToString(fps));

        //---------------------------------
        //stage = "Enable device" + serial;
        cfg.enable_device(serial);
        // Start the pipeline with the configuration

        stage = "Pipe start";
        device_.profile = device_.pipe.start(cfg);

        //Setting preset and obtain depth_scale
        stage = "Get selected device";
        rs2::device selected_device = device_.profile.get_device();

        stage = "Get depth sensor";
        auto depth_sensor = selected_device.first<rs2::depth_sensor>();

        //Setting preset
        stage = "Set visual preset";
        if (S.visual_preset > -1) {
            if (depth_sensor.supports(RS2_OPTION_VISUAL_PRESET)) {
                depth_sensor.set_option(RS2_OPTION_VISUAL_PRESET, S.visual_preset);

                //High accuracy preset
                //depth_sensor.set_option(RS2_OPTION_VISUAL_PRESET, RS2_RS400_VISUAL_PRESET_HIGH_ACCURACY);
                //High density preset
                //depth_sensor.set_option(RS2_OPTION_VISUAL_PRESET, RS2_RS400_VISUAL_PRESET_HIGH_DENSITY);
            }
        }

        stage = "Obtain depth scale";
        //https://github.com/IntelRealSense/librealsense/issues/2348
        //rs2::device dev = device_.profile.get_device();
        //rs2::depth_sensor ds = dev.query_sensors().front().as<rs2::depth_sensor>();
        device_.depth_scale_mm = depth_sensor.get_depth_scale() * 1000;

        stage = "Set using emitter";
        if (depth_sensor.supports(RS2_OPTION_EMITTER_ENABLED)) {
            depth_sensor.set_option(RS2_OPTION_EMITTER_ENABLED, S.use_emitter);//on/off emitter
        }

        //console_append("RealsenseCamera started");
        device_.connected = true;
    }
    catch (std::exception &error) {
        xclu_exception(
                    QString("Realsense connect error at stage %1. Error text: %2")
                 .arg(stage, error.what()));
    }

    //if (depth_sensor.supports(RS2_OPTION_LASER_POWER)) {
    //	depth_sensor.set_option(RS2_OPTION_LASER_POWER, 0.f); // Disable laser
    //}

    /*
        //Control laser and emitter
        //https://github.com/IntelRealSense/librealsense/wiki/API-How-To
        rs2::pipeline pipe;
        rs2::pipeline_profile selection = pipe.start();
        rs2::device selected_device = selection.get_device();
        auto depth_sensor = selected_device.first<rs2::depth_sensor>();

        if (depth_sensor.supports(RS2_OPTION_EMITTER_ENABLED))
        {
        depth_sensor.set_option(RS2_OPTION_EMITTER_ENABLED, 1.f); // Enable emitter
        depth_sensor.set_option(RS2_OPTION_EMITTER_ENABLED, 0.f); // Disable emitter
        }
        if (depth_sensor.supports(RS2_OPTION_LASER_POWER))
        {
        // Query min and max values:
        auto range = depth_sensor.get_option_range(RS2_OPTION_LASER_POWER);
        depth_sensor.set_option(RS2_OPTION_LASER_POWER, range.max); // Set max power
        depth_sensor.set_option(RS2_OPTION_LASER_POWER, 0.f); // Disable laser
    }
    */
}

//---------------------------------------------------------------------
bool RealsenseCamera::start_camera(int device_index, const RealsenseSettings &settings) {	    //start camera
    xclu_assert(!connected(), "Can't start Realsense, because it's already connected");

    auto &ctx = Realsense_ctx;

    //TODO можно сразу взять нужное устройство, а не перебирать в цикле :)
    int i = 0;
    for (auto&& dev : ctx.query_devices()) // Query the list of connected RealSense devices
    {
        if (i == device_index) {
            setup(dev, settings);
            return connected();
            break;
        }
        i++;
    }
    return false;
}

//--------------------------------------------------------------
void RealsenseCamera::start_bag(QString fileName) {       //play BAG file
    //https://github.com/IntelRealSense/librealsense/issues/2749


    rs2::config cfg;
    cfg.enable_device_from_file(fileName.toStdString());
    device_.profile = device_.pipe.start(cfg);

    //console_append("Started play bag file " + fileName);
    device_.connected = true;
}

//--------------------------------------------------------------
void RealsenseCamera::close() {
    if (device_.connected) {
        //ofxRealsense_devices_.clear();
        device_.pipe.stop();
        device_.connected = false;
    }
}

//--------------------------------------------------------------
void RealsenseCamera::update() {
    frameNew_ = false;

    if (device_.connected) {
        RealsenseSettings &S = settings_;

        //wait for new frame:
        //https://github.com/IntelRealSense/librealsense/blob/master/examples/align/rs-align.cpp
        // Using the align object, we block the application until a frameset is available
        //rs2::frameset frameset = pipe.wait_for_frames();


        //std::lock_guard<std::mutex> lock(ofxRealsense_mutex_);
        // Ask each pipeline if there are new frames available
        rs2::frameset frameset;
        if (device_.pipe.poll_for_frames(&frameset)) {

            if (S.align_to_depth && S.use_depth) {
                // Align all frames to depth viewport
                frameset = device_.align_to_depth->process(frameset);
            }

            frameNew_ = true;
            if (S.use_depth) {
                auto depth = frameset.get_depth_frame();
                device_.points = device_.pc.calculate(depth);			//TODO not compute texture coordinates
                device_.depth = depth;
                //dirty_image_depth_ = true;

                //init instrinsics for project 3d to screen
                if (!intrinsics_inited_) {
                    intrinsics_inited_ = true;
                    auto frame = depth.as<rs2::video_frame>();
                    auto profile = frame.get_profile();
                    auto vsp = profile.as<rs2::video_stream_profile>();
                    intrinsics_ = vsp.get_intrinsics();
                }

            }
            if (S.use_rgb) {
                device_.color_frame = frameset.get_color_frame();
                //dirty_image_ = true;
            }
            if (S.use_ir) {
                device_.ir_frame = frameset.get_infrared_frame(0);	//TODO choose 0,1
            }

            //cout << device.points.size() << endl;

            /*cout << "get frames " << frameset.size() << endl;
            for (int i = 0; i < frameset.size(); i++)
            {
                rs2::frame new_frame = frameset[i];
                int stream_id = new_frame.get_profile().unique_id();
                int stream_type = new_frame.get_profile().stream_type();
                cout << "\t" << stream_type << endl;
                auto depth = frames.get_depth_frame();
                //view.second.frames_per_stream[stream_id] = view.second.colorize_frame.process(new_frame); //update view port with the new stream
            }*/

        }
    }
}

//--------------------------------------------------------------
//project 3d to screen
glm::vec2 RealsenseCamera::project_3d_to_screen(const glm::vec3 &p) {
    if (intrinsics_inited_) {
        float point[3];
        point[0] = p.x;
        point[1] = p.y;
        point[2] = p.z;

        float pix[2];

        rs2_project_point_to_pixel(pix, &intrinsics_, point);
        return glm::vec2(pix[0], pix[1]);
    }
    return glm::vec2(0,0);
}

//--------------------------------------------------------------
bool RealsenseCamera::get_point_cloud(QVector<glm::vec3> &pc,
                             int &gridw, int &gridh,
                             int mirrorx, int mirrory, int mirrorz) {				//get point cloud for connected device i

    pc.clear();
    gridw = 0;
    gridh = 0;
    if (device_.connected && device_.depth.get()) {
        rs2::points &points = device_.points;
        int size = int(points.size());
        pc.resize(size);
        if (size > 0) {
            float kx = (mirrorx) ? -1000 : 1000;
            float ky = (mirrory) ? -1000 : 1000;
            float kz = (mirrorz) ? -1000 : 1000;
            auto *v = points.get_vertices();
            for (int k = 0; k < size; k++) {
                auto V = v[k];
                pc[k] = glm::vec3(V.x * kx, V.y * ky, V.z * kz);
            }
            gridw = settings_.depth_w;
            gridh = settings_.depth_h;
            //qDebug() << "gridwxh = " << gridw * gridh << ", points: " << size << endl;
        }
        return true;
    }
    return false;
}


//--------------------------------------------------------------
bool RealsenseCamera::frame_to_pixels_rgb(const rs2::video_frame& frame, Raster_u8c3 &raster) {
    auto format = frame.get_profile().format();
    int w = frame.get_width();
    int h = frame.get_height();
    raster.allocate(w, h);
    auto &data = raster.data;
    //auto stream = frame.get_profile().stream_type();

    unsigned char *input = (unsigned char *)frame.get_data();

    if (format == RS2_FORMAT_Y8) {
        for (int i = 0; i < w*h; i++) {
            data[i].set(input[i]);
        }
        //__log__("RS2_FORMAT_Y8 ok");
        return true;
    }
    if (format == RS2_FORMAT_RGB8) {
        memcpy(&data[0], input, w*h * 3);
        //__log__("RS2_FORMAT_RGB8 ok");
        return true;
    }
    if (format == RS2_FORMAT_RGBA8) {
        int j = 0;
        for (int i = 0; i < w*h; i++) {
            data[i].v[0] = input[j++];
            data[i].v[1] = input[j++];
            data[i].v[2] = input[j++];
            j++;
        }
        //__log__("RS2_FORMAT_RGBA8 ok");
        return true;
    }
    return false;
}

//--------------------------------------------------------------
bool RealsenseCamera::get_color_pixels_rgb(Raster_u8c3 &raster) {
    if (!settings_.use_rgb) return false;
    if (device_.connected && device_.color_frame.get()) {
        return frame_to_pixels_rgb(device_.color_frame, raster);
    }

    return false;
}

//--------------------------------------------------------------
bool RealsenseCamera::get_depth16_raw(int &w, int &h, uint16_t* &data16) {
    w = 0;
    h = 0;
    data16 = NULL;
    if (!settings_.use_depth) return false;
    if (device_.connected && device_.depth.get()) {
        data16 = (uint16_t*)device_.depth.get_data(); //device_.depth.get_frame_data();
        if (!data16) return false;
        w = settings_.depth_w;		//TODO get straight from depth frame
        h = settings_.depth_h;
        return true;
    }
    return true;
}

//--------------------------------------------------------------
bool RealsenseCamera::get_depth_pixels8(float min_dist, float max_dist, Raster_u8 &raster) {
    raster.clear();
    int w = 0;
    int h = 0;
    raster.clear();
    uint16_t *data16;
    bool result = get_depth16_raw(w, h, data16);
    if (result) {
        raster.allocate(w, h);
        for (int i = 0; i < w*h; i++) {
            if (data16[i] > 0) {
                raster.data[i] = mapi_clamped(data16[i] * device_.depth_scale_mm, min_dist, max_dist, 255, 0);
            }
            else {
                raster.data[i] = 0;
            }
        }
        return true;
    }

    return false;
}

//--------------------------------------------------------------
bool RealsenseCamera::get_depth_pixels_rgb(Raster_u8c3 &raster) {
    if (!settings_.use_depth) return false;
    if (device_.connected && device_.depth.get()) {
        auto frame = device_.colorize_frame.process(device_.depth).as<rs2::video_frame>();
        return frame_to_pixels_rgb(frame, raster);
    }

    return false;
}


//--------------------------------------------------------------
bool RealsenseCamera::get_depth_pixels_mm(Raster_float &raster) {
    raster.clear();
    int w = 0;
    int h = 0;
    uint16_t *data16;
    bool result = get_depth16_raw(w, h, data16);
    if (result) {
        //https://github.com/IntelRealSense/librealsense/issues/2348
        raster.allocate(w, h);
        for (int i = 0; i < w*h; i++) {
            raster.data[i] = data16[i];// * device_.depth_scale_mm;
        }
        return true;
    }
    return false;
}

//--------------------------------------------------------------
bool RealsenseCamera::get_depth_pixels_mm(Raster_u16 &raster) {
    raster.clear();
    int w = 0;
    int h = 0;
    uint16_t *data16;
    bool result = get_depth16_raw(w, h, data16);
    if (result) {
        //https://github.com/IntelRealSense/librealsense/issues/2348
        raster.allocate(w, h);
        for (int i = 0; i < w*h; i++) {
            raster.data[i] = data16[i];// * device_.depth_scale_mm;
        }
        return true;
    }
    return false;
}

//--------------------------------------------------------------
bool RealsenseCamera::get_ir_pixels8(Raster_u8 &raster) {
    raster.clear();
    if (!settings_.use_ir) return false;
    if (device_.connected && device_.ir_frame.get()) {
        uint8 *data8 = (uint8*)device_.ir_frame.get_data();
        if (!data8) return false;
        int w = settings_.depth_w;		//TODO get straight from IR frame
        int h = settings_.depth_h;
        raster.allocate(w, h);
        for (int i=0; i<w*h; i++) {
            raster.data[i] = data8[i];
        }
        return true;
    }
    return false;
}

//--------------------------------------------------------------
bool RealsenseCamera::get_ir_pixels_rgb(Raster_u8c3 &raster) {
    if (!settings_.use_ir) return false;
    if (device_.connected && device_.ir_frame.get()) {
        auto frame = device_.colorize_frame.process(device_.ir_frame).as<rs2::video_frame>();
        //__log__("calling frame_to_pixels_rgb");
        return frame_to_pixels_rgb(frame, raster);
    }
    return false;
}

//---------------------------------------------------------------------


