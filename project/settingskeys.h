#ifndef SETTINGSKEYS_H
#define SETTINGSKEYS_H

//Ключи для записи настроек QSettings
#include <QString>

class SettingsKey
{
public:
    static QString dialogaddmodule_tab() { return "dialogaddmodule/tab"; }
    static QString dialogtestmodule_folder() { return "dialogtestmodule/folder"; }
    static QString dialogtestmodule_tab() { return "dialogtestmodule/tab"; }

    static QString recentProjects() { return QStringLiteral("recent_projects"); }
    static QString file() { return QStringLiteral("file"); }

};

#endif // SETTINGSKEYS_H
