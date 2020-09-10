#ifndef XCLU_PATHS_H
#define XCLU_PATHS_H

//Пути к папке приложения, файл настроек
#include <QString>

//Папка приложения
QString xclu_app_folder();

//Путь к файлу настроек
QString xclu_settings_file();

//корневая папка со встроенными ресурсами - например, Xclu_custom.ini
QString xclu_root_resources_folder();

//папка со встроенными ресурсами - темы, общие XGUI
QString xclu_builtin_resources_folder();
//папка с описанием встроенных модулей
QString xclu_builtin_modules_folder();

//Файл кастомных модулей
QString xclu_custom_modules_file();

//Файл с описанием интерфейса страницы General - добавляется во все модули
QString xclu_general_page_file();

//Расширение файлов для описания интерфейса
QString xclu_XGUI_ext();

#endif // XCLU_PATHS_H
