#include "projectruntime.h"
#include "incl_cpp.h"
#include "project.h"
#include "interfaceitem.h"
#include "xcluobject.h"

ProjectRuntime RUNTIME;

//---------------------------------------------------------------------
//Работа с link - получение переменных по имени модуля и названию в формате webcam1->image
VarLink::VarLink(QString link_str) {
    auto query = link_str.trimmed().split("->");
    xclu_assert(query.size() == 2
                && !query.at(0).isEmpty()
                && !query.at(1).isEmpty(),
                "Bad link '" + link_str + "', expected in format webcam1->image");
    module = query.at(0);
    var = query.at(1);
};


//---------------------------------------------------------------------
ProjectRuntime::ProjectRuntime()
{

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
//Получение модуля
Module *ProjectRuntime::get_module(QString module_id) {
    return PROJ.module_by_id(module_id);
}

//---------------------------------------------------------------------
//Получение переменных по link
int ProjectRuntime::get_int_by_link(QString link_str) {
    VarLink link(link_str);
    return RUNTIME.get_module(link.module)->access_get_int(link.var);
}

//---------------------------------------------------------------------
float ProjectRuntime::get_float_by_link(QString link_str) {
    VarLink link(link_str);
    return RUNTIME.get_module(link.module)->access_get_float(link.var);
}

//---------------------------------------------------------------------
QString ProjectRuntime::get_string_by_link(QString link_str) {
    VarLink link(link_str);
    return RUNTIME.get_module(link.module)->access_get_string(link.var);
}

//---------------------------------------------------------------------
XcluObject *ProjectRuntime::get_object_by_link(QString link_str) {
    VarLink link(link_str);
    return RUNTIME.get_module(link.module)->access_get_object(link.var);
}


//---------------------------------------------------------------------
/*InterfaceItem *ProjectRuntime::get_var_by_link(QString link_str) {
    VarLink link(link_str);
    Module *module = get_module(link.module);
    return module->interf()->var(link.var);
}*/

//---------------------------------------------------------------------
/*XcluObject *ProjectRuntime::get_object_by_link(QString link_str) {
    VarLink link(link_str);
    Module *module = get_module(link.module);
    return module->access_get_object(link.var);
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
}

//---------------------------------------------------------------------
double ProjectRuntime::elapsed_time_sec() {   //время в секундах, прошедшее от запуска проекта
    return elapsed_timer_.elapsed() * 0.001;
}

//---------------------------------------------------------------------

