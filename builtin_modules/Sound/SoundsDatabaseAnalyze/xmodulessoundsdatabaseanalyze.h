#ifndef XModuleSoundsDatabaseAnalyze_H
#define XModuleSoundsDatabaseAnalyze_H

/*
By given set of sound samples module arranges them at 2D and plays by mouse click.
*/

#include "sdk_h.h"
#include "xmodulevisual.h"
#include "soundsamplesdatabase.h"
#include "soundsamplesanalyze.h"

class XModuleSoundsDatabaseAnalyze: public XModuleVisual
{
public:
    XModuleSoundsDatabaseAnalyze(QString class_name);
    ~XModuleSoundsDatabaseAnalyze();
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



#endif // XModuleSoundsDatabaseAnalyze_H
