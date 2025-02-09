#include <QJsonObject>
#include <QJsonArray>
#include "xclass.h"
#include "xmoduleinterface.h"
#include "incl_cpp.h"
#include "xguieditor.h"
#include "consoleview.h"
#include "xitembutton.h"

//---------------------------------------------------------------------
XModuleInterface::XModuleInterface(const XModulePrototype &info)
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
void XModuleInterface::set_general_values() {
    //установка "пожеланий" из настроек
    //var("run_mode")->set_value_int(description_.default_run_mode); //режим запуска

    //установка списков calls
    var("send_calls")->set_value_string(description_.send_calls.to_string_gui());
    var("accept_calls")->set_value_string(description_.accept_calls.to_string_gui());
}


//---------------------------------------------------------------------
XModuleInterface::~XModuleInterface() {
    clear();
}

//---------------------------------------------------------------------
XModuleDescription &XModuleInterface::description() {
    return description_;
}

//---------------------------------------------------------------------
void XModuleInterface::set_module(XModule *module) {
    module_ = module;
}

//---------------------------------------------------------------------
XModule *XModuleInterface::module() {
    return module_;
}

//---------------------------------------------------------------------
QVector<XItem *> &XModuleInterface::items() {
    return items_;
}

//---------------------------------------------------------------------
void XModuleInterface::clear() {
    for (int i=0; i<items_.size(); i++) {
        delete items_[i];
    }
    items_.clear();

    items_by_name_.clear();
}

//---------------------------------------------------------------------
QString XModuleInterface::generate_separator_name() {
    return "__separator" + QString::number(separator_index_++);
}

//---------------------------------------------------------------------
//собрать описание элемента (строки, начинающиеся с "//"), и изменить счетчик i
QStringList XModuleInterface::collect_description(const QStringList &lines, int &i) {
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
void XModuleInterface::add_to_vis_group() {
    if (vis_group_opened_) {
        vis_groups_.last().add_affected_item(items_.last()->name());
    }
}

//---------------------------------------------------------------------
void XModuleInterface::parse_trimmed(const QStringList &lines) {
    //При ошибке парсинга - можно генерировать исключение, которое перехватывает FACTORY:
    //например, CONS.throw_exception("Test parsing exception");
    //или xc_assert(...)

    items_.clear();

    //Начинаем страницу Main - закомментировано
    //new_decorate_item("Main", XItemTypePage, QStringList(""));

    //Общая страница добавляется в XModulePrototype::gui_lines().
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

        const QString &line_raw = lines[i];
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
                xc_exception("Description '" + line + "' is not related to some item");
                //QString descr = line.mid(2);
                //xc_assert(!items_.isEmpty(), "can't use description '" + descr + "', because there are no objects yet");
                //items_.last()->add_description(descr);
                continue;
            }


            //--------------------------------------------
            //Fixing problem with default value for string, to be able parse values with spaces:
            //in string Name name="aaa bbb"
            //For this, we capture "...." value and append it to last item to query value below

            //find position of = and first " and last " after = for using in string parsing
            int eq_index = line.indexOf('=');
            int quot1 = (eq_index>=0) ? line.indexOf('"', eq_index+1) : -1;
            int quot2 = (quot1>=0) ? line.lastIndexOf('"') : -1;
            //compute def value - if all this components exists
            QString def_value_string;
            if (eq_index >= 0 && quot1 >= 0 && quot2 > quot1) {
                def_value_string = line.mid(quot1, quot2-quot1+1);

                //remove from original string - we will add it to last item of query value
                line = line.left(eq_index+1);
            }

            //--------------------------------------------
            //split by spaces and tabs
            QRegExp rx("(\\ |\\t)"); //RegEx for ' ' or '\t'
            QStringList query = line.split(rx);

            xc_assert(!query.isEmpty(), "Internal error: empty query while parsing '" + line_raw + "'");

            //now if we shorten line - add def_value_string to the last item
            query[query.size()-1] += def_value_string;
            //--------------------------------------------
            int n = query.size();
            int query_scan = 0;
            QString item1 = query.at(query_scan++);

            //начало группы видимости
            if (item1 == "if") {
                //начать новую группу
                //if mode 3,4
                xc_assert(n >= 3, "not enough parameters,  expected 'if mode 3,4'");
                QString item_name = query.at(query_scan++);
                QStringList variants = query.at(query_scan++).split(",");

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
                xc_assert(found, "item '" + item_name + "' is not found, it must be declared before 'if'");
                vis_groups_.push_back(VisibleGroupBase(item_name, variants));
                //помечаем, что группа для заполнения открыта
                vis_group_opened_ = true;
                //нужно везде увеличивать i самим
                i++;
                continue;
            }

            //конец группы видимости
            if (item1 == "endif") {
                xc_assert(vis_group_opened_, "'endif' without opening 'if'");
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
                QString type = (item1 == xitem_separator()) ? xitem_separator():"separator_line";
                push_item(XItemCreator::new_separator(this, generate_separator_name(), type));
                //collect_description увеличивает i
                collect_description(lines, i); //считываем описание, но никуда его не используем
                continue;
            }

            //page
            if (item1 == xitem_page()) {
                xc_assert(n>=2, "bad definiton - no item title");
                QString name = query.at(query_scan++);
                xc_assert(!name.isEmpty(), "empty page name");

                auto type = item1;
                //xc_assert(!type.isEmpty(), "internal error: empty type");

                //collect_description увеличивает i
                new_decorate_item(name, type, collect_description(lines, i));
                continue;
            }

            // переменная
            // [in/const/out][(options)] type[_option1_...] title_gui name, и затем опционально '=' или ' ', var_details
            // если нет квалификатора, то используется "in"
            // (options) = (not_save) - не сохранять в проекте выходное значение.

            xc_assert(n >= 3, "Not enough arguments for variable description, expected '[in/const/out] type title_gui name...'");

            //парсинг квалификатора и опций out(not_save)
            QStringList qual_list=item1.split(QRegExp("(\\(|\\))"));
            xc_assert(!qual_list.isEmpty(), "bad qualifiers string");

            bool throw_exception = false;
            auto qual = string_to_xqualifier(qual_list.at(0), throw_exception);

            QString qual_options;

            // Если не распознан, то это in
            if (qual == XQualifier::None) {
                qual = XQualifier::In;
                query_scan--;   // сбрасываем номер в query, чтобы конвертировать уже тип
            }
            else {
                // Парсинг опций типа out(not_save)
                if (qual_list.size() >= 2) {
                    qual_options = qual_list.at(1);
                }
            }

            // Тип
            xc_assert(query_scan+1<n, "Can't read type");
            QString type_raw = query.at(query_scan++);
            //replace "group" with "checkbox_group"
            if (type_raw == xitem_group()) {
                type_raw = "checkbox_group";
            }


            //парсим type_attribute1_attribute2_... на тип и атрибуты:
            //QStringList type_options=type_raw.split(QRegExp("(\\(|\\))"));
            QStringList type_options=type_raw.split("_");
            xc_assert(!type_options.isEmpty(), "bad type name");

            auto type = type_options.at(0);
            //remove first and join back
            type_options.removeFirst();
            QString options = type_options.join("_");

            //title
            xc_assert(query_scan+1<n, "Can't read title");
            QString title = query.at(query_scan++);
            //title = xc_remove_underscore(title);

            //qDebug() << "var " << line << ":" << qual << "," << type << "," << title;
            //удаляем первые элементы, чтобы потом остаток соединить и допарсить в конкретных элементах
            for (int i=0; i<query_scan;i++) {
                query.removeFirst();
            }
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
            xc_exception("Parsing error at line '" + line + "':\n" + e.whatQt());
        }

    }

    //Mark items of general page
    if (general_page_start >= 0) {
        for (int i=general_page_start; i<items_.size(); i++) {
            items_[i]->set_belongs_general_page(true);
        }
    }

    //Проверяем, что интерфейс начался с создания страницы
    xc_assert(items_[0]->type() == xitem_page(), "Interface description must start with a page");

}

//---------------------------------------------------------------------
//Общая функция добавления элемента интерфейса в список
//а также вставка в группу визуализации
void XModuleInterface::push_item(XItem *item) {
    items_.push_back(item);
    add_to_vis_group();
}

//---------------------------------------------------------------------
void XModuleInterface::new_item(const XItemPreDescription &pre_description) {
    push_item(XItemCreator::new_item(this, pre_description));
}

//---------------------------------------------------------------------
void XModuleInterface::new_item(QString title_underscored, QString type,
                                  const QStringList &description,
                                  XQualifier qual, QString line_to_parse, QString options,
                                  QString qual_options) {
    push_item(XItemCreator::new_item(this, title_underscored, type, description, qual, line_to_parse, options, qual_options));
}

//---------------------------------------------------------------------
void XModuleInterface::new_decorate_item(QString name, QString type, const QStringList &description) {
    items_.push_back(XItemCreator::new_decorate_item(this, name, type, description));
    add_to_vis_group();
}


//---------------------------------------------------------------------
//проверка того, что разные элементы имеют разные имена, и заполнение map для быстрого доступа
void XModuleInterface::update_maps() {
    items_by_name_.clear();

    for (int i=0; i<items_.size(); i++) {
        XItem *item = items_[i];
        QString name = item->name();

        xc_assert(!name.isEmpty(), "Item name can't be empty, title: '" + item->title() + "'");
        xc_assert(!item->title().isEmpty(), "Item title can't be empty, name: '" + name + "'");

        xc_assert(!items_by_name_.contains(name), "Duplicated item '" + name + "'");
        items_by_name_[name] = item;
    }
}

//---------------------------------------------------------------------
//does module contains item with given name
bool XModuleInterface::has_item(QString name) {
    return items_by_name_.contains(name);
}

//---------------------------------------------------------------------
//элемент по имени - кроме сепараторов
XItem *XModuleInterface::var(QString name) {
    xc_assert(has_item(name), "Unknown item '" + name + "'");
    return items_by_name_[name];
}

//---------------------------------------------------------------------
//группы видимости - для создания дерева управления видимостью на GUI
QVector<VisibleGroupBase> &XModuleInterface::vis_groups() {
    return vis_groups_;
}

//---------------------------------------------------------------------
//Compiling links and other things
bool XModuleInterface::compile() {
    bool ok = true;
    for (auto item: items_) {
        try{
            item->compile();
        }
        catch(XException& e) {
            xc_console_append(e.whatQt());
            ok = false;
        }
    }
    return ok;
}

//---------------------------------------------------------------------
//called at start - enable buttons
void on_start() {
}

//---------------------------------------------------------------------
//called at start, stop and attach interface - enable/disable buttons
void XModuleInterface::update_is_running(bool running) {
    for (auto item: items_) {
        item->update_is_running(running);
    }
}

//---------------------------------------------------------------------
//сигнал, что GUI подключен/отключен
void XModuleInterface::gui_attached(XGuiEditor *editor) {
    editor_ = editor;
    for (int i=0; i<items_.size(); i++) {
        items_[i]->gui_attached();
    }
}

//---------------------------------------------------------------------
void XModuleInterface::gui_detached() {
    for (int i=0; i<items_.size(); i++) {
        items_[i]->gui_detached();
    }
    editor_ = nullptr;
}

//---------------------------------------------------------------------
bool XModuleInterface::is_gui_attached() {
    return (editor_ != nullptr);
}

//---------------------------------------------------------------------
//установить видимость, используется при тестировании интерфейса
void XModuleInterface::propagate_visibility() {
    for (auto item: items_) {
        item->propagate_visibility();
    }
}

//---------------------------------------------------------------------
//команды для обновления внутренних значений из GUI и в GUI
void XModuleInterface::gui_to_vars(const XQualifierMask &qual, bool evaluate_expr) {
    if (is_gui_attached()) {
        for (auto &item: items_) {
            item->gui_to_var(qual, evaluate_expr);
        }
    }
}

//---------------------------------------------------------------------
void XModuleInterface::vars_to_gui(const XQualifierMask &qual) {
    if (is_gui_attached()) {
        for (auto &item: items_) {
            item->var_to_gui(qual);
        }
    }
}

//---------------------------------------------------------------------
//заблокировать константы, вызывается перед запуском проекта
void XModuleInterface::block_gui(const XQualifierMask &qual) {
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
void XModuleInterface::unblock_gui(const XQualifierMask &qual) {
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
void XModuleInterface::reset_was_changed() {
    for (auto &item: items_) {
        item->reset_was_changed_simple();
    }
}

//---------------------------------------------------------------------
//update before rt-module's update
void XModuleInterface::update() {
    for (auto &item: items_) {
        item->update();
    }
}

//---------------------------------------------------------------------
//запомнить/восстановить состояние GUI (страницу, промотку)
void XModuleInterface::gui_to_state() {
    if (is_gui_attached()) {
        //xc_assert(editor_, "Internal error - XModuleInterface::gui_to_state is called, but editor_ == nullptr");
        editor_state_ = editor_->state();
    }
}

//---------------------------------------------------------------------
void XModuleInterface::state_to_gui() {
    if (is_gui_attached()) {
        //xc_assert(editor_, "Internal error - XModuleInterface::state_to_gui is called, but editor_ == nullptr");
        editor_->set_state(editor_state_);
    }
}

//---------------------------------------------------------------------
//callback из GUI
void XModuleInterface::callback_button_pressed(QString button_id) {
    xc_assert(module(), "Can't process pressing button '" + button_id + "' because module() is nullptr");
    module()->button_pressed(button_id);
}


//---------------------------------------------------------------------
//internal calling - user shouldn't call this
void XModuleInterface::_hit_button_(QString button_id) {
    XItem *item = var(button_id);
    xc_assert(item->type() == xitem_button(), "Can't press '" + button_id + "', because it's not button");
    ((XItemButton *)(item))->hit_value();
}

//---------------------------------------------------------------------
EditorModuleState XModuleInterface::editor_state() {
    return editor_state_;
}

//---------------------------------------------------------------------
void XModuleInterface::set_editor_state(EditorModuleState editor_state) {
    editor_state_ = editor_state;
}

//---------------------------------------------------------------------
//дублирование данных переменных и состояние редактора, используется при дублировании модулей
void XModuleInterface::copy_data_to(XModuleInterface *interf) {
    xc_assert(interf, "Internal error in XModuleInterface::copy_data_to: interface to copy is nullptr");
    interf->set_editor_state(editor_state());
    for (int i=0; i<items_.size(); i++) {
        auto *item = items_[i];
        if (item->store_data()) {
            QString name = item->name();
            auto *item1 = interf->var(name);
            xc_assert(item1, "Internal error in XModuleInterface::copy_data_to: no item '"
                        + name + "' in the destination interface");
            item->copy_data_to(item1);
        }
    }
}

//---------------------------------------------------------------------
//Запись и считывание json
void XModuleInterface::write_json(QJsonObject &json) {
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
void XModuleInterface::read_json(const QJsonObject &json) {

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
        xc_console_warning("Error(s) loading module '" + description().class_name + "':");
        for (int i=0; i<errors.size(); i++) {
            xc_console_warning("   " + errors.at(i));
        }
    }
}

//---------------------------------------------------------------------
//Variables access
//int, checkbox, button, enum (index), string, text
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
QString XModuleInterface::gets(QString name, int index, int index2) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xc_assert(var->supports_string(), "variable '" + name + "' doesn't supports string");
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
QStringList XModuleInterface::get_strings(QString name) {
    return gets(name).split("\n");
}

//---------------------------------------------------------------------
//только out: int, checkbox, enum (index), string, text
void XModuleInterface::sets(QString name, QString v) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xc_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xc_assert(var->supports_string(), "variable '" + name + "' doesn't supports string");
    var->set_value_string(v);
}

//---------------------------------------------------------------------
void XModuleInterface::clear_string(QString name) {
    sets(name, "");
}

//---------------------------------------------------------------------
//дописать к строке, применимо где sets
void XModuleInterface::append_string(QString name, QString v, int extra_new_lines_count) {
    QString value = gets(name);
    value.append(v);
    for (int i=0; i<1 + extra_new_lines_count; i++) {
        value.append("\n");
    }
    sets(name, value);
}

//---------------------------------------------------------------------
void XModuleInterface::append_string(QString name, QStringList v, int extra_new_lines_count) { //дописать к строке, применимо где sets
    append_string(name, v.join("\n"), extra_new_lines_count);
}

//---------------------------------------------------------------------
//int, checkbox, button, enum (index)
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
int XModuleInterface::geti(QString name, int index, int index2) {
    if (index == -1) {
        XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
        xc_assert(var->supports_int(), "variable '" + name + "' doesn't supports int");
        return var->value_int();
    }
    else {
        return gets(name, index, index2).toInt();
    }
}

//---------------------------------------------------------------------
//только out: int, checkbox, enum (index)
void XModuleInterface::seti(QString name, int v) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xc_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xc_assert(var->supports_int(), "variable '" + name + "' doesn't supports int");
    var->set_value_int(v);
}

//---------------------------------------------------------------------
//увеличение значения
void XModuleInterface::increase_int(QString name, int increase) { //value+=increase
    seti(name, geti(name) + increase);
}

//---------------------------------------------------------------------
//float
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
float XModuleInterface::getf(QString name, int index, int index2) {
    if (index == -1) {
        XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
        xc_assert(var->supports_float(), "variable '" + name + "' doesn't supports float");
        return var->value_float();
    }
    else {
        return gets(name, index, index2).toFloat();
    }
}

//---------------------------------------------------------------------
//только out: float
void XModuleInterface::setf(QString name, float v) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xc_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xc_assert(var->supports_float(), "variable '" + name + "' doesn't supports float");
    var->set_value_float(v);
}

//---------------------------------------------------------------------
//enum
QString XModuleInterface::getraw(QString name) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xc_assert(var->supports_value_raw(), "variable '" + name + "' doesn't supports raw value");
    return var->value_raw();
}

//---------------------------------------------------------------------
void XModuleInterface::set_raw(QString name, QString text) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xc_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xc_assert(var->supports_value_raw(), "variable '" + name + "' doesn't supports raw value");
    var->set_value_raw(text);
}

//---------------------------------------------------------------------
//enum (title)
QString XModuleInterface::get_title_value(QString name) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xc_assert(var->supports_value_title(), "variable '" + name + "' doesn't supports title value");
    return var->value_title();

}

//---------------------------------------------------------------------
//только out: enum (title)
void XModuleInterface::set_title_value(QString name, QString v) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xc_assert(var->is_out(), "Can't set value to var '" + name + "' because it's not output variable");
    xc_assert(var->supports_value_title(), "variable '" + name + "' doesn't supports title value");
    var->set_value_title(v);
}

//---------------------------------------------------------------------
//Access to objects is only by pointers - because we are required not to copy data, it can be large
XProtectedObject *XModuleInterface::get_object(QString name) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xc_assert(var->supports_object(), "variable '" + name + "' doesn't supports object");
    return var->get_object();
}

//---------------------------------------------------------------------
//Set pointer to object
//Note: object must be live, because only pointer to it is stored
void XModuleInterface::set_object(QString name, XProtectedObject *object) {
    XItem *var = this->var(name);   //проверка, что переменная есть - не требуется
    xc_assert(var->supports_object(), "variable '" + name + "' doesn't supports object");
    var->set_object(object);
}

//---------------------------------------------------------------------



