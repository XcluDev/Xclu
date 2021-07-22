#include "qt_widgets.h"
#include "xmodulessoundsdatabaseanalyze.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QProcess>
#include <QDirIterator>
#include "xcore.h"
#include "xc_audio_wavfile.h"
#include "xc_audio.h"
#include "soundsamplesdatabase.h"

//registering module implementation
REGISTER_XMODULE(SoundsDatabaseAnalyze)

//---------------------------------------------------------------------
XModuleSoundsDatabaseAnalyze::XModuleSoundsDatabaseAnalyze(QString class_name)
    :XModuleVisual(class_name)
{

}

//---------------------------------------------------------------------
XModuleSoundsDatabaseAnalyze::~XModuleSoundsDatabaseAnalyze()
{

}

//---------------------------------------------------------------------
void XModuleSoundsDatabaseAnalyze::start() {
    //Analyze
    analyze_.clear();


    //Create database
    clear_string_join_console();

    //Load database
    seti_db_sounds(0);
    seti_db_length(0);
    seti_db_sample_rate(0);
    seti_db_channels(0);



    //autoload
    if (geti_db_autoload()) {
        load_database();
    }

    //play sound
    player_.write().data().clear();

}

//---------------------------------------------------------------------
void XModuleSoundsDatabaseAnalyze::update() {
    //buttons
    if (geti_join_convert()) {
        join_wavs(gets_join_input_folder(), gets_join_output_folder());
    }
    if (geti_db_load()) {
        load_database();
    }

    //changes

    //envelope size must be set first before further analysis
    if (was_changed_an_envelope_size()) {
        analyze_.set_envelope_size(geti_an_envelope_size());
    }
    if (was_changed_an_method()) {
        analyze_reload();
    }
    if (was_changed_vis_thumb_rad()) {
        refresh();
    }
}

//---------------------------------------------------------------------
void XModuleSoundsDatabaseAnalyze::stop() {

}

//---------------------------------------------------------------------
void XModuleSoundsDatabaseAnalyze::join_wavs(QString input_folder, QString output_folder) {
    xc_assert(!input_folder.isEmpty(), "Input folder is empty");
    xc_assert(!output_folder.isEmpty(), "Output folder is empty");

    xc_assert(QDir(input_folder).exists(), "Folder '" + input_folder + "' doesn't exists");

    //Create output folder
    xc_assert(QDir().mkpath(output_folder), "Can't create folder '" + output_folder + "'");

    //scan folder for wavs
    QDirIterator input_iter(input_folder,//xc_abs_path(folder_name),
                            QStringList() << "*.wav"// << "*.aiff"
                            ); //, QDirIterator::Subdirectories);

    xc_assert(input_iter.hasNext(), "No wav or aiff files in folder '" + input_folder +"'");

    //Create database
    SoundSamplesDatabase database;

    int channels = 1;
    database.set_params(geti_join_sample_rate(), channels);


    int n = 0;
    while (input_iter.hasNext()) {
        append_string_join_console(QString("Processing WAV: %1")
                                   .arg(n+1));

        QString path = input_iter.next();
        join_wav(path, database);

        //refresh console - not each sample for speedup
        if (n % 10 == 0) {
            repaint_join_console();
        }
        n++;
    }
    append_string_join_console(QString("Processed input audio files: %1").arg(n));
    append_string_join_console(QString("Collected fragments: %1").arg(database.size()));


    //if (database.is_equal_length()) append_string_join_console("All samples have equal length");
    //else append_string_join_console("Samples have different length");

    //truncate
    int len = database.truncate_to_equal_length();
    append_string_join_console(QString("Samples truncated to length %1").arg(len));

    //save database
    QString folder = gets_join_output_folder();
    append_string_join_console(QString("Save to: %1").arg(folder));
    repaint_join_console();


    database.save(folder);
    append_string_join_console("Finished!");
    repaint_join_console();
}

//---------------------------------------------------------------------
//returns number of used parts
int XModuleSoundsDatabaseAnalyze::join_wav(QString wav_file, SoundSamplesDatabase &database) {
    xc_audio::WavFile wav;

    //The code of loading WAV is based on the "Spectrum" Qt example
    xc_assert(wav.open(wav_file), "Could not open WAV file '" + wav_file + "'");
    auto &format = wav.fileFormat();

    //We support only 16 bit signed, Little Endian
    xc_assert(xc_audio::is_PCMS16LE(format),
              "Audio format '" + xc_audio::format_to_string(format) + "' not supported, expected signed int16, Little Endian");

    //Actually we don't need 44100, but just fixed sample rate
    int sample_rate = format.sampleRate();
    xc_assert(sample_rate == geti_join_sample_rate(),
              QString("Bad sample rate in '" + wav_file + "': %1, but expected %2 Hz")
              .arg(sample_rate).arg(geti_join_sample_rate()));

    int channels = format.channelCount();
    xc_assert(channels <= 2, "Only 1 and 2 channels are supported, but '" + wav_file + "' is multi-channel");

    QByteArray bytes = wav.readAll();
    int size = bytes.size() / (2*channels);
    xc_assert(bytes.size() > 0, "Empty WAV file '" + wav_file + "'");

    const int16* data = (int16 *)bytes.constData();


    //scan parts
    int discard_empty = geti_join_discard_empty();

    //usage statistics
    int used_parts = 0;
    int skipped_parts = 0;

    int n = geti_join_wav_parts();
    for (int k=0; k<n; k++) {
        int i0 = k * size / n;
        int i1 = (k+1) * size / n;
        int n_samples = i1 - i0;      //Use that it's S16LE format
        if (n_samples == 0) {
            skipped_parts++;  //Note: silent scipping of very short wavs
            continue;
        }
        //collect sample and check if it's not empty
        QVector<int16> sample(n_samples);
        bool is_empty = true;
        for (int i=0; i<n_samples; i++) {
            int16 &smp = sample[i];
            if (channels == 1) {
                smp = data[i + i0];
            }
            if (channels == 2) {
                //join channels
                int ind = 2*(i + i0);
                smp = (int(data[ind]) + int(int(data[ind+1])))/2;
            }
            if (smp != 0) {
                is_empty = false;
            }
        }
        if (is_empty && discard_empty) {
            skipped_parts++;
            continue;
        }
        //Add collected sample to database
        used_parts++;
        database.add(sample);
    }

    //info about skipping
    append_string_join_console(QString("  used parts: %1")
                               .arg(used_parts));
    //repaint_join_console();   //will call not each frame

    return used_parts;
}

//---------------------------------------------------------------------
void XModuleSoundsDatabaseAnalyze::load_database() {
    db_.load(gets_db_folder());

    seti_db_sounds(db_.size());
    seti_db_length(db_.length());
    seti_db_sample_rate(db_.sample_rate());
    seti_db_channels(db_.channels());

    analyze_reload();
}

//---------------------------------------------------------------------
void XModuleSoundsDatabaseAnalyze::analyze_reload() {
    selected_ = -1;

    switch (gete_an_method()) {
    case an_method_File_Order:
        analyze_.method_natural_order(db_);
        break;
    case an_method_tSNE:
        analyze_.method_tsne(db_);
        break;
    default:
        xc_exception(QString("XModuleSoundsDatabaseAnalyze::analyze_reload - unknown method %1").arg(gete_an_method()));
    }

    refresh();
}

//---------------------------------------------------------------------
void XModuleSoundsDatabaseAnalyze::draw(QPainter &painter, int outw, int outh) {

    //Antialiasing
    painter.setRenderHint(QPainter::Antialiasing);

    //Draw background
    painter.setBrush(QColor(0, 0, 0));
    painter.setPen(Qt::PenStyle::NoPen);
    painter.drawRect(0, 0, outw, outh);

    analyze_.draw(painter, outw, outh, selected_, geti_vis_thumb_rad());
    analyze_.draw_sound(painter, outw, outh, player_.write().data().sound);

    //store size to use in mouse_pressed
    w_ = qMax(outw, 1);
    h_ = qMax(outh, 1);
}

//---------------------------------------------------------------------
//click mouse to play the sound
void XModuleSoundsDatabaseAnalyze::mouse_pressed(int2 pos, XMouseButton /*button*/) {
    //xc_console_append(QString("mouse %1 %2").arg(pos.x).arg(pos.y));
    int id = analyze_.find_by_mouse(glm::vec2(float(pos.x)/w_, float(pos.y)/h_));
    if (id >= 0) {
        //Play
        selected_ = id;
        refresh();  //repaint
        //start to play
        player_.write().data().play(db_.sounds()[id], getf_play_volume());
    }
}

//---------------------------------------------------------------------
//sound generation
//"sound_buffer_add" call, fills `data` buffer
//there are required to fill channels * samples values at data
void XModuleSoundsDatabaseAnalyze::on_sound_buffer_add(int /*sample_rate*/, int channels, int samples, float *data) {
    auto writer = player_.write(); //create locking object - will be unlocked when reader will be destroyed
    auto &player = writer.data();
    float vol = player.volume / 32768.0; //16bit->float
    int k = 0;
    for (int i=0; i<samples; i++) {
        if (player.pos < player.sound.size()) {
            float v = player.sound[player.pos++] * vol;
            for (int u=0; u<channels; u++) {
                data[k++] += v;
            }
        }
    }
}

//---------------------------------------------------------------------
