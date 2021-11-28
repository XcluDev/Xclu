#ifndef XCVHELPER_H
#define XCVHELPER_H

// Helper for working with OpenCV
#include "sdk_h.h"
#include "xobject.h"

#include <cv.h>

class QImage;
class QPainter;

class XCvHelper {
public:
    // Usage:
    // auto read = getobject_input_image()->read();
    // cv::Mat img = XCvHelper::link_to_cv(read.data());
    // Be careful: link is valid until object will be changed
    // So use it inside protected envirunment (as always, Read/Write objects in a scope)
    static cv::Mat link_to_cv(const XObject& object);

};


#endif // XCVHELPER_H
