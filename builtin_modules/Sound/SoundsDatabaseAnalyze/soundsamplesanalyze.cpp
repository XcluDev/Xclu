#include "soundsamplesanalyze.h"
#include "incl_cpp.h"
#include "xcore.h"
#include "xc_audio.h"

//---------------------------------------------------------------------
void SoundSamplesAnalyze::clear() {
    pos_.clear();
}

//---------------------------------------------------------------------
//set envelope size for analysis
void SoundSamplesAnalyze::set_envelope_size(int size) {
    env_size = size;
}

//---------------------------------------------------------------------
QVector<int16> SoundSamplesAnalyze::make_envelope(const QVector<int16> &sound) {
    return xc_audio::make_envelope(sound, -1, env_size);
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
void SoundSamplesAnalyze::draw_sound(QPainter &painter, int w, int h, const QVector<int16> &sound) {
    if (w <= 0 || h <= 0 || sound.isEmpty()) return;

    //Parameters
    int y0 = h/2;
    int height = h / 2;
    QColor pen(0,255,0);
    QColor brush(0,255,0,128);

    painter.setPen(pen);
    painter.setBrush(brush);

    //Draw envelope
    auto env = make_envelope(sound);
    int n = env.size();
    if (n == 0) return;
    for (int x=0; x < n; x++) {
        int x0 = x*w/n;
        int x1 = (x+1)*w/n;
        int v = qAbs(env[x]) * height/32768;
        painter.drawRect(x0, y0, x1-x0, -v);
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
