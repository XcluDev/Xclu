#pragma once

//Здесь реализована автоматизация регистрации исполняемых модулей
//Модули с конкретными реализациями должны добавлять в своем CPP-файле строку:
//REGISTER_XCLASS(Имя), например, для XModuleExecute это будет:
//REGISTER_XCLASS(Execute)
//После этого модуль зарегистрируется и может быть создан в XModulesFactory
//Макрос REGISTER_XCLASS объявлен в конце этого файла.

#include "incl_h.h"
#include "xmoduledescription.h"

//тип функции для регистрации модуля
class XClass;
typedef std::function<XClass *()> XModuleCreateFunction;

//класс для регистрации модуля
class RegistrarXClass
{
public:
    RegistrarXClass();

    //Функция для регистрации модуля по имени класса
    static void register_rt_class(QString class_name, XModuleCreateFunction creator_function);

    //Проверка, реализован ли модуль
    static bool is_module_implemented(QString class_name);

    //Создание модуля по имени класса
    static XClass *create_rt_module(const XModuleDescription &description);
};

//------------------------------------------------------------------
//макрос для регистрации класса модуля
//для этого создаем класс и объявляем один объект, который в своем конструкторе вызывает нужное добавление в класc
//так мы избавляемся от необходимости прописывать в коде все названия классов
//  ## - конкатенация в коде   # - превратить в строку
#define REGISTER_XCLASS(CLASS_NAME) \
    struct Registrar_XClass##CLASS_NAME { \
        static XClass *create() { return new XClass##CLASS_NAME(#CLASS_NAME); } \
        Registrar_XClass##CLASS_NAME() { \
            RegistrarXClass::register_rt_class(#CLASS_NAME, std::bind(&Registrar_XClass##CLASS_NAME::create)); \
        } \
    }; \
    Registrar_XClass##CLASS_NAME registrar_XModule##CLASS_NAME;

/*
Использование:
REGISTER_XCLASS(Execute)

приведет к вставке такого кода:

    struct Registrar_XClassExecute { \
        static XClass *create() { return new XClass##CLASS_NAME("Execute"); } \
        Registrar_XClassExecute() { \
            RegistrarXClass::register_rt_class("Execute", std::bind(&Registrar_XClassExecute::create)); \
        } \
    }; \
    Registrar_XClassExecute registrar_XModuleExecute;
*/


