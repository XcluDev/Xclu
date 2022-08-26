#ifndef PROJECTCORE_H
#define PROJECTCORE_H

//Project core - set of modules and properties.

#include <QJsonObject>
#include "incl_h.h"
#include "xmodule.h"
#include "projecteditorprops.h"



class Project
{
public:
    Project();

    //Свойства проекта
    ProjectEditorProperties &properties();

    //Создание, запись и загрузка проекта
    enum SaveFormat {
        Json, Binary
    };
    void close_project();
    void new_project();
    bool save_project(QString file_name, SaveFormat format = Json);

    enum LoadProjectStatus : int {
        LoadProjectStatusNo = 0,
        LoadProjectStatusOk = 1,
        LoadProjectStatusWarnings = 2
    };

    LoadProjectStatus load_project(QString file_name, SaveFormat format = Json);


    //Compile links and all other needed to check errors
    //Also clears console
    bool compile();

    //Runtime
    void execute_start(bool &stop_out);
    void execute_update(bool &stop_out);
    void execute_stop();    

    //Runtime-состояние проекта - см. XCORE

    //Модули
    //Выбор уникального имени - webcam1, webcam2,...
    QString generate_unique_name(QString name_hint, bool dont_change_if_ok = false);
    QString generate_unique_name_by_class_name(QString class_name);

    //Сгенерировать модуль данного типа с заданным именем, если оно уже есть - добавить 1,2,3...
    XModule *new_module(int i, QString class_name, QString name_hint);


    void duplicate_module(int i);
    void delete_module(int i);
    void rename_module(int i, QString new_name);
    void swap_modules(int i);   //i<->i+1

    //число модулей
    int modules_count();
    //проверка, есть ли запрашиваемый модуль
    bool has_module_with_index(int i);
    bool has_module_with_name(QString name);

    // Search module by index or name
    XModule *find_module_by_index(int i, bool can_return_null = false);
    XModule *find_module_by_name(QString name);

    // Find modules by a filter
    // 'accept_calls_filter', 'send_calls_filter', 'type_filter' are parts of name,
    // if XCallType::None or if empty - it means "all" for a given filter
    QVector<XModule *> find_modules_by_filter(XCallType accept_calls_filter = XCallType::None,
                                             XCallType send_calls_filter = XCallType::None,
                                             QString class_filter = "",
                                             bool require_enabled = true);

    bool can_rename_module(QString old_name, QString new_name);

    //работа с name модулей
    //обновить все name - вызывается перед стартом проекта и при переименовании,
    //выдает message_box при ошибке (пустое name или повторяющееся name). Возвращает true - если без ошибок
    bool update_names();

private:
    //Свойства проекта
    ProjectEditorProperties properties_;

    //Модули
    QVector<XModule *> modules_;
    void clear_modules();

    //Execute operation for all modules
    //"exception_on_errors" - if true, any module error stops, if false - only prints to console
    //for example, stopping - always print to console only
    void execute(ModuleExecuteStage stage, bool &stop_out, bool exception_on_errors = true);

    //Запись и считывание проекта через json-объект
    void write_json(QJsonObject &json);
    void read_json(const QJsonObject &json);

    //обновить имена - следует делать после загрузки проекта и добавления/удаления/переименования/изменения порядка модулей
    QMap<QString, int> names_;

    //вычисление expressions и работа с GUI, см. определение GuiStage
    //тут можно вызывать только GuiStageProjectAfterLoading и GuiStageProjectBeforeSaving
    void gui_action(GuiStage stage);

    //Файл проекта был изменен - обновить рабочую папку для запуска
    //если пустая строка - ставит на папку XCLU
    void update_project_folder(QString project_file);


};

extern Project PROJECT;

#endif //PROJECTCORE_H
