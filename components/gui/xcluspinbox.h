#ifndef XCLUSPINBOX_H
#define XCLUSPINBOX_H

//Кастомный SpinBox
//Убираем реакцию на колесико
//https://stackoverflow.com/questions/5821802/qspinbox-inside-a-qscrollarea-how-to-prevent-spin-box-from-stealing-focus-when

#include <QWidget>
#include <QSpinBox>
#include "incl_h.h"

class QWheelEvent;

class XcluSpinBox : public QSpinBox {
    Q_OBJECT
public:
    XcluSpinBox(QWidget *parent = 0);

protected:
    virtual void wheelEvent(QWheelEvent *event);
};


#endif // XCLUSPINBOX_H
