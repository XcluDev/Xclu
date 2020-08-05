#include <QApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "project.h"
#include "incl_qtcpp.h"
#include "modulesfactory.h"
#include "module.h"
#include "projectruntime.h"
#include "consoleview.h"

Project PROJ;

//---------------------------------------------------------------------
Project::Project()
{

}

//---------------------------------------------------------------------
ProjectProperties &Project::properties() {
    return properties_;
}

//---------------------------------------------------------------------
//Файл проекта был изменен - обновить рабочую папку для запуска
//если пустая строка - ставит на папку XCLU
void Project::update_project_folder(QString project_file) {
    if (project_file.isEmpty()) {
        RUNTIME.set_project_folder("");//qApp->applicationDirPath());
    }
    else {
        QFileInfo fileinfo(project_file);
        RUNTIME.set_project_folder(fileinfo.absolutePath());
    }
}



//---------------------------------------------------------------------
void Project::new_project() {
    close_project();
}

//---------------------------------------------------------------------
void Project::close_project() {
    properties().reset_name();
    update_project_folder("");
    clear_modules();

}

//---------------------------------------------------------------------
bool Project::save_project(QString file_name, SaveFormat format) {
    try {
        //записываем значения переменных из GUI
        gui_action(GuiStageProjectBeforeSaving);

        //запись файла проекта
        QFile saveFile(file_name);

        //QFile saveFile(format == Json
        //               ? QStringLiteral("save.json")
        //               : QStringLiteral("save.dat"));

        if (!saveFile.open(QIODevice::WriteOnly)) {
            xclu_exception("Couldn't open file for saving");
        }

        QJsonObject gameObject;
        write_json(gameObject);
        QJsonDocument saveDoc(gameObject);
        saveFile.write(format == Json
                       ? saveDoc.toJson()
                       : saveDoc.toBinaryData());

        update_project_folder(file_name);
    }
    catch(XCluException& e) {
        xclu_message_box("Can't save the project to '" + file_name + "':\n" + e.whatQt());
        return false;
    }
    return true;

}

//---------------------------------------------------------------------
Project::LoadProjectStatus Project::load_project(QString file_name, SaveFormat format) {
    try {
        xclu_assert(!RUNTIME.is_running(), "Please stop the current project before loading");
        close_project();

        //QFile loadFile(format == Json
        //               ? QStringLiteral("save.json")
        //               : QStringLiteral("save.dat"));
        QFile loadFile(file_name);

        if (!loadFile.open(QIODevice::ReadOnly)) {
            xclu_exception("Couldn't open file");
        }

        QByteArray saveData = loadFile.readAll();

        QJsonDocument loadDoc(format == Json
                              ? QJsonDocument::fromJson(saveData)
                              : QJsonDocument::fromBinaryData(saveData));

        xclu_assert(!loadDoc.isNull(), "Error parsing file");

        read_json(loadDoc.object());

        //GUI - выполняем настройки, но сейчас там ничего не делается - а делается на уровне PROJGUI (считывается выбранный модуль)
        gui_action(GuiStageProjectAfterLoading);
        update_names();
        update_project_folder(file_name);

    }
    catch(XCluException& e) {
        xclu_message_box("Can't load a project '" + file_name + "':\n" + e.whatQt());
        close_project();
        return LoadProjectStatusNo;
    }

    //Если успено загрузили - то, если были ошибки в консоли, то предупредим об этом
    if (!CONS_VIEW->is_empty()) {
        xclu_message_box("Some problems occured during loading the project.\nPlease see Console view for the details.");
        //возвращаем, что были warnings - чтобы PROJ поставил пометку, что проект был изменен - так как при сохранении он изменится
        return LoadProjectStatusWarnings;
    }
    return LoadProjectStatusOk;
}


//---------------------------------------------------------------------
//Запись и считывание проекта через json-объект
void Project::write_json(QJsonObject &json) {
    //Описание приложения
    QJsonObject appObject;
    appObject["name"] = QCoreApplication::instance()->applicationName();
    appObject["version"] = QCoreApplication::instance()->applicationVersion();
    json["application"] = appObject;

    //Свойства проекта
    QJsonObject propObject;
    properties().write_json(propObject);
    json["aproject_properties"] = propObject;  //"aproject...", а не просто "project..." - чтобы в тексте шло сверху, до modules

    //Модули
    QJsonArray modulesArray;
    for (int i=0; i<modules_.size(); i++) {
        QJsonObject moduleObject;
        modules_[i]->write_json(moduleObject);
        modulesArray.append(moduleObject);
    }
    json["modules"] = modulesArray;
}

//---------------------------------------------------------------------
void Project::read_json(const QJsonObject &json) {
    //Описание приложения - сейчас не нужно

    //Свойства проекта
    properties().read_json(json_object(json,"aproject_properties"));

    //Модули
    QJsonArray modulesArray = json_array(json, "modules");
    int n = modulesArray.size();
    for (int i=0; i<n; i++) {
         QJsonObject moduleObject = json_array_object(modulesArray, i);
        //получаем класс и версию модуля, а также имя - для обработки исключения
        QJsonObject descrObject = json_object(moduleObject, "description");
        QString class_name = json_string(descrObject, "class");
        QString version = json_string(descrObject, "version");
        QString name = json_string(descrObject, "name");

        //делаем перехват исключений, чтобы к ним добавить имя модуля
        //ошибки выводим в консоль и продолжаем загрузку проекта
        try {
            Module *module = FACTORY.create_unnamed_module(class_name, version);
            module->read_json(moduleObject);
            modules_.append(module);
        }
        catch(XCluException& e) {
            xclu_console_warning("Error loading module '" + name + "', class '" + class_name + "':\n    " +  e.whatQt());
        }
    }
    update_names();

}

//---------------------------------------------------------------------
void Project::clear_modules() {
    if (RUNTIME.is_running()) {
        xclu_halt("Internal error - command to clear project, but project is running");
    }
    for (int i=0; i<modules_.size(); i++) {
        delete modules_[i];
    }
    modules_.clear();
    update_names();
}

//---------------------------------------------------------------------
bool Project::update_names() {  //обновить все name - вызывается перед стартом проекта
    names_.clear();

    for (int i=0; i<modules_.size(); i++) {
        QString name = modules_[i]->name();
        if (name.isEmpty()) {
            xclu_message_box("Empty 'name' in module '" + modules_[i]->name() + "'");
            return false;
        }
        if (names_.contains(name)) {
            xclu_message_box("Duplicated 'name' in modules '" + modules_[i]->name() + "' and '" + modules_[names_[name]]->name() + "'");
            return false;
        }
        names_[name] = i;
    }
    return true;
}

//---------------------------------------------------------------------
//Выбор уникального имени - webcam1, webcam2,...
QString Project::generate_unique_name(QString name_hint, bool dont_change_if_ok) {
    update_names();

    if (dont_change_if_ok && !names_.contains(name_hint)) {
        return name_hint;
    }

    QString result;
    //бесконечный цикл
    for (int i=1;; i++) {
        QString name = name_hint + QString::number(i);
        if (!names_.contains(name)) {
            return name;
        }
    }
    return result;
}

//---------------------------------------------------------------------
QString Project::generate_unique_name_by_class_name(QString class_name) {
    auto *module = FACTORY.get_module(class_name);
    return generate_unique_name(module->description.name_hint);
}

//---------------------------------------------------------------------
//Cгенерировать модуль данного типа и сгенерировать ему уникальное имя type1, type2,...
Module *Project::new_module(int i, QString class_name, QString name_hint) {
    if (class_name.isEmpty()) {
        return nullptr;
    }

    //проверка, можно ли обновить все name, чтобы вычислить новое имя
    if (!update_names()) {
        return nullptr;
    }

    Module *module = nullptr;
    try {
        module = FACTORY.create_unnamed_module(class_name);
    }
    catch(XCluException& e) {
        xclu_message_box("Can't create module of class '" + class_name +"':\n" +  e.whatQt());
        return nullptr;
    }

    QString name = generate_unique_name(name_hint, true); //не менять имя, если такого нет
    module->set_name(name);
    modules_.insert(i, module);
    update_names();
    return module;
}

//---------------------------------------------------------------------
bool Project::can_rename_module(QString old_name, QString new_name) {
    if (new_name.isEmpty()) return false;
    if (new_name == old_name) {
        return true;
    }
    if (has_module_with_name(new_name)) return false;
    return true;
}

//---------------------------------------------------------------------
void Project::duplicate_module(int i) {
    QString new_nameid = generate_unique_name(modules_[i]->name());
    Module *module = modules_[i]->duplicate(new_nameid);
    if (!module) {
        //не выводим сообщение - так как описание ошибки выведет module
        return;
    }
    modules_.insert(i+1, module);
    update_names();
}

//---------------------------------------------------------------------
void Project::delete_module(int i) {
    //к этому моменту модуль уже отсоединен от GUI
    auto *module = modules_[i];
    modules_.remove(i);
    delete module;
    update_names();

}

//---------------------------------------------------------------------
void Project::rename_module(int i, QString new_name) {
    auto *modul = module_by_index(i);
    if (!modul) {
        xclu_halt("Can't rename module " + new_name);
        return;
    }
    modul->set_name(new_name);
    update_names();
}

//---------------------------------------------------------------------
void Project::swap_modules(int i) {   //i<->i+1
    xclu_assert(i>=0 && i+1<modules_count(), "Internal error, Project::swap_modules - bad index '" + QString::number(i) + "'");
    qSwap(modules_[i], modules_[i+1]);
    update_names();
}

//---------------------------------------------------------------------
int Project::modules_count() {
    return modules_.size();
}

//---------------------------------------------------------------------
bool Project::has_module_with_index(int i) {
    return i >= 0 && i < modules_count();
}

//---------------------------------------------------------------------
bool Project::has_module_with_name(QString name) {
    return names_.contains(name);
}

//---------------------------------------------------------------------
bool Project::has_module_with_id(QString name) {
    return names_.contains(name);
}


//---------------------------------------------------------------------
Module *Project::module_by_index(int i, bool can_return_null) {
    if (has_module_with_index(i)) {
        return modules_[i];
    }
    else {
        if (!can_return_null) {
            xclu_exception(QString("Requested module with bad index '%1'").arg(i));
        }
        return nullptr;
    }
}

//---------------------------------------------------------------------
Module *Project::module_by_name(QString name) {
    xclu_assert(has_module_with_name(name), QString("Requested module with unknown name '%1'").arg(name));
    return module_by_index(names_.value(name));
}

//---------------------------------------------------------------------
Module *Project::module_by_id(QString name) {
    xclu_assert(has_module_with_id(name), QString("Requested module with unknown name '%1'").arg(name));
    return module_by_index(names_.value(name));
}

//---------------------------------------------------------------------
//вычисление expressions и работа с GUI, см. определение GuiStage
//тут можно вызывать только GuiStageProjectAfterLoading и GuiStageProjectBeforeSaving
void Project::gui_action(GuiStage stage) {
    if (stage != GuiStageProjectAfterLoading && stage != GuiStageProjectBeforeSaving) {
        xclu_message_box("Internal error: Project::gui_action can be used only with project-related stages");
        return;
    }

    //записываем модули
    for (int i=0; i<modules_.size(); i++) {
        modules_[i]->gui_action(stage);
    }
}

//---------------------------------------------------------------------
//выполнить операцию для всех модулей
void Project::execute(ModuleExecuteStage stage, bool &stop_out) {
    for (int i=0; i<modules_count(); i++) {
        auto *module = modules_[i];
        //захватываем ошибки из модулей
        try{
            module->execute(stage);
            if (module->is_stop_out()) {
                stop_out = true;
                break;
            }
        }
        catch(XCluException& e) {
            stop_out = true;
            xclu_message_box("Runtime error in module '" +module->name() + "' at stage '" + ModuleExecuteStage_to_string(stage)
                         + "':\n" +  e.whatQt());
            break;
        }
    }
}

//---------------------------------------------------------------------
void Project::execute_start(bool &stop_out) {
    stop_out = false;
    if (RUNTIME.is_running()) {
        xclu_message_box("Internal error: project starting command, but it's already started");
        return;
    }

    //очистка консоли
    CONS_VIEW->clear();

    //начало измерения времени
    RUNTIME.reset_elapsed_timer();

    //Сбор name всех модулей - для парсинга в дальнейшем
    //очень важно это делать до modules_[i]->execute_start();
    //так как в них могут считаться expression в зависимости от name
    //и поэтому процедуру сбора name делаем до этого
    if (!update_names()) {    //он сам выдаст ошибку, поэтому здесь можно просто выйти
        stop_out = true;
    }

    //start
    if (!stop_out) {
        execute(ModuleExecuteStageStart, stop_out);
    }

    //запустились
    if (!stop_out) {
        RUNTIME.set_state(ProjectRunStateBinaryRunning);
    }

    //after_start
    if (!stop_out) {
        execute(ModuleExecuteStageAfterStart, stop_out);
    }
}

//---------------------------------------------------------------------
void Project::execute_update(bool &stop_out) {
    stop_out = false;
    xclu_assert(RUNTIME.is_running(), "Internal error: project update command, but not started");
    execute(ModuleExecuteStageUpdate, stop_out);
}

//---------------------------------------------------------------------
void Project::execute_stop() {
    //если уже остановлены - все равно считываем значения
    //поэтому это закомментировано:
    ////if (RUNTIME.is_stopped()) return;

    RUNTIME.set_state(ProjectRunStateBinaryStopped);

    bool stop_out = false;
    execute(ModuleExecuteStageBeforeStop, stop_out);
    execute(ModuleExecuteStageStop, stop_out);
}

//---------------------------------------------------------------------
