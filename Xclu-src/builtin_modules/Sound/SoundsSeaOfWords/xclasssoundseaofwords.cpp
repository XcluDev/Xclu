#include "qt_widgets.h"
#include "xclasssoundseaofwords.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include <QProcess>
#include <QDirIterator>
#include "project_props.h"
#include "xc_audio_wavfile.h"
#include "xc_audio.h"

//registering module implementation
REGISTER_XCLASS(SoundSeaOfWords)

//---------------------------------------------------------------------
XClassSoundSeaOfWords::XClassSoundSeaOfWords(QString class_name)
    :XClassWidget(class_name)
{

}

//---------------------------------------------------------------------
XClassSoundSeaOfWords::~XClassSoundSeaOfWords()
{

}

//---------------------------------------------------------------------
void XClassSoundSeaOfWords::start() {

    //play sound
    //player_.write().data().clear();

}

//---------------------------------------------------------------------
void XClassSoundSeaOfWords::update() {
    //buttons

    //changes

    //envelope size must be set first before further analysis
    //if (was_changed_vis_thumb_rad()) {
    //    redraw();
    //}
}

//---------------------------------------------------------------------
void XClassSoundSeaOfWords::stop() {

}


//---------------------------------------------------------------------
void XClassSoundSeaOfWords::draw(QPainter &painter, int outw, int outh) {

    //Antialiasing
    painter.setRenderHint(QPainter::Antialiasing);

    //Draw background
    painter.setBrush(QColor(0, 0, 0));
    painter.setPen(Qt::PenStyle::NoPen);
    painter.drawRect(0, 0, outw, outh);

    //store size to use in mouse_pressed
    w_ = qMax(outw, 1);
    h_ = qMax(outh, 1);
}

//---------------------------------------------------------------------
//click mouse to play the sound
void XClassSoundSeaOfWords::mouse_pressed(int2 pos, XMouseButton /*button*/) {
    //xc_console_append(QString("mouse %1 %2").arg(pos.x).arg(pos.y));
    //int id = analyze_.find_by_mouse(vec2(float(pos.x)/w_, float(pos.y)/h_));
    //if (id >= 0) {
    //    //Play
    //    selected_ = id;
    //    redraw();  //redraw
    //    //start to play
    //    player_.write().data().play(db_.sounds()[id], getf_play_volume());
    //}
}

//---------------------------------------------------------------------
//sound generation
//"sound_buffer_add" call, fills `data` buffer
//there are required to fill channels * samples values at data
void XClassSoundSeaOfWords::on_sound_buffer_add(int /*sample_rate*/, int channels, int samples, float *data) {
    auto writer = player_.write(); //create locking object - will be unlocked when reader will be destroyed
    auto &player = writer.data();
    /*float vol = player.volume / 32768.0; //16bit->float
    int k = 0;
    for (int i=0; i<samples; i++) {
        if (player.pos < player.sound.size()) {
            float v = player.sound[player.pos++] * vol;
            for (int u=0; u<channels; u++) {
                data[k++] += v;
            }
        }
    }*/
}

//---------------------------------------------------------------------
