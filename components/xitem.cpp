#include <QJsonObject>
#include <QJsonArray>

#include "xitem.h"
#include "incl_cpp.h"
#include "xitempage.h"
#include "xitemseparator.h"
#include "xitemfloat.h"
#include "xitemint.h"
#include "xitemcheckbox.h"
#include "xitemstring.h"
#include "xitemenum.h"
#include "xitembutton.h"
#include "xitemtext.h"
#include "xitemobject.h"

#include "xguicomp.h"
#include "registrarxitem.h"
#include "xmoduleinterface.h"
#include "xmodule.h"
#include "dialogeditlink.h"

//---------------------------------------------------------------------
/*static*/ XItem *XItemCreator::new_item(XModuleInterface *interf,
                                         QString title_underscored,
                                         QString type,
                                         const QStringList &description,
                                         XQualifier qual,
                                         QString line_to_parse,
                                         QString options,
                                         QString qual_options
                                         ) {
    XItemPreDescription descr;
    descr.title = xc_remove_underscore(title_underscored);
    descr.type = type;
    descr.qualifier = qual;
    descr.qualifier_options = qual_options;
    descr.line_to_parse = line_to_parse;
    descr.options = options;
    descr.description = description;
    return new_item(interf, descr);
}

//---------------------------------------------------------------------
//page, group
/*static*/ XItem *XItemCreator::new_decorate_item(XModuleInterface *interf,
                                                  QString name,
                                                  QString type, const QStringList &description) {
    //QString title = xc_remove_underscore(name);
    return new_item(interf, name, type, description, XQualifier::In, name);
}

//---------------------------------------------------------------------
//separator, separator_line
/*static*/ XItem *XItemCreator::new_separator(XModuleInterface *interf, QString name, QString type_raw) {
    QString descr;

    QStringList type_options=type_raw.split("_");
    xc_assert(!type_options.isEmpty(), "bad type name for separator '" + type_raw + "'");

    auto type = type_options.at(0);
    type_options.removeFirst();

    QString options = type_options.join("_");

    return new_item(interf, name, type, QStringList(), XQualifier::In, name, options);
}

//---------------------------------------------------------------------
/*static*/ XItem *XItemCreator::new_item(XModuleInterface *interf, const XItemPreDescription &pre_description) {
    return RegistrarXItem::create_xitem(interf, &pre_description);
}


//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//создание пункта интерфейса, и парсинг остатка строки line_to_parse
XItem::XItem(XModuleInterface *interf, const XItemPreDescription &pre_description) {
    //Проверка, что interf не нулевой - возможно, в конструкторе это не очень хорошо, но все же лучше проверить:)
    xc_assert(interf,
              "Internal error in XItem constructor, empty 'XModuleInterface *interf' at '" + pre_description.title + "'");
    interf_ = interf;
    title_ = pre_description.title;
    type_ = pre_description.type;
    qualifier_ = pre_description.qualifier;
    description_ = pre_description.description;

    //опции квалификатора, может быть только out(save)
    auto &options = pre_description.qualifier_options;
    xc_assert(options.isEmpty() || (options.contains("save") && qualifier_ == XQualifier::Out),
              "Currently only out(save) option supported, but get other for " + pre_description.line_to_parse);

    //ставим, нужно ли сохранять в проект
    if (qualifier_ != XQualifier::Out) {
        save_to_project_ = true;
    }
    else {
        save_to_project_ = (options.contains("save"));
    }

}

//---------------------------------------------------------------------
XItem::~XItem() {

}

//---------------------------------------------------------------------
XModuleInterface *XItem::interf() {
    return interf_;
}

//---------------------------------------------------------------------
XModule *XItem::module() {
    xc_assert(interf(), "XItem::module() error: empty interf()");
    return interf()->module();
}

//---------------------------------------------------------------------
//Compiling links and other things
void XItem::compile() {
    resolve_link();
}

//---------------------------------------------------------------------
//checks changes at current frame
//and maintains "link" copying (for scalars and objects) or sets pointer (for objects optionally)
//Note: update should be called after updating value from user GUI to correctly maintain "was changed"
void XItem::update() {

    //Copy value from link
    if (is_linked()) {
        auto *linkres = link_resolved_.data();
        // If nullptr - then may be we just starting, so omit assert
        //xc_assert(linkres, "XItem::update error for `" + name() + "`: link_resolved_ is nullptr");
        if (linkres) {
            set_value_from_link(linkres);
        }
    }

    //Update was_changed
    was_changed_ = was_changed(was_changed_checker_);
}

//---------------------------------------------------------------------
QString XItem::name() {
    return name_;
}

//---------------------------------------------------------------------
QString XItem::title() {
    return title_;
}

//---------------------------------------------------------------------
QString XItem::type() {
    return type_;
}

//---------------------------------------------------------------------
XQualifier XItem::qualifier() {
    return qualifier_;
}

//---------------------------------------------------------------------
bool XItem::is_const() {
    return (qualifier_ == XQualifier::Const);
}

//---------------------------------------------------------------------
bool XItem::is_in() {
    return (qualifier_ == XQualifier::In);
}

//---------------------------------------------------------------------
bool XItem::is_out() {
    return (qualifier_ == XQualifier::Out);
}

//---------------------------------------------------------------------
bool XItem::is_save_to_project() {
    return save_to_project_;
}

//---------------------------------------------------------------------
//Описание добавляется уже после создания, следующей строкой в скрипте GUI
QString XItem::description(int index) {
    if (index >= 0 && index < description_.size()) {
        return description_.at(index);
    }
    return "";
}

//---------------------------------------------------------------------
//Checking that value was changed
//works relative to save "change chacker", which stores frame fo last check
//It's really implemented at XItem_<T>, so here just returns "false"
bool XItem::was_changed(XWasChangedChecker & /*checker*/) {
    return false;
}

//---------------------------------------------------------------------
//Set "was changed" at start. Really it's implemented in XItem_<T>, but here just reset was_changed_
void XItem::reset_was_changed_simple() {
    was_changed_checker_.reset();
    was_changed_ = true;
}

//---------------------------------------------------------------------
int XItem::description_count() {
    return description_.size();
}

//---------------------------------------------------------------------
/*void XItem::add_description(QString description) {
    //xc_assert(description_.isEmpty(), "non-empty description for variable '" + name_ + "' is already set, but trying to set another '" + description + "'");
    //description_ = description;
    description_.append(description);
}
*/

//---------------------------------------------------------------------
//Link ----------------------------------------------------------------
//---------------------------------------------------------------------
//link to itself
XLinkParsed XItem::get_link_to_itself() {
    return XLinkParsed(interf()->module()->name(), name());
}

//---------------------------------------------------------------------
//can be link used (for out - no), used for project saving
bool XItem::is_link_can_be_used() {
    return (!is_out());
}

//---------------------------------------------------------------------
//use link
bool XItem::is_linked() const {
    return link_.enabled;
}

//---------------------------------------------------------------------
const XLink &XItem::link() const {
    return link_;
}

//---------------------------------------------------------------------
void XItem::set_link(const XLink &link) {
    if (!link_.is_equal(link)) {
        link_ = link;
        link_was_changed();
    }
}

//---------------------------------------------------------------------
void XItem::set_link(bool enabled, QString link) {
    set_link(XLink(enabled, link));
}

//---------------------------------------------------------------------
void XItem::clear_link() {
    set_link(XLink());
}

//---------------------------------------------------------------------
//Function for setting value using link
//Subclasses must implement it
void XItem::set_value_from_link(XLinkResolved * /*linkres*/) {
    xc_exception("set_value_from_link is not implemented for `" + name() + "`");
}

//---------------------------------------------------------------------
//User change link settings - should show it in GUI
void XItem::link_was_changed() {
    if (is_gui_attached() && gui__) {
        gui__->link_was_changed();
    }
    xc_document_modified();
    //if running - then resolve link immediately
    if (is_running()) {
        resolve_link();
    }
}

//---------------------------------------------------------------------
//status of run - get from parent module
bool XItem::is_running() {
    return (module() && module()->is_running());
}

//---------------------------------------------------------------------


//---------------------------------------------------------------------
//find item corresponding to link
//called from `compile` and `link_was_changed`
void XItem::resolve_link() {
    try{
        if (is_linked()) {
            link_resolved_.reset(new XLinkResolved(link_.link));
        }
        else {
            link_resolved_.reset();
        }
    }
    catch(XException& e) {
        throw XException(QString("Error at module '%1' while resolving link for `%2`: %3")
                         .arg(module()->name())
                         .arg(title()).arg(e.whatQt()));
    }

}

//---------------------------------------------------------------------
//Expression ----------------------------------------------------------
//---------------------------------------------------------------------
bool XItem::is_expression_can_be_used() {
    return (!is_out());
}

//---------------------------------------------------------------------
bool XItem::is_use_expression() {  //используется ли expression для установки значения
    return use_expression_;
}

//---------------------------------------------------------------------
void XItem::set_use_expression(bool v) {
    use_expression_ = v;
}

//---------------------------------------------------------------------
QString XItem::expression() {
    return expression_;
}

//---------------------------------------------------------------------
void XItem::set_expression(const QString &expr) {
    expression_ = expr;
}

//---------------------------------------------------------------------
//парсинг q=0 0:1 100,10 -> name='q', query = '0','0:1','100,10'
//        v="aaa bbb" -> name='v', query = "aaa bbb"
/*static*/ void XItem::split_equal(const QString &line, QString &name, QStringList &query) {
    int equal = line.indexOf('=');
    xc_assert(equal != -1, "no '=', expect 'some_name=...'");
    xc_assert(equal != 0, "empty variable name, expect 'some_name=...'");
    name = line.left(equal);

    QString right = line.mid(equal+1);
    query.clear();
    if (!right.isEmpty()) {
        //"aaa bbb"
        if (right.startsWith('"')) {
            query.push_back(right);
        }
        else {
            //0 0:1 100,10
            QRegExp rx("(\\ |\\t)"); //RegEx for ' ' or '\t'
            query = QString(line.mid(equal+1)).split(rx);
        }
    }
    //xc_assert(!query.isEmpty(), "expected something after '='");
}

//---------------------------------------------------------------------
//парсинг q A B -> name='q', query = 'A','B'
/*static*/ void XItem::split_spaced(const QString &line, QString &name, QStringList &query) {
    QRegExp rx("(\\ |\\t)"); //RegEx for ' ' or '\t'
    query = line.split(rx);
    xc_assert(!query.isEmpty(), "empty name, expected ... q ...");
    name = query.at(0);
    query.removeFirst();
}

//---------------------------------------------------------------------
//графический интерфейс, он тут создается, но хранится отдельно
XGuiComp *XItem::create_gui(XGuiPageBuilder &page_builder) {
    gui__ = new XGuiComp(page_builder, this);
    return gui__;   //не нужно его удалять
}

//---------------------------------------------------------------------
//сигнал, что GUI подключен/отключен
void XItem::gui_attached() {
    gui_attached_ = true;
}

//---------------------------------------------------------------------
void XItem::gui_detached() {
    gui_attached_ = false;
}

//---------------------------------------------------------------------
bool XItem::is_gui_attached() {
    return gui_attached_;
}

//---------------------------------------------------------------------
bool XItem::is_matches_qual_mask(const XQualifierMask &qual) {
    //if item is linked - it's the most important!
    if (is_linked()) {
        return qual.qual_link;
    }
    else {
        return (
                    (qual.qual_const && is_const())
                    || (qual.qual_in && is_in())
                    || (qual.qual_out && is_out())
                    );
    }

}

//---------------------------------------------------------------------
void XItem::gui_to_var(const XQualifierMask &qual, bool evaluate_expr) { //вычисление expression и получение значения из gui
    if (is_gui_attached() && is_matches_qual_mask(qual)) {
        if (is_use_expression()) {
            if (evaluate_expr) {
                //... expression()
                //if (is_gui_attached()) {
                //    var_to_gui_internal();
                //}
            }
        }
        else {
            if (is_gui_attached()) {
                gui_to_var_internal();
            }
        }
    }
}

//---------------------------------------------------------------------
void XItem::var_to_gui(const XQualifierMask &qual) { //установка значения в gui, также отправляет сигнал о видимости
    //if (!is_use_expression()) {
    if (is_gui_attached() && is_matches_qual_mask(qual)) {
        var_to_gui_internal();
        //отправляем сигнал о видимости
        propagate_visibility();
    }
}

//---------------------------------------------------------------------
void XItem::propagate_visibility() {    //обновить дерево видимости - используется, в частности, при тестировании интерфейса
    if (gui__) {
        gui__->propagate_visibility();
    }
}

//---------------------------------------------------------------------
//запретить редактирование - всегда для out и после запуска для const
void XItem::block_gui_editing(const XQualifierMask &qual) {
    if (is_matches_qual_mask(qual) && is_gui_attached()) {
        if (gui__) {
            gui__->block_editing_on_running();
        }
    }
}

//---------------------------------------------------------------------
//force GUI element to update - useful at long operations for updating texts/numbers, calls repaint_internal()
void XItem::redraw() {
    if (is_gui_attached()) {
        var_to_gui_internal();
        //propagate_visibility();

        bool force_process_events = true;
        gui__->repaint_(force_process_events);  //NOTE: forcing qApp to process events!
    }
}

//---------------------------------------------------------------------
//разрешить редактирование
void XItem::unblock_gui_editing(const XQualifierMask &qual) {
    if (is_matches_qual_mask(qual) && is_gui_attached()) {
        if (gui__) {
            gui__->unblock_editing_on_stopping();
        }
    }
}

//---------------------------------------------------------------------
//копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
//специальные типы, которые не поддерживают перенос через строку (array и image) - должны переписать copy_data_to_internal
void XItem::copy_data_to(XItem *item) {
    //если для данного типа не надо копировать - то ничего не делаем
    if (!store_data()) return;

    xc_assert(name() == item->name(), "Internal error XItem::copy_data_to: different items names '"
              + name() + "' and '" + item->name() + "'");
    xc_assert(type() == item->type(), "Internal error XItem::copy_data_to: different items types '"
              + type() + "' and '" + item->type() + "'");

    item->set_use_expression(is_use_expression());
    item->set_expression(expression());

    //если можно пробросить через строку - делаем так
    if (supports_string()) {
        item->set_value_string(value_string());
    }
    else {
        //иначе - item должен иметь реализованную copy_data_to_internal
        copy_data_to_internal(item);
    }

}

//---------------------------------------------------------------------
void XItem::copy_data_to_internal(XItem *) {
    xc_halt("Internal error: copy_data_to_internal is not implemented for type '" + type() + "'");
}

//---------------------------------------------------------------------
//Запись и считывание json
void XItem::write_json(QJsonObject &json) {
    if (!is_save_to_project()) return;
    if (!store_data()) return;
    xc_assert(supports_string(), "Can't write item '" + name_ + "' to json");

    //"a..." - чтобы были в начале списка
    json["aname"] = name_;
    json["avalue"] = value_string_json();

    //link
    if (!link().is_empty()) {
        json["link"] = link().to_str();
        //xc_console_append(link().to_str());
    }

    //json["atitle"] = title_;
    //json["atype"] = interfacetype_to_string(type_);  //записываем, чтобы отловить ошибки при изменении интерфейса

    //if (is_expression_can_be_used()) {
    //json["expr_use"] = use_expression_;
    //json["expr"] = expression_;
    // }
}

//---------------------------------------------------------------------
void XItem::read_json(const QJsonObject &json) {
    if (!is_save_to_project()) return;
    if (!store_data()) return;
    xc_assert(supports_string(), "Can't read item '" + name_ + "' from json, because it's has 'out' (that means read-only) qualifier.\n"
                                                               "May be module's version is different");
    //проверяем, что имя совпадает
    QString name = JsonUtils::json_string(json, "aname");
    xc_assert(name == name_, "Different name for '" + name_ + "'.\n"
                                                              "May be module's version is different");

    //значение
    set_value_string_json(JsonUtils::json_string(json, "avalue"));

    //link
    QString link_str = JsonUtils::json_string(json, "link", "");
    if (!link_str.isEmpty()) {
        set_link(XLink(link_str));
    }

    //заголовок - закомментировал, пусть он меняется
    //title_ = JsonUtils::json_string(json, "atitle");

    //проверяем, что тип совпадает
    //QString type_str = JsonUtils::json_string(json, "atype");
    //xc_assert(type_str == interfacetype_to_string(type_), "Different type for '" + name_ + "'.\n"
    //            "May be module's version is different");


    //expression
    //if (is_expression_can_be_used()) {
    //    use_expression_ = JsonUtils::json_bool(json, "expr_use");
    //    expression_ = JsonUtils::json_string(json, "expr");
    //}

}


//---------------------------------------------------------------------
//Belonging to general page, common for all modules
void XItem::set_belongs_general_page(bool v) {
    belongs_general_page_ = v;
}

//---------------------------------------------------------------------
bool XItem::belongs_general_page() {
    return belongs_general_page_;
}

//---------------------------------------------------------------------
//Context menu
ComponentContextMenuInfo XItem::context_menu_info() {
    //xc_console_append(get_link_to_itself);
    return ComponentContextMenuInfo(
                get_link_to_itself().to_str(), link().link,
                is_link_can_be_used(), is_linked(),
                context_menu_has_set_default_value(),
                context_menu_has_set_size());
}

//---------------------------------------------------------------------
//Processing the context menu actions
//Subclasses must implement non-common actions and call parent method
void XItem::context_menu_on_action(ComponentContextMenuEnum id, QString action_text) {
    switch (id) {
    case ComponentContextMenu_use_input: {
        XLink link1 = link();
        link1.enabled = false;
        set_link(link1);
    }
        break;
    case ComponentContextMenu_use_link: {
        XLink link1 = link();
        link1.enabled = true;
        set_link(link1);
    }
        break;
    case ComponentContextMenu_edit_link: {
        DialogEditLink::call_dialog(DialogEditLinkData(module()->name(), this));
    }
        break;
    case ComponentContextMenu_paste_link:
    {
        QString text = XLink::get_link_from_clipboard();
        if (!text.isEmpty()) {
            set_link(XLink(true, text));
        }
    }
        break;
    case ComponentContextMenu_copy_link: {
        QString link = get_link_to_itself().to_str();
        xc_clipboard_set_text(link);
        xc_console_append("Clipboard: `" + link + "'");
    }
        break;
        //this cases must be implemented in subclasses
    case ComponentContextMenu_reset_default_value:
    case ComponentContextMenu_set_size:
        xc_exception(QString("XGuiComp::on_component_popup_action - not implemented response to `%1`").arg(action_text));
        break;
    default:
        xc_exception(QString("XGuiComp::on_component_popup_action error - bad action `%1`").arg(action_text));
    }

}

//---------------------------------------------------------------------
//function `export_interface` generates function or functions definitions
//Subclasses must reimplement it, in opposite case the exception will arise.

/* The example generation:
//Page Main
//...

//Folder to scan.
QString gets_folder() {...}
void sets_folder(QString value) {...}

//Enum Position
//Position of the window.
enum enum_position {
    position_Default = 0,
    position_Custom = 1,
    position_Screen_Center = 2,
    position_N__ = 3
};
bool was_changed_position() { ... }
enum_position gete_position() { ... }

Function names begin with prefix denoting type of the item as the following:

    geti_..., seti_... - int, button, checkbox
    gete_..., sete_..., gets_... - enum
    getf_...,setf_... - float
    gets_..., sets_... - string, text
    getstruct_... - structure

Also are defined the following useful functions:

    was_changed_... - all items,
    get_strings_... - string, text
    clear_string_..., append_string_... - out string, out text,
    increase_int_... - out int,
    QString button_... - button, for using in impl_button_pressed()
    repaint_... - applicable to all out items, it refreshes the associated GUI widget; applied for out variables for informing user about status during long operations.

 */

void XItem::export_interface(QStringList & /*file*/) {
    xc_exception("Can't generate C++ header for interface element of type `" + type() + "' - not implemented yet!");
}

//---------------------------------------------------------------------
//Helper for export_interface
//----------------------------------------------------
/*
    //Page Main
    //...

    //Folder to scan.
    QString gets_folder() {...}
    void sets_folder(QString value) {...}

    //Enum Position
    //Position of the window.
    enum enum_position {
        position_Default = 0,
        position_Custom = 1,
        position_Screen_Center = 2,
        position_N__ = 3
    };
    bool was_changed_position() { ... }
    enum_position gete_position() { ... }
*/
//-----------------
//Note: `enum` main part of export is added at file `xitemenum.cpp`
//-----------------

void XItem::export_interface_template(QStringList &file,
                                      bool horiz_line,
                                      bool comment_description,
                                      QString custom_comment_begin,
                                      bool getter_setter,
                                      QString cpp_type,
                                      QString fun_prefix,
                                      QString cpp_getter,
                                      QString cpp_setter,
                                      bool final_blank,
                                      bool is_int,
                                      bool is_string,
                                      bool is_object) {
    if (horiz_line) {
        file.append("//----------------------------------------------------");
    }
    if (comment_description) {
        QString qualif;
        if (qualifier() == XQualifier::Out) qualif = "Out ";
        if (qualifier() == XQualifier::Const) qualif = "Const ";
        file.append("//" + qualif + custom_comment_begin + title());
        file.append("//" + description());
    }
    if (getter_setter) {
        file.append(QString("bool was_changed_%1() { return was_changed_(\"%1\"); }").arg(name()));
        file.append(QString("%2get%3_%1() { return %4_(\"%1\"); }").arg(name()).arg(cpp_type).arg(fun_prefix).arg(cpp_getter));

        if (is_string) {
            //get_strings
            file.append(QString("QStringList get_strings_%1() { return get_strings_(\"%1\"); }").arg(name()));
        }

        //out
        if (qualifier() == XQualifier::Out
                && !cpp_setter.isEmpty()) {
            file.append(QString("void set%3_%1(%2value) { %4_(\"%1\", value); }").arg(name()).arg(cpp_type).arg(fun_prefix).arg(cpp_setter));
            //additional for object without pointers:
            if (is_object) {
                //looks like: void setobject_output1(XProtectedObject *value) { set_object_("output1", value); }
                file.append(QString("void setobject_%1(XProtectedObject &value) { set_object_(\"%1\", value); }").arg(name()).arg(cpp_type).arg(fun_prefix).arg(cpp_setter));
            }

            if (is_int) {
                //increase_int
                file.append(QString("void increase_int_%1(int increase = 1) { increase_int_(\"%1\", increase); }").arg(name()));
            }
            if (is_string) {
                //clear_string
                file.append(QString("void clear_string_%1() { clear_string_(\"%1\"); }").arg(name()));
                //append_string
                file.append(QString("void append_string_%1(QString v, int extra_new_lines_count = 0) { append_string_(\"%1\", v, extra_new_lines_count); }").arg(name()));
                file.append(QString("void append_string_%1(QStringList v, int extra_new_lines_count = 0) { append_string_(\"%1\", v, extra_new_lines_count); }").arg(name()));
            }
        }
        //redraw
        file.append(QString("void repaint_%1() { repaint_(\"%1\"); }").arg(name()));
    }
    if (final_blank) {
        file.append("");
    }
}


//---------------------------------------------------------------------



