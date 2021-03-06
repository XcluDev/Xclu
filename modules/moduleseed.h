#ifndef MODULESEED_H
#define MODULESEED_H

//Информация о модуле:
//Имя, тип, версия модуля и его GUI в виде строк
//Парсится из description.xgui и хранится в modules,
//но также может создаваться и меняться runtime в отдельном moduleinstance.
//Для скорости запуска, сначала парсятся только заголовки модуля
//А текст описания GUI считывается как строки, но сразу не парсится

#include "incl_h.h"
#include "moduledescription.h"

//TODO can be optimized loading of the project.
//No the interface is parsed each time when createing a module.


class ModuleSeed
{
public:
    //Загрузить модуль из папки. В случае ошибки - возвращает NULL
    //Если category_name и module_name непустые - они ставятся в категорию и имя модуля
    //(это полезно при загрузке встроенных модулей прямо из папок)
    static ModuleSeed* load_module(QString folder, QString category_name = "", QString module_name = "");

    //Загрузить GUI-файл, отбросив комментарии и сделать trim строк
    //применяется при считывании описания общей страницы General.
    static QStringList read_gui_file(QString file_name);

    ModuleSeed();

    //Загрузить информацию из папки
    //Если category_name и module_name непустые - они ставятся в категорию и имя модуля
    //(это полезно при загрузке встроенных модулей прямо из папок)
    void load_module_from_folder(QString folder, QString category_name = "", QString module_name = "");

    ModuleDescription description;

    //Module folder
    QString folder() { return folder_; }

    //строки с описанием GUI, не включающие описание модуля, пустые и комментарии
    //так же, с добавлением General Page
    QStringList gui_lines() const;

    //Help-файл в разметке Markdown, возможно, с HTML-тэгами
    QString help();

private:
    QString folder_;
    QString description_file_;

    //парсинг GUI
    QStringList gui_lines_;

    //Help
    //мы считываем его при необходимости, при первом обращении к help(), и затем храним
    bool help_was_read_ = false;
    QString help_;



};

#endif // MODULESEED_H
