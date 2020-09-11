#ifndef SETTINGSKEYS_H
#define SETTINGSKEYS_H

//Настройки приложения и ключи для записи настроек
#include <QString>
#include <QSettings>
#include "xclu_paths.h"

class QWindow;
class QMainWindow;

class Settings {
public:
    //Взятие и получение строки
    static QString gets(QString key, QString def = "");
    static void sets(QString key, QString value);
    static int geti(QString key, int def = 0);
    static void seti(QString key, int value);

    //Конкретные ключи
    static QString key_main_window() { return "main_window"; }

    //Диалог добавления модуля
    static QString dialogaddmodule_tab() { return "dialogaddmodule/tab"; }

    //Диалог тестирования GUI новых модулей
    static QString dialogtestmodule_folder() { return "dialogtestmodule/folder"; }
    static QString dialogtestmodule_tab() { return "dialogtestmodule/tab"; }

    //Основное окно
    static QString recentProjects() { return QStringLiteral("recent_projects"); }
    static QString file() { return QStringLiteral("file"); }

    static QString lastProjectFile() { return "app/last_project_file"; }
    static QString lastProjectFolder() { return "app/last_project_folder"; }

    //запись/восстановление окна
    static void save_window(QString window_name, QMainWindow *win);
    static void load_window(QString window_name, QMainWindow *win);
};

//Настройки приложения из файла xclu_settings_file()
//В документации указано, что создание Settings происходит мгновенно
//Хотя у нас сохранение в кастомный файл.
//Также, важно что для мгновенного сброса настроек можно использовать метод sync()
//Мы сейчас делаем макрос, который создает локально QSettings settings
//Использование: XCLU_SETTINGS
#define XCLU_SETTINGS QSettings settings(xclu_settings_file(), QSettings::IniFormat);


#endif // SETTINGSKEYS_H
