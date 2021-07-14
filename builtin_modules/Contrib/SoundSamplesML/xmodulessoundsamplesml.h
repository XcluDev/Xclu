#ifndef XMODULESOUNDSAMPLESML_H
#define XMODULESOUNDSAMPLESML_H

/*
ML exploration of sound samples - used as a part of project Endless Instruments.
*/


#include "sdk_h.h"
#include "xmodulepainter.h"
#include "soundsamplesdatabase.h"

class XModuleSoundSamplesML: public XModulePainter
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

protected slots:


protected:
    void join_wavs(QString input_folder, QString output_folder);
    int join_wav(QString wav_file, SoundSamplesDatabase &database);
};



#endif // XMODULESOUNDSAMPLESML_H
