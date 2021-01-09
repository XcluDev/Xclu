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
    seti_last_success(0);
    setf_last_time(0);
    setf_last_duration(0);

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
    double start_time = xc_elapsed_time_sec();
    setf_last_time(start_time);

    bool success = false;

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

    //timeout - время ожидания, если -1, то ждать неограниченно
    int timeout = (geti_set_timeout()) ? int(getf_timeout_sec()*1000): -1;

    //запуск
    subprocess.setProcessChannelMode(QProcess::MergedChannels);

    subprocess->setReadChannel(QProcess::StandardOutput);
    subprocess->setProcessChannelMode(QProcess::SeparateChannels);
        QObject::connect( subprocess,SIGNAL(readyReadStandardOutput()),this,SLOT(onReadyReadStandardOutput()) );
        QObject::connect( subprocess,SIGNAL(readyReadStandardError()),this,SLOT(onReadyReadStandardError()) );
        QObject::connect( subprocess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(finished(int,QProcess::ExitStatus)) );
        QObject::connect( subprocess,SIGNAL(error(QProcess::ProcessError)),this,SLOT(crashed(QProcess::ProcessError)) );

subprocess->start( cmd,QProcess::Unbuffered | QProcess::ReadWrite );




    process.start();
    bool result = process.waitForFinished(timeout);

    //код выхода
    int exit_code = process.exitCode();
    seti_exit_code(exit_code);

    //проверяем результат
    success = result && (process.exitStatus() == QProcess::NormalExit)
            && (exit_code == 0);
    if (success) {
        seti_success(1);
    }
    //запоминаем результат
    seti_last_success(success);

    //Пишем в консоль
    if (geti_show_console()) {
        sets_local_console(process.readAll());
    }

    //если ошибка - выдаем это
    xc_assert(success, "Execution error or time is out");

    //ставим продолжительность
    double time = xc_elapsed_time_sec();
    setf_last_duration(time - start_time);
}



//---------------------------------------------------------------------
