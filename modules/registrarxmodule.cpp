#include "registrarxmodule.h"
#include "incl_cpp.h"
#include "xmodule.h"

//---------------------------------------------------------------------
//Мы должны указать переменную как указатель, так как у нас модули регистрируются с помощью
//переменных и неизвестно, когда запустится их конструктор - раньше или позже rt_registered_classes_
//Внимание: сейчас нет удаления этой переменной.
QMap<QString, XModuleCreateFunction> *rt_registered_classes_ = nullptr;

//---------------------------------------------------------------------
//Функция для регистрации модуля по имени класса
/*static*/ void RegistrarXModule::register_rt_class(QString class_name, XModuleCreateFunction creator_fun) {
    if (!rt_registered_classes_) {
        rt_registered_classes_ = new QMap<QString, XModuleCreateFunction>;
    }
    //qDebug() << "Registered module implementation " << class_name;
    (*rt_registered_classes_)[class_name] = creator_fun;
}

//---------------------------------------------------------------------
//Проверка, реализован ли модуль
/*static*/ bool RegistrarXModule::is_module_implemented(QString class_name) {
    if (!rt_registered_classes_) return false;
    return rt_registered_classes_->contains(class_name);
}

//---------------------------------------------------------------------
//Создание модуля по имени класса
/*static*/ XModule *RegistrarXModule::create_rt_module(const ModuleDescription &description) {
    xclu_assert(rt_registered_classes_, "No modules classes were added at startup");

    //получаем функцию для создания элемента класса
    QString class_name = description.class_name;

    //возврат модуля, если он зарегистрирован
    if (is_module_implemented(class_name)) {
        XModuleCreateFunction creator_fun = (*rt_registered_classes_)[class_name];

        //создаем модуль
        return creator_fun();
    }

    //модуль не зарегистрирован
    //выдать исключение
    //xclu_exception("Module class implementation is not found");

    //или создать пустой модуль - удобно для отладки и создания новых модулей
    return new XModule("Empty module");

}

//---------------------------------------------------------------------
