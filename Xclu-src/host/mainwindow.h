#pragma once

#include <QTimer>
#include "incl_h.h"
#include "recentfiles.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QWidget;
class QAction;
class QMenu;
class QMenuBar;
class QSettings;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

#define XCLU_VERSION "1.173"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent, QString startupRelProjectPath);
    virtual ~MainWindow();

    static MainWindow *window();   //эта функция используется для передачи изменений проекта из xc_document_modified()

    //сигнал извне, из xc_document_modified(), что проект был изменен
    void set_document_modified();
    void reset_document_modified();
    bool is_document_modified();

private:
    Ui::MainWindow *ui;

    void init();
    void setup_internal(QString startupRelProjectPath);   //запуск всех процессов - считывание списка модулей, открытие проекта

    //Функция, которая вызывается при закрытии окна
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_actionNew_Project_triggered();
    void on_actionOpen_Project_triggered();
    void on_actionSave_Project_triggered();
    void on_actionSave_Project_As_triggered();
    void on_actionExit_triggered();
    void on_actionTest_Module_Interface_triggered();
    void on_actionUpdate_auto_h_files_for_all_modules_triggered();
    void on_actionAbout_triggered();
    void on_actionRun_triggered();
    void on_actionStop_triggered();

    void on_actionShow_Component_Names_triggered(bool checked);

    void on_actionLinks_Editor_triggered();

    void on_actionCompile_triggered();

private:
    //обновить заголовок окна и состояние элементов управления
    void update_window_state();
    void update_window_title();
    QString stage_to_string();

    void newProjectStartup();
    void closeProject();
    bool saveProject();
    bool saveAsProject();

    //устанавливает текущий файл в заголовок, а также сбрасывает флажок изменения проекта
    void set_current_file(const QString &fileName);

    //папка для операций открытия проекта - в начале ставится из последней папки проекта, а затем ""
    QString open_projects_folder_;

public:
    //показать диалог сохранения проекта, если он был изменен
    bool maybeSave();

    //загрузить файл проекта
    //предполагается, что до этого вызван maybeSave()
    void openProject(const QString &fileName);

    //сохранить файл проекта
    bool saveProject(const QString &fileName);

    void updateMenusVisible();

    void readSettings();
    void writeSettings();

private:
    //Recent files
    QScopedPointer<RecentFiles> recent_;

    //Project name
    QString projectFile;
    bool isUntitled = true;

    //Execution
    void execute_run();
    void execute_stop();    //остановка, но когда вызовет таймер
public:
    void immediate_stop();    //немедленная остановка таймера и проекта
private:
    ProjectRunState run_state_ = ProjectRunStateLoading;
    void set_state(ProjectRunState run_state);
    bool is_stopped();

    QTimer *timer = 0;
    int timer_fps_ = -1;
    //эта функция вызывается таймером
    void execute_update();

};

