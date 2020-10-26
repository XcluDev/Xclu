#include "qt_widgets.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "project.h"
#include "incl_cpp.h"
#include "projectgui.h"
#include "xcore.h"
#include "xcluobjectimage.h"
#include "consoleview.h"
#include "dialogtestmoduleinterface.h"
#include "exportinterface.h"

MainWindow *MAIN_WINDOW = nullptr;

//---------------------------------------------------------------------
/*static*/ MainWindow *MainWindow::window() {
    return MAIN_WINDOW;
}

//---------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //recent files
    recent_.reset(new RecentFiles(ui->menuRecent_Projects));

    MAIN_WINDOW = this;

    init();
    readSettings();

    setup_internal();
}

//---------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
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

    PROJ_GUI = new ProjectGui(nullptr, ui->menuProject);

    setCentralWidget(PROJ_GUI);

}

//---------------------------------------------------------------------
void MainWindow::setup_internal() {   //запуск всех процессов
    //помечаем, что готовы к запуску
    set_state(ProjectRunStateStopped);

    //ставим папку для первого открытия проекта из последней папки сохраненного проекта
    open_projects_folder_ = Settings::gets(Settings::lastProjectFolder());

    //открываем последний проект, если он есть
    QString last_project = Settings::gets(Settings::lastProjectFile());
    bool loaded = false;
    if (!last_project.isEmpty()) {
        QFileInfo file(last_project);
        if (file.exists() && file.isFile()) {
            openProject(last_project);
            loaded = true;
        }
    }
    //иначе - создаем новый проект
    if (!loaded) {
        newProjectStartup();
    }

}

//---------------------------------------------------------------------
//Функция, которая вызывается при закрытии окна
void MainWindow::closeEvent(QCloseEvent *event) {
    //Запись проекта, если требуется
    if (maybeSave()) {
        //Запись состояния - делаем до остановки, чтобы в случае ошибки все равно записалось
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
void MainWindow::on_actionNew_Project_triggered()
{
    if (!maybeSave()) return;

    xclu_console_append("New project");
    newProjectStartup();
}

//---------------------------------------------------------------------
void MainWindow::newProjectStartup() {
    closeProject();
}

//---------------------------------------------------------------------
void MainWindow::closeProject() {
    if (XCORE.is_running()) return;

    xclu_console_clear();//очистка списка сообщений

    PROJ_GUI->before_close_project();
    PROJ.new_project();
    PROJ_GUI->after_close_project();

    XCORE.reset_fps_autostart();  //сброк предыдущего FPS и aurostart

    //устанавливает текущий файл в заголовок, а также сбрасывает флажок изменения проекта
    set_current_file(""); //поставится в Untitled с новым номером

}


//---------------------------------------------------------------------
void MainWindow::on_actionOpen_Project_triggered()
{
    if (!maybeSave()) return;

    //Берем папку открытия проектов - она нужна только при первом открытии, а затем будет использоваться предыдущая
    QString folder = open_projects_folder_;
    open_projects_folder_ = "";

    const QString fileName = QFileDialog::getOpenFileName(this, tr("Open Project"), folder, "*.xclu");
    if (!fileName.isEmpty()) {
        openProject(fileName);
    }
}

//---------------------------------------------------------------------
bool MainWindow::saveProject() {
    return isUntitled ? saveAsProject() : saveProject(projectFile);
}

//---------------------------------------------------------------------
void MainWindow::on_actionSave_Project_triggered()
{
    saveProject();
}

//---------------------------------------------------------------------
bool MainWindow::saveAsProject() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), projectFile, "*.xclu");
    if (fileName.isEmpty()) {
        return false;
    }
    return saveProject(fileName);
}

//---------------------------------------------------------------------
void MainWindow::on_actionSave_Project_As_triggered() {
    saveAsProject();
}

//---------------------------------------------------------------------
void MainWindow::on_actionExit_triggered()
{
    qApp->closeAllWindows();
}

//---------------------------------------------------------------------
void MainWindow::on_actionTest_Module_Interface_triggered()
{
    //диалог тестирования XGUI создаваемых модулей
    DialogTestModuleInterface::call_dialog(this);
}

//---------------------------------------------------------------------
void MainWindow::on_actionUpdate_auto_h_files_for_all_modules_triggered()
{
    try {
        xclu_console_append("Updating auto.h files for all modules...");
        ExportInterface exporter;
        exporter.export_all_builtin_h_files();
        xclu_console_append("Updating finished");
    }
    catch(XException& e) {
        xclu_message_box("Error during export: " + e.whatQt());
    }
}

//---------------------------------------------------------------------
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About XCLU"),
                       tr("<b>XCLU</b> is a module-based system for creating production-ready applications"
                          " for art and technology."));
}

//---------------------------------------------------------------------
void MainWindow::on_actionRun_triggered()
{
    execute_run();
}

//---------------------------------------------------------------------
void MainWindow::on_actionStop_triggered()
{
    execute_stop();
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
        title.append(QFileInfo(projectFile).fileName());
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
        return saveProject();
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
    bool dirty = false; //не помечаем, что в консоли есть ошибки, а просто сообщение
    xclu_console_append("Loading project `" + fileName + "`", dirty);
    xclu_console_append("", dirty);

    auto load_result = PROJ.load_project(fileName);
    if (load_result != Project::LoadProjectStatusNo) {
        PROJ_GUI->after_load_project();
        //устанавливает текущий файл в заголовок, а также сбрасывает флажок изменения проекта
        set_current_file(fileName);
        //если были warnings при загрузке - то, ставим флажок изменения проекта, так как при сохранении он изменится
        if (load_result == Project::LoadProjectStatusWarnings) {
            xclu_document_modified();
        }

        //Если требуется - автозапуск проекта
        if (XCORE.get_autostart()) {
            execute_run();
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
void MainWindow::readSettings() {
    Settings::load_window(Settings::key_main_window(), this);

    ui->actionShow_Component_Names->setChecked(Settings::is_show_components_names());
}

//---------------------------------------------------------------------
void MainWindow::writeSettings() {
    Settings::save_window(Settings::key_main_window(), this);
}

//---------------------------------------------------------------------
void MainWindow::updateMenusVisible() {
    bool visible = is_stopped();


    ui->actionNew_Project->setVisible(visible);
    ui->actionOpen_Project->setVisible(visible);

    //bool recent_visible = MainWindow::hasRecentFiles() && visible;
    //ui->menuFile->setVisible(recent_visible);
    //ui->menuRecent_Projects->setVisible(recent_visible);
}

//---------------------------------------------------------------------
//устанавливает текущий файл в заголовок, а также сбрасывает флажок изменения проекта
void MainWindow::set_current_file(const QString &fileName) {
    static int sequenceNumber = 1;

    isUntitled = fileName.isEmpty();
    if (isUntitled) {
        projectFile = tr("Untitled%1.xclu").arg(sequenceNumber++);
    } else {
        //Внимание, эта функция дает непустую строку, только если файл существует.
        projectFile = QFileInfo(fileName).canonicalFilePath();
    }

    if (!isUntitled) {
        //запомнить файл проекта, чтобы его потом открыть
        Settings::sets(Settings::lastProjectFile(), projectFile);

        //запомнить папку проекта, чтобы от нее затем начинать Open Project
        QString folder = QFileInfo(projectFile).canonicalPath();
        Settings::sets(Settings::lastProjectFolder(), folder);

        //добавить в список недавно открытых файлов
        if (windowFilePath() != projectFile) {
            recent_->prependToRecentFiles(projectFile);
        }
    }

    setWindowFilePath(projectFile);


    //снять флажок, что проект был изменен
    reset_document_modified();

    //обновить заголовок и состояние элементов управления
    update_window_state();
}


//---------------------------------------------------------------------
void MainWindow::on_actionCompile_triggered()
{
    //compile links and all other needed to check errors
    PROJ.compile();
}

//---------------------------------------------------------------------
void MainWindow::execute_run() {
    qDebug("execute_run");

    if (run_state_ == ProjectRunStateStopped) {
        set_state(ProjectRunStateStarting);

        //вызываем "setup" модулей - чтобы сработали модули и установили время для FPS
        execute_update();

        //создаем таймер - теперь FPS есть
        if (!timer) {
            timer = new QTimer(this);
            timer->setTimerType(Qt::PreciseTimer);
            connect(timer, &QTimer::timeout, this, &MainWindow::execute_update);
        }

        //вычисляем частоту обновления
        //float FPS = PROJ.properties().frame_rate;
        int frame_rate = XCORE.get_frame_rate();
        xclu_assert(frame_rate>1 && frame_rate<120, QString("Bad frame rate %1").arg(frame_rate));
        //запускаем таймер
        int delay = int(1000.0/frame_rate); //TODO вообще, при больших частотах будет вызываться неравномерно.
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
void MainWindow::on_actionShow_Component_Names_triggered(bool checked)
{
    Settings::seti(Settings::key_show_components_names(), checked);
    PROJ_GUI->on_changed_show_components_names(checked);
}

//---------------------------------------------------------------------
void MainWindow::on_actionLinks_Editor_triggered()
{
    PROJ_GUI->show_links_editor();
}

//---------------------------------------------------------------------
