#include "soundsamplesanalyze.h"
#include "incl_cpp.h"
#include "xcore.h"

//---------------------------------------------------------------------
void SoundSamplesAnalyze::clear() {
    pos_.clear();
}

//---------------------------------------------------------------------
//method of placing sounds in a square just as they are in the database
void SoundSamplesAnalyze::method_natural_order(SoundSamplesDatabase &db) {
    int n = db.size();
    pos_.resize(n);

    //compute square size
    int m = int(sqrt(n));
    if (n > m*m) {
        m++;
    }
    if (m < 2) m = 2;
    //place
    for (int i=0; i<n; i++) {
        int x = i % m;
        int y = i / m;
        pos_[i] = glm::vec2(xmapf(x, 0, m-1, 0, 1), xmapf(y, 0, m-1, 0, 1));
    }
}

//---------------------------------------------------------------------
void SoundSamplesAnalyze::draw(QPainter &painter, int w, int h, int selected_index, int thumb_rad) {
    int rad = thumb_rad;
    int sz = rad*2;
    painter.setPen(QColor(255, 255, 255));
    painter.setBrush(QColor(128, 128, 128));
    for (auto &p: pos_) {
        painter.drawRect(rad + p.x * (w-sz) - rad, rad + p.y * (h-sz)-rad, sz, sz);
    }
    //redraw selected
    if (selected_index >= 0) {
        auto &p = pos_[selected_index];
        painter.setPen(QColor(255, 0, 0));
        painter.setBrush(QColor(128, 0, 0));
        painter.drawRect(rad + p.x * (w-sz) - rad, rad + p.y * (h-sz)-rad, sz, sz);
    }
}

//---------------------------------------------------------------------
//find id, -1 means no sound found, coordinates uniform (0..1)
int SoundSamplesAnalyze::find_by_mouse(glm::vec2 pos) {
    //search nearest sound
    int k = -1;
    float dist = 100000;
    for (int i=0; i<pos_.size(); i++) {
        float d = glm::distance2(pos, pos_[i]);
        if (d < dist) {
            dist = d;
            k = i;
        }
    }
    return k;
}

//---------------------------------------------------------------------
