#pragma once

//Properties of a project for access from modules

#include "incl_h.h"
#include "xobject.h"
#include "xlink.h"
#include <QElapsedTimer>
class XModule;
class XItem;


//Runtime properties of the project class - controlled mainly by "Project" module
class ProjectRtProperties {
public:
    //reset all values to default
    void reset();

    //Frame rate of the execution
    //Xclu timer reads this at start
    void set_frame_rate(int fps);
    int get_frame_rate();

    //Autostart project:
    //if some module sets this in its loaded_internal,
    //then after loading the project it starts
    void set_autostart(int v, int wait_sec=0); // the command just remembers, and the project itself reads after loading the json of the project
    bool get_autostart();
    int get_autostart_wait_sec();

    //Don't save at exit - it's useful to disable for read installations working autonomously
    void set_dont_save_at_exit(int v);
    bool get_dont_save_at_exit();

protected:
    int frame_rate_ = 30;
    int autostart_ = 0;
    int wait_sec_ = 0;          // Wait seconds after autostart
    int dont_save_at_exit_ = 0;
};


//Properties of entire project, such as frame rate, autostart, save at exit
//It's controlled mainly by "Project" modile
ProjectRtProperties &xc_working_properties();

//Enable/disable

//Состояние запуска
void xc_set_state(ProjectRunStateBinary state);
bool xc_is_running();
bool xc_is_stopped();

//Измерение времени, прошедшего от запуска проекта
void xc_reset_elapsed_timer();
double xc_elapsed_time_sec();
void xc_update_dt();    //вызывается для обновления dt, в начале работы кадра
float xc_dt(float clamp_0 = 0, float clamp_1 = 1);
int xc_frame();         //current frame

//Папка проекта
void xc_set_project_folder(QString project_folder);
QString xc_project_folder();   //папка проекта - полный путь

//"Save as" dialog
//filter examples: "Txt (*.txt)", "Images (*.jpg *.png *.bmp *.tif *.tiff);; All files (*.*)"
QString xc_dialog_save_as(QString title, QString extensions_filter, QString folder="");

//"Load" dialog
//filter examples: "Txt (*.txt)", "Images (*.jpg *.png *.bmp *.tif *.tiff);; All files (*.*)"
//QString dialog_load(QString title, QString extensions_filter, QString folder="");

//возвращает абсолютный путь для папки, заданной относительно проекта
//также, может создать эту папку, если это требуется
QString xc_absolute_path(QString relative_path, bool create_folder = false);



