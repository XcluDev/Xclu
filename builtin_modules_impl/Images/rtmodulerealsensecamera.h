#ifndef RTMODULEREALSENSECAMERA_H
#define RTMODULEREALSENSECAMERA_H

//Working with Realsense camera

#include <QScopedPointer>
#include <QImage>
#include <QMutex>
#include "incl_qt.h"
#include "rtmodule.h"
#include "xcluobjectimage.h"
#include "xcluprotecteddata.h"

#include "incl.h"
#include "librealsense2/rs.hpp"
#include "librealsense2/hpp/rs_internal.hpp"
#include "librealsense2/rsutil.h"


void camera_test();

/*
    Available resolutions and framerates:
    Depth/IR:
    424x240
    480x270
    640x360
    640x480
    848x480
    1280x720
    1280x800
    FPS: 6,15,25,30,60,90

    RGB:
    320x180
    320x240
    424x240
    640x360
    640x480
    848x480
    960x540
    1280x720
    1920x1080
    FPS: 6,15,30,60

    Visual presets
    Table and more info: https://github.com/IntelRealSense/librealsense/wiki/D400-Series-Visual-Presets
    Load from JSON: https://github.com/IntelRealSense/librealsense/issues/3037

    RS2_RS400_VISUAL_PRESET_CUSTOM,            0
    RS2_RS400_VISUAL_PRESET_DEFAULT,           1
    RS2_RS400_VISUAL_PRESET_HAND,              2
    RS2_RS400_VISUAL_PRESET_HIGH_ACCURACY,     3
    RS2_RS400_VISUAL_PRESET_HIGH_DENSITY,      4
    RS2_RS400_VISUAL_PRESET_MEDIUM_DENSITY,    5
    RS2_RS400_VISUAL_PRESET_REMOVE_IR_PATTERN  6
*/


//Settings for starting device
struct Realsense_Settings {
    //Loading settings from JSON file made with RealSense Viewer
    //void set_config_file(QString file_name) {
    //    use_config_file = true;
    //    this->config_file_name = file_name;
    //}

    //bool use_config_file = false;
    //QString config_file_name;

    int visual_preset = RS2_RS400_VISUAL_PRESET_HIGH_DENSITY; //-1;	//-1 - Disable setting visual preset

    int use_depth = 1;
    int use_ir = 0;
    int use_rgb = 1;
    int use_emitter = 1;

    int depth_w = 1280;
    int depth_h = 720;
    int depth_fps = 30;

    int rgb_w = 1280;
    int rgb_h = 720;
    int rgb_fps = 30;
};


//Holder for Realsense device structures
struct Realsense_Device
{
    bool connected = false;
    rs2::frame depth;
    float depth_scale_mm = 1;

    rs2::colorizer colorize_frame;
    rs2::pipeline pipe;
    rs2::pipeline_profile profile;

    // Declare pointcloud object, for calculating pointclouds and texture mappings
    rs2::pointcloud pc;
    // We want the points object to be persistent so we can display the last cloud when a frame drops
    rs2::points points;

    rs2::frame color_frame;
    rs2::frame ir_frame;

    //Aligning
    //https://github.com/IntelRealSense/librealsense/blob/master/examples/align/rs-align.cpp
    QScopedPointer<rs2::align> align_to_depth;
};

class Camera
{
public:
    static QString get_sdk_version();
    static int get_number_of_connected_devices();
    static QStringList get_connected_devices_list();

    Camera();
    ~Camera();

    void start_camera(const Realsense_Settings &settings);	    //start camera
    void start_bag(QString fileName);       //play BAG file

    void update();
    void close();

    bool connected() { return device_.connected; }

    bool isFrameNew() { return frameNew_;  }

    QImage &get_rgb_image();
    QImage &get_depth_image();

    bool get_depth_pixels_rgb(int &w, int &h, QVector<quint8> &data);
    bool get_color_pixels_rgb(int &w, int &h, QVector<quint8> &data);

    //TODO
    //callback for connecting/disconnecting devices, see rs-multicam example in SDK
    //auto reconnect if device was connected again

    //TODO optimization
    //not compute texture coordinates if not required


    bool get_point_cloud(QVector<glm::vec3> &pc,
                         int &gridw, int &gridh,
                         int mirrorx = 0, int mirrory = 0, int mirrorz = 0);	//get point cloud for connected device

    //bool get_depth_pixels_mm(int &w, int &h, vector<float> &data);
    //bool get_depth_pixels_mm(int &w, int &h, vector<unsigned short> &data);
    //bool get_depth_pixels8(float min_dist, float max_dist, int &w, int &h, vector<unsigned char> &data);


    //bool get_color_pixels_rgb(int &w, int &h, vector<unsigned char> &data);
    //bool get_ir_pixels_rgb(int &w, int &h, vector<unsigned char> &data);

    //project 3d to screen
    glm::vec2 project_3d_to_screen(const glm::vec3 &p);

protected:
    Realsense_Settings settings_;

    bool frameNew_ = false;

    //QMutex Realsense_mutex_;
    rs2::context Realsense_ctx;

    Realsense_Device device_;

    bool frame_to_pixels_rgb(const rs2::video_frame& frame, int &w, int &h, QVector<quint8> &data);

    bool get_depth16_raw(int &w, int &h, uint16_t* &data16);

    bool dirty_image_ = false;
    QImage image_;
    bool dirty_image_depth_ = false;
    QImage image_depth_;

    void setup(rs2::device &dev, const Realsense_Settings &settings);

    //intrinsics for converting 3d to image
    bool intrinsics_inited_ = false;
    rs2_intrinsics intrinsics_;


};


#endif // RTMODULEREALSENSECAMERA_H
