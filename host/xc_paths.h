#ifndef XC_PATHS_H
#define XC_PATHS_H

//Пути к папке приложения, файл настроек
#include <QString>

//Папка приложения
QString xc_app_folder();

//Путь к файлу настроек
QString xc_settings_file();

//корневая папка со встроенными ресурсами - например, Xclu_custom.ini
QString xc_root_resources_folder();

//папка со встроенными ресурсами - темы, общие XGUI
QString xc_builtin_resources_folder();
//папка с описанием встроенных модулей
QString xc_builtin_modules_folder();

//transforms folder to modules/{name} folder if deployment mode
QString xc_custom_module_folder(QString name, QString folder);

//Файл кастомных модулей
QString xc_custom_modules_file();

//h file template for modules
QString xc_module_h_template_file();


//Файл с описанием интерфейса страницы General - добавляется во все модули
QString xc_general_page_file();

//Расширение файлов для описания интерфейса
QString xc_XGUI_ext();

#endif // XC_PATHS_H
