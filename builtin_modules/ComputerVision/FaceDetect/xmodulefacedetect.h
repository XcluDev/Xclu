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
#include "cv.h"

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

    // The default value is 1.2. For accuracy, bring it closer but not equal to 1.0. To make it faster, use a larger value.
    void haar_set_scale(float scaleHaar);
    // How many neighbors can be grouped into a face? Default value is 2. If set to 0, no grouping will be done.
    void haar_set_neighbors(int neighbors);

    CvHaarClassifierCascade* haar_cascade_ = nullptr;
    float haar_scale_ = 1.2;
    int haar_neighbors = 2;
};



#endif // XMODULEFACEDETECT_H
