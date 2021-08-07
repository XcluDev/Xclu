#include "xc_paths.h"
#include <QCoreApplication>
#include <QApplication>
#include "incl_cpp.h"

//---------------------------------------------------------------------
QString xc_app_folder() {
    return QCoreApplication::applicationDirPath();
}

QString xc_settings_file() {
    return xc_app_folder() + "/Xclu_settings.ini";
}


//---------------------------------------------------------------------
//корневая папка со встроенными ресурсами - например, Xclu_custom.ini
QString xc_root_resources_folder() {
    return ":/";
}

//---------------------------------------------------------------------
//папка со встроенными ресурсами - темы, общие XGUI
//это файлы ресурсов, поэтому путь начинается с ":/"
QString xc_builtin_resources_folder() {
    return  ":/builtin_resources/";
}

//---------------------------------------------------------------------
//папка с описанием встроенных модулей
//это файлы ресурсов, поэтому путь начинается с ":/"
QString xc_builtin_modules_folder() {
#ifdef XCLU_DEPLOY
    //в режиме сборки Release-Deploy - это встроенные папки, и требуется добавить все в QRC
    //в в остальных режимах - это путь на диске
    return  ":/builtin_modules/";
#else
    QFileInfo file("../Xclu/builtin_modules/");
    return file.canonicalFilePath();
#endif

}

//---------------------------------------------------------------------
//transforms folder to modules/{name} folder if deployment mode
QString xc_custom_module_folder(QString name, QString folder) {
#ifdef XCLU_DEPLOY
    return  xc_app_folder() + "/Modules/" + name;
#else
    return folder;
#endif

}

//---------------------------------------------------------------------
//Файл с описанием интерфейса страницы General - добавляется во все модули
QString xc_general_page_file() {
    return xc_builtin_resources_folder() + "general_page" + xc_XGUI_ext();
}

//---------------------------------------------------------------------
//Расширение файлов для описания интерфейса
QString xc_XGUI_ext() {
    return ".xgui";
}

//---------------------------------------------------------------------
//Файл кастомных модулей
QString xc_custom_modules_file() {
    return xc_root_resources_folder() + "Xclu_custom.ini";
}


//---------------------------------------------------------------------
//h file template for modules
QString xc_module_h_template_file() {
    return xc_builtin_resources_folder() + "module_h_template.h";
}

//---------------------------------------------------------------------
