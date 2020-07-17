#include <QWheelEvent>
#include "xcluspinbox.h"
#include "incl_qtcpp.h"

//---------------------------------------------------------------------
XcluSpinBox::XcluSpinBox(QWidget *parent)
    :QSpinBox(parent)
{
    setFocusPolicy(Qt::StrongFocus);
}

//---------------------------------------------------------------------
void XcluSpinBox::wheelEvent(QWheelEvent *event) {
    if (!hasFocus()) {
        event->ignore();
    } else {
        QSpinBox::wheelEvent(event);
    }
}

//---------------------------------------------------------------------
