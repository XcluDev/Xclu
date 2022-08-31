#pragma once

//Кастомный DoubleSpinBox
//Убираем реакцию на колесико
//https://stackoverflow.com/questions/5821802/qspinbox-inside-a-qscrollarea-how-to-prevent-spin-box-from-stealing-focus-when

#include <QWidget>
#include <QDoubleSpinBox>
#include "incl_h.h"

class QWheelEvent;

class XcluDoubleSpinBox : public QDoubleSpinBox {
    Q_OBJECT
public:
    XcluDoubleSpinBox(QWidget *parent = 0);

protected:
    virtual void wheelEvent(QWheelEvent *event);
};

