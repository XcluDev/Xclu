#pragma once

//Automation of registration of XItem components is implemented here
//Modules with specific implementations should add the line in their CPP file:
//REGISTER_XITEM(Name, Xgui_name), for example for XItemButton it would be:
//REGISTER_XITEM(Button, button)
//After that the module is registered and can be created in XItemsFactory
//The REGISTRAR_XITEM macro is declared at the end of this file.

#include "incl_h.h"

class XItem;
class XModuleInterface;
class XItemPreDescription;

typedef std::function<XItem *(XModuleInterface *interf, const XItemPreDescription *pre_description)> XItemCreateFunction;

class RegistrarXItem
{
public:
    RegistrarXItem();

    //Registering item class by name
    static void register_xitem(QString class_name, XItemCreateFunction creator_function);

    //Check if item class registered
    static bool is_xitem_registered(QString class_name);

    //Create item object
    static XItem *create_xitem(XModuleInterface *interf, const XItemPreDescription *pre_description);
};

//------------------------------------------------------------------
//макрос для регистрации класса модуля
//для этого создаем класс и объявляем один объект, который в своем конструкторе вызывает нужное добавление в класc
//так мы избавляемся от необходимости прописывать в коде все названия классов
//  ## - конкатенация в коде   # - превратить в строку
#define REGISTER_XITEM(CLASS_NAME, XGUI_NAME) \
    struct Registrar_XItem_##XGUI_NAME { \
        static XItem *create(XModuleInterface *interf, const XItemPreDescription *pre_description) {\
            return new CLASS_NAME(interf, *pre_description);\
        } \
        Registrar_XItem_##XGUI_NAME() { \
            using namespace std::placeholders;  \
            RegistrarXItem::register_xitem(#XGUI_NAME, std::bind(&Registrar_XItem_##XGUI_NAME::create, _1, _2)); \
        } \
    }; \
    Registrar_XItem_##XGUI_NAME registrar_XItem_##XGUI_NAME;

/*
Usage:
REGISTER_XITEM(XItemButton,button)
REGISTER_XITEM(XItemRaster<uint8>, raster_u8)

This results in the following code:

struct Registrar_XItem_button {
    static XItem *create(XModuleInterface *interf, const XItemPreDescription *pre_description) {
        return new XItemButton(interf, *pre_description);
    }
    Registrar_XItem_button() {
        using namespace std::placeholders;  // for _1, _2, _3...
        RegistrarXItem::register_xitem("button", std::bind(&Registrar_XItem_button::create, _1, _2));
    }
};
Registrar_XItem_button registrar_XItem_button;

*/
