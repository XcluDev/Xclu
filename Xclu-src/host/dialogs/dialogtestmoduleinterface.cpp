#include "qt_widgets.h"

#include "dialogtestmoduleinterface.h"
#include "incl_cpp.h"
#include "project.h"
#include "xmoduleprototype.h"
#include "xmoduleinterface.h"
#include "xguieditor.h"
#include "exportinterface.h"

DialogTestModuleInterface *D_TEST_MODULE_INTERFACE = nullptr;

//---------------------------------------------------------------------
//Call this function for working with dialog
/*static*/ void DialogTestModuleInterface::call_dialog(QWidget *parent) {
    //Внимание, тут parent только один раз задается
    if (!D_TEST_MODULE_INTERFACE) {
        D_TEST_MODULE_INTERFACE = new DialogTestModuleInterface(parent);
    }
    auto *dialog = D_TEST_MODULE_INTERFACE;
    dialog->exec();
}

//---------------------------------------------------------------------
DialogTestModuleInterface::DialogTestModuleInterface(QWidget *parent)
    : QDialog(parent)
{
    //Кнопки для выбора файла
    QPushButton *load_button;
    QPushButton *reload_button;
    QPushButton *export_button;

    QWidget *buttonBox = xclu::hwidget(0,
                                       load_button = new QPushButton(tr("Load...")), 0,
                                       reload_button = new QPushButton(tr("Reload")),0,
                                       new QLabel(""), 5,
                                       export_button = new QPushButton(tr("Export .h file")),0
                                       );
    export_button->setToolTip("Create h file with interface description.");

    xclu::set_font_size(buttonBox, xclu::main_font_size);

    connect(load_button, &QPushButton::released, this, &DialogTestModuleInterface::pressed_load);
    connect(reload_button, &QPushButton::released, this, &DialogTestModuleInterface::pressed_reload);
    connect(export_button, &QPushButton::released, this, &DialogTestModuleInterface::pressed_export_h);

    //Выбор файла
    QGroupBox *control_group = new QGroupBox(tr("Module folder"));
    control_group->setLayout(xclu::vlayout(-1,
                                           folder_edit_ = new QPlainTextEdit(), 0,
                                           buttonBox, 0)
                             );
    //устанавливаем шрифт
    xclu::set_font_size(control_group, xclu::main_font_size);

    int font_spacing = folder_edit_->fontMetrics().lineSpacing();
    int hmin = font_spacing * 4;    //TODO Параметр минимальное число строк
    folder_edit_->setMinimumHeight(hmin);
    folder_edit_->setMaximumHeight(hmin);

    //Редактор параметров
    editor_ = new XGuiEditor(nullptr);

    //Сборка layout диалога
    setLayout(xclu::vlayout(-1,
                           control_group, 0,
                           editor_, 10
                            )
              );

    //Заголовок
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("Test module interface"));

    resize(600,720);

    load_button->setFocus();

    //Cчитывание запомненного пути из настроек приложения
    //QSettings settings;
    QString last_folder = Settings::gets(Settings::dialogtestmodule_folder(), "");

    //TODO - сейчас dialogtestmodule_tab не ставится!!!
    if (!last_folder.isEmpty()) {
        int last_tab  = Settings::geti(Settings::dialogtestmodule_tab(), 0);
        load_module(last_folder, last_tab);
    }


}

//---------------------------------------------------------------------
void DialogTestModuleInterface::pressed_load() {
    QString dir = folder_edit_->toPlainText();
    QString folder = QFileDialog::getExistingDirectory(this, tr("Choose module folder"),
                                                    dir,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    if (!folder.isEmpty()) {
        load_module(folder);
    }
}

//---------------------------------------------------------------------
void DialogTestModuleInterface::pressed_reload() {
    //перезагружаем и показываем ту же вкладку
    int tab_index = 0; //tabs->currentIndex();
    reload(tab_index);
}

//---------------------------------------------------------------------
void DialogTestModuleInterface::pressed_export_h() {
    try {
        xc_assert(interf_.data(), "No module loaded");
        xc_console_append("Exporting to `" + folder_ + "`");
        ExportInterface exporter;
        exporter.export_to_h_file(interf_.data(), folder_);
    }
    catch(XException& e) {
        xc_message_box("Error during export: " + e.whatQt());
    }
}

//---------------------------------------------------------------------
void DialogTestModuleInterface::load_module(QString folder, int tab_index) {
    folder_edit_->setPlainText(folder);
    reload(tab_index);
}

//---------------------------------------------------------------------
void DialogTestModuleInterface::clear() {
    if (interf_.data()) {
        interf_.data()->gui_detached();
        interf_.reset();
    }
    module_seed_.reset();
}

//---------------------------------------------------------------------
void DialogTestModuleInterface::reload(int /*tab_index*/) {
    clear();

    folder_ = folder_edit_->toPlainText();
    if (folder_.isEmpty()) {
        xc_message_box("Please choose module folder");
        return;
    }
    if (!xc_folder_exists_abspath(folder_)) {
        xc_message_box("Folder doesn't exists: '" + folder_ + "'");
        return;
    }

    //запись папки в настройки
    Settings::sets(Settings::dialogtestmodule_folder(), folder_);

    //загрузка описания модуля
    //если там ошибка - он выдаст на экран сообщение
    module_seed_.reset(XModulePrototype::load_module(folder_, "Category is not set", "Name is not set"));
    if (!module_seed_.data()) return;

    //могут возникнуть исключения - поэтому, отлавливаем их
    try {
        //загрузка интерфейса модуля
        interf_.reset(new XModuleInterface(*module_seed_.data()));
        if (!interf_.data()) return;

        //загружаем GUI и устанавливаем видимость
        bool force_propagate_visibility = true;
        editor_->load_module(module_seed_.data(), interf_.data(), "Name...", force_propagate_visibility);
    }
    catch (XException &e) {
        xc_message_box(e.whatQt());
        clear();
    }
}

//---------------------------------------------------------------------

