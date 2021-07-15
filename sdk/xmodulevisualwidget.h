#ifndef XMODULEPAINTERWIDGET_H
#define XMODULEPAINTERWIDGET_H

//Helper class for XModuleVisual, implementing custom drawing widget
#include <QWidget>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QPaintEvent>
#include "sdk_h.h"

class XModuleVisual;

class XModuleVisualWidget : public QWidget
{
    Q_OBJECT

public:
    XModuleVisualWidget(QWidget *parent, XModuleVisual *xmodule);

    void set_fixed_size(int2 size);

    int w() { return width(); }
    int h() { return height(); }

protected:
    //drawing function
    //call update(); to repaint widget
    void paintEvent(QPaintEvent *event) override;

    //void mouseDoubleClickEvent(QMouseEvent *event);

private:
    XModuleVisual *xmodule_ = nullptr;

    //bool fixed_size_ = false;
    //int w_ = 100;
    //int h_ = 100;
};



#endif // XMODULEPAINTERWIDGET_H
