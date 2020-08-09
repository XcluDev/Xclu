#include "xclu_paths.h"
#include <QCoreApplication>

//---------------------------------------------------------------------
QString xclu_app_folder() {
    return QCoreApplication::applicationDirPath();
}

QString xclu_settings_file() {
    return xclu_app_folder() + "/Xclu_settings.ini";
}


//---------------------------------------------------------------------
