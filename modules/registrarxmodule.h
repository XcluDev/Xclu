#ifndef XMODULEREGISTRAR_H
#define XMODULEREGISTRAR_H

//Здесь реализована автоматизация регистрации исполняемых модулей
//Модули с конкретными реализациями должны добавлять в своем CPP-файле строку:
//REGISTER_XMODULE(Имя), например, для XModuleExecute это будет:
//REGISTER_XMODULE(Execute)
//После этого модуль зарегистрируется и может быть создан в XModulesFactory
//Макрос REGISTER_XMODULE объявлен в конце этого файла.

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
#define REGISTER_XMODULE(CLASS_NAME) \
    struct Registrar_XModule##CLASS_NAME { \
        static XModule *create() { return new XModule##CLASS_NAME(#CLASS_NAME); } \
        Registrar_XModule##CLASS_NAME() { \
            RegistrarXModule::register_rt_class(#CLASS_NAME, std::bind(&Registrar_XModule##CLASS_NAME::create)); \
        } \
    }; \
    Registrar_XModule##CLASS_NAME registrar_XModule##CLASS_NAME;

/*
Использование:
REGISTER_XMODULE(Execute)

приведет к вставке такого кода:

    struct Registrar_XModuleExecute { \
        static XModule *create() { return new XModule##CLASS_NAME("Execute"); } \
        Registrar_XModuleExecute() { \
            RegistrarXModule::register_rt_class("Execute", std::bind(&Registrar_XModuleExecute::create)); \
        } \
    }; \
    Registrar_XModuleExecute registrar_XModuleExecute;
*/

//------------------------------------------------------------------
#endif // XMODULEREGISTRAR_H
