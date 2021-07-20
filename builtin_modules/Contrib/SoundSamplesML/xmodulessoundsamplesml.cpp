#include "qt_widgets.h"
#include "xmodulessoundsamplesml.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QProcess>
#include <QDirIterator>
#include "xcore.h"
#include "xaudio_wavfile.h"
#include "xaudio_utils.h"
#include "soundsamplesdatabase.h"

//registering module implementation
REGISTER_XMODULE(SoundSamplesML)

//---------------------------------------------------------------------
XModuleSoundSamplesML::XModuleSoundSamplesML(QString class_name)
    :XModuleVisual(class_name)
{

}

//---------------------------------------------------------------------
XModuleSoundSamplesML::~XModuleSoundSamplesML()
{

}

//---------------------------------------------------------------------
void XModuleSoundSamplesML::start() {
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

}

//---------------------------------------------------------------------
void XModuleSoundSamplesML::update() {
    //buttons
    if (geti_join_convert()) {
        join_wavs(gets_join_input_folder(), gets_join_output_folder());
    }
    if (geti_db_load()) {
        load_database();
    }

    //changes
    if (was_changed_draw_method()) {
        analyze_reload();
    }
    if (was_changed_thumb_rad()) {
        refresh();
    }
}

//---------------------------------------------------------------------
void XModuleSoundSamplesML::stop() {

}

//---------------------------------------------------------------------
void XModuleSoundSamplesML::join_wavs(QString input_folder, QString output_folder) {
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
int XModuleSoundSamplesML::join_wav(QString wav_file, SoundSamplesDatabase &database) {
    xc_audio::WavFile wav;

    //The code of loading WAV is based on the "Spectrum" Qt example
    xc_assert(wav.open(wav_file), "Could not open WAV file '" + wav_file + "'");
    auto &format = wav.fileFormat();

    //We support only 16 bit signed, Little Endian
    xc_assert(xc_audio::isPCMS16LE(format),
              "Audio format '" + xc_audio::formatToString(format) + "' not supported, expected signed int16, Little Endian");

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
            skipped_parts++;  //Note: silent scikkping of very short wavs
            continue;
        }
        //collect sample and check if it's not empty
        QVector<int16> sample(n_samples);
        int smp = 0;
        bool is_empty = true;
        for (int i=0; i<n_samples; i++) {
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
void XModuleSoundSamplesML::load_database() {
    db_.load(gets_db_folder());

    seti_db_sounds(db_.size());
    seti_db_length(db_.length());
    seti_db_sample_rate(db_.sample_rate());
    seti_db_channels(db_.channels());

    analyze_reload();
}

//---------------------------------------------------------------------
void XModuleSoundSamplesML::analyze_reload() {
    selected_ = -1;

    switch (gete_draw_method()) {
    case draw_method_File_Order:
        analyze_.method_natural_order(db_);
        break;
    case draw_method_Simple:
        break;
    case draw_method_tSNE:
        break;
    default:
        xc_exception(QString("XModuleSoundSamplesML::analyze_reload - unknown method %1").arg(gete_draw_method()));
    }

    refresh();
}

//---------------------------------------------------------------------
void XModuleSoundSamplesML::draw(QPainter &painter, int outw, int outh) {

    //Antialiasing
    painter.setRenderHint(QPainter::Antialiasing);

    //Draw background
    painter.setBrush(QColor(0, 0, 0));
    painter.setPen(Qt::PenStyle::NoPen);
    painter.drawRect(0, 0, outw, outh);

    analyze_.draw(painter, outw, outh, selected_, geti_thumb_rad());

    //store size to use in mouse_pressed
    w_ = qMax(outw, 1);
    h_ = qMax(outh, 1);
}

//---------------------------------------------------------------------
//click mouse to play the sound
void XModuleSoundSamplesML::mouse_pressed(int2 pos, XMouseButton /*button*/) {
    //xc_console_append(QString("mouse %1 %2").arg(pos.x).arg(pos.y));
    int id = analyze_.find_by_mouse(glm::vec2(float(pos.x)/w_, float(pos.y)/h_));
    if (id >= 0) {
        //Play
        selected_ = id;
        refresh();  //repaint
    }
}

//---------------------------------------------------------------------
