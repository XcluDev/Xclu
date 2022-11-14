#pragma once

#include "xmodule.h"

// Вспомогательный класс для поиска модулей, а также нажатия кнопок
// и получения значений по ссылкам вида MODULE->item

class XModuleUtils {
public:
    //----------------------------------------------------------
    //Find modules by a filter
    //----------------------------------------------------------
    // 'accept_calls_filter', 'send_calls_filter', 'type_filter' are parts of name,
    // if XType::none or if empty - it means "all" for a given filter
    static QVector<XModule *> find_modules_by_filter(XCallType accept_calls_filter = XCallType::none,
                                             XCallType send_calls_filter = XCallType::none,
                                             QString class_filter = "",
                                             bool require_enabled = true);

    //Получение модуля - можно получить к нему доступ, см. класс XLinkParsed
    //а затем взять нужную переменную по geti и прочим
    static XModule* find_module(QString module_name);

    //Построение списка модулей по строке, в которой модули разделены \n,
    //а также могут быть пустые строки и комментарии, начинающиеся с #, например:
    //    #name of modules to play sound
    //    Synth1
    //    Synth2
    //Это используется для callback модулей, а также сбора данных с разных модулей - например, звуковых буферов
    //для воспроизведения
    static QVector<XModule *> find_modules(QString modules_list);


    //Получение переменных по link - то есть по имени модуля и названию в формате webcam1->image//
    //Если link пустой - возвращает def_val
    static int get_int_by_link(QString link_str, int def_val = 0);
    static float get_float_by_link(QString link_str, float def_val = 0);
    static QString get_string_by_link(QString link_str, QString def_val = "");
    static XProtectedObject* get_object_by_link(QString link_str);

    //Send signal to press button to module, or bang to whole module
    //"module1->button1" or "module1"
    static void press_button_by_link(QString module_link);

    //Send signals to press buttons to modules, or bang to whole modules
    //Empty lines and lines started from "#" - ignored
    static void press_button_by_link(QStringList modules);

    //Выполнение Callbacks
    //список name модулей может быть разделен \n, TAB, пробелами
    //то есть идти из text или string
    //static void execute_callbacks(QVector<XModule *> modules_list);
    //static void execute_callbacks(QString modules_list_string);

protected:
    // static void call(XModule *module, XType function, XObject *input, XObject *output = nullptr);
};

