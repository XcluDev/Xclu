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
    //method of placing sounds in a square just as they are in the database
    void method_natural_order(SoundSamplesDatabase &db);

    //draw
    void draw(QPainter &painter, int w, int h, int selected_index, int thumb_rad);

    //find id, -1 means no sound found, coordinates uniform (0..1)
    int find_by_mouse(glm::vec2 pos);
protected:
    QVector<glm::vec2> pos_;

};


#endif // SOUNDSAMPLESANALYZE_H
