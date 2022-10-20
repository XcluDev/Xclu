#include "qt_widgets.h"
#include "editormodules.h"
#include "xmodulesfactory.h"
#include "projectgui.h"
#include "dialogrenamemodule.h"
#include "dialogaddmodule.h"
#include "project.h"
#include "dialogmodulename.h"

//---------------------------------------------------------------------
EditorModules::EditorModules(QWidget *parent, QMenu *modulesMenu)
    :QWidget(parent)
{
    //list
    moduleListWidget = new QListWidget();
    xclu::set_font_size(moduleListWidget, xclu::main_font_size);
    //moduleListWidget->setContentsMargins(5, 5, 5, 5);
    XcluTheme::set_theme(moduleListWidget);


    connect(moduleListWidget, SIGNAL (itemSelectionChanged()), this, SLOT (module_selected()));
    connect(moduleListWidget, SIGNAL (itemDoubleClicked(QListWidgetItem*)), this, SLOT (module_double_clicked(QListWidgetItem*)));

    //buttons
    toolBar = new QToolBar(tr("Modules"));

    new_action(addAction, tr("Add Module"), "module_add.png", modulesMenu);
    toolBar->addSeparator();
    new_action(renameAction, tr("Rename Module"), "module_rename.png", modulesMenu);
    toolBar->addSeparator();
    new_action(downAction, tr("Move Down"), "module_down.png", modulesMenu);
    new_action(upAction, tr("Move Up"), "module_up.png", modulesMenu);
    new_action(duplicateAction, tr("Duplicate Module"), "module_duplicate.png", modulesMenu);
    toolBar->addSeparator();
    new_action(deleteAction, tr("Delete Module"), "module_delete.png", modulesMenu);

    connect(addAction, SIGNAL (triggered()), this, SLOT (add_module_click()));
    connect(renameAction, SIGNAL (triggered()), this, SLOT (rename_module_click()));
    connect(upAction, SIGNAL (triggered()), this, SLOT (up_module_click()));
    connect(downAction, SIGNAL (triggered()), this, SLOT (down_module_click()));
    connect(duplicateAction, SIGNAL (triggered()), this, SLOT (duplicate_module_click()));
    connect(deleteAction, SIGNAL (triggered()), this, SLOT (delete_module_click()));

    //Главный layout
    QVBoxLayout *layout = xclu::vlayout(-1, new QLabel(tr("Modules")), 0,
                                                moduleListWidget, 0,
                                                toolBar, 0);
    //layout->setSpacing(5);

    this->setLayout(layout);
}

//---------------------------------------------------------------------
void EditorModules::new_action(QAction *&action, QString title, QString icon_file, QMenu *modulesMenu) {
    icon_file = xclu::builtin_icons_folder() + icon_file;
    action = new QAction(QIcon(icon_file), title, nullptr);
    toolBar->addAction(action);
    modulesMenu->addAction(action);
}

//---------------------------------------------------------------------
//включено ли редактирование
void EditorModules::set_editable(bool editable) {
    editable_ = editable;
    update_buttons();
}

//---------------------------------------------------------------------
//включено ли редактирование
void EditorModules::update_buttons() {
    addAction->setEnabled(editable_);
    bool selected = editable_ && (current_index() >= 0 && current_index() < modules_count());
    renameAction->setEnabled(selected);
    duplicateAction->setEnabled(selected);
    deleteAction->setEnabled(selected);
    upAction->setEnabled(selected);
    downAction->setEnabled(selected);
}

//---------------------------------------------------------------------
void EditorModules::before_close_project() {

}

//---------------------------------------------------------------------
void EditorModules::after_close_project() {
    moduleListWidget->clear();
}

//---------------------------------------------------------------------
//пересчитать список модулей из проекта
void EditorModules::update_module_list() {
    moduleListWidget->clear();
    for (int i=0; i<PROJECT.modules_count(); i++) {
        inserted_module(i, PROJECT.find_module_by_index(i)->name());
    }
    update_buttons();
}

//---------------------------------------------------------------------
int EditorModules::current_index() {
    return moduleListWidget->currentRow();
}

//---------------------------------------------------------------------
int EditorModules::modules_count() {
    return moduleListWidget->count();
}

//---------------------------------------------------------------------
void EditorModules::emit_selection_changed() {  //послать сигнал, что текущий модуль был изменен
    //qDebug() << "emit_selection_changed";

    int i = moduleListWidget->currentRow();
    if (i >= 0 && i < modules_count()) {
        //qDebug() << QString("module_selected %1").arg(i);
        //auto *interf = PROJECT.modules.get_interface(i);

        emit PROJ_GUI->changed_module_selection(i);
    }
}

//---------------------------------------------------------------------
void EditorModules::module_selected() {
    //qDebug() << "module_selected";
    emit_selection_changed();
    update_buttons();
}

//---------------------------------------------------------------------
void EditorModules::module_double_clicked(QListWidgetItem *) {
    //qDebug() << "double clicked";
    rename_module_click();
}

//---------------------------------------------------------------------
//выбрать модуль и загрузить для него параметры
void EditorModules::select_item(int i) {
    moduleListWidget->setCurrentRow(i);

    //тут не надо отправлять команду в ProjectGui,
    //так как setCurrentRow уже пошлет сигнал в module_selected
    //поэтому, закомментировано:
    //emit_selection_changed();
}

//---------------------------------------------------------------------
void EditorModules::add_module_click() {
    //qDebug("add_module_click");
    //возвращает адрес диалога, если он успешен
    DialogAddModule *dialog = DialogAddModule::call_dialog(this);
    if (!dialog) return;
    //подбор имени
    QString class_name = dialog->selected_type;
    auto name_hint = PROJECT.generate_unique_name_by_class_name(class_name);

    //диалог выбора имени
    auto *name_dialog = DialogModuleName::call_dialog(this, name_hint);
    if (!name_dialog) return;

    qDebug() << "add module " << class_name;
    //отправляем команду в ProjectGui
    PROJ_GUI->new_module(current_index()+1, class_name, name_dialog->name_hint());
    //если все ок, то нам уже потом придет сигнал на добавление модуля

}

//---------------------------------------------------------------------
//возвратная команда, что модуль был вставлен,
//и осуществляется фактическая вставка в список
void EditorModules::inserted_module(int i, QString name) {
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(name);
    moduleListWidget->insertItem(i, newItem);

    //выбираем его
    select_item(i);
}

//---------------------------------------------------------------------
void EditorModules::rename_module_click() {
    //qDebug("rename_module_click");
    auto *item = moduleListWidget->currentItem();
    if (item) {
        QString name = item->text();
        if (DialogRenameModule::call_dialog(name, this)) {
            PROJ_GUI->rename_module(current_index(), name);
        }
    }
}

//---------------------------------------------------------------------
//сигнал, что модуль был переименован
void EditorModules::renamed_module(int i, QString name) {
    if (i >= 0 && i < modules_count()) {
        moduleListWidget->item(i)->setText(name);
    }
}

//---------------------------------------------------------------------
void EditorModules::duplicate_module_click() {
    //qDebug("duplicate_module_click");
    int index = current_index();
    if (index < 0) return;
    PROJ_GUI->duplicate_module(index);
}

//---------------------------------------------------------------------
void EditorModules::delete_module_click() {
    //qDebug("delete_module_click");

    int index = current_index();
    if (index < 0 || index > PROJECT.modules_count()) return;
    XModule *module = PROJECT.find_module_by_index(index);
    if (!module) return;

    QMessageBox msgBox;
    msgBox.setText("Deleting module '" + module->name() + "'.");
    msgBox.setInformativeText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
        PROJ_GUI->delete_module(index);
        break;
    default:
        break;
    }
}

//---------------------------------------------------------------------
//сигнал, что модуль был удален
void EditorModules::deleted_module(int i) {
    if (i >= 0 && i < modules_count()) {
        auto *item = moduleListWidget->takeItem(i);
        if (item) {
            delete item;
        }
        int i = current_index();
        if (i >= 0) {
            PROJ_GUI->changed_module_selection(i);
        }
    }
}

//---------------------------------------------------------------------
void EditorModules::up_module_click() {
    //qDebug("up_module_click");
    int index = current_index();
    if (index >= 1) {
        PROJ_GUI->swap_modules(index-1);
    }

}

//---------------------------------------------------------------------
void EditorModules::down_module_click() {
    //qDebug("down_module_click");
    int index = current_index();
    if (index >= 0 && index + 1< PROJECT.modules_count()) {
        PROJ_GUI->swap_modules(index);
    }
}

//---------------------------------------------------------------------
//сигнал, что модули были поменяны местами
void EditorModules::swapped_modules(int i) {
    //qDebug() << "swapped_modules " << i;
    int index = current_index();
    int new_index = (i==index)?(i+1):i;

    auto *item = moduleListWidget->takeItem(i);
    moduleListWidget->insertItem(i+1, item);

    select_item(new_index);

}

//---------------------------------------------------------------------
