#include <QWheelEvent>
#include "xcludoublespinbox.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
XcluDoubleSpinBox::XcluDoubleSpinBox(QWidget *parent)
    :QDoubleSpinBox(parent)
{
    setFocusPolicy(Qt::StrongFocus);
}

//---------------------------------------------------------------------
void XcluDoubleSpinBox::wheelEvent(QWheelEvent *event) {
    if (!hasFocus()) {
        event->ignore();
    } else {
        QDoubleSpinBox::wheelEvent(event);
    }
}

//---------------------------------------------------------------------
