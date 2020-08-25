#ifndef MODULEINFO_H
#define MODULEINFO_H

//Информация о модуле:
//Имя, тип, версия модуля и его GUI
//Парсится из description.xgui и хранится в modules,
//но также может создаваться и меняться runtime в отдельном moduleinstance.
//Для скорости запуска, сначала парсятся только заголовки модуля
//А текст описания GUI считывается как строки, но сразу не парсится

#include "incl_h.h"
#include "moduledescription.h"

class ModuleInfo
{
public:
    //Загрузить модуль из папки. В случае ошибки - возвращает NULL
    //Если category_name и module_name непустые - они ставятся в категорию и имя модуля
    //(это полезно при загрузке встроенных модулей прямо из папок)
    static ModuleInfo* load_module(QString folder, QString category_name = "", QString module_name = "");

    //Загрузить GUI-файл, отбросив комментарии и сделать trim строк
    //применяется при считывании описания общей страницы General.
    static QStringList read_gui_file(QString file_name);

    ModuleInfo();

    //Загрузить информацию из папки
    //Если category_name и module_name непустые - они ставятся в категорию и имя модуля
    //(это полезно при загрузке встроенных модулей прямо из папок)
    void load_module_from_folder(QString folder, QString category_name = "", QString module_name = "");

    ModuleDescription description;

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

#endif // MODULEINFO_H
