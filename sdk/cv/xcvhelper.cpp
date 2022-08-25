#include "xcvhelper.h"

#include "incl_cpp.h"
#include <QImage>
#include <QPainter>
#include <xobjectimage.h>


//---------------------------------------------------------------------
// Usage:
// auto read = getobject_input_image()->read();
// cv::Mat img = XCvHelper::link_to_cv(read.data());
// Be careful: link is valid until object will be changed
// So use it inside protected envirunment (as always, Read/Write objects in a scope)
cv::Mat XCvHelper::link_to_cv(const XRaster& raster) {
    if (raster.is_empty()) {
        return cv::Mat();
    }
    xc_assert(raster.type_id == XTypeId::rgb_u8, "XCvHelper::link_to_cv() - only rgb_u8 raster format is supported");
    auto cv_format = CV_8UC3;   //TODO implement more formats

    return cv::Mat(raster.h, raster.w, cv_format, (void *)raster.data_pointer(), raster.bytes_per_line());
}

//---------------------------------------------------------------------
