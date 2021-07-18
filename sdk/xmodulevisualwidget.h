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

    //Mouse events - will be added to module's events queue
    void mousePressEvent(QMouseEvent *event) override;
    //Note: for tracking mouse moves without pressing, required to call setMouseTracking(bool enable);
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;

    //Keyboard events - will be added to module's events queue
    //TODO currently keyboard events are not sent. May be need set focus on the widget?
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    //Dragging
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dragLeaveEvent(QDragLeaveEvent *event);
    //void dragMoveEvent(QDragMoveEvent *event);

private:
    XModuleVisual *xmodule_ = nullptr;

    void add_mouse_event(int type, QMouseEvent *event);

    //bool fixed_size_ = false;
    //int w_ = 100;
    //int h_ = 100;
};



#endif // XMODULEPAINTERWIDGET_H
