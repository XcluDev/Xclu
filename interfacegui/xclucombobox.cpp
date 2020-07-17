#include <QWheelEvent>
#include "xclucombobox.h"
#include "incl_qtcpp.h"

//---------------------------------------------------------------------
XcluComboBox::XcluComboBox(QWidget *parent)
    :QComboBox(parent)
{
    setFocusPolicy(Qt::StrongFocus);
}

//---------------------------------------------------------------------
void XcluComboBox::wheelEvent(QWheelEvent *event) {
    if (!hasFocus()) {
        event->ignore();
    } else {
        QComboBox::wheelEvent(event);
    }
}

//---------------------------------------------------------------------
