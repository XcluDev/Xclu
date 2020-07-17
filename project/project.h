#ifndef PROJECT_H
#define PROJECT_H

//Проект - работает с инстансами модулей и вычислениями,
//без графического интерфейса.

#include <QJsonObject>
#include "incl_qt.h"
#include "module.h"
#include "projectproperties.h"



class Project
{
public:
    Project();

    //Свойства проекта
    ProjectProperties &properties();

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


    //Runtime
    void execute_start(bool &stop_out);
    void execute_update(bool &stop_out);
    void execute_stop();    

    //Runtime-состояние проекта - см. RUNTIME

    //Модули
    //Сгенерировать модуль данного типа и сгенерировать ему уникальное имя type1, type2,...
    Module *new_module(int i, QString class_name);

    void duplicate_module(int i);
    void delete_module(int i);
    void rename_module(int i, QString new_name);
    void swap_modules(int i);   //i<->i+1

    //число модулей
    int modules_count();
    //проверка, есть ли запрашиваемый модуль
    bool has_module_with_index(int i);
    bool has_module_with_name(QString name);
    bool has_module_with_id(QString id);
    //получение модуля
    Module *module_by_index(int i, bool can_return_null = false);
    Module *module_by_name(QString name);
    Module *module_by_id(QString id);

    bool can_rename_module(QString old_name, QString new_name);

    //работа с id модулей
    //обновить все id - вызывается перед стартом проекта и при переименовании,
    //выдает message_box при ошибке (пустое id или повторяющееся id). Возвращает true - если без ошибок
    bool update_ids();

private:
    //Свойства проекта
    ProjectProperties properties_;

    //Модули
    QVector<Module *> modules_;
    void clear_modules();

    //Запуск
    //выполнить операцию для всех модулей
    void execute(ModuleExecuteStage stage, bool &stop_out);

    //Запись и считывание проекта через json-объект
    void write_json(QJsonObject &json);
    void read_json(const QJsonObject &json);

    //Выбор уникального имени, начинающегося с id_hint - id_hint1, id_hint2,...


    ModuleNameAndId generate_unique_name_and_id(const ModuleDescription &descr);


    //обновить имена - следует делать после загрузки проекта и добавления/удаления/переименования/изменения порядка модулей
    void update_names();
    QMap<QString, int> names;
    //id, см. update_ids()
    QMap<QString, int> ids_;

    //вычисление expressions и работа с GUI, см. определение GuiStage
    //тут можно вызывать только GuiStageProjectAfterLoading и GuiStageProjectBeforeSaving
    void gui_action(GuiStage stage);

    //Файл проекта был изменен - обновить рабочую папку для запуска
    //если пустая строка - ставит на папку XCLU
    void update_project_folder(QString project_file);


};

extern Project PROJ;

#endif
