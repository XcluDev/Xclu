#ifndef MODULESFACTORY_H
#define MODULESFACTORY_H

//База данных модулей, позволяет создавать инстансы модулей
#include "sdk_h.h"
#include "moduleseed.h"
#include "module.h"


class ModulesFactory
{
public:
    ModulesFactory();
    virtual ~ModulesFactory();

    //Имя категории All - используется как Default-значение при считывании настроек
    static QString All_Category_Name() { return "All"; }

    //Загружает модули из папки builtinmodules
    void setup();

    //Доступ к категориям
    int categories();
    QString category_name(int i);
    int category_size(int i);
    QString category_module_type(int i, int j);

    //Доступ к модулям
    int size();
    ModuleSeed *get_module(int i);
    ModuleSeed *get_module(QString class_name);

    //Создание модуля, но без имени
    //version - не пустая при загрузке проекта из файла, можно проверять
    //в случае ошибки генерирует xclu-исключение
    //info_out - информация о модуле, чтобы еще дополнительно использовать
    Module *create_unnamed_module(QString class_name, QString version = "");

    //строки описания страницы General
    QStringList general_page();

private:
    //считывание кастомных модулей
    void read_custom_modules(QStringList &names, QStringList &folders);

    void add_module(QString module_name, QString module_folder, QString category_name);

    QMap<QString, ModuleSeed *> modules_;

    //имена (типы) всех модулей
    QVector<QString> names_;

    //обновить список категорий
    void update_categories();

    //имена категорий
    QVector<QString> categories_;

    //имена модулей в категории
    QMap<QString, QVector<QString>> modules_in_category_;


};

extern ModulesFactory FACTORY;

#endif // MODULESFACTORY_H
