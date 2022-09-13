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
QString xc_absolute_path_from_project(QString relative_path, bool create_folder = false);

//Получение модуля - можно получить к нему доступ, см. класс XLinkParsed
//а затем взять нужную переменную по geti и прочим
XModule *xc_find_module(QString module_name);

//Получение переменных по link - то есть по имени модуля и названию в формате webcam1->image//
//Если link пустой - возвращает def_val
int xc_get_int_by_link(QString link_str, int def_val = 0);
float xc_get_float_by_link(QString link_str, float def_val = 0);
QString xc_get_string_by_link(QString link_str, QString def_val = "");
XProtectedObject *xc_get_object_by_link(QString link_str);


//Send bang to module
//General: module1 or press button: module1->button1
void xc_bang(QString module_link);

//Send bang to modules
//General: module1 or press button: module1->button1
//Empty lines and lines started from "#" - ignored
void xc_bang(QStringList modules);


//Построение списка модулей по строке, в которой модули разделены \n,
//а также могут быть пустые строки и комментарии, начинающиеся с #, например:
//    #name of modules to play sound
//    Synth1
//    Synth2
//Это используется для callback модулей, а также сбора данных с разных модулей - например, звуковых буферов
//для воспроизведения
QVector<XModule *> xc_find_modules(QString modules_list);

//Выполнение Callbacks
//список name модулей может быть разделен \n, TAB, пробелами
//то есть идти из text или string
//static void execute_callbacks(QVector<XModule *> modules_list);
//static void execute_callbacks(QString modules_list_string);

