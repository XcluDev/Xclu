#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static MainWindow *main_window();   //эта функция используется для передачи изменений проекта из xclu_document_modified()

    void setup();   //запуск всех процессов - считывание списка модулей, открытие проекта

    //сигнал извне, из xclu_document_modified(), что проект был изменен
    void set_document_modified();
    void reset_document_modified();
    bool is_document_modified();

protected:
    //Функция, которая вызывается при закрытии окна
    void closeEvent(QCloseEvent *event) override;

    void init();
    //Menu
    void createMenu();

    //QMenuBar *menuBar;
    QMenu *fileMenu;    
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *examplesAct;
    QAction *exitAction;

    QMenu *modulesMenu;

    //обновить заголовок окна и состояние элементов управления
    void update_window_state();
    void update_window_title();
    void updateMenusVisible();
    QString stage_to_string();

private slots:
    void newProject();
    void newProjectStartup();
    void open();
    bool save();
    bool saveAs();
    void closeProject();
    void examples();

    void updateRecentFileActions();
    void openRecentFile();
    void about();

    //Developer
    //диалог тестирования XGUI создаваемых модулей
    void dev_test_module_interface();

private:
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

    //работа с недавними файлами
    enum { MaxRecentFiles = 5 };
    static bool hasRecentFiles();
    void prependToRecentFiles(const QString &fileName);
    static QStringList readRecentFiles(QSettings &settings);
    static void writeRecentFiles(const QStringList &files, QSettings &settings);

    static QString strippedName(const QString &fullFileName);

    QAction *recentFileActs[MaxRecentFiles];
    QAction *recentFileSeparator;
    QAction *recentFileSubMenuAct;

    QString projectFile;
    bool isUntitled = true;

    //Execution
private slots:
    void execute_run();
    void execute_stop();    //остановка, но когда вызовет таймер
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
#endif // MAINWINDOW_H
