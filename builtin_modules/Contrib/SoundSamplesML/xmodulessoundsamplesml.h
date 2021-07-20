#ifndef XMODULESOUNDSAMPLESML_H
#define XMODULESOUNDSAMPLESML_H

/*
ML exploration of sound samples - used as a part of project Endless Instruments.
*/

#include "sdk_h.h"
#include "xmodulevisual.h"
#include "soundsamplesdatabase.h"
#include "soundsamplesanalyze.h"

class XModuleSoundSamplesML: public XModuleVisual
{
public:
    XModuleSoundSamplesML(QString class_name);
    ~XModuleSoundSamplesML();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    virtual void draw(QPainter &painter, int w, int h);

    //click mouse to play the sound
    virtual void mouse_pressed(int2 pos, XMouseButton button);


protected slots:


protected:
    void join_wavs(QString input_folder, QString output_folder);
    int join_wav(QString wav_file, SoundSamplesDatabase &database);

    void load_database();
    SoundSamplesDatabase db_;

    SoundSamplesAnalyze analyze_;
    void analyze_reload();
    int w_ = 1;
    int h_ = 1;

    int selected_ = -1;
};



#endif // XMODULESOUNDSAMPLESML_H
