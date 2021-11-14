#include "project_props.h"
#include <QFileDialog>
#include "incl_cpp.h"
#include "project.h"
#include "xitem.h"
#include "xobject.h"
#include "mainwindow.h"


struct ProjectAccessData {
    ProjectRtProperties running_properties_;

    ProjectRunStateBinary state_ = ProjectRunStateBinaryStopped;

    QString project_folder_;

    QElapsedTimer elapsed_timer_;
    double last_time_for_dt_ = 0;   //используется для вычисления dt
    float dt_ = 0;
    int frame_ = 0;
};

ProjectAccessData access_;

//---------------------------------------------------------------------
//ProjectRtProperties
//---------------------------------------------------------------------
//установить значения по умолчанию для frate_rate и autostar
void ProjectRtProperties::reset() {
    frame_rate_ = 30;   //TODO параметр, значение по умолчанию
    autostart_ = 0;
    dont_save_at_exit_ = 0;
}

//---------------------------------------------------------------------
void ProjectRtProperties::set_frame_rate(int fps) {
    frame_rate_ = fps;
}

//---------------------------------------------------------------------
int ProjectRtProperties::get_frame_rate() {
    return frame_rate_;
}

//---------------------------------------------------------------------
void ProjectRtProperties::set_autostart(int v) {
    autostart_ = v;
}

//---------------------------------------------------------------------
bool ProjectRtProperties::get_autostart() {
    return autostart_;
}

//---------------------------------------------------------------------
void ProjectRtProperties::set_dont_save_at_exit(int v) {
    dont_save_at_exit_ = v;
}

//---------------------------------------------------------------------
bool ProjectRtProperties::get_dont_save_at_exit() {
    return dont_save_at_exit_;
}

//---------------------------------------------------------------------
//ProjectAccess
//---------------------------------------------------------------------
ProjectRtProperties &xc_working_properties() {
    return access_.running_properties_;
}

//---------------------------------------------------------------------
bool xc_is_running() {
    return (access_.state_ == ProjectRunStateBinaryRunning);
}

//---------------------------------------------------------------------
bool xc_is_stopped() {
    return (access_.state_ == ProjectRunStateBinaryStopped);
}

//---------------------------------------------------------------------
void xc_set_state(ProjectRunStateBinary state) {
    access_.state_ = state;
}

//---------------------------------------------------------------------
void xc_set_project_folder(QString project_folder) {
    access_.project_folder_ = project_folder;
}

//---------------------------------------------------------------------
QString xc_project_folder() {   //папка проекта - полный путь
    return access_.project_folder_;
}


//---------------------------------------------------------------------
//"Save as" dialog
//filter examples: "Txt (*.txt)", "Images (*.jpg *.png *.bmp *.tif *.tiff);; All files (*.*)"
QString xc_dialog_save_as(QString title, QString extensions_filter, QString folder) {
    if (folder.isEmpty()) folder = xc_project_folder();

    return QFileDialog::getSaveFileName(MainWindow::window(), title,
                                 folder,
                                 extensions_filter);
}

//---------------------------------------------------------------------
//возвращает абсолютный путь для папки, заданной относительно проекта
//также, может создать эту папку, если это требуется
QString xc_absolute_path_from_project(QString relative_path, bool create_folder) {
    QDir dir(xc_project_folder());
    QString path = dir.absoluteFilePath(relative_path);
    if (create_folder) {
        QDir dir;
        xc_assert(dir.mkpath(path), "Can't create folder " + path);
    }
    return path;
}

//---------------------------------------------------------------------
//Получение модуля
Module *xc_find_module(QString module_name) {
    return PROJECT.find_module_by_name(module_name);
}

//---------------------------------------------------------------------
//Получение переменных по link
int xc_get_int_by_link(QString link_str, int def_val) {
    XLinkParsed link(link_str);
    if (link.is_empty) return def_val;
    return xc_find_module(link.module)->geti(link.var, link.index, link.index2);
}

//---------------------------------------------------------------------
float xc_get_float_by_link(QString link_str, float def_val) {
    XLinkParsed link(link_str);
    if (link.is_empty) return def_val;
    return xc_find_module(link.module)->getf(link.var, link.index, link.index2);
}

//---------------------------------------------------------------------
QString xc_get_string_by_link(QString link_str, QString def_val) {
    XLinkParsed link(link_str);
    if (link.is_empty) return def_val;
    return xc_find_module(link.module)->gets(link.var, link.index, link.index2);
}

//---------------------------------------------------------------------
XProtectedObject *xc_get_object_by_link(QString link_str) {
    XLinkParsed link(link_str);
    return xc_find_module(link.module)->get_object(link.var);
}

//---------------------------------------------------------------------
//Send bang to module
//General: module1 or press button: module1->button1
void xc_bang(QString module_link) {
    XLinkParsed link(module_link);
    if (link.var.isEmpty()) xc_find_module(link.module)->bang();
    else xc_find_module(link.module)->button_pressed(link.var);
}

//---------------------------------------------------------------------
//Send bang to modules
//General: module1 or press button: module1->button1
//Empty lines and lines started from "#" - ignored
void xc_bang(QStringList modules) {
    for (auto &line: modules) {
        QString module_link = line.trimmed();
        if (module_link.isEmpty()) continue;
        if (module_link.startsWith("#")) continue;
        xc_bang(module_link);
    }
}

//---------------------------------------------------------------------
/*XItem *xc_get_var_by_link(QString link_str) {
    XLinkParsed link(link_str);
    Module *module = get_module(link.module);
    return module->interf()->var(link.var);
}*/

//---------------------------------------------------------------------
/*XObject *xc_get_object_by_link(QString link_str) {
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
/*static*/ QVector<Module *> xc_find_modules(QString modules_list) {
    QStringList list = QString(modules_list).split("\n");
    QVector<Module *> out_list;

    for (int i=0; i<list.size(); i++) {
        QString name = list.at(i).trimmed();
        if (!name.isEmpty() && !name.startsWith("#")) {
            out_list.push_back(PROJECT.find_module_by_name(name));
        }
    }
    return out_list;
}

//---------------------------------------------------------------------
//Выполнение Callbacks
//список name модулей может быть разделен \n, TAB, пробелами
//то есть идти из text или string
/*static*/ /*void xc_execute_callbacks(QVector<Module *> modules_list) {
    for (int i=0; i<modules_list.size(); i++) {
        modules_list[i]->execute(ModuleExecuteStageCallback);
    }
}*/

//---------------------------------------------------------------------
/*static*//* void xc_execute_callbacks(QString modules_list_string) {
    execute_callbacks(get_modules(modules_list_string));
}*/

//---------------------------------------------------------------------
//Измерение времени от начала проекта
void xc_reset_elapsed_timer() {
    access_.elapsed_timer_.start();
    access_.last_time_for_dt_ = xc_elapsed_time_sec();
    access_.dt_ = 0;

    access_.frame_ = 0;
}

//---------------------------------------------------------------------
double xc_elapsed_time_sec() {   //время в секундах, прошедшее от запуска проекта
    return access_.elapsed_timer_.elapsed() * 0.001;
}

//---------------------------------------------------------------------
void xc_update_dt() {    //вызывается для обновления dt, в начале работы кадра
    double time = xc_elapsed_time_sec();
    access_.dt_ = time - access_.last_time_for_dt_;
    access_.last_time_for_dt_ = time;

    access_.frame_++;
}

//---------------------------------------------------------------------
float xc_dt() {
    return access_.dt_;
}

//---------------------------------------------------------------------
int xc_frame() {         //current frame
    return access_.frame_;
}

//---------------------------------------------------------------------

