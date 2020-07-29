#ifndef MODULEDESCRIPTION_H
#define MODULEDESCRIPTION_H

//Описание модуля - имя класса, категория,
//а также описание, какие вызовы он принимает и какие вызовы может осуществлять

#include "incl_qt.h"


//Класс для работы с вызовами.
//Его конструктор принимает строку, в которй идет список названий функций через запятую,
//"*" - значит все функции.
//В случае ошибки конструктор генерирует исключение
//После создания, класс позволяет проверить, является ли заданная функция зарегистрированной
//Это используется для контроля call-вызовов
class ModuleRegisteredCalls {
public:
    ModuleRegisteredCalls() {}
    ModuleRegisteredCalls(QString line);
    bool accepts(QString function);     //разрешен ли вызов функции
    QString to_string_gui();        //конвертация в строку для выдачи в text
protected:
    QMap<QString, int> functions_;   //делаем QMap, чтобы было упорядоченно
    bool any_ = false;
};


//Описание модуля
struct ModuleDescription {
    //Внимание, при изменении - требуется скорректировать
    //запись/считывание json в module.cpp


    //Названия полей - заводим переменную, а также добавляем название поля
#define MOD_DESCR_FIELD(NAME, SUFFIX) \
    QString NAME##SUFFIX; \
    static QString field_##NAME() { return "module_"#NAME; }

    QString class_name;
    static QString field_class_name() { return "module_class"; }

    //после запятой пусто - значит будет создана переменная id_hint, а поле - module_id_hint
    //если не пусто - то это суфикс, например impl_ - чтобы хранить строку
    MOD_DESCR_FIELD(id_hint, );
    MOD_DESCR_FIELD(name_hint,);
    MOD_DESCR_FIELD(category,);
    MOD_DESCR_FIELD(description,);
    MOD_DESCR_FIELD(version,);
    MOD_DESCR_FIELD(impl, _);
    MOD_DESCR_FIELD(default_run_mode, _);
    MOD_DESCR_FIELD(accept_calls, _);
    MOD_DESCR_FIELD(send_calls, _);

    ModuleImplType impl=ModuleImplTypeNone;
    ModuleRunMode default_run_mode = ModuleRunMode_Main_Loop; //режим работы, который выставлять по умолчанию
    ModuleRegisteredCalls accept_calls;   //список через запятую названий функций, которые модуль может обработать. "*" - значит все функции.
    ModuleRegisteredCalls send_calls;  //список через запятую названий функций, которые модуль может послать. "*" - значит все функции.

    //парсинг описания модуля
    //возвращает true, если строка использовалась
    bool parse_module_header_line(QString line);
    bool parse_module_header_line(QString name, QString value);

    bool is_implemented();  //реализован ли уже модуль

    //полное ли описание
    bool is_complete() {
        return !class_name.isEmpty()
                && !id_hint.isEmpty()
                && !category.isEmpty()
                && !description.isEmpty()
                && !version.isEmpty()
                && (impl != ModuleImplTypeNone);
    }
};

#endif // MODULEDESCRIPTION_H
