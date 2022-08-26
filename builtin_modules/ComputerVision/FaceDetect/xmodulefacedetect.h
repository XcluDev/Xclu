#ifndef XMODULEFACEDETECT_H
#define XMODULEFACEDETECT_H

// FaceDetect - search faces on the image.
// Based on openFramework/addons/ofxOpenCV/ofxCvHaarFinder class.

#include <QImage>
#include "sdk_h.h"
#include "xclass.h"
#include "xobjectimage.h"
#include "xprotecteddata.h"
#include "sdk_h.h"

#include <cv.h>
#include "opencv2/objdetect.hpp"

class XModuleFaceDetect: public XClass
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
        FaceBlob(const QRect &face, int w, int h) {
            rect = QRectF(float(face.x())/w, float(face.y())/h,
                          float(face.width())/w, float(face.height())/h);
            recti = face;
        }
        QRectF rect = QRectF(0,0,0,0);
        QRect recti = QRect(0,0,0,0);
        float area() const { return rect.width() * rect.height(); }
        vec2 center() const { return vec2(rect.x() + rect.width()/2, rect.y() + rect.height()/2); }
    };
    QVector<FaceBlob> blobs_;

    void update_biggest();

    // Apply threshold and create only one blob; all blobs_ are copyed to raw_blobs_ for debug drawing.
    void apply_thresholding(int w, int h);
    QVector<FaceBlob> raw_blobs_;       // Used when thresholding on
    QVector<int> accum_image_;          // Accumulator image


    void clear_results();
    bool input_image_was_changed();
    XWasChangedChecker image_changed_checker_;

    float last_time_ = 0;       // Time of last processing
};



#endif // XMODULEFACEDETECT_H
