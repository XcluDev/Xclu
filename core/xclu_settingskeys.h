#ifndef SETTINGSKEYS_H
#define SETTINGSKEYS_H

//Объект QSettings с настройками приложения и ключи для записи настроек
#include <QString>
#include <QSettings>

class SettingsKey
{
public:
    static QString dialogaddmodule_tab() { return "dialogaddmodule/tab"; }
    static QString dialogtestmodule_folder() { return "dialogtestmodule/folder"; }
    static QString dialogtestmodule_tab() { return "dialogtestmodule/tab"; }

    static QString recentProjects() { return QStringLiteral("recent_projects"); }
    static QString file() { return QStringLiteral("file"); }

    //QScopedPointer<QSettings> settings_;


};

//Настройки приложения из файла xclu_settings_file()
//В документации указано, что создание Settings происходит мгновенно
//Хотя у нас сохранение в кастомный файл.
//Также, важно что для мгновенного сброса настроек можно использовать метод sync()
//Мы сейчас делаем макрос, который создает локально QSettings settings
//Использование: XCLU_SETTINGS
#define XCLU_SETTINGS QSettings settings(xclu_settings_file(), QSettings::IniFormat);


#endif // SETTINGSKEYS_H
