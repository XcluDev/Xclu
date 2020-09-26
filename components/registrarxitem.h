#ifndef RESISTRARXITEM_H
#define RESISTRARXITEM_H

//Automation of registration of XItem components is implemented here
//Modules with specific implementations should add the line in their CPP file:
//REGISTRAR_XITEM(Name), for example for XItemButton it would be:
//REGISTRAR_XITEM(Button)
//After that the module is registered and can be created in XItemsFactory
//The REGISTRAR_XITEM macro is declared at the end of this file.

#include "incl_h.h"

/*
class XItem;
typedef std::function<XItem *()> XItemCreateFunction;

class RegistrarXItem
{
public:
    RegistrarXItem();

    static void register_xitem(QString class_name, XItemCreateFunction creator_function);

    //Check if item is registered
    static bool is_item_registered(QString class_name);

    //Create item by name
    static XItem *create_item();
};
*/

//------------------------------------------------------------------
//макрос для регистрации класса модуля
//для этого создаем класс и объявляем один объект, который в своем конструкторе вызывает нужное добавление в класc
//так мы избавляемся от необходимости прописывать в коде все названия классов
//  ## - конкатенация в коде   # - превратить в строку
/*#define REGISTRAR_XITEM(CLASS_NAME) \
    QString *XItem##CLASS_NAME::static_class_name_ptr; \
    QString XItem_ClassName_##CLASS_NAME = #CLASS_NAME; \
    struct Registrar_XItem##CLASS_NAME { \
        Registrar_##CLASS_NAME() { \
            XModule##CLASS_NAME::static_class_name_ptr = &Rt_ClassName_##CLASS_NAME; \
            RegistrarXModule::register_rt_class(Rt_ClassName_##CLASS_NAME, std::bind(&XModule##CLASS_NAME::new_module)); \
        } \
    }; \
    Registrar_XItem##CLASS_NAME registrar_XItem##CLASS_NAME;
*/
/*
Usage REGISTRAR_XITEM(Button)

leads to inserting the following code:

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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


#endif // RESISTRARXITEM_H
