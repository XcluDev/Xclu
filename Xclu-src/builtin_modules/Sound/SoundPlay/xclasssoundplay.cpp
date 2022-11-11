#include "xclasssoundplay.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"
#include <QSound>


//registering module implementation
REGISTER_XCLASS(SoundPlay)

//---------------------------------------------------------------------
XClassSoundPlay::XClassSoundPlay(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassSoundPlay::~XClassSoundPlay()
{

}

//---------------------------------------------------------------------
void XClassSoundPlay::start() {
    stop_fading_ = false;

}

//---------------------------------------------------------------------
void XClassSoundPlay::update() {
    if (geti_play_button()) {
        play_sound();
    }
    if (geti_stop_button()) {
        stop_fade();
    }

    //loop
    update_loop();

    //fading
    update_fade();
}

//---------------------------------------------------------------------
void XClassSoundPlay::stop() {
    player_.reset();
    stop_fading_ = false;

}

//---------------------------------------------------------------------
//void XClassTimerm::on_button_pressed(QString button_id) {
//}


//---------------------------------------------------------------------
int XClassSoundPlay::media_volume(float v) {
    return int(v * 100);
}


//---------------------------------------------------------------------
void XClassSoundPlay::play_sound() {
    QString file_name = gets_file_name();

    QFile file(file_name);
    xc_assert(xc_file_exists_relpath(file_name), "XClassSoundPlay - file not exists: '" + file_name +"'");
    //QSound::play(file_name);

    player_.reset(new QMediaPlayer);
    //connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player_->setMedia(QUrl::fromLocalFile(file_name));
    player_->setVolume(media_volume(getf_volume()));

    player_->play();

    playing_ = true;
    stop_fading_ = false;

}

//---------------------------------------------------------------------
void XClassSoundPlay::update_loop() {
    if (player_.data()) {
        if (playing_ && gete_loop_mode_file() == loop_mode_file_Loop) {
            if (player_->state() == QMediaPlayer::StoppedState) {
                play_sound();
            }
        }
    }
}

//---------------------------------------------------------------------
//stop with fading
void XClassSoundPlay::stop_fade() {
    if (!stop_fading_) {
        float fade = getf_fade_out_sec();
        if (fade <= 0) {
            stop_sound();
        }
        else {
            stop_fading_ = true;
            time_ = xc_elapsed_time_sec();
        }
    }
}

//---------------------------------------------------------------------
void XClassSoundPlay::update_fade() {
    if (player_.data()) {
        if (stop_fading_) {
            float time = xc_elapsed_time_sec();

            float vol = xmapf_clamped(time, time_, time_+getf_fade_out_sec(), 1, 0);
            //xc_console_append(QString("vol %1").arg(vol));
            player_->setVolume(media_volume(vol * getf_volume()));
            if (vol <= 0) {
                stop_sound();
            }
        }
    }
}

//---------------------------------------------------------------------
//immediate stop
void XClassSoundPlay::stop_sound() {
    if (player_.data()) {
        player_->stop();
    }
    playing_ = false;
    stop_fading_ = false;
}

//---------------------------------------------------------------------
