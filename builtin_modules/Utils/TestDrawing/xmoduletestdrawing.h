#ifndef XMODULETESTDRAWING_H
#define XMODULETESTDRAWING_H

//Реализация модуля Test - для проверки элементов GUI и исполнения - печатает в консоль, что делает

#include "sdk_h.h"
#include "xmodulewidget.h"

class XModuleTestDrawing: public XModuleWidget
{
public:
    XModuleTestDrawing(QString class_name);
    virtual ~XModuleTestDrawing();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    virtual void draw(QPainter &painter, int w, int h);


};

#endif // XMODULETESTDRAWING_H
