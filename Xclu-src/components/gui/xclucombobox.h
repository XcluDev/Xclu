#pragma once

//Кастомный ComboBox
//Убираем реакцию на колесико
//https://stackoverflow.com/questions/5821802/qspinbox-inside-a-qscrollarea-how-to-prevent-spin-box-from-stealing-focus-when

#include <QWidget>
#include <QComboBox>
#include "incl_h.h"

class QWheelEvent;

class XcluComboBox : public QComboBox {
    Q_OBJECT
public:
    XcluComboBox(QWidget *parent = 0);

protected:
    virtual void wheelEvent(QWheelEvent *event);
};
