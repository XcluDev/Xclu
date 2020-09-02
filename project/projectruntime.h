#ifndef PROJECTRUNTIME_H
#define PROJECTRUNTIME_H

//Свойства проекта, которые могут быть "интересны" модулям,
//такие так время от старта приложения и рабочая папка проекта

#include "incl_h.h"
#include <QElapsedTimer>
class Module;
class InterfaceItem;
class XcluObject;

//Работа с link - получение переменных по имени модуля и названию в формате:
//webcam1->image
//module1->line(1)
//module1->line(1,2)
class VarLink {
public:
    bool is_empty = true;
    QString module;
    QString var;
    int index = -1; //if index >= 0 - interpret as a string separated by spaces 'a b c' and get its item 'index'
    int index2 = -1; //if index2 >= 0 - interpret as a string separated by "\n" and then spaces 'a b c' and get its line 'index' and item 'index2'
    bool has_index() { return index >= 0; }
    VarLink();
    VarLink(QString link);
};


class ProjectRuntime
{
public:
    ProjectRuntime();

    void reset_fps_autostart();    //установить значения по умолчанию для frate_rate и autostar

    //Команды для управления проектом - модули могут их посылать
    //Установка частоты таймера обновления проекта (вызова update)
    void set_frame_rate(int fps);   //команда просто запоминает, а сам проект уже считывает при старте
    int get_frame_rate();

    //Автозапуск проекта:
    //если какой-то модуль устанавливает это в своем internal_loaded,
    //то после загрузки проекта он стартует
    void set_autostart(int v);  //команда просто запоминает, а сам проект уже считывает после загрузки json проекта
    bool get_autostart();

    //Состояние запуска
    void set_state(ProjectRunStateBinary state);
    bool is_running();
    bool is_stopped();

    //Измерение времени, прошедшего от запуска проекта
    void reset_elapsed_timer();
    double elapsed_time_sec();
    void update_dt();    //вызывается для обновления dt, в начале работы кадра
    float dt();

    //Папка проекта
    void set_project_folder(QString project_folder);
    QString project_folder();   //папка проекта - полный путь

    //возвращает абсолютный путь для папки, заданной относительно проекта
    //также, может создать эту папку, если это требуется
    QString absolute_path_from_project(QString relative_path, bool create_folder = false);

    //Получение модуля - можно получить к нему доступ, см. класс VarLink
    //а затем взять нужную переменную по geti и прочим
    Module *get_module(QString module_id);

    //Получение переменных по link - то есть по имени модуля и названию в формате webcam1->image//
    //Если link пустой - возвращаеь def_val
    int get_int_by_link(QString link_str, int def_val = 0);
    float get_float_by_link(QString link_str, float def_val = 0);
    QString get_string_by_link(QString link_str, QString def_val = "");
    XcluObject *get_object_by_link(QString link_str);

    //Нажатие кнопки
    void press_button_by_link(QString link_str);


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
    int frame_rate_ = 30;
    int autostart_ = 0;

    ProjectRunStateBinary state_ = ProjectRunStateBinaryStopped;

    QString project_folder_;

    QElapsedTimer elapsed_timer_;
    double last_time_for_dt_ = 0;   //используется для вычисления dt
    float dt_ = 0;

};

extern ProjectRuntime RUNTIME;

#endif // PROJECTRUNTIME_H
