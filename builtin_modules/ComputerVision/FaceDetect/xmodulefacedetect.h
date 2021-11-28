#ifndef XMODULEFACEDETECT_H
#define XMODULEFACEDETECT_H

// FaceDetect - search faces on the image.
// Based on openFramework/addons/ofxOpenCV/ofxCvHaarFinder class.

#include <QImage>
#include "sdk_h.h"
#include "xmodule.h"
#include "xobjectimage.h"
#include "xprotecteddata.h"
#include "sdk_h.h"

#include <cv.h>
#include "opencv2/objdetect.hpp"

class XModuleFaceDetect: public XModule
{
public:
    XModuleFaceDetect(QString class_name);
    ~XModuleFaceDetect();
protected:
#include "auto.h"
    virtual void on_loaded();
    virtual void start();
    virtual void update();
    virtual void stop();
    virtual void on_button_pressed(QString button_id);

    virtual void draw(QPainter &painter, int w, int h);

protected:
    void haar_load(QString file_name);
    void haar_unload();

    void haar_search();

    //https://docs.opencv.org/3.4/db/d28/tutorial_cascade_classifier.html
    cv::CascadeClassifier face_cascade_;


    struct FaceBlob {
        FaceBlob() {}
        FaceBlob(const QRectF &rect0) {
            rect = rect0;
        }
        QRectF rect = QRectF(0,0,0,0);
        float area() const { return rect.width() * rect.height(); }
        glm::vec2 center() const { return glm::vec2(rect.x() + rect.width()/2, rect.y() + rect.height()/2); }
    };
    QVector<FaceBlob> blobs_;

    void update_biggest();
};



#endif // XMODULEFACEDETECT_H
