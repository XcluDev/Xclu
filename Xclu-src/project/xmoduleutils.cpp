#include "xmoduleutils.h"
#include "project.h"

//---------------------------------------------------------------------
QVector<XModule *> XModuleUtils::find_modules_by_filter(XCallType accept_calls_filter,
                                         XCallType send_calls_filter,
                                         QString class_filter,
                                         bool require_enabled) {
    return PROJECT.find_modules_by_filter(accept_calls_filter, send_calls_filter, class_filter, require_enabled);
}

//---------------------------------------------------------------------
// void XModuleUtils::call(XModule *module, XType function, XObject *input, XObject *output) {
//    xc_assert(module, "XModuleUtils::call failed, module is nullptr");
//    module->call(function, input, output);
// }

//---------------------------------------------------------------------
//Получение модуля
XModule *XModuleUtils::find_module(QString module_name) {
    return PROJECT.find_module_by_name(module_name);
}

//---------------------------------------------------------------------
//Построение списка модулей по строке, в которой модули разделены \n,
//а также могут быть пустые строки и комментарии, начинающиеся с #, например:
//    #name of modules to play sound
//    Synth1
//    Synth2
//Это используется для callback модулей, а также сбора данных с разных модулей - например, звуковых буферов
//для воспроизведения
/*static*/ QVector<XModule *> XModuleUtils::find_modules(QString modules_list) {
    QStringList list = QString(modules_list).split("\n");
    QVector<XModule *> out_list;

    for (int i=0; i<list.size(); i++) {
        QString name = list.at(i).trimmed();
        if (!name.isEmpty() && !name.startsWith("#")) {
            out_list.push_back(PROJECT.find_module_by_name(name));
        }
    }
    return out_list;
}

//---------------------------------------------------------------------
//Получение переменных по link
int XModuleUtils::get_int_by_link(QString link_str, int def_val) {
    XLinkParsed link(link_str);
    if (link.is_empty) return def_val;
    return XModuleUtils::find_module(link.module)->geti(link.var, link.index, link.index2);
}

//---------------------------------------------------------------------
float XModuleUtils::get_float_by_link(QString link_str, float def_val) {
    XLinkParsed link(link_str);
    if (link.is_empty) return def_val;
    return XModuleUtils::find_module(link.module)->getf(link.var, link.index, link.index2);
}

//---------------------------------------------------------------------
QString XModuleUtils::get_string_by_link(QString link_str, QString def_val) {
    XLinkParsed link(link_str);
    if (link.is_empty) return def_val;
    return XModuleUtils::find_module(link.module)->gets(link.var, link.index, link.index2);
}

//---------------------------------------------------------------------
XProtectedObject *XModuleUtils::get_object_by_link(QString link_str) {
    XLinkParsed link(link_str);
    return XModuleUtils::find_module(link.module)->get_object(link.var);
}

//---------------------------------------------------------------------
//Send bang to module
//General: module1 or press button: module1->button1
void XModuleUtils::press_button_by_link(QString module_link) {
    XLinkParsed link(module_link);
    if (link.var.isEmpty()) XModuleUtils::find_module(link.module)->bang();
    else XModuleUtils::find_module(link.module)->button_pressed(link.var);
}

//---------------------------------------------------------------------
//Send bang to modules
//General: module1 or press button: module1->button1
//Empty lines and lines started from "#" - ignored
void XModuleUtils::press_button_by_link(QStringList modules) {
    for (auto &line: modules) {
        QString module_link = line.trimmed();
        if (module_link.isEmpty()) continue;
        if (module_link.startsWith("#")) continue;
        XModuleUtils::press_button_by_link(module_link);
    }
}

//---------------------------------------------------------------------
/*XItem *xc_get_var_by_link(QString link_str) {
    XLinkParsed link(link_str);
    XModule *module = get_module(link.module);
    return module->interf()->var(link.var);
}*/

//---------------------------------------------------------------------
/*XObject *XModuleUtils::get_object_by_link(QString link_str) {
    XLinkParsed link(link_str);
    XModule *module = get_module(link.module);
    return module->get_object(link.var);
}*/

//---------------------------------------------------------------------
//Выполнение Callbacks
//список name модулей может быть разделен \n, TAB, пробелами
//то есть идти из text или string
/*static*/ /*void xc_execute_callbacks(QVector<XModule *> modules_list) {
    for (int i=0; i<modules_list.size(); i++) {
        modules_list[i]->execute(ModuleExecuteStageCallback);
    }
}*/

//---------------------------------------------------------------------
/*static*//* void xc_execute_callbacks(QString modules_list_string) {
    execute_callbacks(get_modules(modules_list_string));
}*/


//---------------------------------------------------------------------
