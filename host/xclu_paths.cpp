#include "xclu_paths.h"
#include <QCoreApplication>
#include <QApplication>
#include "incl_cpp.h"

//---------------------------------------------------------------------
QString xclu_app_folder() {
    return QCoreApplication::applicationDirPath();
}

QString xclu_settings_file() {
    return xclu_app_folder() + "/Xclu_settings.ini";
}


//---------------------------------------------------------------------
//корневая папка со встроенными ресурсами - например, Xclu_custom.ini
QString xclu_root_resources_folder() {
    return ":/";
}

//---------------------------------------------------------------------
//папка со встроенными ресурсами - темы, общие XGUI
//это файлы ресурсов, поэтому путь начинается с ":/"
QString xclu_builtin_resources_folder() {
    return  ":/builtin_resources/";
}

//---------------------------------------------------------------------
//папка с описанием встроенных модулей
//это файлы ресурсов, поэтому путь начинается с ":/"
QString xclu_builtin_modules_folder() {
#ifdef XCLU_DEPLOY
    //в режиме сборки Release-Deploy - это встроенные папки, и требуется добавить все в QRC
    //в в остальных режимах - это путь на диске
    return  ":/builtin_modules";
#else
    QFileInfo file("../Xclu/builtin_modules/");
    return file.canonicalFilePath();
#endif

}

//---------------------------------------------------------------------
//Файл с описанием интерфейса страницы General - добавляется во все модули
QString xclu_general_page_file() {
    return xclu_builtin_resources_folder() + "general_page" + xclu_XGUI_ext();
}

//---------------------------------------------------------------------
//Расширение файлов для описания интерфейса
QString xclu_XGUI_ext() {
    return ".xgui";
}

//---------------------------------------------------------------------
//Файл кастомных модулей
QString xclu_custom_modules_file() {
    return xclu_root_resources_folder() + "Xclu_custom.ini";
}


//---------------------------------------------------------------------
//h file template for modules
QString xclu_module_h_template_file() {
    return xclu_builtin_resources_folder() + "module_h_template.h";
}

//---------------------------------------------------------------------
