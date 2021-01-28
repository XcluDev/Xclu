#ifndef XMODULEPAINTERWIDGET_H
#define XMODULEPAINTERWIDGET_H

//Helper class for XModulePainter, implementing custom drawing widget
#include <QWidget>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QPaintEvent>
#include "sdk_h.h"

class XModulePainter;

class XModulePainterWidget : public QWidget
{
    Q_OBJECT

public:
    XModulePainterWidget(QWidget *parent, XModulePainter *xmodule);

    void set_fixed_size(int2 size);

    int w() { return width(); }
    int h() { return height(); }

protected:
    //drawing function
    //call update(); to repaint widget
    void paintEvent(QPaintEvent *event) override;

    //void mouseDoubleClickEvent(QMouseEvent *event);

private:
    XModulePainter *xmodule_ = nullptr;

    //bool fixed_size_ = false;
    //int w_ = 100;
    //int h_ = 100;
};



#endif // XMODULEPAINTERWIDGET_H
