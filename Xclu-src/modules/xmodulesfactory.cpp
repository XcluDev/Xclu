#include "xmodulesfactory.h"
#include <QDirIterator>
#include "incl_cpp.h"
#include "xmoduleprototype.h"
#include "xmoduleinterface.h"
#include "registrarxclass.h"

XModulesFactory FACTORY;

//---------------------------------------------------------------------
XModulesFactory::XModulesFactory() {

}

//---------------------------------------------------------------------
XModulesFactory::~XModulesFactory() {
    //qDebug() << "XModulesFactory destructor:";
    QMapIterator<QString, XModulePrototype *> i(modules_);
    while (i.hasNext()) {
        i.next();
        //qDebug() << "    " << i.key() << ": " << i.value();
        delete i.value();
    }
}

//---------------------------------------------------------------------
void XModulesFactory::setup() {
    //qDebug("Listing modules:");

    //собираем встроенные модули
    QDirIterator categories(xc_builtin_modules_folder()); //, QDirIterator::Subdirectories);
    while (categories.hasNext()) {
        QString category_folder = categories.next();
        QString category_name = categories.fileName();
        if (category_name == "." || category_name == "..") continue;
        QDirIterator it(category_folder);
        while (it.hasNext()) {
            QString module_folder = it.next();
            QString module_name = it.fileName();
            if (module_name == "." || module_name == "..") continue;
            add_module(module_name, module_folder, category_name);
        }
    }

    //считывание кастомных модулей
    QStringList custom_names, custom_folders;
    QString custom_category = "Custom";
    read_custom_modules(custom_names, custom_folders);
    for (int i=0; i<custom_names.size(); i++) {
        add_module(custom_names[i], custom_folders[i], custom_category);
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
//считывание кастомных модулей из файла
//#------------------------------------------
//#Custom modules list
//#------------------------------------------
//[windows]
//module1=CosmoVibro
//module1_folder=D:/eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt

//[linux]
//module1=CosmoVibro
//module1_folder=~/Desktop/Cosmo/Cosmovibro/CosmovibroRt
//#------------------------------------------

void XModulesFactory::read_custom_modules(QStringList &names, QStringList &folders) {
    names.clear();
    folders.clear();

    QString file_name = xc_custom_modules_file();
    xc_assert(QFileInfo::exists(file_name), "Can't find list of custom modules `" + file_name + "`");

    QSettings settings(file_name, QSettings::IniFormat);

    int max_n = 100;    //Параметр, сколько кастомных файлов

    //определение секции по ОС
#ifdef XCLU_WINDOWS
    QString section = "windows";
#endif
#ifdef XCLU_LINUX
    QString section = "unix";
#endif


    for (int i=1; i<=max_n; i++) {
        //module1
        QString key_name = QString("%1/module%2").arg(section).arg(i);
        //module1_folder
        QString key_folder = QString("%1/module%2_folder").arg(section).arg(i);
        QString name = settings.value(key_name, "").toString();
        QString folder = settings.value(key_folder, "").toString();

        //if deployment mode, then get folder from Modules folder
        folder = xc_custom_module_folder(name, folder);

        if (!name.isEmpty() && !folder.isEmpty()) {
            names.push_back(name);
            folders.push_back(folder);
        }
    }

}

//---------------------------------------------------------------------
void XModulesFactory::add_module(QString module_name, QString module_folder, QString category_name) {
    //обработка исключений проводится внутри load_module
    auto *module = XModulePrototype::load_module(module_folder, category_name, module_name);
    if (module) {
        QString name = module->description.class_name;
        //qDebug() << "--- " << name;
        //Если модуль с таким именем уже есть - предупредить
        if (modules_.contains(name)) {
            xc_console_warning("Warning: duplicated module '" + name + "'.");
        }
        else {
            modules_.insert(name, module);
        }
    }
}

//---------------------------------------------------------------------
//Доступ к модулям
int XModulesFactory::size() {
    return names_.size();
}

//---------------------------------------------------------------------
XModulePrototype *XModulesFactory::get_module(int i) {
    if (i >= 0 && i < size()) {
        return modules_.value(names_[i]);
    }
    return nullptr;
}

//---------------------------------------------------------------------
XModulePrototype *XModulesFactory::get_module(QString class_name) {
    xc_assert(modules_.contains(class_name), "Internal error at XModulesFactory::get_module, unknown module class '" + class_name + "'");
    return modules_.value(class_name, nullptr);
}

//---------------------------------------------------------------------
//обновить список имен и категорий
void XModulesFactory::update_categories() {
    names_.clear();
    categories_.clear();
    modules_in_category_.clear();

    //сбор имен
    {
        QMapIterator<QString, XModulePrototype *> i(modules_);
        while (i.hasNext()) {
            i.next();
            names_.push_back(i.key());
        }
    }

    //qDebug() << "size " << size();

    //сбор категорий, и создание новой категории "All", содержащей все модули
    QString All = All_Category_Name();
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
            QString cat_name_with_spaces = xc_remove_underscore(cat_name);
            categories_.push_back(cat_name_with_spaces);
        }
    }
}

//---------------------------------------------------------------------
//Доступ к категориям
int XModulesFactory::categories() {
    return categories_.size();
}

//---------------------------------------------------------------------
QString XModulesFactory::category_name(int i) {
    if (i >= 0 && i < categories()) {
        return categories_[i];
    }
    return "";
}

//---------------------------------------------------------------------
int XModulesFactory::category_size(int i) {
    if (i >= 0 && i < categories()) {
        return modules_in_category_[categories_[i]].size();
    }
    return 0;
}

//---------------------------------------------------------------------
QString XModulesFactory::category_module_type(int i, int j) {
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
XModule *XModulesFactory::create_unnamed_module(QString class_name, QString /*version*/) {

    //если возникла ошибка парсинга - то выдастся исключение
    XModulePrototype *info = nullptr; //удалять не надо, это внешняя информация!
    XClass *rtmodule_new = nullptr;
    XModule *module_new = nullptr;
    try {
        //Получение информации
        info = get_module(class_name);
        xc_assert(info, "XModule class is unknown");

        //Загрузка
        rtmodule_new = RegistrarXClass::create_rt_module(info->description);
        xc_assert(rtmodule_new, "Internal error: module implementation is not created");

        //Создание модуля
        module_new = new XModule(info, rtmodule_new);
        return module_new;

    } catch(XException& e) {
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
        xc_exception(e.whatQt());
    }
    return nullptr;
}

//---------------------------------------------------------------------
