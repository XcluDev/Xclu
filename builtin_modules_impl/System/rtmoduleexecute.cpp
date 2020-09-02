#include "rtmoduleexecute.h"
#include "incl_cpp.h"
#include "rtmoduleregistrar.h"
#include <QProcess>
#include "projectruntime.h"


//заполнение имени класса и регистрация класса
REGISTRAR(Execute)

//---------------------------------------------------------------------
/*static*/ RtModuleExecute *RtModuleExecute::new_module() {
    return new RtModuleExecute();
}

//---------------------------------------------------------------------
RtModuleExecute::RtModuleExecute()
    :RtModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
RtModuleExecute::~RtModuleExecute()
{

}

//---------------------------------------------------------------------
void RtModuleExecute::execute_start_internal() {
    //qDebug() << "start";
    seti("success", 0);
    seti("exit_code", 0);
    seti("last_success", 0);
    setf("last_time", 0);
    setf("last_duration", 0);
    clear_string("local_console");

    clear_string("folder_path");
    clear_string("file_path");

}

//---------------------------------------------------------------------
void RtModuleExecute::execute_update_internal() {
    //очищаем флажок success - он действует только в рамках одного кадра
    seti("success", 0);

    WorkMode mode = WorkMode(geti("work_mode"));

    //вычисляем, требуется ли запуск
    bool bang = false;
    if (mode == WorkModeEach_Frame) bang = true;
    if (mode == WorkModeOn_Bang) bang = geti("bang_signal") || geti("bang_button");

    //запуск
    if (bang) {

        //вычисляем пути, даже если не требуется запуск
        QString folder = gets("folder_name");
        QString file_name_short = gets("file_name");

        //относительный путь
        folder = RUNTIME.project_folder() + "/" + folder;
        sets("folder_path", folder);

        //построение имени файла
        xclu_assert(!file_name_short.isEmpty(), "File Name is empty");
        QString file_name = folder + "/" + file_name_short;
        //проверяем - если имя файла абсолютное (то есть с folder файла не существует), то используем краткое имя
        if (!QFileInfo::exists(file_name)) {
            file_name = file_name_short;
        }
        sets("file_path", file_name);

        //сейчас поддерживаем только режим ожидания результата
        //int wait_finish = geti("wait_finish");

        //запоминаем время старта
        double start_time = RUNTIME.elapsed_time_sec();
        setf("last_time", start_time);

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
        arguments << gets("args");
        process.setArguments(arguments);

        //timeout - время ожидания, если -1, то ждать неограниченно
        int timeout = (geti("set_timeout")) ? int(getf("timeout_sec")*1000): -1;

        //запуск
        process.start();
        bool result = process.waitForFinished(timeout);

        //код выхода
        int exit_code = process.exitCode();
        seti("exit_code", exit_code);

        //проверяем результат
        success = result && (process.exitStatus() == QProcess::NormalExit)
                && (exit_code == 0);
        if (success) {
            seti("success", 1);
        }
        //запоминаем результат
        seti("last_success", success);

        //Пишем в консоль
        if (geti("show_console")) {
            sets("local_console", process.readAll());
        }

        //если ошибка - выдаем это
        xclu_assert(success, "Execution error or time is out");

        //ставим продолжительность
        double time = RUNTIME.elapsed_time_sec();
        setf("last_duration", time - start_time);
    }


}

//---------------------------------------------------------------------
void RtModuleExecute::execute_stop_internal() {
    //qDebug() << "stop";

}

//---------------------------------------------------------------------
