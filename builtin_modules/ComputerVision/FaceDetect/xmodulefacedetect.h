#ifndef XMODULEFACEDETECT_H
#define XMODULEFACEDETECT_H

//FaceDetect - search faces on the image.

#include <QImage>
#include "sdk_h.h"
#include "xmodule.h"
#include "xobjectimage.h"
#include "xprotecteddata.h"
#include "sdk_h.h"

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

protected:


};



#endif // XMODULEFACEDETECT_H
