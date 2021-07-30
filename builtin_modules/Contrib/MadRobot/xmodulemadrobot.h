#ifndef XMODULEMADROBOT_H
#define XMODULEMADROBOT_H

//EmoAI
#include "sdk_h.h"
#include "xraster.h"
#include "xmodulevisual.h"


class XModuleMadRobot: public XModuleVisual
{
    Q_OBJECT
public:
    XModuleMadRobot(QString class_name);
    ~XModuleMadRobot();

protected:
#include "auto.h"
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    virtual void draw(QPainter &painter, int w, int h);

    //web cam image
    XRaster_u8c3 webcam_;   //input image
    XRaster_u8c3 image_;   //transformed image for Python
    XProtectedObject image_gui_;

    //Data from Python
    void parse_python();

    enum ReceivedState: int {
        ReceivedStateStarted = 0,
        ReceivedStateWaiting = 1,
        ReceivedStateParsed = 2
    };
    ReceivedState received_state_ = ReceivedStateStarted;   // used for output info to console

};

#endif // XMODULEMADROBOT_H
