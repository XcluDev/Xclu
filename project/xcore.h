#ifndef XCORE_H
#define XCORE_H

//Свойства проекта, которые могут быть "интересны" модулям,
//такие так время от старта приложения и рабочая папка проекта

#include "incl_h.h"
#include "xobject.h"
#include "xlink.h"
#include <QElapsedTimer>
class Module;
class XItem;


//Properties of the project - controlled mainly by "Project" module
class XCoreWorkingProperties {
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
    void set_autostart (int v); // the command just remembers, and the project itself reads after loading the json of the project
    bool get_autostart();

    //Don't save at exit - it's useful to disable for read installations working autonomously
    void set_dont_save_at_exit(int v);
    bool get_dont_save_at_exit();

protected:
    int frame_rate_ = 30;
    int autostart_ = 0;
    int dont_save_at_exit_ = 0;
};


//Main XCore class
class XCore
{
public:
    XCore();

    //Properties of entire project, such as frame rate, autostart, save at exit
    //It's controlled mainly by "Project" modile
    XCoreWorkingProperties &working_properties();

    //Enable/disable

    //Состояние запуска
    void set_state(ProjectRunStateBinary state);
    bool is_running();
    bool is_stopped();

    //Измерение времени, прошедшего от запуска проекта
    void reset_elapsed_timer();
    double elapsed_time_sec();
    void update_dt();    //вызывается для обновления dt, в начале работы кадра
    float dt();
    int frame();         //current frame

    //Папка проекта
    void set_project_folder(QString project_folder);
    QString project_folder();   //папка проекта - полный путь

    //возвращает абсолютный путь для папки, заданной относительно проекта
    //также, может создать эту папку, если это требуется
    QString absolute_path_from_project(QString relative_path, bool create_folder = false);

    //Получение модуля - можно получить к нему доступ, см. класс XLinkParsed
    //а затем взять нужную переменную по geti и прочим
    Module *get_module(QString module_name);

    //Получение переменных по link - то есть по имени модуля и названию в формате webcam1->image//
    //Если link пустой - возвращает def_val
    int get_int_by_link(QString link_str, int def_val = 0);
    float get_float_by_link(QString link_str, float def_val = 0);
    QString get_string_by_link(QString link_str, QString def_val = "");
    XProtectedObject *get_object_by_link(QString link_str);


    //Send bang to module
    //General: module1 or press button: module1->button1
    void bang(QString module_link);

    //Send bang to modules
    //General: module1 or press button: module1->button1
    //Empty lines and lines started from "#" - ignored
    void bang(QStringList modules);


    //Построение списка модулей по строке, в которой модули разделены \n,
    //а также могут быть пустые строки и комментарии, начинающиеся с #, например:
    //    #name of modules to play sound
    //    Synth1
    //    Synth2
    //Это используется для callback модулей, а также сбора данных с разных модулей - например, звуковых буферов
    //для воспроизведения
    static QVector<Module *> get_modules(QString modules_list);

    //Выполнение Callbacks
    //список name модулей может быть разделен \n, TAB, пробелами
    //то есть идти из text или string
    //static void execute_callbacks(QVector<Module *> modules_list);
    //static void execute_callbacks(QString modules_list_string);
protected:
    XCoreWorkingProperties running_properties_;

    ProjectRunStateBinary state_ = ProjectRunStateBinaryStopped;

    QString project_folder_;

    QElapsedTimer elapsed_timer_;
    double last_time_for_dt_ = 0;   //используется для вычисления dt
    float dt_ = 0;
    int frame_ = 0;

};

extern XCore XCORE;

#endif // XCORE_H
