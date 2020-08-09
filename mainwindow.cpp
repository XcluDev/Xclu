#include <QtWidgets>

#include "mainwindow.h"
#include "project.h"
#include "incl_qtcpp.h"
#include "projectgui.h"
#include "projectruntime.h"
#include "xcluobjectimage.h"
#include "consoleview.h"
#include "dialogtestmoduleinterface.h"
#include "engines.h"

MainWindow *MAIN_WINDOW = nullptr;

//---------------------------------------------------------------------
/*static*/ MainWindow *MainWindow::main_window() {
    return MAIN_WINDOW;
}

//---------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();
    readSettings();
    MAIN_WINDOW = this;

    //тестирование
    //XcluImage_test();
}

//---------------------------------------------------------------------
MainWindow::~MainWindow()
{
}


//---------------------------------------------------------------------
void MainWindow::init() {
    setAttribute(Qt::WA_DeleteOnClose);
    setUnifiedTitleAndToolBarOnMac(true);
    //setMinimumSize(900, 800);
    resize(900,800);

    //Установка шрифта
    //auto font_ = font();
    //font_.setFamily(xclu::font_family_main());
    //setFont(font_);
    //Установка темы
    //XcluTheme::set_theme(this);

    isUntitled = true;
    run_state_ = ProjectRunStateLoading;

    createMenu();

    PROJ_GUI = new ProjectGui(nullptr, modulesMenu);

    //Layout
    //mainTabs = new QTabWidget;
    //mainTabs->addTab((QWidget *)PROJ_GUI, tr("Program"));
    //setCentralWidget(mainTabs);

    setCentralWidget(PROJ_GUI);

    //next will run setup
}

//---------------------------------------------------------------------
void MainWindow::setup() {   //запуск всех процессов
    //запуск движков - Python
    ENGINES.setup();

    //помечаем, что готовы к запуску
    set_state(ProjectRunStateStopped);

    //создаем новый проект
    //newProjectStartup();

    openProject()
}

//---------------------------------------------------------------------
//сигнал извне, из xclu_document_modified(), что проект был изменен
void MainWindow::set_document_modified() {
    if (!is_document_modified()) {
        setWindowModified(true);
        update_window_title();
    }
}

//---------------------------------------------------------------------
void MainWindow::reset_document_modified() {
    if (is_document_modified()) {
        setWindowModified(false);
        update_window_title();
    }
}

//---------------------------------------------------------------------
bool MainWindow::is_document_modified() {
    return isWindowModified();
}

//---------------------------------------------------------------------
void MainWindow::set_state(ProjectRunState run_state) {
    //Закомментировал проверку - так как при закрытии окна это событие может прийти параллельно с таймером
    //xclu_assert(run_state != run_state_, "Internal error - MainWindow::set_state the same state");
    if (run_state != run_state_) {
        run_state_ = run_state;
        update_window_state();
    }
}

//---------------------------------------------------------------------
bool MainWindow::is_stopped() {
    return (run_state_ == ProjectRunStateStopped);
}

//---------------------------------------------------------------------
QString MainWindow::stage_to_string() {
    QString stage;
    switch (run_state_) {
    case ProjectRunStateLoading: stage = tr("Loading");
        break;
    case ProjectRunStateStopped: stage = "";
        break;
    case ProjectRunStateStarting: stage = tr("Starting");
        break;
    case ProjectRunStateRunning: stage = tr("Running");
        break;
    case ProjectRunStateStopping: stage = tr("Stopping");
        break;
    default: break;
    }
    return stage;
}

//---------------------------------------------------------------------
//обновить заголовок окна и состояние элементов управления
void MainWindow::update_window_state() {
    //Управление элементами
    //редактирование разрешено только в режиме полной остановки
    bool editing = is_stopped();
    PROJ_GUI->set_editable(editing);

    //меню
    updateMenusVisible();

    //Заголовок окна
    update_window_title();
}

//---------------------------------------------------------------------
void MainWindow::update_window_title() {
    //Заголовок окна

    //XCLU - proj.xclu* - Running
    QString title = "Xclu";
    if (!projectFile.isEmpty()) {
        title.append(" - ");
        title.append(strippedName(projectFile));
    }
    //if (!stage.isEmpty()) title.append(" - " + stage);
    title.append("[*]");    //чтобы показывать, что документ изменен
    QString stage = stage_to_string();
    if (!stage.isEmpty()) {
        title.append(" - ");
        title.append(stage);
    }

    setWindowTitle(title);
}

//---------------------------------------------------------------------
void MainWindow::createMenu() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    //Project
    newAct = fileMenu->addAction(tr("&New Project"), this, &MainWindow::newProject);
    newAct->setShortcuts(QKeySequence::New);

    openAct = fileMenu->addAction(tr("&Open Project..."), this, &MainWindow::open);
    openAct->setShortcuts(QKeySequence::Open);

    saveAct = fileMenu->addAction(tr("&Save Project"), this, &MainWindow::save);
    saveAct->setShortcuts(QKeySequence::Save);

    saveAsAct = fileMenu->addAction(tr("Save Project &As..."), this, &MainWindow::saveAs);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);

    //Recent Files
    fileMenu->addSeparator();
    QMenu *recentMenu = fileMenu->addMenu(tr("Recent Projects..."));
    connect(recentMenu, &QMenu::aboutToShow, this, &MainWindow::updateRecentFileActions);
    recentFileSubMenuAct = recentMenu->menuAction();

    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActs[i] = recentMenu->addAction(QString(), this, &MainWindow::openRecentFile);
        recentFileActs[i]->setVisible(false);
    }

    recentFileSeparator = fileMenu->addSeparator();

    //Examples
    //fileMenu->addSeparator();
    examplesAct = fileMenu->addAction(tr("Examples..."), this, &MainWindow::examples);

    //Exit
    fileMenu->addSeparator();
    QAction *exitAct = fileMenu->addAction(tr("E&xit"), qApp, &QApplication::closeAllWindows);
    exitAct->setShortcuts(QKeySequence::Quit);
    //exitAct->setStatusTip(tr("Exit the application"));

    //Modules
    //будут заполнены в EditorModules
    modulesMenu = menuBar()->addMenu(tr("&Project"));


    //Run
    QToolBar *toolBar = addToolBar(tr("Run"));
    QMenu *runMenu = menuBar()->addMenu(tr("&Run"));

    const QIcon runIcon = QIcon::fromTheme("run", QIcon(xclu::builtin_icons_folder() + "run.png"));
    QAction *runAct = new QAction(runIcon, tr("&Run"), this);
    runAct->setStatusTip(tr("Run"));
    connect(runAct, SIGNAL (triggered()), this, SLOT (execute_run()));
    runMenu->addAction(runAct);
    toolBar->addAction(runAct);

    //Stop
    const QIcon stopIcon = QIcon::fromTheme("stop", QIcon(xclu::builtin_icons_folder() + "stop.png"));
    QAction *stopAct = new QAction(stopIcon, tr("&Stop"), this);
    stopAct->setStatusTip(tr("Stop"));
    connect(stopAct, SIGNAL (triggered()), this, SLOT (execute_stop()));
    runMenu->addAction(stopAct);
    toolBar->addAction(stopAct);

    //Developer
    QMenu *devMenu = menuBar()->addMenu(tr("Developer"));
    devMenu->addAction(tr("Test module interface..."), this, &MainWindow::dev_test_module_interface);


    //Help
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(tr("&About"), this, &MainWindow::about);

    //See SDI example for more menu items and working with Copy/Paste
}




//---------------------------------------------------------------------
void MainWindow::newProject() {
    if (!maybeSave()) return;
    CONS_VIEW->clear(); //очистка списка соощений

    newProjectStartup();
}

//---------------------------------------------------------------------
void MainWindow::newProjectStartup() {
    closeProject();
}

//---------------------------------------------------------------------
void MainWindow::closeProject() {
    if (RUNTIME.is_running()) return;

    PROJ_GUI->before_close_project();
    PROJ.new_project();
    PROJ_GUI->after_close_project();

    //устанавливает текущий файл в заголовок, а также сбрасывает флажок изменения проекта
    set_current_file(""); //поставится в Untitled с новым номером
}

//---------------------------------------------------------------------
void MainWindow::open() {
    if (!maybeSave()) return;
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Open Project"), "", "*.xclu");
    if (!fileName.isEmpty()) {
        openProject(fileName);
    }
}

//---------------------------------------------------------------------
bool MainWindow::save() {
    return isUntitled ? saveAs() : saveProject(projectFile);
}

//---------------------------------------------------------------------
bool MainWindow::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), projectFile, "*.xclu");
    if (fileName.isEmpty()) {
        return false;
    }
    return saveProject(fileName);
}

//---------------------------------------------------------------------
void MainWindow::examples() {

}

//---------------------------------------------------------------------
void MainWindow::about() {
    QMessageBox::about(this, tr("About XCLU"),
                       tr("<b>XCLU</b> is a module-based system for creating production-ready applications"
                          " for art and technology."));
}

//---------------------------------------------------------------------
void MainWindow::dev_test_module_interface() {
    //диалог тестирования XGUI создаваемых модулей
    DialogTestModuleInterface::call_dialog(this);
}

//---------------------------------------------------------------------
void MainWindow::readSettings() {

}

//---------------------------------------------------------------------
void MainWindow::writeSettings() {

}

//---------------------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent *event)
{
    //Запись проекта, если требуется
    if (maybeSave()) {
        //Запись состояния
        writeSettings();
        //Остановка проекта
        immediate_stop();
        //Подтверждение выхода
        event->accept();
    } else {
        event->ignore();
    }
}

//---------------------------------------------------------------------
bool MainWindow::maybeSave() {
    if (!is_document_modified()) {
        return true;
    }

    QMessageBox msgBox;
    //msgBox.setText(tr("Xclu"));//setInformativeText
    msgBox.setText(tr("The project has been modified.\n"
                      "Do you want to save your changes?"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);

    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

//---------------------------------------------------------------------
//загрузить файл проекта
//предполагается, что до этого вызван maybeSave()
void MainWindow::openProject(const QString &fileName) {
    closeProject();
    auto load_result = PROJ.load_project(fileName);
    if (load_result != Project::LoadProjectStatusNo) {
        PROJ_GUI->after_load_project();
        //устанавливает текущий файл в заголовок, а также сбрасывает флажок изменения проекта
        set_current_file(fileName);
        //если были warnings при загрузке - то, ставим флажок изменения проекта, так как при сохранении он изменится
        if (load_result == Project::LoadProjectStatusWarnings) {
            xclu_document_modified();
        }
    }
}

//---------------------------------------------------------------------
bool MainWindow::saveProject(const QString &fileName) {
    PROJ_GUI->before_save_project();
    if (PROJ.save_project(fileName)) {
        //устанавливает текущий файл в заголовок, а также сбрасывает флажок изменения проекта
        set_current_file(fileName);
        //statusBar()->showMessage(tr("File saved"), 2000);
        return true;
    }
    return false;
}

//---------------------------------------------------------------------
QStringList MainWindow::readRecentFiles(QSettings &settings)
{
    QStringList result;
    const int count = settings.beginReadArray(SettingsKey::recentProjects());
    for (int i = 0; i < count; ++i) {
        settings.setArrayIndex(i);
        result.append(settings.value(SettingsKey::file()).toString());
    }
    settings.endArray();
    return result;
}

//---------------------------------------------------------------------
void MainWindow::writeRecentFiles(const QStringList &files, QSettings &settings)
{
    const int count = files.size();
    settings.beginWriteArray(SettingsKey::recentProjects());
    for (int i = 0; i < count; ++i) {
        settings.setArrayIndex(i);
        settings.setValue(SettingsKey::file(), files.at(i));
    }
    settings.endArray();
}

//---------------------------------------------------------------------
bool MainWindow::hasRecentFiles() {
    //QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    XCLU_SETTINGS
    const int count = settings.beginReadArray(SettingsKey::recentProjects());
    settings.endArray();
    return count > 0;
}

//---------------------------------------------------------------------
void MainWindow::prependToRecentFiles(const QString &fileName) {
    //QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    XCLU_SETTINGS

    const QStringList oldRecentFiles = readRecentFiles(settings);
    QStringList recentFiles = oldRecentFiles;
    recentFiles.removeAll(fileName);
    recentFiles.prepend(fileName);
    if (oldRecentFiles != recentFiles)
        writeRecentFiles(recentFiles, settings);

    updateMenusVisible();
}


//---------------------------------------------------------------------
void MainWindow::updateRecentFileActions() {
    //QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    XCLU_SETTINGS

    const QStringList recentFiles = readRecentFiles(settings);
    const int count = qMin(int(MaxRecentFiles), recentFiles.size());
    int i = 0;
    for ( ; i < count; ++i) {
        const QString fileName = strippedName(recentFiles.at(i));
        recentFileActs[i]->setText(tr("&%1 %2").arg(i + 1).arg(fileName));
        recentFileActs[i]->setData(recentFiles.at(i));
        recentFileActs[i]->setVisible(true);
    }
    for ( ; i < MaxRecentFiles; ++i)
        recentFileActs[i]->setVisible(false);
}

//---------------------------------------------------------------------
void MainWindow::openRecentFile() {
    if (const QAction *action = qobject_cast<const QAction *>(sender())) {
        if (!maybeSave()) return;
        openProject(action->data().toString());
    }
}

//---------------------------------------------------------------------
void MainWindow::updateMenusVisible() {
    bool visible = is_stopped();

    newAct->setVisible(visible);
    openAct->setVisible(visible);
    //saveAct->setVisible(visible);
    //saveAsAct->setVisible(visible);
    examplesAct->setVisible(visible);

    bool recent_visible = MainWindow::hasRecentFiles() && visible;
    recentFileSubMenuAct->setVisible(recent_visible);
    recentFileSeparator->setVisible(recent_visible);
}

//---------------------------------------------------------------------
//устанавливает текущий файл в заголовок, а также сбрасывает флажок изменения проекта
void MainWindow::set_current_file(const QString &fileName) {
    static int sequenceNumber = 1;

    isUntitled = fileName.isEmpty();
    if (isUntitled) {
        projectFile = tr("Untitled%1.xclu").arg(sequenceNumber++);
    } else {
        //Внимание, эта функция дает непустую строку только если файл существует.
        projectFile = QFileInfo(fileName).canonicalFilePath();
    }

    if (!isUntitled && windowFilePath() != projectFile)
        MainWindow::prependToRecentFiles(projectFile);

    setWindowFilePath(projectFile);

    //снять флажок, что проект был изменен
    reset_document_modified();

    //обновить заголовок и состояние элементов управления
    update_window_state();
}

//---------------------------------------------------------------------
QString MainWindow::strippedName(const QString &fullFileName) {
    return QFileInfo(fullFileName).fileName();
}

//---------------------------------------------------------------------
void MainWindow::execute_run() {
    qDebug("execute_run");

    if (run_state_ == ProjectRunStateStopped) {
        set_state(ProjectRunStateStarting);

        //создаем таймер
        if (!timer) {
            timer = new QTimer(this);
            timer->setTimerType(Qt::PreciseTimer);
            connect(timer, &QTimer::timeout, this, &MainWindow::execute_update);
        }

        //запускаем таймер
        float FPS = PROJ.properties().frame_rate;
        int delay = int(1000.0/FPS);
        timer->start(delay);
    }
}

//---------------------------------------------------------------------
void MainWindow::execute_stop() {
    qDebug("execute_stop");
    if (run_state_ == ProjectRunStateStarting || run_state_ == ProjectRunStateRunning) {
        set_state(ProjectRunStateStopping);
    }
}

//---------------------------------------------------------------------
//немедленная остановка
void MainWindow::immediate_stop() {
    if (run_state_ != ProjectRunStateStopped) {
        timer->stop();
        //остановка вычислений
        PROJ.execute_stop();
        set_state(ProjectRunStateStopped);
    }
}

//---------------------------------------------------------------------
//эта функция вызывается таймером
void MainWindow::execute_update() {
    //идет запуск
    if (run_state_ == ProjectRunStateStarting) {
        bool stopped;
        //пробуем стартовать программу
        PROJ.execute_start(stopped);

        if (!stopped) {
            //запуск успешный, продолжаем работу
            set_state(ProjectRunStateRunning);
            return; //чтобы обновился заголовок
        }
        else {
            //останавливаем все - по факту, это произойдет на следующем шаге таймера
            set_state(ProjectRunStateStopping);
            return; //чтобы обновился заголовок
        }
    }

    //если сигнал остановки - то останавливаем таймер и интерпретатор
    if (run_state_ == ProjectRunStateStopping) {
        immediate_stop();
        return;
    }

    //осуществление вычислений
    if (run_state_ == ProjectRunStateRunning) {
        bool stopped;
        PROJ.execute_update(stopped);
        //если по какой-то причине останов - то посылаем сигнал остановки
        if (stopped) {
            emit execute_stop();
        }
    }
}

//---------------------------------------------------------------------

