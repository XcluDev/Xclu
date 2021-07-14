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
    :XModulePainter(class_name)
{

}

//---------------------------------------------------------------------
XModuleSoundSamplesML::~XModuleSoundSamplesML()
{

}

//---------------------------------------------------------------------
void XModuleSoundSamplesML::start() {
    clear_string_join_console();
}

//---------------------------------------------------------------------
void XModuleSoundSamplesML::update() {
    //buttons
    if (geti_join_convert()) {
        join_wavs(gets_join_input_folder(), gets_join_output_folder());
    }

}

//---------------------------------------------------------------------
void XModuleSoundSamplesML::stop() {
    /*  subprocess_.reset();*/
}

//---------------------------------------------------------------------
void XModuleSoundSamplesML::draw(QPainter &painter, int outw, int outh) {

    //Antialiasing
    painter.setRenderHint(QPainter::Antialiasing);

    //Draw background
    painter.setBrush(QColor(0, 0, 0));
    painter.setPen(Qt::PenStyle::NoPen);
    painter.drawRect(0, 0, outw, outh);

  /*  //Compute translate and scale
    //Note: we use scaling to have independence of lines width from screen resolution
    int spacing = geti_spacing();

    float w = 300;  //base size
    float h = 300;
    float wsp = w + spacing;

    float scrw = 3*w + 2*spacing;
    float scrh = h;

    float scl = qMin(outw/scrw, outh/scrh);
    float outw1 = scrw*scl;
    float outh1 = scrh*scl;

    int x0 = (outw-outw1)/2;
    int y0 = (outh-outh1)/2;

    painter.save();
    painter.translate(x0, y0);
    painter.scale(scl, scl);

    //------------------------
    //Actual drawing

    //Face
    face_draw(painter, w, h);

    //Vector field - attractors
    painter.save();
    painter.translate(wsp, 0);
    //painter.setPen(QColor(255,255,255));
    //painter.setBrush(Qt::BrushStyle::NoBrush);
    //painter.drawRect(0,0,w,h);
    attr_draw(painter, w, h);

    painter.restore();

    //Morph
    painter.save();
    painter.translate(2*wsp, 0);
    morph_draw(painter, w, h);
    painter.restore();

    //border
    painter.setPen(get_col(getf_border_color()));
    painter.setBrush(Qt::BrushStyle::NoBrush);
    painter.drawRect(0,0,scrw,scrh);
    painter.drawLine(w,0,w,h);
    painter.drawLine(scrw-w,0,scrw-w,h);


    //------------------------
    painter.restore();*/
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
        append_string_join_console(QString("Processing %1")
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
    QString database_file_bin = gets_join_output_folder() + "/database.bin";
    QString database_file_ini = gets_join_output_folder() + "/database.ini";
    append_string_join_console(QString("Save to: %1, %2").arg(database_file_bin, database_file_ini));
    repaint_join_console();


    database.save(database_file_bin, database_file_ini);
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
