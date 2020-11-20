#ifndef XMODULESOUNDPLAY_H
#define XMODULESOUNDPLAY_H

//SoundPlay implementation

#include "sdk_h.h"
#include "xmodule.h"
#include <QMediaPlayer>
#include <QScopedPointer>

class XModuleSoundPlay: public XModule
{
public:
    XModuleSoundPlay(QString class_name);
    ~XModuleSoundPlay();
#include "auto.h"

protected:
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();
    //virtual void impl_button_pressed(QString button_id);


    //https://doc.qt.io/qt-5/audiooverview.html
    //https://doc.qt.io/qt-5/qmediaplayer.html#details

    QScopedPointer<QMediaPlayer> player_;
    void play_sound();

    //immediate stop
    void stop_sound();

    //stop with fading
    void stop_fade();

    void update_loop();
    void update_fade();

    bool playing_ = false;

    bool stop_fading_ = false;
    float time_ = 0;   //time for fade out


    int media_volume(float v);   //0..100

};



#endif // XMODULESOUNDPLAY_H
