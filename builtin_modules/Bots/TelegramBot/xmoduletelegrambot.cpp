#include "xmoduletelegrambot.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xcore.h"


//registering module implementation
REGISTER_XMODULE(TelegramBot)

//---------------------------------------------------------------------
XModuleTelegramBot::XModuleTelegramBot(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleTelegramBot::~XModuleTelegramBot()
{

}

//---------------------------------------------------------------------
void XModuleTelegramBot::impl_start() {

}

//---------------------------------------------------------------------
void XModuleTelegramBot::impl_update() {
    //Реализовать отправку bang не только в модуль, но и в кнопку по link (уже реализовано)
    //https://stackoverflow.com/questions/13302236/qt-simple-post-request

}

//---------------------------------------------------------------------
void XModuleTelegramBot::impl_stop() {

}

//---------------------------------------------------------------------
//void XModuleTelegramBot::impl_button_pressed(QString button_id) {
//}

//---------------------------------------------------------------------
