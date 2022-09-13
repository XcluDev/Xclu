#ifndef XCLASSREALSENSECAMERAIMPL_H
#define XCLASSREALSENSECAMERAIMPL_H

//Implementation of working with Realsense camera, based on https://github.com/perevalovds/ofxRealsense

#include "librealsense2/rs.hpp"
#include "librealsense2/hpp/rs_internal.hpp"
#include "librealsense2/rsutil.h"
#include "sdk_h.h"
#include "xraster.h"


/*
 For converting BAGs to 3D files and images, use Intel Realsense SDK's
 rs-convert.
 On Linux it runs just as rs-convert,
 on Windows it's at C:\Program Files (x86)\Intel RealSense SDK 2.0\tools>
 For example, to extract PNGs to 'png' folder (create it first):
 rs-convert -i MadRobot_20210703.bag -p png/
*/

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
struct RealsenseSettings {
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

    int align_to_depth = 0; //Should RGB frames to be aligned to depth frames.
};


//Holder for Realsense device structures
struct RealsenseDevice
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

//Description of a camera
class RealsenseCameraInfo {
public:
    QString descr_full;
    QString descr_short;
    QString serial;
};

//Class for working with camera
class RealsenseCamera
{
public:
    static QString get_sdk_version();
    static int get_number_of_connected_devices();
    static QVector<RealsenseCameraInfo> get_connected_devices_info();
    static QStringList get_connected_devices_list();

    RealsenseCamera();
    virtual ~RealsenseCamera();

    bool start_camera(int device_index, const RealsenseSettings &settings);	    //start camera
    void start_bag(QString fileName);       //play BAG file

    void update();
    void close();

    bool connected() { return device_.connected; }
    const RealsenseSettings &settings() { return settings_; }

    bool isFrameNew() { return frameNew_;  }

    //RGB
    bool get_color_pixels_rgb(XRaster_u8c3 &raster);

    //Depth
    bool get_depth_pixels8(float min_dist, float max_dist, XRaster_u8 &raster);
    bool get_depth_pixels_rgb(XRaster_u8c3 &raster);
    bool get_depth_pixels_mm(XRaster_float &raster);
    bool get_depth_pixels_mm(XRaster_u16 &raster);

    //IR
    bool get_ir_pixels8(XRaster_u8 &raster);
    bool get_ir_pixels_rgb(XRaster_u8c3 &raster);

    //TODO
    //callback for connecting/disconnecting devices, see rs-multicam example in SDK
    //auto reconnect if device was connected again

    //TODO optimization
    //not compute texture coordinates if not required
    bool get_point_cloud(QVector<vec3> &pc,
                         int &gridw, int &gridh,
                         int mirrorx = 0, int mirrory = 0, int mirrorz = 0);	//get point cloud for connected device


    //project 3d to screen
    vec2 project_3d_to_screen(const vec3 &p);

protected:
    RealsenseSettings settings_;

    bool frameNew_ = false;

    //QMutex Realsense_mutex_;
    rs2::context Realsense_ctx;

    RealsenseDevice device_;

    bool frame_to_pixels_rgb(const rs2::video_frame& frame, XRaster_u8c3 &raster);

    bool get_depth16_raw(int &w, int &h, uint16_t* &data16);

    void setup(rs2::device &dev, const RealsenseSettings &settings);

    //intrinsics for converting 3d to image
    bool intrinsics_inited_ = false;
    rs2_intrinsics intrinsics_;


};


#endif // XCLASSREALSENSECAMERAIMPL_H
