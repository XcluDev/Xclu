#ifndef SOUNDSAMPLESANALYZE_H
#define SOUNDSAMPLESANALYZE_H

/*
Analyze sounds by placing them on 2D screen,
and also mouse interaction (used for playng sound).
*/

#include "sdk_h.h"
#include "soundsamplesdatabase.h"
#include <QPainter>

class SoundSamplesAnalyze
{
public:
    void clear();
    //set envelope size for analysis
    void set_envelope_size(int size);

    //method of placing sounds in a square just as they are in the database
    void method_natural_order(SoundSamplesDatabase &db);

    //draw
    void draw(QPainter &painter, int w, int h, int selected_index, int thumb_rad);
    void draw_sound(QPainter &painter, int w, int h, const QVector<int16> &sound);

    //find id, -1 means no sound found, coordinates uniform (0..1)
    int find_by_mouse(glm::vec2 pos);
protected:
    //positions of samples obtained during analysis, 0..1
    QVector<glm::vec2> pos_;

    QVector<int16> make_envelope(const QVector<int16> &sound);

    int env_size = 512; //envelope size used for analysis
};


#endif // SOUNDSAMPLESANALYZE_H
