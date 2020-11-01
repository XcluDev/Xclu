#ifndef XMODULETELEGRAMBOT_H
#define XMODULETELEGRAMBOT_H

//TelegramBot implementation

#include "sdk_h.h"
#include "xmodule.h"

class XModuleTelegramBot: public XModule
{
public:
    XModuleTelegramBot(QString class_name);
    ~XModuleTelegramBot();
#include "auto.h"

protected:
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();
    //virtual void impl_button_pressed(QString button_id);


};



#endif // XMODULETELEGRAMBOT_H
