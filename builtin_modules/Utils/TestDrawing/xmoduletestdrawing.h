#ifndef XMODULETESTDRAWING_H
#define XMODULETESTDRAWING_H

//Реализация модуля Test - для проверки элементов GUI и исполнения - печатает в консоль, что делает

#include "sdk_h.h"
#include "xmodulepainter.h"

class XModuleTestDrawing: public XModulePainter
{
public:
    XModuleTestDrawing(QString class_name);
    ~XModuleTestDrawing();
protected:
#include "auto.h"

    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();

    virtual void draw(QPainter &painter, int w, int h);


};

#endif // XMODULETESTDRAWING_H
