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
void ProjectRtProperties::set_autostart(int v, int wait_sec) {
    autostart_ = v;
    wait_sec_ = wait_sec;
}

//---------------------------------------------------------------------
bool ProjectRtProperties::get_autostart() {
    return autostart_;
}

//---------------------------------------------------------------------
int ProjectRtProperties::get_autostart_wait_sec() {
    return wait_sec_;
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
QString xc_absolute_path(QString relative_path, bool create_folder) {
    QDir dir(xc_project_folder());
    QString path = dir.absoluteFilePath(relative_path);
    if (create_folder) {
        QDir dir;
        xc_assert(dir.mkpath(path), "Can't create folder " + path);
    }
    return path;
}

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
float xc_dt(float clamp_0, float clamp_1) {
    return xclampf(access_.dt_, clamp_0, clamp_1);
}

//---------------------------------------------------------------------
int xc_frame() {         //current frame
    return access_.frame_;
}

//---------------------------------------------------------------------

