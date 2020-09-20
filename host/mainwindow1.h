#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QMainWindow>
#include <QTimer>
#include "incl_h.h"

QT_BEGIN_NAMESPACE
class QWidget;
class QAction;
class QMenu;
class QMenuBar;
class QSettings;
QT_END_NAMESPACE

namespace Ui {
class MainWindow1;
}

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(QWidget *parent = nullptr);
    ~MainWindow1();

    static MainWindow1 *main_window();   //эта функция используется для передачи изменений проекта из xclu_document_modified()

    //сигнал извне, из xclu_document_modified(), что проект был изменен
    void set_document_modified();
    void reset_document_modified();
    bool is_document_modified();

private:
    Ui::MainWindow1 *ui;


    void init();
    void setup_internal();   //запуск всех процессов - считывание списка модулей, открытие проекта

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

private:
    //обновить заголовок окна и состояние элементов управления
    void update_window_state();
    void update_window_title();
    void updateMenusVisible();
    QString stage_to_string();

    void newProjectStartup();
    void closeProject();
    bool saveProject();
    bool saveAsProject();

    //устанавливает текущий файл в заголовок, а также сбрасывает флажок изменения проекта
    void set_current_file(const QString &fileName);

    //папка для операций открытия проекта - в начале ставится из последней папки проекта, а затем ""
    QString open_projects_folder_;

    //показать диалог сохранения проекта, если он был изменен
    bool maybeSave();

    //загрузить файл проекта
    //предполагается, что до этого вызван maybeSave()
    void openProject(const QString &fileName);

    //сохранить файл проекта
    bool saveProject(const QString &fileName);

    void readSettings();
    void writeSettings();

private:
    //работа с недавними файлами
    enum { MaxRecentFiles = 5 };
    static bool hasRecentFiles();
    void prependToRecentFiles(const QString &fileName);
    static QStringList readRecentFiles(QSettings &settings);
    static void writeRecentFiles(const QStringList &files, QSettings &settings);

    static QString strippedName(const QString &fullFileName);

    QAction *recentFileActs[MaxRecentFiles];

    QString projectFile;
    bool isUntitled = true;

    void updateRecentFileActions();
    void openRecentFile();

private:
    //Execution
    void execute_run();
    void execute_stop();    //остановка, но когда вызовет таймер
    void immediate_stop();    //немедленная остановка таймера и проекта

    ProjectRunState run_state_ = ProjectRunStateLoading;
    void set_state(ProjectRunState run_state);
    bool is_stopped();

    QTimer *timer = 0;
    int timer_fps_ = -1;
    //эта функция вызывается таймером
    void execute_update();



};

#endif // MAINWINDOW1_H
