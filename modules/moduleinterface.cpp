#include <QJsonObject>
#include <QJsonArray>
#include "xmodule.h"
#include "moduleinterface.h"
#include "incl_cpp.h"
#include "xguieditor.h"
#include "consoleview.h"

//---------------------------------------------------------------------
ModuleInterface::ModuleInterface(const ModuleSeed &info)
{
    //копирование описания модуля
    description_ = info.description;

    //парсинг - создание элементов интерфейса
    parse_trimmed(info.gui_lines());

    //проверка целостности и заполнение maps для быстрого доступа
    update_maps();

    //установка параметров по-умолчанию из описания модуля на страницу general
    set_general_values();

    //еще нужно установить видимость propagate_visibility()
    //- но это нужно делаеть, когда будут установлены значения переменных,
    //а при тестировании модулей - просто вызвать

}

//---------------------------------------------------------------------
//установка параметров по-умолчанию из описания модуля на страницу general
void ModuleInterface::set_general_values() {
    //установка "пожеланий" из настроек
    //var("run_mode")->set_value_int(description_.default_run_mode); //режим запуска

    //установка списков calls
    var("send_calls")->set_value_string(description_.send_calls.to_string_gui());
    var("accept_calls")->set_value_string(description_.accept_calls.to_string_gui());
}


//---------------------------------------------------------------------
ModuleInterface::~ModuleInterface() {
    clear();
}

//---------------------------------------------------------------------
ModuleDescription &ModuleInterface::description() {
    return description_;
}

//---------------------------------------------------------------------
void ModuleInterface::set_module(Module *module) {
    module_ = module;
}

//---------------------------------------------------------------------
Module *ModuleInterface::module() {
    return module_;
}

//---------------------------------------------------------------------
QVector<XItem *> &ModuleInterface::items() {
    return items_;
}

//---------------------------------------------------------------------
void ModuleInterface::clear() {
    for (int i=0; i<items_.size(); i++) {
        delete items_[i];
    }
    items_.clear();

    items_by_name_.clear();
}

//---------------------------------------------------------------------
QString ModuleInterface::generate_separator_name() {
    return "__separator" + QString::number(separator_index_++);
}

//---------------------------------------------------------------------
//собрать описание элемента (строки, начинающиеся с "//"), и изменить счетчик i
QStringList ModuleInterface::collect_description(const QStringList &lines, int &i) {
    i++;
    QStringList list;
    while (i < lines.size()) {
        QString line = lines[i];
        if (line.startsWith("//")) {
            list.append(line.mid(2));   //строка с удаленными "//"
        }
        else break;
        i++;
    }
    return list;
}

//---------------------------------------------------------------------
//добавить последний элемент в текущую vis_group_ если, конечно, она открыта для добавления
void ModuleInterface::add_to_vis_group() {
    if (vis_group_opened_) {
        vis_groups_.last().add_affected_item(items_.last()->name());
    }
}

//---------------------------------------------------------------------
void ModuleInterface::parse_trimmed(const QStringList &lines) {
    //При ошибке парсинга - можно генерировать исключение, которое перехватывает FACTORY:
    //например, CONS.throw_exception("Test parsing exception");
    //или xclu_assert(...)

    items_.clear();

    //Начинаем страницу Main - закомментировано
    //new_decorate_item("Main", XItemTypePage, QStringList(""));

    //Общая страница добавляется в ModuleSeed::gui_lines().
    //general_page_start sets by "GENERAL_PAGE" at general_page.xgui
    //after parsing all such items marked as "general_page_ = true;"
    QString general_page_marker = GENERAL_PAGE_marker();
    int general_page_start = -1;


    for (int i=0; i<lines.count(); /*i++*/) {//не увеличиваем i, так как это делает collect_desctiption
        // page XXX
        // //description
        //[in/const/out] type title_gui name, и затем опционально '=' или ' ', var_details
        // #title_gui - подчерки трансформируются в пробелы
        // //description
        // //description ... - может быть несколько строк описания
        //группы видимости:
        //if mode 3,4
        //...
        //endif (или снова if)

        QString line = lines[i];
        //будем отлавливать исключение и добавлять к нему информацию, какую строку парсим
        try {
            //GENERAL_PAGE - command for switching to general page
            if (line == general_page_marker) {
                general_page_start = items_.size();
                i++;
                continue;
            }

            //описание - его не должно быть, так как мы их сразу считываем
            if (line.startsWith("//")) {
                xclu_exception("Description '" + line + "' is not related to some item");
                //QString descr = line.mid(2);
                //xclu_assert(!items_.isEmpty(), "can't use description '" + descr + "', because there are no objects yet");
                //items_.last()->add_description(descr);
                continue;
            }

            QRegExp rx("(\\ |\\t)"); //RegEx for ' ' or '\t'
            QStringList query = line.split(rx);

            int n = query.size();
            QString item1 = query.at(0);

            //начало группы видимости
            if (item1 == "if") {
                //начать новую группу
                //if mode 3,4
                xclu_assert(n >= 3, "not enough parameters, expected 'if mode 3,4'");
                QString item_name = query.at(1);
                QStringList variants = query.at(2).split(",");

                //проверка, зарегистрирован ли уже этот элемент
                //нужно именно просканировать список, так как maps еще не готовы
                //(TODO - можно создавать maps по ходу дела для оптимизации)
                bool found = false;
                for (int i=0; i<items_.size(); i++) {
                    if (items_[i]->name() == item_name) {
                        found = true;
                        break;
                    }
                }
                xclu_assert(found, "item '" + item_name + "' is not found - it must be declared before 'if'");
                vis_groups_.push_back(VisibleGroupBase(item_name, variants));
                //помечаем, что группа для заполнения открыта
                vis_group_opened_ = true;
                //нужно везде увеличивать i самим
                i++;
                continue;
            }

            //конец группы видимости
            if (item1 == "endif") {
                xclu_assert(vis_group_opened_, "'endif' without opening 'if'");
                //завершение группы видимости
                //помечаем, что группа для заполнения закрыта
                vis_group_opened_ = false;

                //нужно везде увеличивать i самим
                i++;
                continue;
            }

            //сепаратор: separator или line
            //line сейчас задан неофициально,  в программе он как тип не обозначен,
            //его обрабатываем только тут и еще в XItem::new_separator
            if (item1 == xitem_separator() || item1 == xitem_line()) {
                auto type = xitem_separator(); //string_to_interfacetype(item1);
                bool is_line = (item1 == "line");
                new_separator(type, is_line);
                //collect_description увеличивает i
                collect_description(lines, i); //считываем описание, но никуда его не используем
                continue;
            }

            //страница или группа
            if (item1 == "page" || item1 == "group") {
                xclu_assert(n>=2, "bad definiton at line " + line + ", no item title");
                QString name = query.at(1);
                xclu_assert(!name.isEmpty(), "empty page name at line " + line);

                auto type = item1;
                //xclu_assert(!type.isEmpty(), "internal error: empty type at line " + line);

                //collect_description увеличивает i
                new_decorate_item(name, type, collect_description(lines, i));
                continue;
            }

            //переменная
            //[in/const/out][(options)] type(options) title_gui name, и затем опционально '=' или ' ', var_details

            xclu_assert(n >= 4, "bad variable description at line '" + line + "', expected '[in/const/out] type title_gui name...'");

            //парсинг квалификатора и опций out(not_save)
            QStringList qual_list=item1.split(QRegExp("(\\(|\\))"));
            xclu_assert(!qual_list.isEmpty(), "bad qualifiers string at line '" + line + "'");

            auto qual = string_to_xqualifier(qual_list.at(0));
            xclu_assert(qual != XQualifierNone, "unknown variable qualifier at line '" + line + "', expected: 'in', 'out', 'const'");
            QString qual_options;
            if (qual_list.size() >= 2) {
                qual_options = qual_list.at(1);
            }


            //парсим type_attribute1_attribute2_... на тип и атрибуты:
            //QStringList type_options=query.at(1).split(QRegExp("(\\(|\\))"));
            QStringList type_options=query.at(1).split("_");
            xclu_assert(!type_options.isEmpty(), "bad type name at line '" + line + "'");

            auto type = type_options.at(0);
            //xclu_assert(type != XItemTypeNone, "unknown variable type at line '" + line + "', expected: 'int', 'float', ...");

            QString options;
            if (type_options.size() >= 2) {
                options = type_options.at(1);
            }

            //заголовок
            QString title = query.at(2);
            //title = xclu_remove_underscore(title);

            //qDebug() << "var " << line << ":" << qual << "," << type << "," << title;
            //удаляем первые элементы, чтобы потом остаток соединить и допарсить в конкретных элементах
            query.removeFirst();
            query.removeFirst();
            query.removeFirst();
            //соединяем
            QString line_to_parse = query.join(" ");
            //qDebug() << "var   " << line_to_parse;
            //парсим уже в зависимости от типа переменной
            //здесь при возникновении ошибки добавляем, откуда она взялась
            //collect_description увеличивает i
            new_item(title, type, collect_description(lines, i),
                        qual, line_to_parse, options, qual_options);
        }
        catch (XException& e) {
            xclu_exception("Parsing error at line '" + line + "':\n" + e.whatQt());
        }

    }

    //Mark items of general page
    if (general_page_start >= 0) {
        for (int i=general_page_start; i<items_.size(); i++) {
            items_[i]->set_belongs_general_page(true);
        }
    }

    //Проверяем, что интерфейс начался с создания страницы
    xclu_assert(items_[0]->type() == xitem_page(), "Interface description must start with a page");

}

//---------------------------------------------------------------------
//Общая функция добавления элемента интерфейса в список
//а также вставка в группу визуализации
void ModuleInterface::push_item(XItem *item) {
    items_.push_back(item);
    add_to_vis_group();
}

//---------------------------------------------------------------------
void ModuleInterface::new_item(const XItemPreDescription &pre_description) {
    push_item(XItemCreator::new_item(this, pre_description));
}

//---------------------------------------------------------------------
void ModuleInterface::new_item(QString title_underscored, QString type,
                                  const QStringList &description,
                                  XQualifier qual, QString line_to_parse, QString options,
                                  QString qual_options) {
    push_item(XItemCreator::new_item(this, title_underscored, type, description, qual, line_to_parse, options, qual_options));
}

//---------------------------------------------------------------------
void ModuleInterface::new_decorate_item(QString name, QString type, const QStringList &description) {
    items_.push_back(XItemCreator::new_decorate_item(this, name, type, description));
    add_to_vis_group();
}

//---------------------------------------------------------------------
void ModuleInterface::new_separator(QString type, bool is_line) {
    push_item(XItemCreator::new_separator(this, generate_separator_name(), type, is_line));
}

//---------------------------------------------------------------------
//проверка того, что разные элементы имеют разные имена, и заполнение map для быстрого доступа
void ModuleInterface::update_maps() {
    items_by_name_.clear();

    for (int i=0; i<items_.size(); i++) {
        XItem *item = items_[i];
        QString name = item->name();

        xclu_assert(!name.isEmpty(), "Item name can't be empty, title: '" + item->title() + "'");
        xclu_assert(!item->title().isEmpty(), "Item title can't be empty, name: '" + name + "'");

        xclu_assert(!items_by_name_.contains(name), "Duplicated item '" + name + "'");
        items_by_name_[name] = item;
    }
}

//---------------------------------------------------------------------
//does module contains item with given name
bool ModuleInterface::has_item(QString name) {
    return items_by_name_.contains(name);
}

//---------------------------------------------------------------------
//элемент по имени - кроме сепараторов
XItem *ModuleInterface::var(QString name) {
    xclu_assert(has_item(name), "Unknown item '" + name + "'");
    return items_by_name_[name];
}

//---------------------------------------------------------------------
//группы видимости - для создания дерева управления видимостью на GUI
QVector<VisibleGroupBase> &ModuleInterface::vis_groups() {
    return vis_groups_;
}

//---------------------------------------------------------------------
//Compiling links and other things
bool ModuleInterface::compile() {
    bool ok = true;
    for (auto item: items_) {
        try{
            item->compile();
        }
        catch(XException& e) {
            xclu_console_append(e.whatQt());
            ok = false;
        }
    }
    return ok;
}

//---------------------------------------------------------------------
//сигнал, что GUI подключен/отключен
void ModuleInterface::gui_attached(XGuiEditor *editor) {
    editor_ = editor;
    for (int i=0; i<items_.size(); i++) {
        items_[i]->gui_attached();
    }
}

//---------------------------------------------------------------------
void ModuleInterface::gui_detached() {
    for (int i=0; i<items_.size(); i++) {
        items_[i]->gui_detached();
    }
    editor_ = nullptr;
}

//---------------------------------------------------------------------
bool ModuleInterface::is_gui_attached() {
    return (editor_ != nullptr);
}

//---------------------------------------------------------------------
//установить видимость, используется при тестировании интерфейса
void ModuleInterface::propagate_visibility() {
    for (auto item: items_) {
        item->propagate_visibility();
    }
}

//---------------------------------------------------------------------
//команды для обновления внутренних значений из GUI и в GUI
void ModuleInterface::gui_to_vars(const XQualifierMask &qual, bool evaluate_expr) {
    if (is_gui_attached()) {
        for (auto &item: items_) {
            item->gui_to_var(qual, evaluate_expr);
        }
    }
}

//---------------------------------------------------------------------
void ModuleInterface::vars_to_gui(const XQualifierMask &qual) {
    if (is_gui_attached()) {
        for (auto &item: items_) {
            item->var_to_gui(qual);
        }
    }
}

//---------------------------------------------------------------------
//заблокировать константы, вызывается перед запуском проекта
void ModuleInterface::block_gui(const XQualifierMask &qual) {
    if (is_gui_attached()) {
        if (is_gui_attached()) {
            for (auto &item: items_) {
                item->block_gui_editing(qual);
            }
        }
    }
}

//---------------------------------------------------------------------
//разблокировать константы, вызывается после остановки проекта
void ModuleInterface::unblock_gui(const XQualifierMask &qual) {
    if (is_gui_attached()) {
        if (is_gui_attached()) {
            for (auto &item: items_) {
                item->unblock_gui_editing(qual);
            }
        }
    }
}


//---------------------------------------------------------------------
//пометить, что все элементы были изменены - при старте
void ModuleInterface::reset_was_changed() {
    for (auto &item: items_) {
        item->reset_was_changed_simple();
    }
}

//---------------------------------------------------------------------
//update before rt-module's update
void ModuleInterface::update() {
    for (auto &item: items_) {
        item->update();
    }
}

//---------------------------------------------------------------------
//запомнить/восстановить состояние GUI (страницу, промотку)
void ModuleInterface::gui_to_state() {
    if (is_gui_attached()) {
        //xclu_assert(editor_, "Internal error - ModuleInterface::gui_to_state is called, but editor_ == nullptr");
        editor_state_ = editor_->state();
    }
}

//---------------------------------------------------------------------
void ModuleInterface::state_to_gui() {
    if (is_gui_attached()) {
        //xclu_assert(editor_, "Internal error - ModuleInterface::state_to_gui is called, but editor_ == nullptr");
        editor_->set_state(editor_state_);
    }
}

//---------------------------------------------------------------------
//callback из GUI
void ModuleInterface::callback_button_pressed(QString button_id) {
    xclu_assert(module(), "Can't process pressing button '" + button_id + "' because module() is nullptr");
    module()->button_pressed(button_id);
}

//---------------------------------------------------------------------
EditorModuleState ModuleInterface::editor_state() {
    return editor_state_;
}

//---------------------------------------------------------------------
void ModuleInterface::set_editor_state(EditorModuleState editor_state) {
    editor_state_ = editor_state;
}

//---------------------------------------------------------------------
//дублирование данных переменных и состояние редактора, используется при дублировании модулей
void ModuleInterface::copy_data_to(ModuleInterface *interf) {
    xclu_assert(interf, "Internal error in ModuleInterface::copy_data_to: interface to copy is nullptr");
    interf->set_editor_state(editor_state());
    for (int i=0; i<items_.size(); i++) {
        auto *item = items_[i];
        if (item->store_data()) {
            QString name = item->name();
            auto *item1 = interf->var(name);
            xclu_assert(item1, "Internal error in ModuleInterface::copy_data_to: no item '"
                        + name + "' in the destination interface");
            item->copy_data_to(item1);
        }
    }
}

//---------------------------------------------------------------------
//Запись и считывание json
void ModuleInterface::write_json(QJsonObject &json) {
    //переменные
    QJsonArray itemsArray;
    for (int i=0; i<items_.size(); i++) {
        auto *item = items_[i];
        if (!item->store_data() || !item->is_save_to_project()) continue;
        QJsonObject itemObject;
        item->write_json(itemObject);
        itemsArray.append(itemObject);
    }
    json["items"] = itemsArray;
    //состояние редактора
    QJsonObject editorObject;
    editorObject["tab_index"] = QString::number(editor_state_.tab_index);   //int пишем как строки
    json["editor_state"] = editorObject;

}

//---------------------------------------------------------------------
void ModuleInterface::read_json(const QJsonObject &json) {

    QStringList errors; //сюда накопим ошибки про считывание модуля и потом их выдадим в консоль
    //переменные
    QJsonArray itemsArray = JsonUtils::json_array(json, "items");
    for (int i=0; i<itemsArray.size(); i++) {
        QJsonObject itemObject = JsonUtils::json_array_object(itemsArray, i);
        QString name = JsonUtils::json_string(itemObject, "aname");

        //пытаемся считать переменную,
        //если не получается - пишем сообщение в лог и продолжаем загрузку
        try {
            auto *item = var(name);
            //если элемент не хранит данные, то не записываем
            //вообще, такого не должно случиться, так как мы не записываем такие элементы,
            //но проигнорируем эту проблему
            if (!item->store_data() || !item->is_save_to_project()) continue;

            item->read_json(itemObject);
        }
        catch(XException& e) {
            errors.append(e.whatQt());
        }
    }

    //состояние редактора
    QJsonObject editorObject = JsonUtils::json_object(json, "editor_state");
    editor_state_.tab_index = JsonUtils::json_int(editorObject, "tab_index");

    //выдача ошибок в консоль про даннный модуль
    if (!errors.isEmpty()) {
        xclu_console_warning("Error(s) loading module '" + description().class_name + "':");
        for (int i=0; i<errors.size(); i++) {
            xclu_console_warning("   " + errors.at(i));
        }
    }
}

//---------------------------------------------------------------------
//Variables access
//int, checkbox, button, enum (index), string, text
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
QString ModuleInterface::gets(QString name, int index, int index2) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->supports_string(), "variable '" + name + "' doesn't supports string");
    QString value = var->value_string();
    if (index2 == -1) {
        if (index == -1) {  //plain string: "aaa"
            return value;
        }
        else {
            QStringList list = value.split(" "); //string, separated by spaces: "a b c"
            if (index < list.size()) {
                return list.at(index);
            }
            //No error, just empty string
            //For future improvement: exception text:
            //QString("Can't get value from `%1` with index %2, because value is `%3`")
            //.arg(name).arg(index).arg(value));
            return "";
        }
    }
    else {
        //string, separated by '\n' and spaces: "a b c\nc d e"
        QStringList list = value.split("\n");
        if (index < list.size()) {
            QStringList list2 = list[index].split(" ");
            if (index2 < list2.size()) {
                return list2.at(index2);
            }
        }
        return "";
    }
}

//---------------------------------------------------------------------
//splits text using "\n"
QStringList ModuleInterface::get_strings(QString name) {
    return gets(name).split("\n");
}

//---------------------------------------------------------------------
//только out: int, checkbox, enum (index), string, text
void ModuleInterface::sets(QString name, QString v) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xclu_assert(var->supports_string(), "variable '" + name + "' doesn't supports string");
    var->set_value_string(v);
}

//---------------------------------------------------------------------
void ModuleInterface::clear_string(QString name) {
    sets(name, "");
}

//---------------------------------------------------------------------
//дописать к строке, применимо где sets
void ModuleInterface::append_string(QString name, QString v, int extra_new_lines_count) {
    QString value = gets(name);
    value.append(v);
    for (int i=0; i<1 + extra_new_lines_count; i++) {
        value.append("\n");
    }
    sets(name, value);
}

//---------------------------------------------------------------------
void ModuleInterface::append_string(QString name, QStringList v, int extra_new_lines_count) { //дописать к строке, применимо где sets
    append_string(name, v.join("\n"), extra_new_lines_count);
}

//---------------------------------------------------------------------
//int, checkbox, button, enum (index)
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
int ModuleInterface::geti(QString name, int index, int index2) {
    if (index == -1) {
        XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
        xclu_assert(var->supports_int(), "variable '" + name + "' doesn't supports int");
        return var->value_int();
    }
    else {
        return gets(name, index, index2).toInt();
    }
}

//---------------------------------------------------------------------
//только out: int, checkbox, enum (index)
void ModuleInterface::seti(QString name, int v) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xclu_assert(var->supports_int(), "variable '" + name + "' doesn't supports int");
    var->set_value_int(v);
}

//---------------------------------------------------------------------
//увеличение значения
void ModuleInterface::increase_int(QString name, int increase) { //value+=increase
    seti(name, geti(name) + increase);
}

//---------------------------------------------------------------------
//float
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
float ModuleInterface::getf(QString name, int index, int index2) {
    if (index == -1) {
        XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
        xclu_assert(var->supports_float(), "variable '" + name + "' doesn't supports float");
        return var->value_float();
    }
    else {
        return gets(name, index, index2).toFloat();
    }
}

//---------------------------------------------------------------------
//только out: float
void ModuleInterface::setf(QString name, float v) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xclu_assert(var->supports_float(), "variable '" + name + "' doesn't supports float");
    var->set_value_float(v);
}

//---------------------------------------------------------------------
//enum
QString ModuleInterface::getraw(QString name) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->supports_value_raw(), "variable '" + name + "' doesn't supports raw value");
    return var->value_raw();
}

//---------------------------------------------------------------------
void ModuleInterface::set_raw(QString name, QString text) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xclu_assert(var->supports_value_raw(), "variable '" + name + "' doesn't supports raw value");
    var->set_value_raw(text);
}

//---------------------------------------------------------------------
//enum (title)
QString ModuleInterface::get_title_value(QString name) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->supports_value_title(), "variable '" + name + "' doesn't supports title value");
    return var->value_title();

}

//---------------------------------------------------------------------
//только out: enum (title)
void ModuleInterface::set_title_value(QString name, QString v) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xclu_assert(var->supports_value_title(), "variable '" + name + "' doesn't supports title value");
    var->set_value_title(v);
}

//---------------------------------------------------------------------
//доступ к объектам идет только по указателям -
//так как объекты могут быть очень большими, и поэтому с ними работаем непосредтсвенно,
//без копирования
//в объектах пока нет mutex - так как предполагается,
//что в gui посылается информация об обновлении объектов только из основного потока
XProtectedStruct *ModuleInterface::get_object(QString name) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xclu_assert(var->supports_object(), "variable '" + name + "' doesn't supports object");
    return var->get_object();
}


//---------------------------------------------------------------------



