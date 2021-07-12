#include "xmodulessoundsamplesml.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QProcess>
#include <QDirIterator>
#include "xcore.h"
#include "xaudio_wavfile.h"
#include "xaudio_utils.h"
#include <QApplication>
#include <QThread>


//registering module implementation
REGISTER_XMODULE(SoundSamplesML)

//---------------------------------------------------------------------
XModuleSoundSamplesML::XModuleSoundSamplesML(QString class_name)
    :XModule(class_name)
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

    int n = 0;
    while (input_iter.hasNext()) {
        QString path = input_iter.next();
        join_wav(path);
        n++;
    }
    append_string_join_console(QString("Processed input audio files: %1").arg(n));

}

//---------------------------------------------------------------------
void XModuleSoundSamplesML::join_wav(QString wav_file) {            
    xc_audio::WavFile wav;

    //The code of loading WAV is based on the "Spectrum" Qt example
    xc_assert(wav.open(wav_file), "Could not open WAV file '" + wav_file + "'");
    auto &format = wav.fileFormat();
    xc_assert(xc_audio::isPCMS16LE(format),
              "Audio format '" + xc_audio::formatToString(format) + "' not supported");

    int sample_rate = format.sampleRate();
    int channels = format.channelCount();
    int sample_size = format.sampleSize();
    int size = wav.size();

    QByteArray bytes = wav.readAll();
    //append_string_join_console(QString("sample rate %1, channels %2, sample_size %3")
    //        .arg(sample_rate).arg(channels).arg(sample_size));
    append_string_join_console(QString("file size %1, read %2")
            .arg(size).arg(bytes.size()));
    repaint_join_console();



}

//---------------------------------------------------------------------
