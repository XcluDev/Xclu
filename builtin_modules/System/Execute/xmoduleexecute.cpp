#include "xmoduleexecute.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QProcess>
#include "xcore.h"


//registering module implementation
REGISTER_XMODULE(Execute)

//---------------------------------------------------------------------
XModuleExecute::XModuleExecute(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleExecute::~XModuleExecute()
{

}

//---------------------------------------------------------------------
void XModuleExecute::start() {
    //qDebug() << "start";
    seti_success(0);
    seti_exit_code(0);
    //seti_last_success(0);
    //setf_last_time(0);
    //setf_last_duration(0);

    clear_string_folder_path();
    clear_string_file_path();

    subprocess_.reset();

    if (gete_execute() == execute_At_First_Frame) {
        run();
    }
}

//---------------------------------------------------------------------
void XModuleExecute::update() {
    auto execute = gete_execute();
    if (execute == execute_Each_Frame
            || (execute == execute_On_Button && geti_run_button())) {
        run();
    }

}

//---------------------------------------------------------------------
void XModuleExecute::stop() {
    subprocess_.reset();
}

//---------------------------------------------------------------------
void XModuleExecute::run() {
    seti_success(0);

    //compute paths
    QString folder = gets_folder_name();
    QString file_name_short = gets_file_name();

    folder = xc_project_folder() + "/" + folder;
    sets_folder_path(folder);

    //file name
    xc_assert(!file_name_short.isEmpty(), "File Name is empty");
    QString file_name = folder + "/" + file_name_short;
    //if user provided absolute path - then use it - we detect it as if file_name doesn't extsts
    if (!QFileInfo::exists(file_name)) {
        file_name = file_name_short;
    }
    sets_file_path(file_name);

    //check that folder and file exist
    xc_assert(QDir(folder).exists(), "Folder '" + folder + "' doesn't exists");
    xc_assert(QFileInfo::exists(file_name), "File '" + file_name + "' doesn't exists");

    //starting time
    //double start_time = xc_elapsed_time_sec();
    //setf_last_time(start_time);


    //qDebug() << "execute...";

    //create process

    //Note: this stops current process if exists - don't know, should we manage this additionally
    subprocess_.reset(new QProcess);

    QProcess &subprocess = *subprocess_;
    subprocess.setWorkingDirectory(folder);
    subprocess.setProgram(file_name);

    //arguments
    QStringList arguments;
    arguments << gets_args();
    subprocess.setArguments(arguments);

    //timeout - if -1, then wait infinite
    int timeout = (geti_enable_timeout()) ? int(getf_timeout_sec()*1000): -1;

    //run

    subprocess.setReadChannel(QProcess::StandardOutput);
    subprocess.setProcessChannelMode(QProcess::SeparateChannels); //separate output and error to process them differently
    //subprocess.setProcessChannelMode(QProcess::MergedChannels);

    connect(&subprocess, &QProcess::readyReadStandardOutput, this, &XModuleExecute::onReadyReadStandardOutput);
    connect(&subprocess, &QProcess::readyReadStandardError, this, &XModuleExecute::onReadyReadStandardError);

    connect(&subprocess, QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished), this, &XModuleExecute::finished);
    connect(&subprocess, QOverload<QProcess::ProcessError>::of(&QProcess::error), this, &XModuleExecute::crashed);


    subprocess.start(QProcess::Unbuffered | QProcess::ReadWrite );

    //decide - wait finishing or work async
    auto thread_mode = gete_thread_mode();

    if (thread_mode == thread_mode_Wait_Finishing) {
        //sync run
        subprocess.start(QProcess::Unbuffered | QProcess::ReadWrite );
        console_write();
        bool success = subprocess.waitForFinished(timeout);
        console_read();
        if (!success) {
            xc_assert(success, "Timeout");
        }
        check_error();
    }
    else {
        //async run
    }

    //double time = xc_elapsed_time_sec();
    //setf_last_duration(time - start_time);
}

//---------------------------------------------------------------------
void XModuleExecute::check_error() {
    if (subprocess_.data()) {
        QProcess &subprocess = *subprocess_;
        //exit code
        int exit_code = subprocess.exitCode();
        seti_exit_code(exit_code);

        bool success = /*result && */(subprocess.exitStatus() == QProcess::NormalExit)
                && (exit_code == 0);
        seti_success(success);

        //read all data from console anyway
        //QByteArray error = subprocess.readAll(); //readAllStandardError();
        //sets_text_errors(error);

        xc_assert(success, "Execution error, see Console - Errors");

    }
}

//---------------------------------------------------------------------
void XModuleExecute::onReadyReadStandardOutput() {
    //Note, this is async callback
    //console_read();
    qDebug() << "Standard" << subprocess_.data()->readAllStandardOutput();
}

//---------------------------------------------------------------------
void XModuleExecute::onReadyReadStandardError() {
    //Note, this is async callback

    QString text = subprocess_.data()->readAllStandardError();
    //qDebug() << "Error" << text;
    //QByteArray error = subprocess_.data()->readAll(); //readAllStandardError();
    sets_text_errors(text);
}

//---------------------------------------------------------------------
void XModuleExecute::finished(int, QProcess::ExitStatus) {

}

//---------------------------------------------------------------------
void XModuleExecute::crashed(QProcess::ProcessError) {

}

//---------------------------------------------------------------------
void XModuleExecute::console_read() {
    if (subprocess_.data()) {
        QProcess &subprocess = *subprocess_;

        QByteArray output = subprocess.readAllStandardOutput();
        QByteArray error = subprocess.readAllStandardError();


       /* if (geti_show_console()) {

            sets_local_console();
        }*/
    }
}

//---------------------------------------------------------------------
void XModuleExecute::console_write() {

}

//---------------------------------------------------------------------
