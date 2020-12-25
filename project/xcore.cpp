#include "xcore.h"
#include "incl_cpp.h"
#include "project.h"
#include "xitem.h"
#include "xobject.h"

XCore XCORE;

//---------------------------------------------------------------------
//XCoreWorkingProperties
//---------------------------------------------------------------------
//установить значения по умолчанию для frate_rate и autostar
void XCoreWorkingProperties::reset() {
    frame_rate_ = 30;   //TODO параметр, значение по умолчанию
    autostart_ = 0;
    dont_save_at_exit_ = 1;
}

//---------------------------------------------------------------------
void XCoreWorkingProperties::set_frame_rate(int fps) {
    frame_rate_ = fps;
}

//---------------------------------------------------------------------
int XCoreWorkingProperties::get_frame_rate() {
    return frame_rate_;
}

//---------------------------------------------------------------------
void XCoreWorkingProperties::set_autostart(int v) {
    autostart_ = v;
}

//---------------------------------------------------------------------
bool XCoreWorkingProperties::get_autostart() {
    return autostart_;
}

//---------------------------------------------------------------------
void XCoreWorkingProperties::set_dont_save_at_exit(int v) {
    dont_save_at_exit_ = v;
}

//---------------------------------------------------------------------
bool XCoreWorkingProperties::get_dont_save_at_exit() {
    return dont_save_at_exit_;
}

//---------------------------------------------------------------------
//XCore
//---------------------------------------------------------------------
XCore::XCore()
{

}

//---------------------------------------------------------------------
XCoreWorkingProperties &XCore::working_properties() {
    return running_properties_;
}

//---------------------------------------------------------------------
bool XCore::is_running() {
    return (state_ == ProjectRunStateBinaryRunning);
}

//---------------------------------------------------------------------
bool XCore::is_stopped() {
    return (state_ == ProjectRunStateBinaryStopped);
}

//---------------------------------------------------------------------
void XCore::set_state(ProjectRunStateBinary state) {
    state_ = state;
}

//---------------------------------------------------------------------
void XCore::set_project_folder(QString project_folder) {
    project_folder_ = project_folder;
}

//---------------------------------------------------------------------
QString XCore::project_folder() {   //папка проекта - полный путь
    return project_folder_;
}

//---------------------------------------------------------------------
//возвращает абсолютный путь для папки, заданной относительно проекта
//также, может создать эту папку, если это требуется
QString XCore::absolute_path_from_project(QString relative_path, bool create_folder) {
    QDir dir(project_folder());
    QString path = dir.absoluteFilePath(relative_path);
    if (create_folder) {
        QDir dir;
        xc_assert(dir.mkpath(path), "Can't create folder " + path);
    }
    return path;
}

//---------------------------------------------------------------------
//Получение модуля
Module *XCore::get_module(QString module_name) {
    return PROJ.module_by_name(module_name);
}

//---------------------------------------------------------------------
//Получение переменных по link
int XCore::get_int_by_link(QString link_str, int def_val) {
    XLinkParsed link(link_str);
    if (link.is_empty) return def_val;
    return get_module(link.module)->geti(link.var, link.index, link.index2);
}

//---------------------------------------------------------------------
float XCore::get_float_by_link(QString link_str, float def_val) {
    XLinkParsed link(link_str);
    if (link.is_empty) return def_val;
    return get_module(link.module)->getf(link.var, link.index, link.index2);
}

//---------------------------------------------------------------------
QString XCore::get_string_by_link(QString link_str, QString def_val) {
    XLinkParsed link(link_str);
    if (link.is_empty) return def_val;
    return get_module(link.module)->gets(link.var, link.index, link.index2);
}

//---------------------------------------------------------------------
XProtectedObject *XCore::get_object_by_link(QString link_str) {
    XLinkParsed link(link_str);
    return get_module(link.module)->get_object(link.var);
}

//---------------------------------------------------------------------
//Send bang to module
//General: module1 or press button: module1->button1
void XCore::bang(QString module_link) {
    XLinkParsed link(module_link);
    if (link.var.isEmpty()) get_module(link.module)->bang();
    else get_module(link.module)->button_pressed(link.var);
}

//---------------------------------------------------------------------
//Send bang to modules
//General: module1 or press button: module1->button1
//Empty lines and lines started from "#" - ignored
void XCore::bang(QStringList modules) {
    for (auto &line: modules) {
        QString module_link = line.trimmed();
        if (module_link.isEmpty()) continue;
        if (module_link.startsWith("#")) continue;
        bang(module_link);
    }
}

//---------------------------------------------------------------------
/*XItem *XCore::get_var_by_link(QString link_str) {
    XLinkParsed link(link_str);
    Module *module = get_module(link.module);
    return module->interf()->var(link.var);
}*/

//---------------------------------------------------------------------
/*XObject *XCore::get_object_by_link(QString link_str) {
    XLinkParsed link(link_str);
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
/*static*/ QVector<Module *> XCore::get_modules(QString modules_list) {
    QStringList list = QString(modules_list).split("\n");
    QVector<Module *> out_list;

    for (int i=0; i<list.size(); i++) {
        QString name = list.at(i).trimmed();
        if (!name.isEmpty() && !name.startsWith("#")) {
            out_list.push_back(PROJ.module_by_name(name));
        }
    }
    return out_list;
}

//---------------------------------------------------------------------
//Выполнение Callbacks
//список name модулей может быть разделен \n, TAB, пробелами
//то есть идти из text или string
/*static*/ /*void XCore::execute_callbacks(QVector<Module *> modules_list) {
    for (int i=0; i<modules_list.size(); i++) {
        modules_list[i]->execute(ModuleExecuteStageCallback);
    }
}*/

//---------------------------------------------------------------------
/*static*//* void XCore::execute_callbacks(QString modules_list_string) {
    execute_callbacks(get_modules(modules_list_string));
}*/

//---------------------------------------------------------------------
//Измерение времени от начала проекта
void XCore::reset_elapsed_timer() {
    elapsed_timer_.start();
    last_time_for_dt_ = elapsed_time_sec();
    dt_ = 0;
}

//---------------------------------------------------------------------
double XCore::elapsed_time_sec() {   //время в секундах, прошедшее от запуска проекта
    return elapsed_timer_.elapsed() * 0.001;
}

//---------------------------------------------------------------------
void XCore::update_dt() {    //вызывается для обновления dt, в начале работы кадра
    double time = elapsed_time_sec();
    dt_ = time - last_time_for_dt_;
    last_time_for_dt_ = time;
}

//---------------------------------------------------------------------
float XCore::dt() {
    return dt_;
}

//---------------------------------------------------------------------

