#ifndef RTMODULEREGISTRAR_H
#define RTMODULEREGISTRAR_H

//Здесь реализована автоматизация регистрации исполняемых модулей
//Модули с конкретными реализациями должны добавлять в своем CPP-файле строку:
//REGISTRAR(Имя), например, для XModuleExecute это будет:
//REGISTRAR(Execute)
//После этого модуль зарегистрируется и может быть создан в XModulesFactory
//Макрос REGISTRAR объявлен в конце этого файла.

#include "incl_h.h"
#include "moduledescription.h"

//тип функции для регистрации модуля
class XModule;
typedef std::function<XModule *()> XModuleCreateFunction;

//класс для регистрации модуля
class RegistrarXModule
{
public:
    RegistrarXModule();

    //Функция для регистрации модуля по имени класса
    static void register_rt_class(QString class_name, XModuleCreateFunction creator_function);

    //Проверка, реализован ли модуль
    static bool is_module_implemented(QString class_name);

    //Создание модуля по имени класса
    static XModule *create_rt_module(const ModuleDescription &description);
};

//------------------------------------------------------------------
//макрос для регистрации класса модуля
//для этого создаем класс и объявляем один объект, который в своем конструкторе вызывает нужное добавление в класc
//так мы избавляемся от необходимости прописывать в коде все названия классов
//  ## - конкатенация в коде   # - превратить в строку
#define REGISTRAR(CLASS_NAME) \
    QString *XModule##CLASS_NAME::static_class_name_ptr; \
    QString Rt_ClassName_##CLASS_NAME = #CLASS_NAME; \
    struct Registrar_##CLASS_NAME { \
        Registrar_##CLASS_NAME() { \
            XModule##CLASS_NAME::static_class_name_ptr = &Rt_ClassName_##CLASS_NAME; \
            RegistrarXModule::register_rt_class(Rt_ClassName_##CLASS_NAME, std::bind(&XModule##CLASS_NAME::new_module)); \
        } \
    }; \
    Registrar_##CLASS_NAME registrar_##CLASS_NAME;

/*
Использование:
REGISTRAR(Execute)

приведет к вставке такого кода:

QString Rt_ClassName_Execute = "Execute";
QString *XModuleExecute::static_class_name_ptr;
struct Registrar_Execute {
    Registrar_Execute() {
        XModuleExecute::static_class_name_ptr = &Rt_ClassName_Execute;
        RegistrarXModule::register_rt_class(Rt_ClassName_Execute, std::bind(&XModuleExecute::new_module));
    }
};
Registrar_Execute registrar_Execute;
*/

//------------------------------------------------------------------
#endif // RTMODULEREGISTRAR_H
