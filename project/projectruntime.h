#ifndef PROJECTRUNTIME_H
#define PROJECTRUNTIME_H

//Свойства проекта, которые могут быть "интересны" модулям,
//такие так время от старта приложения и рабочая папка проекта

#include "incl_qt.h"
#include <QElapsedTimer>
class Module;
class InterfaceItem;
class XcluObject;

//Работа с link - получение переменных по имени модуля и названию в формате webcam1->image
class VarLink {
public:
    QString module;
    QString var;
    VarLink();
    VarLink(QString link);
};


class ProjectRuntime
{
public:
    ProjectRuntime();

    //Состояние запуска
    void set_state(ProjectRunStateBinary state);
    bool is_running();
    bool is_stopped();

    //Измерение времени, прошедшего от запуска проекта
    void reset_elapsed_timer();
    double elapsed_time_sec();

    //Папка проекта
    void set_project_folder(QString project_folder);
    QString project_folder();   //папка проекта - полный путь

    //Получение модуля - можно получить к нему доступ, см. класс VarLink
    //а затем взять нужную переменную по access_get_int и прочим
    Module *get_module(QString module_id);

    //Получение переменных по link - то есть по имени модуля и названию в формате webcam1->image
    int get_int_by_link(QString link_str);
    float get_float_by_link(QString link_str);
    QString get_string_by_link(QString link_str);
    XcluObject *get_object_by_link(QString link_str);


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
    ProjectRunStateBinary state_ = ProjectRunStateBinaryStopped;

    QString project_folder_;

    QElapsedTimer elapsed_timer_;

};

extern ProjectRuntime RUNTIME;

#endif // PROJECTRUNTIME_H
