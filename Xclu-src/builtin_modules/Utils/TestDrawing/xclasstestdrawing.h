#ifndef XCLASSTESTDRAWING_H
#define XCLASSTESTDRAWING_H

//Реализация модуля Test - для проверки элементов GUI и исполнения - печатает в консоль, что делает

#include "sdk_h.h"
#include "xclasswidget.h"

class XClassTestDrawing: public XClassWidget
{
public:
    XClassTestDrawing(QString class_name);
    virtual ~XClassTestDrawing();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    virtual void draw(QPainter &painter, int w, int h);


};

#endif // XCLASSTESTDRAWING_H
