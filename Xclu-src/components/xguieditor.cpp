#include "qt_widgets.h"
#include "xguieditor.h"
#include "project.h"
#include "incl_cpp.h"
#include "xguipage.h"
#include "visibilitygroups.h"
#include "componentcontextmenu.h"
#include "componentcontextmenu.h"

//---------------------------------------------------------------------
XGuiEditor::XGuiEditor(QWidget *parent)
    :QWidget(parent)
{
    //Редактор параметров
    editor_frame_ = new QGroupBox("");

    editor_frame_->setLayout(xclu::vlayout(-1,
                                           editor_label_ = new QLabel(""), 0,
                                           tabs = new QTabWidget(), 0)
                             );
    editor_label_->hide();  //скрываем Label - чтобы в DialogTestModuleInterface он не занимал место

    //устанавливаем шрифт
    xclu::set_font_size(editor_frame_, xclu::main_font_size);
    xclu::set_font_size(tabs, xclu::main_font_size);

    //Редактор одного выделенного параметра
    /*paramEditor = new QGroupBox("Enabled - Edit");
    //устанавливаем шрифт
    xclu::set_font_size(paramEditor, xclu::main_font_size);

    QGridLayout *editorgrid = new QGridLayout();
    paramEditor->setLayout(editorgrid);

    QCheckBox *exprCheckbox = new QCheckBox(tr("Expression"));
    QLineEdit *exprEdit = new QLineEdit("");
    editorgrid->addWidget(exprCheckbox,0,0);
    editorgrid->addWidget(exprEdit,0,1);
    QPushButton *promoteButton = new QPushButton(tr("Promote")); //Promote to window
    editorgrid->addWidget(promoteButton,1,0);
    */

    //общий layout
    this->setLayout(xclu::vlayout(0,
                                  editor_frame_,10
                                  ));

    //track changes
    //using tabBarClicked instead currentChanged, because currentChanged fires ad creating project
    connect(tabs, SIGNAL (tabBarClicked(int)), this, SLOT (on_value_changed()));
    //connect(tabs, SIGNAL (currentChanged(int)), this, SLOT (on_value_changed()));

}

//---------------------------------------------------------------------
//сигнал, что модуль сменился и нужно загрузить новый модуль
void XGuiEditor::changed_module_selection(int i) {
    bool can_return_null = true;
    XModule *module = PROJECT.find_module_by_index(i, can_return_null);
    if (module != module_) {
        //qDebug() << "Load params editor for module " << i;
        load_module(module);
    }
}

//---------------------------------------------------------------------
//сигнал, что модуль был переименован
void XGuiEditor::renamed_module() {
    reload_name();
}

//---------------------------------------------------------------------
XModule *XGuiEditor::module() {
    return module_;
}

//---------------------------------------------------------------------
void XGuiEditor::reload_name() { //обновить имя и класс модуля, использует moddule_. Если его нет - скрывает Label
    if (module_) {
        QString title = QString("%1: %2")
                .arg(module_->name()).
                //arg(module_->name()).
                arg(module_->description().class_name);
                //.arg(ModuleRunMode_to_string(module_->xmodule()->run_mode()));
        editor_label_->setText(title);

        //XModule description to tip
        editor_label_->setToolTip(module_->description().description);

        editor_label_->show();
    }
    else {
        editor_label_->setText("");
        editor_label_->setToolTip("");
        editor_label_->hide();
    }
}

//---------------------------------------------------------------------
void XGuiEditor::before_close_project() {
    detach();
}

//---------------------------------------------------------------------
void XGuiEditor::after_close_project() {

}

//---------------------------------------------------------------------
void XGuiEditor::detach() {
    if (module_) {
        //отключаем от модуля
        module_->gui_action(GuiStageBeforeGuiDetached);
        module_->gui_detached();
    }
    module_ = nullptr;

    for (int i=0; i<items_.size(); i++) {
        delete items_[i];
    }
    items_.clear();

    tabs->clear();
    reload_name();
}

//---------------------------------------------------------------------
//создать GUI модуля
void XGuiEditor::load_module(XModule *module) {
    //detach popup menu
    ComponentContextMenu::COMP_MENU()->clear();

    //detach module
    if (!module) {
        detach();
        return;
    }

    //Создание GUI-элементов
    //внимание - тут делается detach, поэтому module_ ставится в nullptr, и поэтому его надо ставить после
    //force_propagate_visibility тут false, так как обновление видимости сделает module->gui_attached(this);
    bool force_propagate_visibility = false;
    load_module(module->info(), module->interf(), module->name(), force_propagate_visibility);

    //Информируем модуль, что подключились
    module->gui_attached(this);

    //Загружаем значения из переменных в GUI
    module->gui_action(GuiStageAfterGuiAttached);

    //запоминаем модуль - он нужен в load_module для reload_name
    module_ = module;

    //Ставим имя в заголовок группы
    reload_name(); //Внимание: этой функции нужен module_, если его нет - то label будет скрыта
}

//---------------------------------------------------------------------
//создать GUI только для интерфейса - например, для отладки интерфейсов
//force_propagate_visibility - нужно ли сделать обновление видимости.
//для вызовов из load_module(XModule *module) - это не нужно, так как там сработает module->gui_action(GuiStageAfterGuiAttached);
//но для кастомного применения, например, тестирования интерфейса - это нужно

void XGuiEditor::load_module(XModulePrototype *info, XModuleInterface *interf, QString module_name, bool force_propagate_visibility) {
    detach();   //внимание - тут делается detach, поэтому module_ ставится в nullptr

    //XModuleDescription &descr = interf->description();
    auto &items = interf->items();

    XGuiPageBuilder input;
    input.parent = nullptr;
    input.tabs = tabs;     //сюда добавляются страницы
    input.grid = nullptr;    //страницы создают новый, а остальные добавляются в него
    input.settings.show_names = Settings::get_xguicomp_show_components_names();

    for (int i=0; i<items.size(); i++) {
        auto *item = items.at(i);
        XGuiComp *itemgui = item->create_gui(input);
        xc_assert(itemgui, "Internal error loading module " + module_name + ": can't create GUI for '" + item->title() + "'");
        items_.push_back(itemgui);
        items_by_name_[item->name()] = itemgui;
    }
    //Завершаем последнюю страницу
    XGuiPage::finalize_page(input);

    //Добавляем страницу Help, если есть файл help.md
    QString help_text = info->help();
    if (!help_text.isEmpty()) {
        QTextEdit *help = new QTextEdit;
        help->setReadOnly(true);
        //TODO Qt 5.15
        //help->setMarkdown(help_text);
        xclu::set_font_size(help, xclu::help_font_size);
        tabs->addTab(help, tr("Help"));
    }

    //Создаем дерево управления видимостью
    auto &vis_groups = interf->vis_groups();
    for (int i=0; i<vis_groups.size(); i++) {
        //получаем родителя
        VisibleGroupBase &group = vis_groups[i];
        QString item_name = group.item_name();
        xc_assert(items_by_name_.contains(item_name), "No GUI item '" + item_name + "' for using as a parent of visibility group");
        XGuiComp *parent = items_by_name_[item_name];

        //создаем и заполняем GUI-группу
        VisibilityGroupGui *new_gui_group = group.create_group_gui();

        QStringList affected_items = group.affected_items();
        for (int i=0; i<affected_items.size(); i++) {
            QString name = affected_items.at(i);
            xc_assert(items_by_name_.contains(name), "No GUI item '" + item_name + "' inside created visibility group");
            new_gui_group->add_affected_item(items_by_name_[name]);
        }
        //добавляем ее в родителя
        //он ее и удалит
        parent->add_visibility_group(new_gui_group);
    }


    //Обновление видимости, если требуется.
    //для вызовов из load_module(XModule *module) - это не нужно, так как там сработает module->gui_action(GuiStageAfterGuiAttached);
    //но для кастомного применения, например, тестирования интерфейса - это нужно
    if (force_propagate_visibility) {
        interf->propagate_visibility();
    }

}

//---------------------------------------------------------------------
EditorModuleState XGuiEditor::state() {
    EditorModuleState s;
    s.tab_index = tabs->currentIndex();
    return s;
}

//---------------------------------------------------------------------
void XGuiEditor::set_state(EditorModuleState state) {
    tabs->setCurrentIndex(state.tab_index);
}

//---------------------------------------------------------------------
//Отслеживание изменений, чтобы пометить, что проект был изменен
//connect(spin_, SIGNAL (valueChanged(double)), this, SLOT (on_value_changed()));
void XGuiEditor::on_value_changed() {
    xc_document_modified();
}

//---------------------------------------------------------------------
//user changed "Show Components Names" checkbox menu item
void XGuiEditor::set_show_components_names(bool show) {
    for (auto item: items_) {
        item->set_show_components_names(show);
    }
}

//---------------------------------------------------------------------
