#include "xmoduleexecute.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QProcess>
#include "projectruntime.h"


//registering module implementation
REGISTRAR(Execute)

//---------------------------------------------------------------------
/*static*/ XModuleExecute *XModuleExecute::new_module() {
    return new XModuleExecute();
}

//---------------------------------------------------------------------
XModuleExecute::XModuleExecute()
    :XModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
XModuleExecute::~XModuleExecute()
{

}

//---------------------------------------------------------------------
void XModuleExecute::impl_start() {
    //qDebug() << "start";
    seti_success(0);
    seti_exit_code(0);
    seti_last_success(0);
    setf_last_time(0);
    setf_last_duration(0);
    clear_string_local_console();

    clear_string_folder_path();
    clear_string_file_path();

}

//---------------------------------------------------------------------
void XModuleExecute::impl_update() {
    //очищаем флажок success - он действует только в рамках одного кадра
    seti_success(0);

   auto mode = gete_work_mode();

    //вычисляем, требуется ли запуск
    bool bang = false;
    if (mode == work_mode_Each_Frame) bang = true;
    if (mode == work_mode_On_Bang) bang = geti_bang_signal() || geti_bang_button();

    //запуск
    if (bang) {

        //вычисляем пути, даже если не требуется запуск
        QString folder = gets_folder_name();
        QString file_name_short = gets_file_name();

        //относительный путь
        folder = rt_project_folder() + "/" + folder;
        sets_folder_path(folder);

        //построение имени файла
        xclu_assert(!file_name_short.isEmpty(), "File Name is empty");
        QString file_name = folder + "/" + file_name_short;
        //проверяем - если имя файла абсолютное (то есть с folder файла не существует), то используем краткое имя
        if (!QFileInfo::exists(file_name)) {
            file_name = file_name_short;
        }
        sets_file_path(file_name);

        //сейчас поддерживаем только режим ожидания результата
        //int wait_finish = geti_wait_finish");

        //запоминаем время старта
        double start_time = rt_elapsed_time_sec();
        setf_last_time(start_time);

        bool success = false;

        xclu_assert(QDir(folder).exists(), "Folder '" + folder + "' doesn't exists");
        xclu_assert(QFileInfo::exists(file_name), "File '" + file_name + "' doesn't exists");

        //qDebug() << "execute...";

        //запуск прямо здесь и ожидание результата
        QProcess process;
        process.setProcessChannelMode(QProcess::MergedChannels);
        process.setWorkingDirectory(folder);
        process.setProgram(file_name);

        //аргумент запуска
        QStringList arguments;
        arguments << gets_args();
        process.setArguments(arguments);

        //timeout - время ожидания, если -1, то ждать неограниченно
        int timeout = (geti_set_timeout()) ? int(getf_timeout_sec()*1000): -1;

        //запуск
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
        xclu_assert(success, "Execution error or time is out");

        //ставим продолжительность
        double time = rt_elapsed_time_sec();
        setf_last_duration(time - start_time);
    }


}

//---------------------------------------------------------------------
void XModuleExecute::impl_stop() {
    //qDebug() << "stop";

}

//---------------------------------------------------------------------
