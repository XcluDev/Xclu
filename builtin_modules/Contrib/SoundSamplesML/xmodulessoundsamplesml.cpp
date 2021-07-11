#include "xmodulessoundsamplesml.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QProcess>
#include <QDirIterator>
#include "xcore.h"


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
                             QStringList() << "*.wav" << "*.aiff"
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
void XModuleSoundSamplesML::join_wav(QString file) {

}

//---------------------------------------------------------------------
