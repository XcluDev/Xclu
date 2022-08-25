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
    xc_assert(raster.channels == 3, "XObjectImage::link_to_cv() - only images with 3 channels are supported");
    auto cv_format = CV_8UC3;   //TODO implement more formats

    const XArray *array = XObjectImage::get_array(object);

    auto data_type = array->data_type();
    xc_assert(data_type == XTypeId::u8,
              "XObjectImage::link_to_cv() - only u8 data type is supported");

    quint8 const *pixels = array->data_u8();

    int bytes_per_line = 1 * image_data.channels * image_data.w;

    return cv::Mat(image_data.h, image_data.w, cv_format, (void *)pixels, bytes_per_line);
}

//---------------------------------------------------------------------
