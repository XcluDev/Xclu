#ifndef XModuleSoundSeaOfWords_H
#define XModuleSoundSeaOfWords_H

/*
By given set of sound samples, module arranges them at 2D and plays by mouse click.
*/

#include "sdk_h.h"
#include "xmodulewidget.h"

class XModuleSoundSeaOfWords: public XModuleWidget
{
public:
    XModuleSoundSeaOfWords(QString class_name);
    ~XModuleSoundSeaOfWords();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    virtual void draw(QPainter &painter, int w, int h);

    //click mouse to play the sound
    virtual void mouse_pressed(int2 pos, XMouseButton button);

    //sound generation
    //"sound_buffer_add" call, fills `data` buffer
    //there are required to fill channels * samples values at data
    virtual void on_sound_buffer_add(int sample_rate, int channels, int samples, float *data);

protected slots:


protected:

    int w_ = 1;
    int h_ = 1;


    //Sound to play, needs to be protected data because audio works in another thread
    struct PlayerData {
        QVector<int16> sound;
        int pos = 0;
        float volume = 0;
        void clear() {
            sound.clear();
            pos = 0;
            volume = 0;
        }
        void play(QVector<int16> sound0, float volume0) {
            sound = sound0;
            pos = 0;
            volume = volume0;
        }
        void stop() {
            clear();
        }
    };
    XProtectedData_<PlayerData> player_;

};



#endif // XModuleSoundSeaOfWords_H
