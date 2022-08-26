#ifndef XCLASSSOUNDPLAY_H
#define XCLASSSOUNDPLAY_H

//SoundPlay implementation

#include "sdk_h.h"
#include "xclass.h"
#include <QMediaPlayer>
#include <QScopedPointer>

class XModuleSoundPlay: public XClass
{
public:
    XModuleSoundPlay(QString class_name);
    virtual ~XModuleSoundPlay();
#include "auto.h"

protected:
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();
    //virtual void on_button_pressed(QString button_id);


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



#endif // XCLASSSOUNDPLAY_H
