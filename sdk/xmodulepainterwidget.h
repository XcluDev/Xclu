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

    void set_size(int2 size);

    int w() { return w_; }
    int h() { return h_; }

protected:
    //drawing function
    //call update(); to repaint widget
    void paintEvent(QPaintEvent *event) override;

    //void mouseDoubleClickEvent(QMouseEvent *event);

private:
    XModulePainter *xmodule_ = nullptr;

    int w_ = 1;
    int h_ = 1;
};



#endif // XMODULEPAINTERWIDGET_H
