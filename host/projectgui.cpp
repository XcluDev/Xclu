#include "qt_widgets.h"
#include "modulesfactory.h"
#include "project.h"
#include "projectgui.h"
#include "incl_cpp.h"
#include "consoleview.h"

ProjectGui *PROJ_GUI;

//---------------------------------------------------------------------
ProjectGui::ProjectGui(QWidget *parent, QMenu *modulesMenu)
    :QWidget(parent)
{
    editor_modules = new EditorModules(nullptr, modulesMenu);
    editor_module = new XGuiEditor(nullptr);
    CONS_VIEW = new ConsoleView(nullptr);

    //CONS_VIEW->setVisible(false);

    //консоль слева внизу
    this->setLayout(xclu::hlayout(0,
                                  xclu::vwidget(0, editor_modules, 10,
                                                CONS_VIEW, 5), 5,
                                 editor_module, 10));

    //консоль внизу
    //this->setLayout(xclu::vlayout(0,
    //                              xclu::hwidget(0,
    //                                            editor_modules, 5,
    //                                            editor_module, 10), 10,
    //                              CONS_VIEW, 2));

    //"фабрика" модулей
    FACTORY.setup();
    set_editable(false);
}

//---------------------------------------------------------------------
//включено ли редактирование
void ProjectGui::set_editable(bool editable) {
    editor_modules->set_editable(editable);
}

//---------------------------------------------------------------------
void ProjectGui::properties_from_gui() {
    //запоминаем выбранный модуль
    PROJ.properties().selected_module = editor_modules->current_index();
}

//---------------------------------------------------------------------
void ProjectGui::properties_to_gui() {
    //выбор модуля
    int i = PROJ.properties().selected_module;
    editor_modules->select_item(i);
}

//---------------------------------------------------------------------
//закрытие проекта
void ProjectGui::before_close_project() {
    //запоминаем выбранный модуль
    properties_from_gui();
    //закрываем все в редакторах модулей
    editor_module->before_close_project();
    editor_modules->before_close_project();
}

//---------------------------------------------------------------------
void ProjectGui::after_close_project() {
    editor_module->after_close_project();
    editor_modules->after_close_project();
}

//---------------------------------------------------------------------
//открытие проекта - выбор модуля
void ProjectGui::after_load_project() {
    update_module_list();
    //выбор модуля
    properties_to_gui();
}

//---------------------------------------------------------------------
//перед сохранением проекта
void ProjectGui::before_save_project() {
    properties_from_gui();
}

//---------------------------------------------------------------------
//пересчитать список модулей из проекта
void ProjectGui::update_module_list() {
    editor_modules->update_module_list();
}

//---------------------------------------------------------------------
//сигнал от списка модулей, что добавился новый модуль
void ProjectGui::new_module(int i, QString class_name, QString name_hint) {
    //из редактора списка модулей пришел сигнал, что требуется создать модуль типа type
    //генерируем его в PROJ, и там ему присваивается уникальное имя
    Module *module = PROJ.new_module(i, class_name, name_hint);
    if (module) {
        emit editor_modules->inserted_module(i, module->name());
        //Сигнал, что проект был изменен
        xclu_document_modified();
    }
}

//---------------------------------------------------------------------
//сигнал, что модуль нужно переименовать
void ProjectGui::rename_module(int i, QString new_name) {
    PROJ.rename_module(i, new_name);
    editor_modules->renamed_module(i, new_name);
    editor_module->renamed_module();
    selected_module_updated();
    //Сигнал, что проект был изменен
    xclu_document_modified();
}

//---------------------------------------------------------------------
//сигнал, что модуль нужно удалить
void ProjectGui::delete_module(int i) {
    editor_module->detach();
    PROJ.delete_module(i);
    editor_modules->deleted_module(i);
    //Сигнал, что проект был изменен
    xclu_document_modified();
}

//---------------------------------------------------------------------
//сигнал, что модуль нужно сдублировать
void ProjectGui::duplicate_module(int i) {
    PROJ.duplicate_module(i);
    editor_modules->inserted_module(i+1, PROJ.module_by_index(i+1)->name());
    //Сигнал, что проект был изменен
    xclu_document_modified();
}

//---------------------------------------------------------------------
//сигнал, что модули нужно поменять местами
void ProjectGui::swap_modules(int i) { //i<->i+1
    PROJ.swap_modules(i);
    editor_modules->swapped_modules(i);
    //Сигнал, что проект был изменен
    xclu_document_modified();
}

//---------------------------------------------------------------------
//сигнал от списка модулей, что изменился выбранный модуль
//после этого следует загрузить новый модуль в редактор параметров
void ProjectGui::changed_module_selection(int i) {
    emit editor_module->changed_module_selection(i);
    //Сигнал, что проект был изменен
    xclu_document_modified();
}

//---------------------------------------------------------------------
//сигнал от списка модулей, что выбранный модуль изменился
//после этого следует обновить этот модуль в редактор параметров
void ProjectGui::selected_module_updated() {
    //emit editor_module->selected_module_updated();
    //Сигнал, что проект был изменен
    xclu_document_modified();
}



//---------------------------------------------------------------------
