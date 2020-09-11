#include "moduledescription.h"
#include "incl_cpp.h"
#include "moduleregistrar.h"

//---------------------------------------------------------------------
ModuleRegisteredCalls::ModuleRegisteredCalls(QString line) {
    line = line.trimmed();
    if (line == "*") {
        any_ = true;
    }
    else {
        QStringList list = line.split(",");
        for (int i=0; i<list.size(); i++) {
            functions_[list[i].trimmed()] = 1;
        }
    }
}


//---------------------------------------------------------------------
bool ModuleRegisteredCalls::accepts(QString function) {
    if (any_) return true;
    return functions_.contains(function);
}

//---------------------------------------------------------------------
QString ModuleRegisteredCalls::to_string_gui() {        //конвертация в строку для выдачи в text
    if (any_) return "*";
    QString s;
    if (!functions_.isEmpty()) {
        QMapIterator<QString, int> i(functions_);
        while (i.hasNext()) {
            i.next();
            s.append(i.key());
            s.append("\n");
        }
    }
    return s;
}

//---------------------------------------------------------------------
QString ModuleDescription::generate_name_hint(QString class_name) { //GuiWindow -> gui_window
    //поиск больших букв
    QString lower = class_name.toLower();
    QString name;
    for (int i=0; i<class_name.length(); i++) {
        if (i > 0 && class_name.at(i) != lower.at(i)) {
            name += "_";
        }
        name += lower.at(i);
    }
    return name;
}

//---------------------------------------------------------------------
//парсинг описания модуля
bool ModuleDescription::parse_module_header_line(QString line) {
    QStringList list = line.split("=");
    if (list.size() >= 2) {
        QString name = list[0];
        QString value = list[1];
        return parse_module_header_line(name, value);
    }
    return false;
}

//---------------------------------------------------------------------
bool ModuleDescription::parse_module_header_line(QString name, QString value) {

    if (name == field_class_name()) {
        //нельзя перезатереть имя, если оно уже было установлено
        //это важно во встроенных модулях - у них имя берется из названия папки
        xclu_assert(class_name.isEmpty() || value.isEmpty(),
                    QString("Modules loading: Conflicting %1, tries to rewrite '%2' by '%3'")
                    .arg(field_class_name()).arg(class_name).arg(value));

        class_name = value;
        //подсказка для name по умолчанию - это class_name в нижнем регистре
        //if (id_hint.isEmpty()) {        //проверяем, что непуст - а вдруг его определенме было до module_class
        //    id_hint = value.toLower();
        //}
        //подсказка для name по умолчанию - это class_name
        if (name_hint.isEmpty()) {     //проверяем, что непуст - а вдруг его определенме было до module_class
            name_hint = generate_name_hint(value);
        }
        return true;
    }
    //if (name == field_id_hint()) {
    //    id_hint = value; return true;
    //}
    if (name == field_name_hint()) {
        name_hint = value; return true;
    }
    if (name == field_category()) {
        //нельзя перезатереть категорию, если она уже была установлена
        //это важно во встроенных модулях - у них категория берется из названия папки
        xclu_assert(category.isEmpty() || value.isEmpty(),
                    QString("Modules loading: Conflicting %1, tries to rewrite '%2' by '%3'")
                    .arg(field_class_name()).arg(category).arg(value));

        category = value;
        return true;
    }
    if (name == field_description()) {
        description = value; return true;
    }
    if (name == field_version()) {
        version = value; return true;
    }
    if (name == field_impl()) {
        impl = string_to_moduleimpltype(value); return true;
    }
    //if (name == field_default_run_mode()) {
    //    default_run_mode = string_to_ModuleRunMode(value); return true;
    //}
    if (name == field_accept_calls()) {
        accept_calls = value;   //вызовется конструктор из QString
        return true;
    }
    if (name == field_send_calls()) {
        send_calls = value;     //вызовется конструктор из QString
        return true;
    }
    return false;
}

//---------------------------------------------------------------------
bool ModuleDescription::is_implemented() {  //реализован ли уже модуль
    return XModuleRegistrar::is_module_implemented(class_name);
}

//---------------------------------------------------------------------

