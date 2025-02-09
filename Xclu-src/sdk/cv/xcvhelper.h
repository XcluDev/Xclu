#pragma once

// Helper for working with OpenCV
#include "sdk_h.h"
#include "xraster.h"

#include <cv.h>

class XCvHelper {
public:
    // Usage:
    // auto read = getobject_input_image()->read();
    // cv::Mat img = XCvHelper::link_to_cv(read.data().raster);
    // Be careful: link is valid until object will be changed
    // So use it inside protected envirunment (as always, Read/Write objects in a scope)
    static cv::Mat link_to_cv(const XRaster& raster);

};

