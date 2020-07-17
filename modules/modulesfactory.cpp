#include "modulesfactory.h"
#include <QDirIterator>
#include "incl_qtcpp.h"
#include "moduleinfo.h"
#include "moduleinterface.h"
#include "rtmoduleregistrar.h"

ModulesFactory FACTORY;

//---------------------------------------------------------------------
ModulesFactory::ModulesFactory() {

}

//---------------------------------------------------------------------
ModulesFactory::~ModulesFactory() {
    //qDebug() << "ModulesFactory destructor:";
    QMapIterator<QString, ModuleInfo *> i(modules_);
    while (i.hasNext()) {
        i.next();
        //qDebug() << "    " << i.key() << ": " << i.value();
        delete i.value();
    }
}

//---------------------------------------------------------------------
void ModulesFactory::setup() {
    //qDebug("Listing modules:");

    //собираем встроенные модули
    QDirIterator categories(xclu::buildin_folder()); //, QDirIterator::Subdirectories);
    while (categories.hasNext()) {
        QString category_folder = categories.next();
        QString category_name = categories.fileName();
        if (category_name == "." || category_name == "..") continue;
        QDirIterator it(category_folder);
        while (it.hasNext()) {
            QString module_folder = it.next();
            QString module_name = it.fileName();
            if (module_name == "." || module_name == "..") continue;
            //обработка исключений проводится внутри
            auto *module_info = ModuleInfo::load_module(module_folder, category_name, module_name);
            if (module_info) {
                add_module(module_info);
            }
        }
    }

    //обновить список категорий
    update_categories();

    //тестовая печать
    //qDebug() << "Categories:";
    //for (int i=0; i<categories_.size(); i++) {
    //    qDebug() << "   " << categories_[i];
    //}
}

//---------------------------------------------------------------------
void ModulesFactory::add_module(ModuleInfo *module) {
    QString name = module->description.class_name;
    //qDebug() << "--- " << name;
    //Если модуль с таким именем уже есть - предупредить
    if (modules_.contains(name)) {
        xclu_console_warning("Warning: duplicated module '" + name + "'.");
    }
    else {
        modules_.insert(name, module);
    }
}

//---------------------------------------------------------------------
//Доступ к модулям
int ModulesFactory::size() {
    return names_.size();
}

//---------------------------------------------------------------------
ModuleInfo *ModulesFactory::get_module(int i) {
    if (i >= 0 && i < size()) {
        return modules_.value(names_[i]);
    }
    return nullptr;
}

//---------------------------------------------------------------------
ModuleInfo *ModulesFactory::get_module(QString class_name) {
    return modules_.value(class_name, nullptr);
}

//---------------------------------------------------------------------
//обновить список имен и категорий
void ModulesFactory::update_categories() {
    names_.clear();
    categories_.clear();
    modules_in_category_.clear();

    //сбор имен
    {
        QMapIterator<QString, ModuleInfo *> i(modules_);
        while (i.hasNext()) {
            i.next();
            names_.push_back(i.key());
        }
    }

    //qDebug() << "size " << size();

    //сбор категорий, и создание новой категории "All", содержащей все модули
    QString All = "All";
    for (int i=0; i<size(); i++) {
        auto *module = get_module(i);
        QString cat = module->description.category;
        QString name = module->description.class_name;
        modules_in_category_[cat].push_back(name);
        //категория "All"
        modules_in_category_[All].push_back(name);
    }

    //строим категории по-порядку, а All ставим впереди
    QMapIterator<QString, QVector<QString>> i(modules_in_category_);
    categories_.push_back(All);
    while (i.hasNext()) {
        i.next();
        QString cat_name = i.key();
        if (cat_name != All) {
            //заменяем подчеркивания на пробел "AI_Services" -> "AI Services"
            QString cat_name_with_spaces = xclu_remove_underscore(cat_name);
            categories_.push_back(cat_name_with_spaces);
        }
    }
}

//---------------------------------------------------------------------
//Доступ к категориям
int ModulesFactory::categories() {
    return categories_.size();
}

//---------------------------------------------------------------------
QString ModulesFactory::category_name(int i) {
    if (i >= 0 && i < categories()) {
        return categories_[i];
    }
    return "";
}

//---------------------------------------------------------------------
int ModulesFactory::category_size(int i) {
    if (i >= 0 && i < categories()) {
        return modules_in_category_[categories_[i]].size();
    }
    return 0;
}

//---------------------------------------------------------------------
QString ModulesFactory::category_module_type(int i, int j) {
    if (i >= 0 && i < categories()) {
        if (j >= 0 && j < category_size(i)) {
            return modules_in_category_[categories_[i]][j];
        }
    }
    return "";
}

//---------------------------------------------------------------------
//Создание модуля, но без имени
//version - не пустая при загрузке проекта из файла, можно проверять
Module *ModulesFactory::create_unnamed_module(QString class_name, QString /*version*/) {

    //если возникла ошибка парсинга - то выдастся исключение
    ModuleInfo *info = nullptr; //удалять не надо, это внешняя информация!
    RtModule *rtmodule_new = nullptr;
    Module *module_new = nullptr;
    try {
        //Получение информации
        info = get_module(class_name);
        xclu_assert(info, "Module class is unknown");

        //Загрузка
        rtmodule_new = RtModuleRegistrar::create_rt_module(info->description);
        xclu_assert(rtmodule_new, "Internal error: module implementation is not created");

        //Создание модуля
        module_new = new Module(info, rtmodule_new);
        return module_new;

    } catch(XCluException& e) {
        //в случае ошибки удаляем все, что создали
        if (module_new) {
            delete module_new;
        }
        else {
            //если модуль не был создан - то удаляем
            if (rtmodule_new) delete rtmodule_new;
        }
        //info удалять не надо, так как мы его не создавали

        //перенаправляем ошибку дальше
        xclu_exception(e.whatQt());
    }
    return nullptr;
}

//---------------------------------------------------------------------
