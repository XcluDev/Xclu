#include "soundsamplesanalyze.h"
#include "incl_cpp.h"
#include "project_props.h"
#include "xc_audio.h"
#include "xc_tsne.h"

//---------------------------------------------------------------------
void SoundSamplesAnalyze::clear() {
    pos_.clear();
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
    auto env = xc_audio::make_envelope(sound, -1, env_size);
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
//save to file
void SoundSamplesAnalyze::save_to_file(QString file_name) {
    QStringList file;
    for (auto &p: pos_) {
        file.push_back(QString("%1 %2").arg(p.x).arg(p.y));
    }
    xc_write_text_file(file, file_name);
}

//---------------------------------------------------------------------
//load from file
void SoundSamplesAnalyze::load_from_file(QString file_name, int database_size) {
    file_name = xc_absolute_path_from_project(file_name);
    if (!xc_file_exists(file_name)) {
        xc_message_box("File '" + file_name + "' doesn't exists");
    }
    auto file = xc_read_text_file(file_name);

    int n = database_size;
    xc_assert(n == file.size(),
              QString("SoundSamplesAnalyze::load_from_file - number of samples %1 and file records %2 are different")
              .arg(n).arg(file.size()));
    pos_.resize(n);
    for (int i=0; i<n; i++) {
        auto list = file[i].split(" ");
        xc_assert(list.size() == 2, QString("SoundSamplesAnalyze::load_from_file - bad line %1").arg(i+1));
        pos_[i] = glm::vec2(list[0].toFloat(), list[1].toFloat());
    }
}

//---------------------------------------------------------------------
//set envelope size for analysis
void SoundSamplesAnalyze::set_envelope_size(int size) {
    env_size = size;
}

//---------------------------------------------------------------------
QVector<QVector<float>> SoundSamplesAnalyze::make_float_envelopes(SoundSamplesDatabase &db) {
    int n = db.size();
    auto &sounds = db.sounds();
    QVector<QVector<float>> envelopes(n);
    for (int k=0; k<n; k++) {
        envelopes[k] = xc_audio::make_float_envelope(sounds[k], -1, env_size);
    }
    return envelopes;
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
//using t-sne
void SoundSamplesAnalyze::method_tsne(SoundSamplesDatabase &db) {
    int n = db.size();
    pos_.resize(n);

    //compute envelopes
    auto envs = make_float_envelopes(db);

    //t-SNE
    xc_ml::xTSNE tsne;
    xc_ml::xTSNE::Params params;
    params.runManually = true; //will call iterations manually
    params.iterations = 1000;   //PARAM

    xc_console_append("t-Sne starting...");
    xc_console_repaint();
    tsne.run_2d(envs, params);

    for (int i=0; i<params.iterations; i++) {
        xc_console_append(QString("  iteration %1 / %2").arg(i).arg(params.iterations));
        xc_console_repaint();
        tsne.iterate();
    }
    pos_ = tsne.result_2d();
}

//---------------------------------------------------------------------
