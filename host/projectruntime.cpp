#include "projectruntime.h"
#include "incl_cpp.h"
#include "project.h"
#include "xitem.h"
#include "xdict.h"

ProjectRuntime RUNTIME;

//---------------------------------------------------------------------
//Работа с link - получение переменных по имени модуля и названию в формате:
//webcam1->image
//module1->line(1)
//module1->line(1,2)
VarLink::VarLink(QString link_str0) {
    is_empty = link_str0.isEmpty();
    if (is_empty) {
        return;
    }

    //для простоты "(", "->" на " " и убираем ")"
    //тогда module1->line(1) будет как "module1 line 1"
    QString link = link_str0.trimmed()
            .replace("->"," ").replace("("," ").replace(","," ").replace(")","");

    auto query = link.trimmed().split(" ");
    int n = query.size();
    xclu_assert(n >= 2
                && !query.at(0).isEmpty()
                && !query.at(1).isEmpty(),
                "Bad link '" + link_str0 + "', expected at format webcam1->image or module1->line(0) or module1->line(1,2)");
    xclu_assert(n < 3 || !query.at(2).isEmpty(), "Empty first index at link '" + link_str0 + "', expected in format webcam1->image or module1->line(0) or module1->line(1,2)");
    xclu_assert(n < 4 || !query.at(3).isEmpty(), "Empty second index at link '" + link_str0 + "', expected in format webcam1->image or module1->line(0) or module1->line(1,2)");

    module = query.at(0);
    var = query.at(1);
    index = (n >= 3) ? query.at(2).toInt():-1;
    index2 = (n >= 4) ? query.at(3).toInt():-1;
}

//---------------------------------------------------------------------
ProjectRuntime::ProjectRuntime()
{

}

//---------------------------------------------------------------------
//установить значения по умолчанию для frate_rate и autostar
void ProjectRuntime::reset_fps_autostart() {
    frame_rate_ = 30;   //TODO параметр, значение по умолчанию
    autostart_ = 0;
}

//---------------------------------------------------------------------
void ProjectRuntime::set_frame_rate(int fps) {
    frame_rate_ = fps;
}

//---------------------------------------------------------------------
int ProjectRuntime::get_frame_rate() {
    return frame_rate_;
}

//---------------------------------------------------------------------
//Автозапуск проекта:
//если какой-то модуль устанавливает это в своем loaded_internal,
//то после загрузки проекта он стартует
void ProjectRuntime::set_autostart(int v) {
    autostart_ = v;
}

//---------------------------------------------------------------------
bool ProjectRuntime::get_autostart() {
    return autostart_;
}

//---------------------------------------------------------------------
bool ProjectRuntime::is_running() {
    return (state_ == ProjectRunStateBinaryRunning);
}

//---------------------------------------------------------------------
bool ProjectRuntime::is_stopped() {
    return (state_ == ProjectRunStateBinaryStopped);
}

//---------------------------------------------------------------------
void ProjectRuntime::set_state(ProjectRunStateBinary state) {
    state_ = state;
}

//---------------------------------------------------------------------
void ProjectRuntime::set_project_folder(QString project_folder) {
    project_folder_ = project_folder;
}

//---------------------------------------------------------------------
QString ProjectRuntime::project_folder() {   //папка проекта - полный путь
    return project_folder_;
}

//---------------------------------------------------------------------
//возвращает абсолютный путь для папки, заданной относительно проекта
//также, может создать эту папку, если это требуется
QString ProjectRuntime::absolute_path_from_project(QString relative_path, bool create_folder) {
    QDir dir(project_folder());
    QString path = dir.absoluteFilePath(relative_path);
    if (create_folder) {
        QDir dir;
        xclu_assert(dir.mkpath(path), "Can't create folder " + path);
    }
    return path;
}

//---------------------------------------------------------------------
//Получение модуля
Module *ProjectRuntime::get_module(QString module_id) {
    return PROJ.module_by_id(module_id);
}

//---------------------------------------------------------------------
//Получение переменных по link
int ProjectRuntime::get_int_by_link(QString link_str, int def_val) {
    VarLink link(link_str);
    if (link.is_empty) return def_val;
    return RUNTIME.get_module(link.module)->geti(link.var, link.index, link.index2);
}

//---------------------------------------------------------------------
float ProjectRuntime::get_float_by_link(QString link_str, float def_val) {
    VarLink link(link_str);
    if (link.is_empty) return def_val;
    return RUNTIME.get_module(link.module)->getf(link.var, link.index, link.index2);
}

//---------------------------------------------------------------------
QString ProjectRuntime::get_string_by_link(QString link_str, QString def_val) {
    VarLink link(link_str);
    if (link.is_empty) return def_val;
    return RUNTIME.get_module(link.module)->gets(link.var, link.index, link.index2);
}

//---------------------------------------------------------------------
XDict *ProjectRuntime::get_object_by_link(QString link_str) {
    VarLink link(link_str);
    return RUNTIME.get_module(link.module)->get_object(link.var);
}

//---------------------------------------------------------------------
//Нажатие кнопки
void ProjectRuntime::press_button_by_link(QString link_str) {
    VarLink link(link_str);
    return RUNTIME.get_module(link.module)->button_pressed(link.var);
}

//---------------------------------------------------------------------
/*XItem *ProjectRuntime::get_var_by_link(QString link_str) {
    VarLink link(link_str);
    Module *module = get_module(link.module);
    return module->interf()->var(link.var);
}*/

//---------------------------------------------------------------------
/*XDict *ProjectRuntime::get_object_by_link(QString link_str) {
    VarLink link(link_str);
    Module *module = get_module(link.module);
    return module->get_object(link.var);
}*/

//---------------------------------------------------------------------
//Построение списка модулей по строке, в которой модули разделены \n,
//а также могут быть пустые строки и комментарии, начинающиеся с #, например:
//    #name of modules to play sound
//    Synth1
//    Synth2
//Это используется для callback модулей, а также сбора данных с разных модулей - например, звуковых буферов
//для воспроизведения
/*static*/ QVector<Module *> ProjectRuntime::get_modules(QString modules_list) {
    QStringList list = QString(modules_list).split("\n");
    QVector<Module *> out_list;

    for (int i=0; i<list.size(); i++) {
        QString name = list.at(i).trimmed();
        if (!name.isEmpty() && !name.startsWith("#")) {
            out_list.push_back(PROJ.module_by_id(name));
        }
    }
    return out_list;
}

//---------------------------------------------------------------------
//Выполнение Callbacks
//список name модулей может быть разделен \n, TAB, пробелами
//то есть идти из text или string
/*static*/ /*void ProjectRuntime::execute_callbacks(QVector<Module *> modules_list) {
    for (int i=0; i<modules_list.size(); i++) {
        modules_list[i]->execute(ModuleExecuteStageCallback);
    }
}*/

//---------------------------------------------------------------------
/*static*//* void ProjectRuntime::execute_callbacks(QString modules_list_string) {
    execute_callbacks(get_modules(modules_list_string));
}*/

//---------------------------------------------------------------------
//Измерение времени от начала проекта
void ProjectRuntime::reset_elapsed_timer() {
    elapsed_timer_.start();
    last_time_for_dt_ = elapsed_time_sec();
    dt_ = 0;
}

//---------------------------------------------------------------------
double ProjectRuntime::elapsed_time_sec() {   //время в секундах, прошедшее от запуска проекта
    return elapsed_timer_.elapsed() * 0.001;
}

//---------------------------------------------------------------------
void ProjectRuntime::update_dt() {    //вызывается для обновления dt, в начале работы кадра
    double time = elapsed_time_sec();
    dt_ = time - last_time_for_dt_;
    last_time_for_dt_ = time;
}

//---------------------------------------------------------------------
float ProjectRuntime::dt() {
    return dt_;
}

//---------------------------------------------------------------------

