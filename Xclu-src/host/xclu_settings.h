#pragma once

// Настройки приложения и ключи для записи настроек
// TODO Считывать настройки приложения в память единожды
// - завести один settings, а не создавать каждый раз
// А также, можно завести структуру (с макросом) для всех параметров
#include <QString>
#include <QSettings>
#include "xc_paths.h"
#include "int2.h"

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

    // Размеры основного окна
    static QString key_main_window() { return "main_window"; }

    //Диалог добавления модуля
    static QString dialogaddmodule_tab() { return "dialogaddmodule/tab"; }
    static QString dialogaddmodule_show_implemented() { return "dialogaddmodule/show_implemented"; }

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

    //View
    //XGuiComp - Show Components Names
    static QString key_show_components_names() { return "view/show_components_names"; }
    static bool get_xguicomp_show_components_names();

    // Размеры thumbnail в XObject
    //static QString xobject_thumb_w() { return "xobject/thumb_w"; }
    //static QString xobject_thumb_h() { return "xobject/thumb_h"; }
    static int2 get_xobject_thumb_size(); // TODO сделать считывание из настроек
};

//Настройки приложения из файла xc_settings_file()
//В документации указано, что создание Settings происходит мгновенно
//Хотя у нас сохранение в кастомный файл.
//Также, важно что для мгновенного сброса настроек можно использовать метод sync()
//Мы сейчас делаем макрос, который создает локально QSettings settings
//Использование: XCLU_SETTINGS
#define XCLU_SETTINGS QSettings settings(xc_settings_file(), QSettings::IniFormat);

